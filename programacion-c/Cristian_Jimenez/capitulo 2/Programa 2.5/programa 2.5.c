#include <stdio.h>  // Incluye la librería estándar de entrada y salida
#include <math.h>   // Incluye la librería para funciones matemáticas

void main(void)  // Define la función principal del programa
{
    int OP, T;    // Declara dos variables enteras: OP para la opción de cálculo y T para el valor entero
    float RES;    // Declara una variable flotante para el resultado

    printf("Ingrese la opción del cálculo y el valor entero: ");  // Imprime un mensaje pidiendo al usuario que ingrese la opción de cálculo y el valor entero
    scanf("%d %d", &OP, &T);  // Lee los valores ingresados por el usuario y los almacena en las variables OP y T

    switch(OP)  // Inicia la estructura de control switch para evaluar la opción de cálculo
    {
        case 1:  // Si la opción es 1
            RES = (float)T / 5;  // Divide T por 5 y almacena el resultado en RES
            break;  // Sale del switch
        case 2:  // Si la opción es 2
            RES = pow(T, T);  // Calcula T elevado a T y almacena el resultado en RES
            break;  // Sale del switch
        case 3:  // Si la opción es 3
        case 4:  // o si la opción es 4
            RES = 6 * T / 2;  // Calcula 6 por T dividido por 2 y almacena el resultado en RES
            break;  // Sale del switch
        default:  // Si la opción no coincide con ningún caso anterior
            RES = 1;  // Asigna 1 a RES
            break;  // Sale del switch
    }

    printf("\nResultado: %7.2f", RES);  // Imprime el resultado con formato de 7 caracteres de ancho y 2 decimales
}
