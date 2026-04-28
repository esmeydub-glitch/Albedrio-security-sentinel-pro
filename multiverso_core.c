#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LOG_FORENSE "/var/log/albedrio_forense.log"

void registrar_evento_legal(const char* ip) {
    FILE* f = fopen(LOG_FORENSE, "a");
    if (f) {
        time_t now = time(NULL);
        char* t_str = ctime(&now);
        t_str[strlen(t_str)-1] = '\0';
        fprintf(f, "[%s] [EVIDENCIA-JUDICIAL] INTRUSION DETECTADA | ORIGEN: %s | ACCION: Redirigido a Multiverso (Terminal Fantasma)\n", t_str, ip);
        fclose(f);
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(2222);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error bind");
        exit(1);
    }

    listen(server_fd, 5);
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd >= 0) {
            char *ip = inet_ntoa(client_addr.sin_addr);
            registrar_evento_legal(ip);
            
            // Simulación de shell fantasma
            write(client_fd, "root@salk-linux:~# ", 19);
            close(client_fd);
        }
    }
    return 0;
}
