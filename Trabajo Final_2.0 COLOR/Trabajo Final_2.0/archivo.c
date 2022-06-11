#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "archivo.h"
#include "cliente.h"
#include "cliente.c"
#include <time.h>

#define ARCHI_CLIENTES "clientes.dat"



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
