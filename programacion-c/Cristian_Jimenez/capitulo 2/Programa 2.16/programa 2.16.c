#include <stdio.h>

void main(void)
{
    int TRA, EDA, DIA;   // Declarar variables para el tipo de tratamiento, edad y duración en días
    float COS;           // Declarar variable para el costo total

    printf("Ingrese tipo de tratamiento, edad y días: ");   // Solicitar al usuario que ingrese la información necesaria
    scanf("%d %d %d", &TRA, &EDA, &DIA);                   // Leer los valores ingresados por el usuario

    // Calcular el costo total del tratamiento según el tipo de tratamiento
    switch(TRA)
    {
        case 1: COS = DIA * 2800; break;
        case 2: COS = DIA * 1950; break;
        case 3: COS = DIA * 2500; break;
        case 4: COS = DIA * 1150; break;
        default: COS = -1; break;  // Asignar -1 si la clave del tratamiento es incorrecta
    }

    // Verificar si la clave del tratamiento es correcta y calcular el descuento según la edad del paciente
    if (COS != -1)
    {
        if (EDA >= 60)
        {
            COS *= 0.75;  // Aplicar un descuento del 25% para pacientes mayores de 60 años
        }
        else if (EDA <= 25)
        {
            COS *= 0.85;  // Aplicar un descuento del 15% para pacientes menores de 25 años
        }

        // Imprimir el costo total del tratamiento con el formato adecuado
        printf("\nClave tratamiento: %d\t Días: %d\t Costo total: %8.2f", TRA, DIA, COS);
    }
    else
    {
        printf("\nLa clave del tratamiento es incorrecta");  // Indicar que la clave del tratamiento es incorrecta si no es válida
    }
}
