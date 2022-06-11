#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED



typedef struct
{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stCliente;


stCliente cargaUnCliente ();
void muestraUnCliente(stCliente c);
int cargaArregloCliente(stCliente e[], int dim);
int validaDni(char dni[], int val);
void muestraMenu();


#endif // CLIENTE_H_INCLUDED
