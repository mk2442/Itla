#include <stdio.h>

int main()
{
    float PRO;
    printf("Ingrese el promedio del alumno:\n");
    scanf("%f", &PRO);

    if ((PRO >= 0.0) && (PRO <= 4.0))
    {
        if (PRO >= 3.0)
        {
            printf("\nAprobado\n");
        }
        else
        {
            printf("\nReprobado\n");
        }
    }
    else
    {
        printf("Valor invalido, ingresar un valor de 0 a 4\n");
    }

    return 0;
}

