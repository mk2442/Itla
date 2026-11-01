#include <stdio.h>
#include <string.h>


void ordena(char [][20], int); 

int main(void)
{
    char fra[5][20];
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("\nIngrese la palabra %d: ", i + 1);
        gets(fra[i]);
    }
    ordena(fra, 5);
    printf("\n\nPalabras ordenadas alfabéticamente:\n");
    for (i = 0; i < 5; i++)
        puts(fra[i]);
    return 0;
}

void ordena(char fra[][20], int n)
{
    int i, j;
    char temp[20];
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (strcmp(fra[i], fra[j]) > 0)
            {
                strcpy(temp, fra[i]);
                strcpy(fra[i], fra[j]);
                strcpy(fra[j], temp);
            }
}
