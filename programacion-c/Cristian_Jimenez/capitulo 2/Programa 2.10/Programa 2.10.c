#include <stdio.h>
#include <math.h>

void main(void)
{
    int NUM;  // Declara una variable de tipo entero para almacenar el número ingresado por el usuario
    
    printf("Ingrese el número: ");  // Pide al usuario que ingrese el número
    scanf("%d", &NUM);  // Lee el número ingresado por el usuario y lo almacena en la variable NUM

    if (NUM == 0)  // Verifica si el número es igual a cero
    {
        printf("\nNulo");  // Imprime "Nulo" si el número es igual a cero
    }
    else if (NUM % 2 == 0)  // Verifica si el número es par
    {
        printf("\nPar");  // Imprime "Par" si el número es par
    }
    else  // Si el número no es cero ni par, entonces es impar
    {
        printf("\nImpar");  // Imprime "Impar" si el número es impar
    }
}
