#include <stdio.h>

void main(void)
{
    float PAG, SPA = 0; // Declaración de variables: PAG para cada pago ingresado, SPA para la suma acumulada de los pagos

    printf("Ingrese el primer pago:\t"); // Solicita al usuario que ingrese el primer pago
    scanf("%f", &PAG); // Lee el primer pago ingresado por el usuario y lo almacena en PAG

    /* Observa que al utilizar la estructura do-while al menos se necesita un pago. */
    do
    {
        SPA = SPA + PAG; // Acumula el pago en la suma total (SPA)
        printf("Ingrese el siguiente pago -0 para terminar-:\t"); // Solicita al usuario que ingrese el siguiente pago
        scanf("%f", &PAG); // Lee el siguiente pago ingresado por el usuario y lo almacena en PAG
    }
    while (PAG); // El bucle se ejecuta mientras PAG sea diferente de 0

    printf("\nEl total de pagos del mes es: %.2f", SPA); // Imprime el total de pagos del mes con dos decimales
}
