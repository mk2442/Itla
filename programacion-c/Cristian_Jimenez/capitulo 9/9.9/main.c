#include <stdio.h>

typedef struct{
    int matricula;
    char nombre[20];
    int carerra;
    float promedio;
}alumno;

void lee(FILE *);

void main(void)
{
FILE *ar;
if((ar = fopen("ad1.dat", "r")) != NULL)
    lee(ar);
else
    printf("\nEl archivo no se puede abrir");
fclose(ar);
}

void lee(FILE *ap)
{
alumno alu;
fread(&alu, sizeof(alumno), 1, ap);

while(!feof(ap))
{
    printf("\nMatricula: %d", alu.matricula);
    printf("\tCarerra: %d", alu.carerra);
    printf("\tPromedio: %f\t ", alu.promedio);
    puts(alu.nombre);
    fread(&alu, sizeof(alumno), 1, ap);
}
}
