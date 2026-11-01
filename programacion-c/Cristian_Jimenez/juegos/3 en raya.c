#include <stdio.h>

char tablero[3][3];
char jugadorActual;

void inicializarTablero() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void imprimirTablero() {
    printf(" %c | %c | %c\n", tablero[0][0], tablero[0][1], tablero[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", tablero[1][0], tablero[1][1], tablero[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", tablero[2][0], tablero[2][1], tablero[2][2]);
}

int verificarVictoria() {
    // Verificar filas y columnas
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != ' ') ||
            (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != ' ')) {
            return 1;
        }
    }
    // Verificar diagonales
    if ((tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[0][0] != ' ') ||
        (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[0][2] != ' ')) {
        return 1;
    }
    return 0;
}

int verificarEmpate() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void cambiarJugador() {
    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
}

void realizarMovimiento() {
    int fila, columna;
    printf("Jugador %c, ingrese su movimiento (fila y columna): ", jugadorActual);
    scanf("%d %d", &fila, &columna);

    if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
        tablero[fila][columna] = jugadorActual;
    } else {
        printf("Movimiento inválido. Intente de nuevo.\n");
        realizarMovimiento();
    }
}

int main() {
    jugadorActual = 'X';
    inicializarTablero();

    while (1) {
        imprimirTablero();
        realizarMovimiento();
        if (verificarVictoria()) {
            imprimirTablero();
            printf("¡El jugador %c gana!\n", jugadorActual);
            break;
        }
        if (verificarEmpate()) {
            imprimirTablero();
            printf("¡Es un empate!\n");
            break;
        }
        cambiarJugador();
    }

    return 0;
}
