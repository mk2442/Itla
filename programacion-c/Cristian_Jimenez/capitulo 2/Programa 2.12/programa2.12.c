#include <stdio.h>
#include <math.h>

void main(void)
{
    int T, P, N;  // Declara variables para T, P y N

    printf("Ingrese los valores de T, P y N: ");  // Pide al usuario que ingrese los valores de T, P y N
    scanf("%d %d %d", &T, &P, &N);  // Lee los valores ingresados por el usuario y los almacena en las variables T, P y N

    if (P != 0)  // Verifica si P es diferente de cero
    {
        if (pow(T / P, N) == (pow(T, N) / pow(P, N)))  // Comprueba la igualdad de dos expresiones
        {
            printf("\nSe comprueba la igualdad");  // Imprime un mensaje si se cumple la igualdad
        }
        else
        {
            printf("\nNo se comprueba la igualdad");  // Imprime un mensaje si no se cumple la igualdad
        }
    }
    else
    {
        printf("\nP tiene que ser diferente de cero");  // Imprime un mensaje si P es igual a cero
    }
}
