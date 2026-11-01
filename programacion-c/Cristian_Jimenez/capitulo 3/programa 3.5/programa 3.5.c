void main(void)
{
    // Declaración de variables
    float PAG, SPA = 0;  // PAG para almacenar cada pago, SPA para acumular la suma de los pagos.

    // Solicitar al usuario que ingrese el primer pago
    printf("Ingrese el primer pago: ");

    // Bucle de entrada de pagos
    do
    {
        // Leer el pago ingresado por el usuario
        scanf("%f", &PAG);
        
        // Acumular el pago en la suma total de pagos (SPA)
        SPA = SPA + PAG;

        // Solicitar al usuario el siguiente pago, indicando cómo terminar (-0)
        printf("Ingrese el siguiente pago, ingrese -0 para terminar: ");
       
    }
    // Continuar el bucle mientras el pago ingresado sea distinto de cero
    while (PAG != 0);

    // Imprimir el total de pagos del mes
    printf("\nEl total de pagos del mes es: %.2f", SPA);
}
