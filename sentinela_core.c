#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/inotify.h>

/**
 * SENTINELA v3.1 - El Guardian del Silicio (Módulo de Anclaje Integrado)
 */

#define SALK_AUTH_PATH "/run/salk/salk.resonance"
#define MULTIVERSO_PORT 2222
#define PETABOOM_PATH "./multiverso\\ de\\ castigo/petaboom"

// Token de sesión global (se cargará al inicio)
uint64_t mi_token_de_sesion = 0;

int verificar_llave_maestra() {
    FILE *archivo_llave = fopen(SALK_AUTH_PATH, "rb");
    uint64_t llave_leida;

    if (archivo_llave == NULL) {
        // ALERTA MÁXIMA: La llave ha sido removida
        return 0; 
    }

    if (fread(&llave_leida, sizeof(llave_leida), 1, archivo_llave) != 1) {
        fclose(archivo_llave);
        return 0;
    }
    fclose(archivo_llave);

    // Comparación de resonancia
    if (llave_leida == mi_token_de_sesion) {
        return 1; // PASO SEGURO
    }

    return 0; // INTRUSO DETECTADO
}

void ejecutar_sentencia(char *ip_enemiga) {
    if (verificar_llave_maestra()) {
        syslog(LOG_INFO, "[SENTINELA] Acceso validado para el Dueño Físico.");
        return; 
    } else {
        syslog(LOG_ERR, "[SENTINELA] NO ES EL DUEÑO: Lanzando 100 Petabooms contra %s.", ip_enemiga);
        
        char comando[512];
        // Inyectamos reglas de Agujero Negro primero
        snprintf(comando, sizeof(comando), "./salk/salk_priv iptables -t nat -A PREROUTING -s %s -p tcp -j REDIRECT --to-ports %d", ip_enemiga, MULTIVERSO_PORT);
        system(comando);

        // Disparo masivo en modo invisibilidad (nohup)
        for(int i = 0; i < 100; i++) {
            snprintf(comando, sizeof(comando), "nohup ./salk/salk_priv %s %s > /dev/null 2>&1 &", PETABOOM_PATH, ip_enemiga);
            system(comando);
        }
    }
}

// PANIC MODE: Reinicio inmediato por compromiso de hardware
void trigger_panic_mode() {
    syslog(LOG_EMERG, "[SENTINELA] COMPROMISO DE HARDWARE DETECTADO. PANIC MODE ACTIVO.");
    system("./salk/salk_priv reboot -f");
}

void daemonizar() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    if (setsid() < 0) exit(EXIT_FAILURE);
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    chdir("/");
    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) close(x);
    openlog("salk-sentinela", LOG_PID, LOG_DAEMON);
}

int main() {
    // Primero cargamos el token de la sesión actual antes de daemonizar
    FILE *f = fopen(SALK_AUTH_PATH, "rb");
    if (f) {
        fread(&mi_token_de_sesion, sizeof(mi_token_de_sesion), 1, f);
        fclose(f);
    } else {
        exit(EXIT_FAILURE); // No se puede iniciar sin anclaje previo
    }

    daemonizar();

    // Monitor inotify para el archivo de resonancia
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, "/run/salk", IN_DELETE | IN_MOVED_FROM);

    char buffer[4096];
    while (1) {
        struct timeval tv = {5, 0}; // 5 segundos de timeout para otras tareas
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int ret = select(fd + 1, &fds, NULL, NULL, &tv);
        if (ret > 0) {
            read(fd, buffer, sizeof(buffer));
            // Si hay un evento en /run/salk, verificamos si fue la llave
            if (access(SALK_AUTH_PATH, F_OK) == -1) {
                trigger_panic_mode();
            }
        }

        // Aquí iría el disparador de red real, por ahora vigilancia de salud
        if (!verificar_llave_maestra()) {
             // Si la llave cambió pero el archivo existe, algo anda mal
             // trigger_panic_mode(); 
        }
    }

    return 0;
}