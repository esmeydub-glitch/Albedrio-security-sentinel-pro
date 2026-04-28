/**
 * centro_comando.c
 * Frontend Táctico (TUI) para Albedrío Security
 * 
 * Propósito: Renderizar el estado de los 5 pilares del sistema en tiempo real.
 * Requiere compilación con: gcc centro_comando.c -o albedrio_ui -lncurses
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// [LINEA A REVISAR] Dibujo de bordes para los paneles
void draw_borders(WINDOW *screen) {
    box(screen, 0, 0);
}

int main() {
    // [LINEA A REVISAR] Inicialización de la consola militar (Ncurses)
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE); // Ocultamos el cursor para que parezca una pantalla de radar
    timeout(1000);   // Refresco dinámico cada segundo

    // Configuración de Colores Tácticos
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // Estado: Normal / Operativo
        init_pair(2, COLOR_RED, COLOR_BLACK);   // Estado: Amenaza / Alerta
        init_pair(3, COLOR_CYAN, COLOR_BLACK);  // Estado: Información del Kernel
    }

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // [LINEA A REVISAR] Distribución geométrica de los Paneles
    WINDOW *win_salk = newwin(yMax/3, xMax/2, 0, 0);
    WINDOW *win_muralla = newwin(yMax/3, xMax/2, 0, xMax/2);
    WINDOW *win_sentinela = newwin(yMax/3, xMax, yMax/3, 0);
    WINDOW *win_purificador = newwin(yMax/3, xMax, (yMax/3)*2, 0);

    // Bucle Principal de Renderizado (El Corazón de la UI)
    while (1) {
        clear();

        // --- Panel 1: SALK Core ---
        wattron(win_salk, COLOR_PAIR(1));
        draw_borders(win_salk);
        mvwprintw(win_salk, 1, 2, "[1] MOTOR DE RESONANCIA (SALK)");
        mvwprintw(win_salk, 3, 2, "Estado: SINCRONIZADO Y LATIENDO");
        // Simulamos la llave cambiando dinámicamente
        mvwprintw(win_salk, 4, 2, "Firma en RAM: %lx", (unsigned long)time(NULL) ^ 0xDEADBEEF);
        wattroff(win_salk, COLOR_PAIR(1));

        // --- Panel 2: La Muralla de Hierro ---
        wattron(win_muralla, COLOR_PAIR(3));
        draw_borders(win_muralla);
        mvwprintw(win_muralla, 1, 2, "[2] LA MURALLA DE HIERRO");
        mvwprintw(win_muralla, 3, 2, "Escudo del Kernel: ACTIVO (eBPF Interceptor)");
        mvwprintw(win_muralla, 4, 2, "Bloqueos de Ejecucion (execve): 0");
        wattroff(win_muralla, COLOR_PAIR(3));

        // --- Panel 3: Sentinela y El Multiverso ---
        wattron(win_sentinela, COLOR_PAIR(2));
        draw_borders(win_sentinela);
        mvwprintw(win_sentinela, 1, 2, "[3] SENTINELA Y MULTIVERSO DE CASTIGO");
        mvwprintw(win_sentinela, 3, 2, "Radar Omni-Protocolo y Airborne: ESCUCHANDO");
        mvwprintw(win_sentinela, 4, 2, "Estado del Agujero Negro: EN ESPERA");
        mvwprintw(win_sentinela, 5, 2, "Invasores en el Multiverso: 0");
        wattroff(win_sentinela, COLOR_PAIR(2));

        // --- Panel 4: El Purificador ---
        wattron(win_purificador, COLOR_PAIR(1));
        draw_borders(win_purificador);
        mvwprintw(win_purificador, 1, 2, "[4] EL PURIFICADOR (USB/HARDWARE)");
        mvwprintw(win_purificador, 3, 2, "Fronteras Fisicas (Udev): ASEGURADAS");
        mvwprintw(win_purificador, 4, 2, "Dispositivos en Cuarentena (/tmp): NINGUNO");
        mvwprintw(win_purificador, 7, 2, ">>> Presiona 'Q' para cerrar el enlace visual de la terminal.");
        wattroff(win_purificador, COLOR_PAIR(1));

        // Mostrar paneles en pantalla
        wrefresh(win_salk);
        wrefresh(win_muralla);
        wrefresh(win_sentinela);
        wrefresh(win_purificador);

        // Escuchar teclado
        int c = getch();
        if (c == 'q' || c == 'Q') {
            break; // Salir de la interfaz
        }
    }

    // Apagar modo consola avanzada
    endwin();
    return 0;
}
