#include <stdio.h>

void main(void)
{
    int I, N; // Declaración de variables: I para el contador de lanzamientos, N para el número de lanzamientos ingresado por el usuario
    float LAN, SLA = 0; // Declaración de variables: LAN para cada lanzamiento ingresado, SLA para el promedio de los lanzamientos

    do
    {
        printf("Ingrese el número de lanzamientos:\t"); // Solicita al usuario que ingrese el número de lanzamientos
        scanf("%d", &N); // Lee el número de lanzamientos ingresado por el usuario y lo almacena en N
    }
    while (N < 1 || N > 11); // Se utiliza la estructura do-while para verificar que el valor de N esté dentro del rango permitido (1 a 11)

    // Bucle for para ingresar los lanzamientos
    for (I = 1; I <= N; I++)
    {
        printf("\nIngrese el lanzamiento %d: ", I); // Solicita al usuario que ingrese el lanzamiento actual
        scanf("%f", &LAN); // Lee el lanzamiento ingresado por el usuario y lo almacena en LAN
        SLA = SLA + LAN; // Acumula el lanzamiento en la suma total (SLA)
    }

    SLA = SLA / N; // Calcula el promedio de los lanzamientos dividiendo la suma total por el número de lanzamientos
    printf("\nEl promedio de lanzamientos es: %.2f", SLA); // Imprime el promedio de lanzamientos con dos decimales
}
