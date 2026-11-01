#include <stdio.h>  // Incluimos la librería necesaria para usar printf y scanf

void main(void)  // Función principal, el punto de entrada del programa
{
    float PRE, NPR;  // Declaramos dos variables float: una para el precio original y otra para el nuevo precio

    printf("Ingrese el precio del producto: ");  // Pedimos al usuario que ingrese el precio del producto
    scanf("%f", &PRE);  // Leemos el precio ingresado por el usuario y lo guardamos en PRE

    if (PRE > 1500)  // Comprobamos si el precio es mayor a 1500
    {
        NPR = PRE * 1.11;  // Calculamos el nuevo precio con un aumento del 11%
        printf("\nNuevo precio: %7.2f\n", NPR);  // Mostramos el nuevo precio con un formato específico
    }
}
