#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include <string.h>


#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27
#define ARCHI_CLIENTES "clientes.dat"



/// COMO VINCULAR LOS IDstCliente con con lo de consumos



stCliente cargaUnCliente();


int cargaConsumos(stConsumos c[],int dim);
void muestraConsumos (stConsumos c[], int v);
void cargaArchivoClientes(char nombreArchivo[]);
void muestraArchivoClientes(char nombre_Archivo[]);
int cargaArregloCliente(stCliente e[], int dim);

int main()
{
    stCliente clientes[DIM];
    int validos=0;
    cargaArchivoClientes(ARCHI_CLIENTES);
    printf("\nPRUEBA");
    muestraArchivoClientes(ARCHI_CLIENTES);


    ///stConsumos consumos[DIM_CONSUMOS];
    /// int vConsumos=0;

    validos=cargaArregloCliente(clientes, DIM);

    ///system("cls");
    ///muestraClientes(clientes, validos);

    /// vConsumos=cargaConsumos(consumos,DIM_CONSUMOS);
    /// muestraConsumos (consumos, vConsumos);

    return 0;
}



void cargaArchivoClientes(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"ab");
    stCliente clientes;
    char option=0;
    if (archi)
        do
        {
            system("cls");
            clientes=cargaUnCliente();
            fwrite(&clientes,sizeof(stCliente),1,archi);
            printf("Si desea salir presione ESC\n");
            option=getch();
        }
        while(option!=27);
    fclose(archi);
}

void muestraArchivoClientes(char nombre_Archivo[])
{
    FILE *archi=fopen(nombre_Archivo,"rb");
    stCliente c;

    if (archi)
    {
        while(fread(&c,sizeof(stCliente),1,archi)>0)
        {
            muestraUnCliente(c);
        }
        fclose(archi);
    }


}

/*void cargaArchivoConsumos(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"ab");
    stConsumos consu;
    char option=0;
    if (archi)
        do
        {
            consumos=cargaConsumos();
            fwrite(&consumos,sizeof(stConsumos),1,archi);
            printf("Si desea salir presione ESC\n");
            option=getch();
        }
        while(option!=27);
    fclose(archi);


}
*/



