#include <stdio.h>
#include <string.h>


struct empleado {
    int matricula;
    char *nombre;
    char *departamento;
    float salario;
};

void main(void) {
    struct empleado a1, a2;
    char nom1[20] = "María";
    char dep1[20] = "Contabilidad";
    char nom2[20], dep2[20];
    
    a1.matricula = 120;
    a1.nombre = nom1;
    a1.departamento = dep1;
    a1.salario = 8900.50;

    printf("\nIngrese la matrícula del empleado 2: ");
    scanf("%d", &a2.matricula);
    fflush(stdin);
    printf("Ingrese el nombre del empleado 2: ");
    gets(nom2);
    a2.nombre = nom2;
    printf("Ingrese el departamento del empleado 2: ");
    gets(dep2);
    a2.departamento = dep2;
    printf("Ingrese el salario del empleado 2: ");
    scanf("%f", &a2.salario);

    printf("\nDatos del empleado 1:\n");
    printf("Matrícula: %d\nNombre: %s\nDepartamento: %s\nSalario: %.2f\n", a1.matricula, a1.nombre, a1.departamento, a1.salario);
    printf("\nDatos del empleado 2:\n");
    printf("Matrícula: %d\nNombre: %s\nDepartamento: %s\nSalario: %.2f\n", a2.matricula, a2.nombre, a2.departamento, a2.salario);
}
