#include <stdio.h>  // Incluye la biblioteca estándar de entrada y salida, necesaria para usar 'printf' y 'scanf'

void main(void)  // Define la función principal que no devuelve ningún valor (void) y no toma argumentos
{
    float PAG, SPA;  // Declara dos variables de tipo float: 'PAG' (para almacenar cada pago ingresado) y 'SPA' (para acumular el total de los pagos)
    SPA = 0;  // Inicializa la variable 'SPA' en 0 para empezar la suma desde cero
    printf("Ingrese el primer pago:\t");  // Imprime un mensaje solicitando al usuario que ingrese el primer pago, con una tabulación al final
    scanf("%f", &PAG);  // Lee un valor de tipo float ingresado por el usuario y lo almacena en la variable 'PAG'; el operador '&' obtiene la dirección de memoria de 'PAG'
    while (PAG)  // Inicia un bucle 'while' que se repetirá mientras 'PAG' sea diferente de cero
    {
        SPA = SPA + PAG;  // Suma el valor de 'PAG' a 'SPA', acumulando el total de los pagos ingresados
        printf("Ingrese el siguiente pago:\t");  // Imprime un mensaje solicitando al usuario que ingrese el siguiente pago, con una tabulación al final
        scanf("%f", &PAG);  // Lee un valor de tipo float ingresado por el usuario y lo almacena en la variable 'PAG'
    }
    printf("\nEl total de pagos del mes es: %.2f", SPA);  // Imprime el total acumulado de los pagos ('SPA'), con dos decimales de precisión
}
