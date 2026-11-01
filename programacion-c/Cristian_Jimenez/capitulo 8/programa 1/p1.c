#include <stdio.h>
#include <string.h>


struct alumno {                      
    int matricula;
    char nombre[20];
    char carrera[20];                
    float promedio;
    char direccion[20];
};       

void main(void) {

    struct alumno a1 = {120, "María", "Contabilidad", 8.9, "Querétaro"}, a2, a3;
    char nom[20], car[20], dir[20];
    int mat;
    float pro;

    printf("\nIngrese la matrícula del alumno 2: ");
    scanf("%d", &a2.matricula);
    fflush(stdin);
    printf("Ingrese el nombre del alumno 2:");
    gets(a2.nombre);
    printf("Ingrese la carrera del alumno 2: ");
    gets(a2.carrera);
    printf("Ingrese el promedio del alumno 2: ");
    scanf("%f", &a2.promedio);
    fflush(stdin);
    printf("Ingrese la dirección del alumno 2: ");
    gets(a2.direccion);

    printf("\nIngrese la matrícula del alumno 3: ");
    scanf("%d", &mat);
    a3.matricula = mat;
    fflush(stdin);
    printf("Ingrese el nombre del alumno 3: ");
    gets(nom);
    strcpy(a3.nombre, nom);
    printf("Ingrese la carrera del alumno 3: ");
    gets(car);
    strcpy(a3.carrera, car);
    printf("Ingrese el promedio del alumno 3: ");
    scanf("%f", &pro);
    a3.promedio = pro;
    fflush(stdin);
    printf("Ingrese la dirección del alumno 3: ");
    gets(dir);
    strcpy(a3.direccion, dir);
}
