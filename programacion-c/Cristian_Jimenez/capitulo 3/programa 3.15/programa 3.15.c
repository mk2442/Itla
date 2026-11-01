# include <stdio.h>
# include <math.h> // Se corrigió el error de sintaxis en la directiva de inclusión para la biblioteca math.h

void main(void)
{
    int I = 1, B = 0, C;
    double RES;

    RES = 4.0 / I;
    C = 1;

    // Bucle while para calcular el valor de P aplicando una serie
    while ((fabs(3.1415 - RES)) > 0.0005)
    {
        I += 2;

        if (B)
        {
            RES += (double)(4.0 / I);
            B = 0;
        }
        else
        {
            RES -= (double)(4.0 / I);
            B = 1;
        }

        C++;
    }

    printf("\nNúmero de términos:%d", C); // Imprime el número de términos necesarios para alcanzar el valor aproximado de P
}
