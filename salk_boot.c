#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/**
 * SALK BOOT v3.0 - Forjador de Llave de Anclaje
 * Fusión de Silicio y Tiempo para identidad de sesión.
 */

#define RUN_DIR "/run/salk"
#define RESONANCE_FILE "/run/salk/salk.resonance"

// Función para capturar el CPUID (Silicio)
uint64_t obtener_huella_silicio() {
    uint32_t eax, ebx, ecx, edx;
    eax = 1; // Solicitar firma del procesador y características
    __asm__ volatile ("cpuid"
                      : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
                      : "a" (eax));
    // Fusionamos los registros para obtener una huella de 64 bits
    return ((uint64_t)eax << 32) | edx;
}

// Función para capturar entropía temporal
uint64_t obtener_nanosegundos() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_nsec;
}

int main() {
    // 1. Captura
    uint64_t silicio = obtener_huella_silicio();
    uint64_t tiempo = obtener_nanosegundos();

    // 2. Fusión (XOR)
    uint64_t llave_sesion = silicio ^ tiempo;

    printf("[SALK-BOOT] Silicio: 0x%lx | Tiempo: %lu\n", silicio, tiempo);
    printf("[SALK-BOOT] Llave de Sesión Forjada.\n");

    // 3. Almacenamiento Seguro
    mkdir(RUN_DIR, 0700);
    
    int fd = open(RESONANCE_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0400);
    if (fd < 0) {
        perror("[-] Error al crear Safe House en /run/salk");
        return 1;
    }

    if (write(fd, &llave_sesion, sizeof(llave_sesion)) != sizeof(llave_sesion)) {
        perror("[-] Error al escribir la resonancia");
        close(fd);
        return 1;
    }

    close(fd);

    // 4. Protección Inmutable (Esto se hará vía script con salk_priv después)
    printf("[SALK-BOOT] Anclaje completado en %s\n", RESONANCE_FILE);

    return 0;
}
