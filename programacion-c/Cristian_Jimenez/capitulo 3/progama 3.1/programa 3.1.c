#include <stdio.h>  // Incluye la biblioteca estándar de entrada y salida, necesaria para usar 'printf' y 'scanf'

void main(void)  // Define la función principal que no devuelve ningún valor (void) y no toma argumentos
{
    int I;  // Declara una variable entera llamada 'I' que se usará como contador en el bucle 'for'
    float SAL, NOM;  // Declara dos variables de tipo 'float': 'SAL' para almacenar el salario ingresado y 'NOM' para acumular el total de los salarios (nómina)
    NOM = 0;  // Inicializa la variable 'NOM' en 0 para empezar la suma desde cero
    for (I=1; I<=15; I++)  // Inicia un bucle 'for' que se repetirá 15 veces, con 'I' tomando valores de 1 a 15
    {
        printf("Ingrese el salario del profesor %d:\t", I);  // Imprime un mensaje solicitando al usuario que ingrese el salario del profesor número 'I', con una tabulación al final
        scanf("%f", &SAL);  // Lee un valor de tipo 'float' ingresado por el usuario y lo almacena en la variable 'SAL'; el operador '&' obtiene la dirección de memoria de 'SAL'
        NOM = NOM + SAL;  // Suma el valor de 'SAL' a 'NOM', acumulando el total de los salarios ingresados
    }
    printf("\nEl total de la nómina es %.2f", NOM);  // Imprime el total acumulado de la nómina ('NOM'), con dos decimales de precisión
}
