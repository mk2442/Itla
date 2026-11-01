#include <stdio.h>  // Incluye la librería estándar de entrada y salida

void main(void)  // Define la función principal del programa
{
    float PRE, NPR;  // Declara dos variables de tipo float: PRE para el precio original y NPR para el nuevo precio

    printf("Ingrese el precio del producto: ");  // Imprime un mensaje pidiendo al usuario que ingrese el precio del producto
    scanf("%f", &PRE);  // Lee el valor ingresado por el usuario y lo almacena en la variable PRE

    if (PRE < 1500)  // Verifica si el precio ingresado es menor a 1500
    {
        NPR = PRE * 1.11;  // Si la condición es verdadera, calcula el nuevo precio aumentando el 11% y lo almacena en NPR
    }
    else  // Si el precio es mayor o igual a 1500
    {
        NPR = PRE;  // Asigna el valor original a NPR
    }

   else