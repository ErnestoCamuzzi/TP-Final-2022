#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#ifndef CONSUMO_H_INCLUDED
#define CONSUMO_H_INCLUDED


typedef struct
{
    int id; /// campo único y autoincremental
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos; /// expresados en mb.
    int baja; /// 0 si está activo - 1 si está eliminado
} stConsumos;


stConsumos cargaUnConsumo();
void muestraConsumos (stConsumos c[], int v);
stConsumos cargaUnConsumoManual();
int validaMes(int mes);
int validaDia(int mes, int dia);
int validaAnio(int anio);


#endif // CONSUMO_H_INCLUDED
