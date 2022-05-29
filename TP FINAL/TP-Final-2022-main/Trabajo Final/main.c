#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27
#define ARCHI_CLIENTES "clientes.dat"

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

stCliente cargaClientes();
void muestraClientes (stCliente c);
int cargaConsumos(stConsumos c[],int dim);
void muestraConsumos (stConsumos c[], int v);
void cargaArchivoClientes(char nombreArchivo[]);
void muestraArchivoClientes(char nombre_Archivo[]);


int main()
{
    stCliente clientes[DIM];
    int validos=0;
    cargaArchivoClientes(ARCHI_CLIENTES);
    printf("\nPRUEBA");
    muestraArchivoClientes(ARCHI_CLIENTES);


    ///stConsumos consumos[DIM_CONSUMOS];
   /// int vConsumos=0;



    ///validos= cargaClientes(clientes, DIM);
    ///system("cls");
    ///muestraClientes(clientes, validos);

   /// vConsumos=cargaConsumos(consumos,DIM_CONSUMOS);
   /// muestraConsumos (consumos, vConsumos);

    return 0;
}

stCliente cargaClientes()


    { stCliente c;

        fflush(stdin);
        printf("Nombre..........: ");
        gets(c.nombre);

        fflush(stdin);
        printf("Apellido........: ");
        gets(c.apellido);

        fflush(stdin);
        printf("DNI.............: ");
        gets(c.dni);

        printf("E-Mail..........: ");
        gets(c.email);

        fflush(stdin);
        printf("Domicilio.......: ");
        gets(c.domicilio);

        fflush(stdin);
        printf("Telefono movil..: ");
        gets(c.movil);

        c.eliminado = 0;

        return c;
}

void muestraClientes(stCliente c)
{

        printf("\n ID.................: %d", c.id);
        printf("\n N° de cliente......: %d", c.nroCliente);
        printf("\n Apellido y Nombres.: %s, %s",c.apellido, c.nombre);
        printf("\n DNI................: %s", c.dni);
        printf("\n E-mail.............: %s", c.email);
        printf("\n Domicilio..........: %s", c.domicilio);
        printf("\n Movil..............: %s", c.movil);


        if(c.eliminado == 0)
        {
            printf("\n\nCLIENTE ACTIVO.\n\n");
        }
        else
        {
            printf("\n\nCLIENTE INACTIVO.\n\n");

        }
        printf("\n===================================================");

}

stConsumos cargaConsumos()
{
stConsumos consu;
      do
    {
        c.id = rand()%1000;

        c.idCliente=rand()%50+1;

        c.anio=rand()%(2022-2000)+2000;

        c.mes=rand()%12+1;

        c.dia=rand()%31+1;

        c.datosConsumidos=rand()%100+1;

        c.baja = 0;
        }
        return consu;


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

void cargaArchivoClientes(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"ab");
    stCliente clientes;
    char option=0;
    if (archi) do


        {
            clientes=cargaClientes();
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
    muestraClientes(c);
        }
        fclose(archi);
    }


}

void cargaArchivoConsumos(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"ab");
    stConsumos consu;
    char option=0;
    if (archi) do


        {
            consumos=cargaConsumos();
            fwrite(&consumos,sizeof(stConsumos),1,archi);
            printf("Si desea salir presione ESC\n");
            option=getch();


        }
        while(option!=27);


    fclose(archi);


}



