#include <stdio.h>
#include <math.h>

void main(void)
{
    float X;  // Declara una variable flotante para X
    int Y;    // Declara una variable entera para Y

    printf("Ingrese el valor de Y: ");  // Pide al usuario que ingrese el valor de Y
    scanf("%d", &Y);  // Lee el valor ingresado por el usuario y lo almacena en la variable Y

    if (Y < 0 || Y > 50)  // Verifica si Y es menor que 0 o mayor que 50
    {
        X = 0;  // Asigna 0 a X si Y está fuera del rango
    }
    else if (Y <= 10)  // Si Y está en el rango de 0 a 10
    {
        X = 4.0 / Y - Y;  // Calcula el valor de X según la fórmula dada
    }
    else if (Y <= 25)  // Si Y está en el rango de 11 a 25
    {
        X = pow(Y, 3) - 12;  // Calcula el valor de X según la fórmula dada
    }
    else  // Si Y está en el rango de 26 a 50
    {
        X = pow(Y, 2) + pow(Y, 3) - 18;  // Calcula el valor de X según la fórmula dada
    }

    printf("\n\nY = %d\tX = %8.2f", Y, X);  // Imprime los valores de Y y X con formato específico
}
