#include <stdio.h>

void main(void)
{
    float P, S, R;  // Declara variables para las ventas de los tres vendedores

    printf("\nIngrese las ventas de los tres vendedores: ");  // Pide al usuario que ingrese las ventas de los tres vendedores
    scanf("%f %f %f", &P, &S, &R);  // Lee las ventas ingresadas por el usuario

    // Comienza la evaluación de las ventas para determinar el orden
    if (P > S)
    {
        if (P > R)
        {
            if (S > R)
                printf("\n\n El orden es P, S y R: %8.2f %8.2f %8.2f", P, S, R);  // Imprime el orden de ventas si P es el mayor
            else
                printf("\n\n El orden es P, R y S: %8.2f %8.2f %8.2f", P, R, S);  // Imprime el orden de ventas si P es el mayor pero R es mayor que S
        }
        else
            printf("\n\n El orden es R, P y S: %8.2f %8.2f %8.2f", R, P, S);  // Imprime el orden de ventas si R es el mayor
    }
    else
    {
        if (S > R)
        {
            if (P > R)
                printf("\n\n El orden es S, P y R: %8.2f %8.2f %8.2f", S, P, R);  // Imprime el orden de ventas si S es el mayor
            else
                printf("\n\n El orden es S, R y P: %8.2f %8.2f %8.2f", S, R, P);  // Imprime el orden de ventas si S es el mayor pero P es mayor que R
        }
        else
            printf("\n\n El orden es R, S y P: %8.2f %8.2f %8.2f", R, S, P);  // Imprime el orden de ventas si R es el mayor
    }
}
