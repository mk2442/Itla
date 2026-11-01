#include <stdio.h>

void main(void)
{
    int I, MAT, MAMAT, MEMAT;
    float SUM, PRO, CAL, MAPRO = 0.0, MEPRO = 11.0;

    printf("Ingrese la matrícula del primer alumno:\t");
    scanf("%d", &MAT);

    // Bucle while para procesar las calificaciones de cada alumno
    while (MAT)
    {
        SUM = 0;

        // Bucle for para ingresar las calificaciones del alumno
        for (I = 1; I <= 5; I++)
        {
            printf("\tIngrese la calificación %d del alumno: ", I);
            scanf("%f", &CAL);
            SUM += CAL;
        }

        PRO = SUM / 5; // Calcula el promedio del alumno
        printf("\nMatrícula:%d\tPromedio:%5.2f", MAT, PRO);

        // Actualiza el alumno con el mejor promedio
        if (PRO > MAPRO)
        {
            MAPRO = PRO;
            MAMAT = MAT;
        }

        // Actualiza el alumno con el peor promedio
        if (PRO < MEPRO)
        {
            MEPRO = PRO;
            MEMAT = MAT;
        }

        printf("\n\nIngrese la matrícula del siguiente alumno: ");
        scanf("%d", &MAT);
    }

    // Imprime el alumno con el mejor promedio y su promedio
    printf("\n\nAlumno con mejor Promedio:\t%d\t\%5.2f", MAMAT, MAPRO);
}
