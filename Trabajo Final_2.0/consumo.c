#include "consumo.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



stConsumos cargaUnConsumo() /// Imputar un cosumo diario consumos a un cliente.
{
    stConsumos c;

        c.id = rand()%1000;
        c.idCliente=rand()%50+1;
        c.anio=rand()%(2022-2000)+2000;
        c.mes=rand()%12+1;
        c.dia=rand()%31+1;
        c.datosConsumidos=rand()%100+1;
        c.baja = 0;

    return c;
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
            printf("\n\nCLIENTE ACTIVO.\n\n");
        }
        else
        {
            printf("\n\nCLIENTE INACTIVO.\n\n");
        }
        printf("\n===================================================");
    }
}
