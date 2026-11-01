#include <stdio.h>

void main(void)
{
    int DIS, TIE;   // Declara variables para la distancia y el tiempo de estancia
    float BIL;      // Declara una variable para el costo del billete

    printf("Ingrese la distancia entre ciudades y el tiempo de estancia: ");  // Pide al usuario que ingrese la distancia y el tiempo de estancia
    scanf("%d %d", &DIS, &TIE);  // Lee los valores ingresados por el usuario y los almacena en las variables DIS y TIE

    // Calcula el costo del billete basado en la distancia y el tiempo de estancia
    if ((DIS * 2 > 500) && (TIE > 10))  // Verifica si la distancia total es mayor que 500 y el tiempo de estancia es mayor que 10
    {
        // Aplica un descuento del 20% al costo del billete si se cumplen ambas condiciones
        BIL = DIS * 2 * 0.19 * 0.8;
    }
    else
    {
        // Calcula el costo del billete sin descuento
        BIL = DIS * 2 * 0.19;
    }

    // Imprime el costo del billete con dos decimales
    printf("\n\nCosto del billete: %7.2f", BIL);
}
