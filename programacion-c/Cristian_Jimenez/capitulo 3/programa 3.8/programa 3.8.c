# include <stdio.h>

void main(void)
{
    int I, NUM; // Declaración de variables: I para el contador, NUM para el número ingresado por el usuario
    long FAC; // Variable para almacenar el factorial del número

    printf("\nIngrese el número: "); // Solicita al usuario que ingrese el número
    scanf("%d", &NUM); // Lee el número ingresado por el usuario y lo almacena en NUM

    if (NUM >= 0) // Verifica si el número ingresado es mayor o igual a cero
    {
        FAC = 1; // Inicializa la variable FAC en 1 (factorial de 0 es 1)

        // Bucle for para calcular el factorial
        for (I = 1; I <= NUM; I++)
        {
            FAC *= I; // Multiplica FAC por cada número desde 1 hasta NUM
        }

        printf("\nEl factorial de %d es: %ld", NUM, FAC); // Imprime el factorial del número
    }
    else
    {
        printf("\nError en el dato ingresado"); // Si el número ingresado es negativo, imprime un mensaje de error
    }
}
