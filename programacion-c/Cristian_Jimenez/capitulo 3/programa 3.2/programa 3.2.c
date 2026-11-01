#include <stdio.h>  // Incluye la biblioteca estándar de entrada y salida

void main(void)  // Declara la función principal que no devuelve ningún valor
{
    int I, N, NUM, SUM;  // Declara las variables enteras 'I', 'N', 'NUM' y 'SUM'
    SUM = 0;  // Inicializa 'SUM' en 0 para comenzar la suma desde cero
    printf("Ingrese el número de datos:\t");  // Solicita al usuario que ingrese el número de datos
    scanf("%d", &N);  // Lee el número de datos ingresado por el usuario y lo almacena en 'N'
    for (I=1; I<=N; I++)  // Inicia un bucle 'for' que se ejecutará 'N' veces
    {
        printf("Ingrese el dato número %d:\t", I);  // Solicita al usuario que ingrese el dato número 'I'
        scanf("%d", &NUM);  // Lee el dato ingresado por el usuario y lo almacena en 'NUM'
        if (NUM > 0)  // Si 'NUM' es mayor que 0
            SUM = SUM + NUM;  // Suma 'NUM' a 'SUM'
    }
    printf("\nLa suma de los números positivos es: %d", SUM);  // Imprime la suma de los números positivos
}
