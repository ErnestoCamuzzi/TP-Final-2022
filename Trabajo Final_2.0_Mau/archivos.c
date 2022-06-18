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
        fread(&c, sizeof(stCliente), 1, arch);

        id = c.id;

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



void modificarEstadoConsumo(char nombreArchivo[], int idConsumo)
{

    FILE *archi=fopen(nombreArchivo, "r+b");
    stConsumos c;
    int existe=0;

    if(archi)
    {
        fread(&c, sizeof(stConsumos), 1, archi);
        while(!feof(archi))
        {
            if (idConsumo==c.id)
            {

                if(c.baja==1)
                {
                    c.baja=0;
                }
                else if(c.baja==0)
                {
                    c.baja=1;
                }
                int pos=ftell(archi)-sizeof(stConsumos); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&c, sizeof(stConsumos), 1, archi);
                printf("SE MODIFICO EL STATUS DEL CONSUMO.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("NO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarDatosConsumos(char nombreArchivo[], int idConsumo)
{

    FILE *archi=fopen(nombreArchivo, "r+b");
    stConsumos c;
    int existe=0;

    if(archi)
    {
        fread(&c, sizeof(stConsumos), 1, archi);
        while(!feof(archi))
        {
            if (idConsumo==c.id)
            {

                if(c.baja==1)
                {
                    c.baja=0;
                }
                else if(c.baja==0)
                {
                    c.baja=1;
                }
                int pos=ftell(archi)-sizeof(stConsumos); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&c, sizeof(stConsumos), 1, archi);
                printf("SE MODIFICO EL STATUS DEL CONSUMO.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("NO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }
}


void mostrarConsumoPorIdConsumo(char nombreArchivo[],int idConsumo)
{

    FILE *archi=fopen(nombreArchivo, "rb");
    stConsumos c;
    int existe=0;
    int flag=0;

    if(archi)
    {
        fread(&c, sizeof(stConsumos), 1, archi);
        while(!feof(archi) && flag==0)
        {
            if (idConsumo==c.id)
            {
                int pos=ftell(archi)-sizeof(stConsumos);
                fseek(archi,pos,SEEK_SET);
                muestraUnConsumo(c);
                existe=1;
                flag=1;
            }
            fread(&c, sizeof(stConsumos), 1, archi);
        }
        if (existe==0)
            printf("NO EXISTE ESE ID DE CONSUMO.\n");
        system("pause");
        fclose(archi);
    }
}


void modificarConsumo(char nombreArchivo[], int idConsumo, int nuevoConsumo)
{

    FILE *archi=fopen(nombreArchivo, "r+b");
    stConsumos c;
    int existe=0;

    if(archi)
    {
        fread(&c, sizeof(stConsumos), 1, archi);
        while(!feof(archi))
        {
            if (idConsumo==c.id)
            {

                c.datosConsumidos=nuevoConsumo;
                int pos=ftell(archi)-sizeof(stConsumos);
                fseek(archi,pos,SEEK_SET);
                fwrite(&c, sizeof(stConsumos), 1, archi);
                printf("SE MODIFICO LA CANTIDAD CONSUMIDA.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("NO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }
}



void modificarFechaConsumo(char nombreArchivo[], int idConsumo, int dia, int mes, int anio)
{

    FILE *archi=fopen(nombreArchivo, "r+b");
    stConsumos c;
    int existe=0;

    fread(&c, sizeof(stConsumos), 1, archi);
        while(!feof(archi))
        {
            if (idConsumo==c.id)
            {
                c.dia=dia;
                c.mes=mes;
                c.anio=anio;



                int pos=ftell(archi)-sizeof(stConsumos);
                fseek(archi,pos,SEEK_SET);
                fwrite(&c, sizeof(stConsumos), 1, archi);
                printf("SE MODIFICO LA FECHA DEL CONSUMO.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("NO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }


void muestraConsumosCliente(char nombreArchivo[], int idCliente){
    FILE *archi=fopen(nombreArchivo,"r+b");
    stConsumos c;
    int flag=0;

    if (archi)
    {
        while(fread(&c,sizeof(stConsumos),1,archi)>0)
        {
            if(idCliente==c.idCliente){
            flag=1;
            muestraUnConsumo(c);
        }
        }
        fclose(archi);
    }
    if (flag==0){
        printf("\nNO EXISTE CLIENTE CON ESE NUMERO\n ");
    }
}

void mostrarPorFecha(char nombreArchivo[]) {
    stConsumos fecha;
    stConsumos a;
    int flag=0;
    system("cls");

    printf(" Ingrese la Fecha a Buscar Consumos \n");
    printf("\n ingrese el a%co\n",164);
    scanf("\n %d", &fecha.anio);
    printf("\n ingrese el mes\n");
    scanf("\n %d", &fecha.mes);
    printf("\n ingrese un dia\n");
    scanf("\n %d", &fecha.dia);

    FILE *archi=fopen (nombreArchivo, "rb");
    if (archi) {
        while (fread(&a, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia){
                muestraUnConsumo(a);
                flag=1;
            }
        }
        fclose(archi);
    }
     if (flag==0){
        printf("\nEn la Fecha Ingresada No Existen Consumos\n");
     }
}




