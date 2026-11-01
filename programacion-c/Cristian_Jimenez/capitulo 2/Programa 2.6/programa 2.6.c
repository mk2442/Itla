#include <stdio.h>  // Incluye la librería estándar de entrada y salida

void main(void)  // Define la función principal del programa
{
    float SAL;  // Declara una variable flotante para el salario
    int NIV;    // Declara una variable entera para el nivel académico

    printf("Ingrese el nivel académico del profesor: ");  // Pide al usuario que ingrese el nivel académico del profesor
    scanf("%d", &NIV);  // Lee el valor ingresado por el usuario y lo almacena en la variable NIV

    printf("Ingrese salario: ");  // Pide al usuario que ingrese el salario
    scanf("%f", &SAL);  // Lee el valor ingresado por el usuario y lo almacena en la variable SAL

    switch(NIV)  // Inicia la estructura de control switch para evaluar el nivel académico
    {
        case 1:  // Si el nivel académico es 1
            SAL = SAL * 1.0035;  // Calcula el nuevo salario según la tasa de incremento y lo asigna a SAL
            break;  // Sale del switch
        case 2:  // Si el nivel académico es 2
            SAL = SAL * 1.0041;  // Calcula el nuevo salario según la tasa de incremento y lo asigna a SAL
            break;  // Sale del switch
        case 3:  // Si el nivel académico es 3
            SAL = SAL * 1.0040;  // Calcula el nuevo salario según la tasa de incremento y lo asigna a SAL
            break;  // Sale del switch
        case 4:  // Si el nivel académico es 4
            SAL = SAL * 1.0053;  // Calcula el nuevo salario según la tasa de incremento y lo asigna a SAL
            break;  // Sale del switch
        default:  // Si el nivel académico no coincide con ningún caso anterior
            printf("Nivel académico no válido");  // Imprime un mensaje indicando que el nivel académico ingresado no es válido
            return;  // Sale de la función main
    }

    printf("\n\nNivel: %d \tNuevo salario: %8.2f", NIV, SAL);  // Imprime el nivel y el nuevo salario con formato específico
}
