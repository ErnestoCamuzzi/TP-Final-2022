#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include <string.h>
#include "gotoxy.h"



#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CONSUMOS "consumos.dat"



/// COMO VINCULAR LOS IDstCliente con con lo de consumos.
/// ANIDAR LOS CASES DE MUESTRA Y MODIFICACIONES.
/// EN LA MODIFICACION DE DATOS, AL CAMBIAR EL DNI, FALTARIA VALIDAR QUE ESE NUEVO DNI NO ESTE EN LA BASE DE ARCHIVO.



int buscaDniEnArchivo(FILE *archi, char dni[]);
void cargaArchivoClientes(char nombreArchivo[]);
void muestraArchivoClientes(char nombre_Archivo[]);
void modificarEstadoCliente(char nombreArchivo[],int nrCliente);
void mostrarClientePorNrCliente(char nombreArchivo[],int nrCliente);
void mostrarClientesActivos(char nombreArchivo[]);
void mostrarClientesInactivos(char nombreArchivo[]);
void modificarNombreCliente(char nombreArchivo[], int nrCliente);
void modificarDNICliente(char nombreArchivo[], int nrCliente);
void modificarEmailCliente(char nombreArchivo[], int nrCliente);
void modificarDomicilioCliente(char nombreArchivo[], int nrCliente);
void modificarTelefonoCliente(char nombreArchivo[], int nrCliente);
void cargaArchivoConsumosRandom(char nombreArchivo[]);
void muestraArchivoConsumo(char nombreArchivo[]);
int buscaIdClienteEnArchivo(int idCliente);
void cargarArchivoConsumoManual(char nombreArchivo[]);

int main()
{

    char archivoCliente[]= {"clientes.dat"};
    char archivoConsumo[]= {"consumos.dat"};

    stCliente clientes[DIM];
    stConsumos consumos[DIM_CONSUMOS];
    system("pause");

    int validos=0;
    int nrCliente;
    int vConsumo =0;

    char opcion;
    do
    {
        system("cls");
        muestraMenu();
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case 48:
            cargaArchivoClientes(ARCHI_CLIENTES);
            break;

        case 49:
            muestraArchivoClientes(ARCHI_CLIENTES);
            system("pause");
            break;

        case 50:
            printf("INGRE NR CLIENTE: ");
            scanf("%d", &nrCliente);
            modificarEstadoCliente(ARCHI_CLIENTES, nrCliente);
            break;

        case 51:
            printf("INGRE NR CLIENTE: ");
            scanf("%d", &nrCliente);
            mostrarClientePorNrCliente(ARCHI_CLIENTES, nrCliente);
            break;

        case 52:

            mostrarClientesActivos(ARCHI_CLIENTES);
            break;

        case 53:
            mostrarClientesInactivos(ARCHI_CLIENTES);
            break;

        case 54: ///TECLA 6
            printf("INGRE NR CLIENTE: ");
            scanf("%d", &nrCliente);
            modificarNombreCliente(ARCHI_CLIENTES, nrCliente);
            modificarTelefonoCliente(ARCHI_CLIENTES, nrCliente);
            modificarDNICliente(ARCHI_CLIENTES, nrCliente);
            modificarEmailCliente(ARCHI_CLIENTES, nrCliente);
            modificarDomicilioCliente(ARCHI_CLIENTES, nrCliente);
            break;

        case 55: ///TECLA 7
            cargaArchivoConsumosRandom(ARCHI_CONSUMOS);
            system("pause");

            break;

        case 56: ///TECLA 8
            ///cargaUnConsumoManual();
            cargarArchivoConsumoManual(ARCHI_CONSUMOS);
            system("pause");
            break;

        case 57: ///TECLA 9
            muestraArchivoConsumo(ARCHI_CONSUMOS);

            system("pause");
            break;

        }

    }
    while (opcion!=27);
    return 0;
}



void cargaArchivoClientes(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"a+b");
    stCliente clientes;
    char option=0;
    int idCliente = ultimoIdCliente(nombreArchivo);
    if (archi)
        do
        {
            system("cls");
            idCliente++;
            clientes=cargaUnCliente();
            if(buscaDniEnArchivo(archi,clientes.dni) == 0)
            {
                fopen(nombreArchivo,"a+b");
                clientes.id=idCliente;
                clientes.nroCliente=1000+idCliente;
                fwrite(&clientes,sizeof(stCliente),1,archi);
                printf("CLIENTE GUARDADO.\n");

            }
            else
            {
                printf("EL DNI YA ESTA EN USO.\n");
            }

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

void cargaArchivoConsumosRandom(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"a+b");
    stConsumos c;
    int idConsumo=ultimoIdConsumo(nombreArchivo);

    if(archi)
        for(int i=0; i<100; i++)
        {
            idConsumo++;
            c=cargaUnConsumo();
            c.id=idConsumo;
            fwrite(&c,sizeof(stConsumos),1,archi);
        }
    fclose(archi);

}


void cargarArchivoConsumoManual(char nombreArchivo[])
{

    FILE *archi=fopen(nombreArchivo, "a+b");
    stConsumos c;
    char opcion=0;

    if(archi)
    {
        do
        {
            fopen(nombreArchivo, "a+b");
            c=cargaUnConsumoManual();
            fwrite(&c,sizeof(stConsumos),1,archi);
            printf("CONSUMO GUARDADO.\n");
            printf("DESEA CARGAR OTRO CONSUMO? ESC PARA SALIR\n");
            opcion=getch();
            fclose(archi);
        }
        while(opcion!=27);
    }
}





void cargaArchivoConsumosManual(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"a+b");
    stConsumos c;
    int idConsumo=ultimoIdConsumo(nombreArchivo);
    char opcion=0;

    if(archi)
        do
        {
            idConsumo++;
            c=cargaUnConsumo();
            c.id=idConsumo;
            fwrite(&c,sizeof(stConsumos),1,archi);

            printf("DESEA CARGAR OTRO CONSUMO? ESC PARA SALIR.\n");
            opcion=getch();

        }
        while(opcion!=27);
    fclose(archi);

}

void muestraArchivoConsumo(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"rb");
    stConsumos c;

    if (archi)
    {
        while(fread(&c,sizeof(stConsumos),1,archi)>0)
        {
            muestraUnConsumo(c);
        }
        fclose(archi);
    }
}


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


int ultimoIdConsumo(char nombreArchivo[])
{
    int id = 0;
    stConsumos c;
    FILE *arch = fopen(nombreArchivo, "rb");
    if(arch)
    {
        fseek(arch, -1*sizeof(stConsumos), SEEK_END);
        if(fread(&c, sizeof(stConsumos), 1, arch)>0)
        {
            id = c.id;
        }
        fclose(arch);
    }

    return id;
}


int validaMes(int mes)
{

    int flag=0;

    if(mes>=1 && mes<=12)
    {
        flag=1;
    }

    if(flag==0)
    {
        printf("MES INCORRECTO\n");
    }

    return flag;
}

int validaDia(int mes, int dia)
{
    int flag=0;

    if(mes==2)
    {
        if(dia>=1 && dia<=28)
        {
            flag=1;
        }

    }
    else if(mes == 1 ||mes == 3||mes == 5 ||mes == 7 ||mes == 8||mes == 10||mes == 12 )
    {
        if(dia>=1 && dia<=31)
        {
            flag=1;
        }
    }
    else
    {
        if(dia>=1 && dia<=30)
        {
            flag=1;
        }
    }

    if(flag==0)
    {
        printf("DIA INCORRECTO\n");
    }

    return flag;
}


int validaAnio(int anio)
{
    int flag=0;

    if(anio>=2000 && anio<=2022)
    {
        flag=1;
    }

    if(flag==0)
    {
        printf("ANIO INCORRECTO\n");
    }

    return flag;
}


int validaConsumo(int consumo)
{
    int flag=0;

    if(consumo>0)
    {
        flag=1;
    }
    if(flag==0)
    {
        printf("CONUSMO INCORRECTO\n");
    }
    return flag;
}

void getNombre(char n[])
{
    char nombres[][20]= {"Pedro", "Pablo", "Ana"};
    strcpy(n, nombres[rand()%(sizeof(nombres)/20)]);
}

void muestraMenu()
{
    printf("\n");
    color(10);
    replicaChar('=',100);
    printf("\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<MENU CLIENTES>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    color(3);
    printf("\n 0 - Carga de un cliente.");
    printf("\n 1 - Mostrar registro de clientes.");
    printf("\n 2 - Modificar STATUS.");
    printf("\n 3 - Buscar un cliente");
    printf("\n 4 - Muestra clientes ACTIVOS.");
    printf("\n 5 - Muestra clientes INACTIVOS.");
    printf("\n 6 - MODIFICAR NOMBRE Y APELLIDO");
    printf("\n 7 - CARGA 100 CONSUMOS");
    printf("\n 8 -  ");
    printf("\n 9 - MUESTRA ARCHIVO CONSUMOS\n ");
    color(10);
    replicaChar('=',100);


}

void replicaChar(char c, int cant)
{
    for(int i=0; i<cant; i++)
    {
        printf("%c",c);
    }
}



int buscaDniEnArchivo(FILE *archi, char dni[])
{
    stCliente e;
    int flag =0;
    rewind(archi);


    if(archi)
    {
        while(flag ==0 && fread(&e, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmp(e.dni,dni)==0)
            {
                flag=1;
            }
        }
        fclose(archi);
    }
    return flag;
}

int buscaIdClienteEnArchivo(int idCliente)
{
    stConsumos c;
    int flag =0;

    FILE *archi=fopen(ARCHI_CONSUMOS,"rb");


    if(archi)
    {
        while(flag ==0 && fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            if(c.idCliente==idCliente)
            {
                flag=1;
            }
        }
        fclose(archi);
    }
    return flag;
}


void modificarEstadoCliente(char nombreArchivo[],int nrCliente)
{

    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {

                if(e.eliminado==1)
                {
                    e.eliminado=0;
                }
                else if(e.eliminado==0)
                {
                    e.eliminado=1;
                }
                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE MODIFICO EL STATUS DEL CLIENTE.\n\n");
                system("pause");

                existe=1;
                break;

            }
            fread(&e, sizeof(stCliente), 1, archi);

        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);

    }
}


void mostrarClientePorNrCliente(char nombreArchivo[],int nrCliente)
{

    FILE *archi=fopen(nombreArchivo, "rb");
    stCliente e;
    int existe=0;
    int flag=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi) && flag==0)
        {
            if (nrCliente==e.nroCliente)
            {
                int pos=ftell(archi)-sizeof(stCliente);
                fseek(archi,pos,SEEK_SET);
                muestraUnCliente(e);
                existe=1;
                flag=1;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void mostrarClientesActivos(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"rb");
    stCliente c;

    if (archi)
    {
        while(fread(&c,sizeof(stCliente),1,archi)>0)
        {
            if(c.eliminado==0)
            {
                muestraUnCliente(c);
            }
        }
        fclose(archi);
        system("pause");

    }
}


void mostrarClientesInactivos(char nombreArchivo[])
{
    FILE *archi=fopen(nombreArchivo,"rb");
    stCliente c;

    if (archi)
    {
        while(fread(&c,sizeof(stCliente),1,archi)>0)
        {
            if(c.eliminado==1)
            {
                muestraUnCliente(c);
            }
        }
        fclose(archi);
        system("pause");

    }
}


void modificarNombreCliente(char nombreArchivo[], int nrCliente)
{
    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {
                printf("INGRESE NUEVO NOMBRE: ");
                fflush(stdin);
                gets(e.nombre);
                printf("INGRESE NUEVO APELLIDO: ");
                fflush(stdin);
                gets(e.apellido);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarDNICliente(char nombreArchivo[], int nrCliente)
{
    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {
                printf("INGRESE NUEVO DNI: ");
                fflush(stdin);
                gets(e.dni);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarEmailCliente(char nombreArchivo[], int nrCliente)
{
    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {
                printf("INGRESE NUEVO EMAIL: ");
                fflush(stdin);
                gets(e.email);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarTelefonoCliente(char nombreArchivo[], int nrCliente)
{
    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {
                printf("INGRESE NUEVO Nr DE TELEFONO: ");
                fflush(stdin);
                gets(e.movil);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarDomicilioCliente(char nombreArchivo[], int nrCliente)
{
    FILE *archi=fopen(nombreArchivo, "r+b");
    stCliente e;
    int existe=0;

    if(archi)
    {
        fread(&e, sizeof(stCliente), 1, archi);
        while(!feof(archi))
        {
            if (nrCliente==e.nroCliente)
            {
                printf("INGRESE NUEVA DIRECCION: ");
                fflush(stdin);
                gets(e.domicilio);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("SE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}
