#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27

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

/// COMO VINCULAR LOS IDstCliente con con lo de consumos

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

int cargaClientes(stCliente c[],int dim);
void muestraClientes (stCliente c[], int v);
int cargaConsumos(stConsumos c[],int dim);
void muestraConsumos (stConsumos c[], int v);

int main()
{
    stCliente clientes[DIM];
    stConsumos consumos[DIM_CONSUMOS];

    int validos=0;
    int vConsumos=0;

    validos= cargaClientes(clientes, DIM);
    system("cls");
    muestraClientes(clientes, validos);

    vConsumos=cargaConsumos(consumos,DIM_CONSUMOS);
    muestraConsumos (consumos, vConsumos);

    return 0;
}

int cargaClientes(stCliente c[],int dim)
{

    char opcion=0;
    int i=0;

    while(opcion != ESC && i<dim)
    {

        c[i].id = i+1;
        system("cls");

        fflush(stdin);
        printf("Nombre..........: ");
        gets(c[i].nombre);

        fflush(stdin);
        printf("Apellido........: ");
        gets(c[i].apellido);

        fflush(stdin);
        printf("DNI.............: ");
        gets(c[i].dni);

        printf("E-Mail..........: ");
        gets(c[i].email);

        fflush(stdin);
        printf("Domicilio.......: ");
        gets(c[i].domicilio);

        fflush(stdin);
        printf("Telefono movil..: ");
        gets(c[i].movil);

        c[i].eliminado = 0;
        i++;
        printf("DESEA CARGAR OTRO USUARIO? ESC PARA CANCELAR CUALQUIER OTRA COSA PARA SEGUIR.\n\n");
        opcion=getch();
    }
    return i;
}

void muestraClientes (stCliente c[], int v)
{
    for(int i=0; i<v; i++)
    {

        printf("\n ID.................: %d", c[i].id);
        printf("\n Apellido y Nombres.: %s, %s", c[i].apellido, c[i].nombre);
        printf("\n DNI................: %s", c[i].dni);
        printf("\n E-mail.............: %s", c[i].email);
        printf("\n Domicilio..........: %s", c[i].domicilio);
        printf("\n Movil..............: %s", c[i].movil);
        if(c[i].eliminado == 0)
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

int cargaConsumos(stConsumos c[],int dim)
{

    int i=0;

    do
    {
        c[i].id = rand()%1000;

        c[i].idCliente=rand()%50+1;

        c[i].anio=rand()%(2022-2000)+2000;

        c[i].mes=rand()%12+1;

        c[i].dia=rand()%31+1;

        c[i].datosConsumidos=rand()%100+1;

        c[i].baja = 0;

        i++;

    }
    while(i<dim);
    return i;
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
