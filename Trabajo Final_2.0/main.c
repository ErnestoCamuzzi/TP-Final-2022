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




void cargaArchivoClientes(char nombreArchivo[]);
void muestraArchivoClientes(char nombre_Archivo[]);

int main()
{
    stCliente clientes[DIM];
    int validos=0;

    ///cargaArchivoClientes(ARCHI_CLIENTES);
    muestraArchivoClientes(ARCHI_CLIENTES);


    ///stConsumos consumos[DIM_CONSUMOS];
    /// int vConsumos=0;

    ///validos=cargaArregloCliente(clientes, DIM);

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
    int idCliente = ultimoIdCliente(nombreArchivo);
    if (archi)
        do
        {
            system("cls");
            idCliente++;
            clientes=cargaUnCliente();
            clientes.id=idCliente;
            clientes.nroCliente=1000+idCliente;
            fwrite(&clientes,sizeof(stCliente),1,archi);
            printf("Si desea salir presione ESC\n");
            option=getch();
        }
        while(option!=27);
    fclose(archi);
}

void muestraArchivoClientes(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"rb");
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

///void cargaArchivoConsumos(char nombreArchivo[])
/*{
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


}*/


int ultimoIdCliente(char nombreArchivo[])
{
    int id = 0;
    stCliente c;
    FILE *arch = fopen(nombreArchivo, "rb");
    if(arch)
    {
        fseek(arch, -1*sizeof(stCliente), SEEK_END);
        if(fread(&c, sizeof(stCliente), 1, arch)>0)
        {
            id = c.id;
        }
        fclose(arch);
    }

    return id;
}

void getNombre(char n[])
{
    char nombres[][20]= {"Pedro", "Pablo", "Ana"};
    strcpy(n, nombres[rand()%(sizeof(nombres)/20)]);
}
