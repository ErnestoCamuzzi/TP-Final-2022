#include "consumo.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ESC 27

stConsumos cargaUnConsumo() /// Imputar un cosumo diario consumos a un cliente.
{
    stConsumos c;

        c.id = rand()%1000;
        c.idCliente=rand()%50+1;
        c.anio=rand()%(2022-2000)+2000;
        c.mes=rand()%12+1;
        if(c.mes==2){
        c.dia=rand()%28+1;
        } else if(c.mes == 1 ||c.mes == 3||c.mes == 5 ||c.mes == 7 ||c.mes == 8||c.mes == 10||c.mes == 12 ){
        c.dia=rand()%31+1;
        } else{
        c.dia=rand()%30+1;
        }
        c.datosConsumidos=rand()%1000+1;
        c.baja = 0;

    return c;
}

int cargaArregloConsumo(stConsumos con[], int dim)
{
    char opcion = 0;
    int i = 0;

    for(i=0;i<dim;i++)
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
