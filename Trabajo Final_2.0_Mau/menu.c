#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include <string.h>
#include "gotoxy.h"






///FUNCIONES MENU

void muestraMenu()
{
    system ("cls");
    printf("\n");
    system("color 1F");
    ///color(10);
    replicaChar('=',80);
    printf("\n");
    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MENU GENERAL >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    ///color(3);
    printf("\n 0 - MENU CLIENTES.");
    printf("\n 1 - MENU CONSUMOS.\n");
    printf("\n");
    ///color(10);
    replicaChar('=',80);

}


int MenuCliente ()
{
    int opcionCliente;
    system("cls");
    system("color 1F");
    printf("\n");
    replicaChar('=',80);
    printf("\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MENU CLIENTES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    printf("\n 0 - Carga de un cliente.");
    printf("\n 1 - Mostrar registro de clientes.");
    printf("\n 2 - Modificar STATUS.");
    printf("\n 3 - Buscar un cliente");
    printf("\n 4 - Muestra clientes ACTIVOS.");
    printf("\n 5 - Muestra clientes INACTIVOS.");
    printf("\n 6 - MODIFICAR DATO DE CLIENTES");
    printf("\n   - Ingrese opcion\n");
    replicaChar('=',80);
    printf("\n");
    opcionCliente=getch();
    return opcionCliente;
}

int MenuModificarCliente ()
{
    int opcionModificaCliente;
    system("cls");
    system("color 1F");
    printf("\n");
    replicaChar('=',80);
    printf("\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MODIFICAR CLIENTES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    printf("\n 0 - MODIFICAR NOMBRE Y APELLIDO.");
    printf("\n 1 - MODIFICAR NR TELEFONO.");
    printf("\n 2 - MODIFICAR NR DNI.");
    printf("\n 3 - MODIFICAR EMAIL.");
    printf("\n 4 - MODIFICAR DOMICILIO.");
    printf("\n 5 - MODIFICAR STATUS.");
    printf("\n   - Ingrese opcion\n");
    replicaChar('=',80);
    printf("\n");
    opcionModificaCliente=getch();
    return opcionModificaCliente;
}

int MenuConsumo()
{
    int opcionConsumo;
    system("cls");
    system("color 1F");
    printf("\n");
    replicaChar('=',80);
    printf("\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MENU CONSUMO>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    printf("\n 0 - Carga Archivo Consumo Random");
    printf("\n 1 - Carga Archivo Consumo Manual");
    printf("\n 2 - Muestra Archivo de Consumo");
    printf("\n 3 - Modificar Estado De Consumo");
    printf("\n 4 - BUSCAR CONSUMO POR ID");
    printf("\n 5 - MODIFICAR CONSUMO POR ID");
    printf("\n 6 - MODIFICAR FECHA POR ID");
    printf("\n 7 - MOSTRAR CONSUMOS POR CLIENTE");
    printf("\n 8 - MOSTRAR CONSUMOS POR FECHA");
    printf("\n     Ingrese opcion\n");
    replicaChar('=',80);
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
