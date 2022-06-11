#include "consumo.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ESC 27
#define ARCHI_CONSUMOS "consumos.dat"


stConsumos cargaUnConsumo() /// Imputar un cosumo diario consumos a un cliente.
{
    stConsumos c;

    c.idCliente=rand()%50+1;
    c.anio=rand()%(2022-2000)+2000;
    c.mes=rand()%12+1;
    if(c.mes==2)
    {
        c.dia=rand()%28+1;
    }
    else if(c.mes == 1 ||c.mes == 3||c.mes == 5 ||c.mes == 7 ||c.mes == 8||c.mes == 10||c.mes == 12 )
    {
        c.dia=rand()%31+1;
    }
    else
    {
        c.dia=rand()%30+1;
    }
    c.datosConsumidos=rand()%1000+1;
    c.baja = 0;

    return c;
}


stConsumos cargaUnConsumoManual() /// Imputar un cosumo diario consumos a un cliente.
{
    stConsumos c;
    int dato;
    int control=0;
    char opcion=0;
    int ultimoID=ultimoIdConsumo(ARCHI_CONSUMOS);

    do
    {
        ultimoID++;
        system("cls");
        printf("INGRESE ID DE CLIENTE: ");
        scanf("%d", &dato);
        control = buscaIdClienteEnArchivo(dato);
        if(control==0)
        {
            printf("CLIENTE NO EXISTE\n");
            printf("DESEA VOLVER A INTENTAR? ESC PARA SALIR.\n");
            opcion=getch();
        }
        else
        {
            c.id=ultimoID;
            c.idCliente=dato;
            do{
                printf("\nINGRESE MES: ");
                scanf("%d", &c.mes);
            }
            while(validaMes(c.mes)==0);

            do{
            printf("\nINGRESE DIA: ");
            scanf("%d", &c.dia);
            }
            while(validaDia(c.mes, c.dia)==0);

            do{
            printf("\nINGRESE ANIO: ");
            scanf("%d", &c.anio);
            }
            while(validaAnio(c.anio)==0);

            do{
            printf("\nINGRESE DATOS CONSUMIDOS: ");
            scanf("%d", &c.datosConsumidos);
            }
            while(validaConsumo(c.datosConsumidos)==0);
            c.baja=0;
        }
    }
    while(control!=1 && opcion!=27);


    return c;
}



int cargaArregloConsumo(stConsumos con[], int dim)
{
    char opcion = 0;
    int i = 0;

    for(i=0; i<dim; i++)
    {
        system("cls");
        con[i] = cargaUnConsumo();
    }

    return i;
}

void muestraUnConsumo(stConsumos c)
{
    printf("\n ID.................: %d", c.id);
    printf("\n ID Cliente.........: %d", c.idCliente);
    printf("\n Anio...............: %d", c.anio);
    printf("\n Mes................: %d", c.mes);
    printf("\n Dia................: %d", c.dia);
    printf("\n Datos Consumidos...: %d", c.datosConsumidos);
    if(c.baja == 0)
    {
        printf("\n\CONSUMO ACTIVO.\n\n");
    }
    else
    {
        printf("\n\CONSUMO INACTIVO.\n\n");
    }
    printf("\n===================================================");
}



void muestraConsumos (stConsumos c[], int v)
{
    for(int i=0; i<v; i++)
    {
        printf("\n ID.................: %d", c[i].id);
        printf("\n ID Cliente.........: %d", c[i].idCliente);
        printf("\n Anio...............: %d", c[i].anio);
        printf("\n Mes................: %d", c[i].mes);
        printf("\n Dia................: %d", c[i].dia);
        printf("\n Datos Consumidos...: %d", c[i].datosConsumidos);
        if(c[i].baja == 0)
        {
            printf("\n\CONSUMO ACTIVO.\n\n");
        }
        else
        {
            printf("\n\CONSUMO INACTIVO.\n\n");
        }
        printf("\n===================================================");
    }
}
