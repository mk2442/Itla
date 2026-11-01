#include <stdio.h>

int main(void)
{
    float P, S, R;
    printf("\nIngrese las ventas de los tres vendedores: ");
    scanf("%f %f %f", &P, &S, &R);

    if (P > S && P > R) {
        if (S > R) {
            printf("\n\nEl orden es P, S y R: %8.2f %8.2f %8.2f\n", P, S, R);
        } else {
            printf("\n\nEl orden es P, R y S: %8.2f %8.2f %8.2f\n", P, R, S);
        }
    } else if (S > P && S > R) {
        if (P > R) {
            printf("\n\nEl orden es S, P y R: %8.2f %8.2f %8.2f\n", S, P, R);
        } else {
            printf("\n\nEl orden es S, R y P: %8.2f %8.2f %8.2f\n", S, R, P);
        }
    } else {
        if (P > S) {
            printf("\n\nEl orden es R, P y S: %8.2f %8.2f %8.2f\n", R, P, S);
        } else {
            printf("\n\nEl orden es R, S y P: %8.2f %8.2f %8.2f\n", R, S, P);
        }
    }

    return 0;
}
