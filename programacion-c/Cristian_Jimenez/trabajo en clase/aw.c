#include <stdio.h>

int main()
{
    int edad = 0;

    printf("Ingrese su edad: ");
    scanf("%d", &edad);

    if (edad > 0)
    {
        if (edad < 6)
        {
            printf("Eres un bebe\n");
        }
        else if (edad < 12)
        {
            printf("Eres un niño\n");
        }
        else if (edad < 18)
        {
            printf("Eres un adolescente\n");
        }
        else if (edad < 60)
        {
            printf("Eres un adulto\n");
        }
        else if (edad < 121)
        {
            printf("Eres un anciano\n");
        }
        else
        {
            printf("Oyeme David, no seas mentiroso que eso que tú dices está bien dudoso\n");
        }
    }
    else
    {
        printf("Edad no valida\n");
    }

    return 0;
}
