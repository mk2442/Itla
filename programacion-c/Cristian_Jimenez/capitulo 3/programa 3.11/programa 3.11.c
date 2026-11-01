#include <stdio.h>

void main(void)
{
    // Declaración e inicialización de variables para contar las calificaciones en diferentes rangos
    int R1 = 0, R2 = 0, R3 = 0, R4 = 0, R5 = 0;
    float CAL; // Variable para almacenar la calificación del alumno

    printf("Ingresa la calificación del alumno: "); // Solicita al usuario que ingrese la calificación del alumno
    scanf("%f", &CAL); // Lee la calificación ingresada por el usuario y la almacena en CAL

    while (CAL != -1) // Bucle while que se ejecuta mientras la calificación ingresada no sea -1 (indicador de terminación)
    {
        // Evalúa la calificación y la clasifica en uno de los rangos correspondientes
        if (CAL < 4)
            R1++;
        else if (CAL < 6)
            R2++;
        else if (CAL < 8)
            R3++;
        else if (CAL < 9)
            R4++;
        else
            R5++;
        
        printf("Ingresa la calificación del alumno: "); // Solicita al usuario que ingrese la calificación del alumno
        scanf("%f", &CAL); // Lee la calificación ingresada por el usuario y la almacena en CAL
    }

    // Imprime el número de calificaciones en cada rango
    printf("\n0..3.99 = %d", R1);
    printf("\n4..5.99 = %d", R2);
    printf("\n6..7.99 = %d", R3);
    printf("\n8..8.99 = %d", R4);
    printf("\n9..10 = %d", R5);
}
