#include <stdio.h>


void main(void)
{
    int n, i, j, f, c, x, y, mat[50][50];
    printf("\nIngrese el tamaño de la matriz: ");
    scanf("%d", &n);
    if (n % 2 == 0)
        printf("\nEl tamaño debe ser impar.");
    else
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                mat[i][j] = 0;
        f = 0;
        c = n / 2;
        mat[f][c] = 1;
        for (i = 2; i <= n * n; i++)
        {
            x = (f - 1 < 0) ? n - 1 : f - 1;
            y = (c - 1 < 0) ? n - 1 : c - 1;
            if (mat[x][y] == 0)
            {
                f = x;
                c = y;
            }
            else
                f = (f + 1) % n;
            mat[f][c] = i;
        }
        printf("\n\nEl cuadrado mágico es:\n");
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                printf("%5d", mat[i][j]);
            printf("\n");
        }
    }
}
