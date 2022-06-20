#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include <string.h>
#include "gotoxy.h"
#include <windows.h>

///FUNCIONES MENU

void muestraMenu()
{
    system ("cls");
    printf("\n");
    system("color 0");
    color(9);
    printf("\n\t\t");
    replicaChar('<',20);
    printf ("\t\t\tMENU GENERAL\t\t\t");replicaChar('>',20);
    color(9);
    printf("\n");
    printf("\n\t\t\t\t\t\t0    - MENU CLIENTES.");
    printf("\n\t\t\t\t\t\t1    - MENU CONSUMOS.\n");
    printf("\n");
    color(9);


}


int MenuCliente ()
{
    int opcionCliente;
    system("cls");
    system("color 0");
    printf("\n");


    color(9);
    printf("\n\t\t");
    replicaChar('<',20);
    printf("\t\t\tMENU CLIENTES\t\t\t");replicaChar('>',20);
    color(9);
    printf("\n");
    printf("\n\t\t\t\t\t0    - CARGA UN CLIENTE.");
    printf("\n\t\t\t\t\t1    - MOSTRAR REGISTRO DE CLIENTES.");
    printf("\n\t\t\t\t\t2    - BUSCAR UN CLIENTE POR NR CLIENTE.");
    printf("\n\t\t\t\t\t3    - MUESTRA CLIENTES ACTIVOS.");
    printf("\n\t\t\t\t\t4    - MUESTRA CLIENTES INACTIVOS.");
    printf("\n\t\t\t\t\t5    - MODIFICAR DATO DE CLIENTES.");
    printf("\n\t\t\t\t\t       INGRESE UNA OPCION.\n");
    printf("\n");
    color(9);

    printf("\n");
    opcionCliente=getch();
    return opcionCliente;
}

int MenuModificarCliente ()
{
    int opcionModificaCliente;
    system("cls");
    system("color 0");
    printf("\n");

    color(9);
    printf("\n\t\t");
    replicaChar('<',20);
    printf("\t\t\tMODIFICAR CLIENTES\t\t\t");replicaChar('>',20);
    color(9);
    printf("\n");
    printf("\n\t\t\t\t\t0    - MODIFICAR NOMBRE Y APELLIDO.");
    printf("\n\t\t\t\t\t1    - MODIFICAR NR TELEFONO.");
    printf("\n\t\t\t\t\t2    - MODIFICAR NR DNI.");
    printf("\n\t\t\t\t\t3    - MODIFICAR EMAIL.");
    printf("\n\t\t\t\t\t4    - MODIFICAR DOMICILIO.");
    printf("\n\t\t\t\t\t5    - MODIFICAR STATUS.");
    printf("\n\t\t\t\t\t       INGRESE UNA OPCION\n");
    printf("\n");
    color(9);
    printf("\n");
    opcionModificaCliente=getch();
    return opcionModificaCliente;
}

int MenuConsumo()
{
    int opcionConsumo;
    system("cls");
    system("color 0");
    printf("\n");
    color(9);
    printf("\n\t\t");
    replicaChar('<',20);
    printf("\t\t\tMENU CONSUMOS\t\t\t");replicaChar('>',20);
    color(9);
    printf("\n");
    printf("\n\t\t\t\t\t0    - CARGA ARCHIVO DE CONSUMO RANDOM.");
    printf("\n\t\t\t\t\t1    - CARGA ARCHIVO DE CONSUMO MANUAL.");
    printf("\n\t\t\t\t\t2    - MUESTRA ARCHIVO DE CONSUMI.");
    printf("\n\t\t\t\t\t3    - MODIFICAR ESTADO DE CONSUMO.");
    printf("\n\t\t\t\t\t4    - BUSCAR CONSUMO POR ID.");
    printf("\n\t\t\t\t\t5    - MODIFICAR CONSUMO POR ID.");
    printf("\n\t\t\t\t\t6    - MODIFICAR FECHA POR ID.");
    printf("\n\t\t\t\t\t7    - MOSTRAR CONSUMOS POR CLIENTE.");
    printf("\n\t\t\t\t\t8    - MOSTRAR CONSUMOS POR FECHA.");
    printf("\n\t\t\t\t\t9    - SUMAR CONSUMOS POR FECHA.");
    printf("\n\t\t\t\t\t      INGRESE UNA OPCION\n");
    printf("\n");
    color(9);

    printf("\n");
    opcionConsumo=getch();
    return opcionConsumo;
}

void replicaChar(char c, int cant)
{
    for(int i=0; i<cant; i++)
    {
        printf("%c",c);
    }
}
