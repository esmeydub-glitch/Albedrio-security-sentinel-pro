#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <sys/inotify.h>
#include <libudev.h>
#include <fcntl.h>

#define SALK_AUTH_PATH "/run/salk/salk.resonance"
#define LOG_FORENSE "/var/log/albedrio_forense.log"

void registrar_evento_legal(const char* tipo, const char* detalle) {
    FILE* f = fopen(LOG_FORENSE, "a");
    if (f) {
        time_t now = time(NULL);
        char* t_str = ctime(&now);
        t_str[strlen(t_str)-1] = '\0'; // Quitar newline
        fprintf(f, "[%s] [ALERTA-LEGAL] TIPO: %s | DETALLE: %s\n", t_str, tipo, detalle);
        fclose(f);
    }
}

void block_usb_device(struct udev_device *dev) {
    const char *syspath = udev_device_get_syspath(dev);
    char auth_path[512];
    snprintf(auth_path, sizeof(auth_path), "%s/authorized", syspath);
    
    int fd = open(auth_path, O_WRONLY);
    if (fd >= 0) {
        write(fd, "0", 1);
        close(fd);
        char detalle[512];
        snprintf(detalle, sizeof(detalle), "Dispositivo USB bloqueado en %s", syspath);
        registrar_evento_legal("INTRUSION_FISICA", detalle);
    }
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
    daemonizar();
    struct udev *udev = udev_new();
    struct udev_monitor *mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
    udev_monitor_enable_receiving(mon);
    int udev_fd = udev_monitor_get_fd(mon);

    int inotify_fd = inotify_init();
    inotify_add_watch(inotify_fd, "/run/salk", IN_DELETE | IN_MOVED_FROM);

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(udev_fd, &fds);
        FD_SET(inotify_fd, &fds);
        int max_fd = (udev_fd > inotify_fd) ? udev_fd : inotify_fd;
        
        if (select(max_fd + 1, &fds, NULL, NULL, NULL) > 0) {
            if (FD_ISSET(udev_fd, &fds)) {
                struct udev_device *dev = udev_monitor_receive_device(mon);
                if (dev) {
                    const char *action = udev_device_get_action(dev);
                    if (action && strcmp(action, "add") == 0) {
                        block_usb_device(dev);
                    }
                    udev_device_unref(dev);
                }
            }
            if (FD_ISSET(inotify_fd, &fds)) {
                char buf[4096];
                read(inotify_fd, buf, sizeof(buf));
                if (access(SALK_AUTH_PATH, F_OK) == -1) {
                    registrar_evento_legal("VIOLACION_RESONANCIA", "Llave de anclaje removida. Ejecutando Panic Reboot.");
                    system("reboot -f");
                }
            }
        }
    }
    return 0;
}
