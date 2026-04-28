/**
 * salk_core.c
 * Security Algorithm Legitimate Key - Motor de Resonancia
 *
 * Propósito: Generar el Rolling Hash Ks de seguridad basado en hardware y tiempo.
 * Fórmula: Ks = SHA256 ( [π * (UUID + CPU_ID + Disk_Serial)] XOR ms )
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <openssl/sha.h>
#include <unistd.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>

// [LINEA A REVISAR] Constante matemática de dispersión
#define PI_CONSTANT 3.14159265358979323846

// [LINEA A REVISAR] Función para extraer el hardware (Lee archivos del sistema)
void read_file_to_buffer(const char *path, char *buffer, size_t max_len) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        snprintf(buffer, max_len, "ACCESO_DENEGADO");
        return;
    }
    if (fgets(buffer, max_len, fp) == NULL) {
        snprintf(buffer, max_len, "ERROR_VACIO");
    }
    fclose(fp);
    // Limpiar salto de línea
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
}

// [LINEA A REVISAR] Función para obtener El Pulso (Uptime en milisegundos)
uint64_t get_uptime_ms() {
    struct timespec ts;
    // Usamos CLOCK_BOOTTIME para ser inmunes a cambios de hora del sistema
    if (clock_gettime(CLOCK_BOOTTIME, &ts) != 0) return 0;
    return (uint64_t)(ts.tv_sec * 1000) + (uint64_t)(ts.tv_nsec / 1000000);
}

// [NEW] Comunicación con el Kernel (eBPF)
struct bpf_object *obj;
int map_fd = -1;

void init_muralla() {
    printf("[*] Inyectando La Muralla de Hierro en el Kernel...\n");
    obj = bpf_object__open_file("/etc/albedrio/ebpf/muralla_bpf.o", NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "[!] Error: No se pudo abrir muralla_bpf.o\n");
        return;
    }

    if (bpf_object__load(obj)) {
        fprintf(stderr, "[!] Error: No se pudo cargar el programa en el Kernel\n");
        return;
    }

    struct bpf_program *prog = bpf_object__find_program_by_name(obj, "muralla_bloqueo_ejecucion");
    if (prog) {
        struct bpf_link *link = bpf_program__attach(prog);
        if (libbpf_get_error(link)) {
            fprintf(stderr, "[!] Advertencia: No se pudo enganchar LSM. ¿lsm=bpf activo en GRUB?\n");
        } else {
            printf("[+] Muralla enganchada con éxito.\n");
        }
    }

    map_fd = bpf_object__find_map_fd_by_name(obj, "estado_resonancia_salk");
}

void update_resonance_state(uint64_t state) {
    if (map_fd < 0) return;
    uint32_t key = 0;
    bpf_map_update_elem(map_fd, &key, &state, BPF_ANY);
}

// [LINEA A REVISAR] Motor de la Fórmula
void generate_salk_key() {
    char uuid[128] = {0};
    // Placeholder temporal para CPU y Disco (luego los leeremos dinámicamente)
    char cpu_info[256] = "AMD_Ryzen_9_PRO_7940HS"; 
    char disk_serial[128] = "S75YNF0WB64603";

    // 1. Extraer UUID (Físico)
    read_file_to_buffer("/sys/class/dmi/id/product_uuid", uuid, sizeof(uuid));

    // 2. Extraer El Pulso (Temporal)
    uint64_t ms = get_uptime_ms();

    // 3. Cadena base del hardware
    char hardware_base[1024];
    snprintf(hardware_base, sizeof(hardware_base), "%s%s%s", uuid, cpu_info, disk_serial);

    // 4. Hash numérico intermedio del hardware
    uint64_t hw_hash = 0;
    for (int i = 0; hardware_base[i] != '\0'; i++) {
        hw_hash = hw_hash * 31 + hardware_base[i];
    }

    // 5. La Fórmula (Matemática): (Hardware * PI) XOR ms
    uint64_t dispersed_hw = (uint64_t)(hw_hash * PI_CONSTANT);
    uint64_t resonance_value = dispersed_hw ^ ms;

    // 6. Generación del Ks Final (SHA256)
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char resonance_str[64];
    snprintf(resonance_str, sizeof(resonance_str), "%lu", resonance_value);
    SHA256((unsigned char*)resonance_str, strlen(resonance_str), hash);

    // 7. Salida a Pantalla
    printf("Pulso [ms]: %lu | Llave [Ks]: ", ms);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Actualizar el estado en el Kernel
    update_resonance_state(1); // 1 = OK, Resonancia estable
}

int main(int argc, char **argv) {
    printf("--- SALK: Inicializando Motor de Resonancia ---\n");
    
    // Inyectar el muro de hierro
    init_muralla();

    // Prueba de Resonancia: Generar llave cada segundo
    while (1) {
        generate_salk_key();
        usleep(1000000); // Esperar 1000ms
    }
    return 0;
}
