#include <stdio.h>
#include <math.h>

/* Suma cuadrados.
El programa, al recibir como datos un grupo de enteros positivos, obtiene el
➥cuadrado de los mismos y la suma correspondiente a dichos cuadrados. */
void main(void)
{
    int NUM; // Variable para almacenar el número ingresado por el usuario
    long CUA, SUC = 0; // CUA para almacenar el cuadrado de NUM, SUC para acumular la suma de los cuadrados

    printf("\nIngrese un número entero -0 para terminar-:\t"); // Solicita al usuario que ingrese un número entero
    scanf("%d", &NUM); // Lee el número ingresado por el usuario y lo almacena en NUM

    while (NUM)
    {
        // Calcula el cuadrado del número ingresado y lo almacena en CUA
        CUA = pow(NUM, 2);
        
        // Imprime el número ingresado y su cuadrado
        printf("%d al cuadrado es %ld\n", NUM, CUA);
        
        // Acumula el cuadrado en la suma total
        SUC = SUC + CUA;
        
        // Solicita al usuario que ingrese otro número entero o -0 para terminar
        printf("Ingrese un número entero -0 para terminar-:\t");
        scanf("%d", &NUM);
    }
    
    // Imprime la suma de los cuadrados de los números ingresados
    printf("La suma de los cuadrados es %ld\n", SUC);
}
