#include <stdio.h>

void main(void)
{
    int CLA, TIE;   // Declarar variables para la clave y el tiempo
    float COS;      // Declarar variable para el costo

    printf("Ingresa la clave y el tiempo: ");   // Solicitar al usuario que ingrese la clave y el tiempo
    scanf("%d %d", &CLA, &TIE);                 // Leer los valores ingresados por el usuario

    // Calcular el costo del servicio según la clave
    switch(CLA)
    {
        case 1: COS = TIE * 0.13 / 60; break;
        case 2: COS = TIE * 0.11 / 60; break;
        case 5: COS = TIE * 0.22 / 60; break;
        case 6: COS = TIE * 0.19 / 60; break;
        case 7:
        case 9: COS = TIE * 0.17 / 60; break;
        case 10: COS = TIE * 0.20 / 60; break;
        case 15: COS = TIE * 0.39 / 60; break;
        case 20: COS = TIE * 0.28 / 60; break;
        default: COS = -1; break;
    }

    // Verificar si la clave es válida y mostrar el resultado
    if (COS != -1)
    {
        printf("\n\nClave: %d\tTiempo: %d\tCosto: %6.2f", CLA, TIE, COS);
    }
    else
    {
        printf("\nError en la clave");  // Indicar que hay un error en la clave si no es válida
    }
}
