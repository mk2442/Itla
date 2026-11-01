#include <stdio.h>  // Incluye la librería estándar de entrada y salida

void main(void)  // Define la función principal del programa
{
    float PRO;  // Declara una variable de tipo float para almacenar el promedio del alumno

    printf("Ingrese el promedio del alumno: ");  // Imprime un mensaje pidiendo al usuario que ingrese el promedio del alumno
    scanf("%f", &PRO);  // Lee el valor ingresado por el usuario y lo almacena en la variable PRO

    if (PRO >= 6.0)  // Verifica si el promedio ingresado es mayor o igual a 6.0
    {
        printf("\nAprobado");  // Si la condición es verdadera, imprime "Aprobado"
    }
    else
    {
        printf("\nReprobado");  // Si la condición es falsa, imprime "Reprobado"
    }
}
