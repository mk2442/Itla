#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[20];
    int matricula;
    char carrera[20];
    float promedio;
} alumno;

void escritura(int c);
void lectura(int c);

void main(void)
{
    FILE *ar;
    if((ar = fopen("estudiantes.txt", "w+")) == NULL)
    {
        return;
    }
    fclose(ar);

    int cantidad, opcion, lec = 0;

    printf("Bienvenido!!!\n");
    printf("\nIngrese la opcion que quiere realizar\nGrabar datos\t-Ingresa 1- \nLeer disco\t-Ingresa 2-\nSalir\t\t-Ingresa 0-\n");
    scanf("%d", &opcion);
    if(opcion != 0)
    {
        do
        {
            if(opcion == 1 || opcion == 2)
            {
                if(opcion == 1)
                {
                    printf("\nCuantos estudiantes registraras?\n");
                    scanf("%d", &cantidad);
                    lec += cantidad;
                    escritura(cantidad);
                }
                if(opcion == 2)
                {
                    printf("\n\nVa a imprimir %d estudiantes\n\n", lec);
                    lectura(lec);
                }
                printf("\nIngrese la opcion que quiere realizar\nGrabar datos\t-Ingresa 1- \nLeer disco\t-Ingresa 2-\nSalir\t\t-Ingresa 0-\n");
                scanf("%d", &opcion);
            }
            else
            {
                printf("\nLa opcion ingresada no es valida.\nPor favor, ingresa una opcion valida\n");
                printf("\nIngrese la opcion que quiere realizar\nGrabar datos\t-Ingresa 1- \nLeer disco\t-Ingresa 2-\nSalir\t\t-Ingresa 0-\n");
                scanf("%d", &opcion);
            }
        }
        while(opcion);
    }

    printf("\nFin del programa. Gracias!!!");
}

void escritura(int c)
{
    int i;
    FILE *ar;
    alumno *md;
    if((ar = fopen("estudiantes.txt", "a+")))
    {
        if((md = (alumno *)malloc(c * sizeof(alumno))) != NULL)
        {
            for(i=0; i<c; i++)
            {
                printf("\nIngresa el nombre del alumno %d:\n", i+1);
                scanf("%s", &md[i].nombre);
                fprintf(ar, "%s\n", md[i].nombre);

                printf("\nIngresa la matricula del alumno %d:\n", i+1);
                scanf("%d", &md[i].matricula);
                fprintf(ar, "%d\n", md[i].matricula);

                printf("\nIngresa la carrera del alumno %d:\n", i+1);
                scanf("%s", &md[i].carrera);
                fprintf(ar, "%s\n", md[i].carrera);

                printf("\nIngresa el promedio del alumno %d:\n", i+1);
                scanf("%f", &md[i].promedio);
                fprintf(ar, "%.2f\n", md[i].promedio);
            }
            free(md);
        }
        else
            printf("\nNo tiene suficiente memoria para ingresar tantos datos\n");
        fclose(ar);
    }
    else
        printf("\nNo se pudo abrir el archivo");
}

void lectura(int c)
{
    FILE *ar;
    alumno *md;
    int i;
    if((ar = fopen("estudiantes.txt", "r")) != NULL)
    {
        if((md = (alumno *)malloc(c * sizeof(alumno))) != NULL)
        {
            for(i=0; i<c; i++)
            {
                fscanf(ar, "%s", &md[i].nombre);
                printf("\nNombre:\t%s\n", md[i].nombre);

                fscanf(ar, "\t%d\n", &md[i].matricula);
                printf("Matricula:\t%d\n", md[i].matricula);

                fscanf(ar, "\t%s\n", &md[i].carrera);
                printf("Carrera:\t%s\n", md[i].carrera);

                fscanf(ar, "\t%f\n", &md[i].promedio);
                printf("Promedio:\t%.2f\n\n", md[i].promedio);
            }
            free(md);
        }
        fclose(ar);
    }
    else
        printf("/nNo se pudo abrir el archivo.");
}
