#include <stdio.h>

int f1(void);
int f2(void);
int f3(void);
int f4(void);
int K = 3;

void main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
    {
        printf("\nEl resultado de la función f1 es: %d", f1());
        printf("\nEl resultado de la función f2 es: %d", f2());
        printf("\nEl resultado de la función f3 es: %d", f3());
        printf("\nEl resultado de la función f4 es: %d", f4());
    }
}

int f1(void)
{
    K += K;
    return K;
}

int f2(void)
{
    int local_K = 1;
    local_K++;
    return local_K;
}

int f3(void)
{
    static int static_K = 8;
    static_K += 2;
    return static_K;
}

int f4(void)
{
    int local_K = 5;
    local_K = local_K + K;
    return local_K;
}


