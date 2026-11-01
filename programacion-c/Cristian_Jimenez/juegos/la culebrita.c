#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define LONGITUD_MAXIMA 100

typedef struct {
    int x, y;
} Punto;

typedef struct {
    Punto cuerpo[LONGITUD_MAXIMA];
    int longitud;
    Punto direccion;
} Culebrita;

typedef struct {
    Punto posicion;
} Comida;

void inicializarCulebrita(Culebrita *culebrita) {
    culebrita->longitud = 1;
    culebrita->cuerpo[0].x = COLS / 2;
    culebrita->cuerpo[0].y = LINES / 2;
    culebrita->direccion.x = 1;
    culebrita->direccion.y = 0;
}

void inicializarComida(Comida *comida) {
    comida->posicion.x = rand() % COLS;
    comida->posicion.y = rand() % LINES;
}

void dibujarCulebrita(Culebrita *culebrita) {
    for (int i = 0; i < culebrita->longitud; i++) {
        mvprintw(culebrita->cuerpo[i].y, culebrita->cuerpo[i].x, "O");
    }
}

void dibujarComida(Comida *comida) {
    mvprintw(comida->posicion.y, comida->posicion.x, "X");
}

void actualizarCulebrita(Culebrita *culebrita) {
    for (int i = culebrita->longitud - 1; i > 0; i--) {
        culebrita->cuerpo[i] = culebrita->cuerpo[i - 1];
    }
    culebrita->cuerpo[0].x += culebrita->direccion.x;
    culebrita->cuerpo[0].y += culebrita->direccion.y;

    if (culebrita->cuerpo[0].x >= COLS) culebrita->cuerpo[0].x = 0;
    if (culebrita->cuerpo[0].x < 0) culebrita->cuerpo[0].x = COLS - 1;
    if (culebrita->cuerpo[0].y >= LINES) culebrita->cuerpo[0].y = 0;
    if (culebrita->cuerpo[0].y < 0) culebrita->cuerpo[0].y = LINES - 1;
}

int comprobarColisionComida(Culebrita *culebrita, Comida *comida) {
    if (culebrita->cuerpo[0].x == comida->posicion.x && culebrita->cuerpo[0].y == comida->posicion.y) {
        culebrita->longitud++;
        return 1;
    }
    return 0;
}

int comprobarColisionCuerpo(Culebrita *culebrita) {
    for (int i = 1; i < culebrita->longitud; i++) {
        if (culebrita->cuerpo[0].x == culebrita->cuerpo[i].x && culebrita->cuerpo[0].y == culebrita->cuerpo[i].y) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Culebrita culebrita;
    Comida comida;
    int ch;

    initscr();
    timeout(100);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);
    srand(time(NULL));

    inicializarCulebrita(&culebrita);
    inicializarComida(&comida);

    while (1) {
        clear();
        dibujarCulebrita(&culebrita);
        dibujarComida(&comida);
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (culebrita.direccion.y == 0) {
                    culebrita.direccion.x = 0;
                    culebrita.direccion.y = -1;
                }
                break;
            case KEY_DOWN:
                if (culebrita.direccion.y == 0) {
                    culebrita.direccion.x = 0;
                    culebrita.direccion.y = 1;
                }
                break;
            case KEY_LEFT:
                if (culebrita.direccion.x == 0) {
                    culebrita.direccion.x = -1;
                    culebrita.direccion.y = 0;
                }
                break;
            case KEY_RIGHT:
                if (culebrita.direccion.x == 0) {
                    culebrita.direccion.x = 1;
                    culebrita.direccion.y = 0;
                }
                break;
            case 'q':
                endwin();
                return 0;
        }

        actualizarCulebrita(&culebrita);

        if (comprobarColisionComida(&culebrita, &comida)) {
            inicializarComida(&comida);
        }

        if (comprobarColisionCuerpo(&culebrita)) {
            break;
        }
    }

    endwin();
    printf("¡Juego terminado! Tu puntuación fue: %d\n", culebrita.longitud);
    return 0;
}
