#include <stdio.h>

void f1(void);
int K = 5;

void main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
        f1();
}

void f1(void)
{
    int local_K = 2;
    local_K += local_K;
    printf("\n\nEl valor de la variable local es: %d", local_K);
    K = K + local_K;
    printf("\nEl valor de la variable global es: %d", K);
}
