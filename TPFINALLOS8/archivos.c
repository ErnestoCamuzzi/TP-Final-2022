#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include <string.h>
#include "gotoxy.h"
#include <time.h>


#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CONSUMOS "consumos.dat"


void cargaArchivoClientes(char nombreArchivo[])
{/** \brief carga un archivo de clientes, se verifica con el dni que no est� cargado ya el cliente.
     *
     * \param archivo de clientes
     *\return no retorna nada.
     *
     */

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
                printf("\n\t\t\t\t\tCLIENTE GUARDADO.\n");

            }
            else
            {
                printf("\n\t\t\t\t\tEL DNI YA ESTA EN USO.\n");
            }

            printf("\n\t\t\t\t\tSi desea salir presione ESC\n");
            option=getch();
        }
        while(option!=27);
    fclose(archi);
}
void muestraArchivoClientes(char nombreArchivo[])
{/** \brief imprime por consola el archivo de clientes.
     *
     * \param el archivo a mostrar
     * \return no devuelve nada.
     *
     */

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
{/** \brief carga consumos aleatorios.
     *
     * \param el archivo de consumos
     * \return no retorna nada
     *
     */

    FILE *archi=fopen(nombreArchivo,"a+b");
    stConsumos c;
    int datos=0;
    srand(time(NULL));
    int random=0;
    int pos=0;
    int idConsumo=ultimoIdConsumo(nombreArchivo);

    if(archi)
    {
        for(int i=0; i<100; i++)
        {
            c.idCliente=rand()%54+4;
            c.anio=2022;
            c.mes=generaMesRandom();
            c.dia=generaDiaRandom(c.mes);
            c.datosConsumidos=rand()%1000+1;
            c.baja = 0;

            pos=retornaPosConsumo(nombreArchivo, c);

            if(pos==-1)
            {
                    fseek(archi,0,SEEK_END);
                    fwrite(&c,sizeof(stConsumos),1,archi);
                    idConsumo++;
                    c.id=idConsumo;
            }
                else
                {
                    modificaConsumoExistente(nombreArchivo,c.datosConsumidos,pos);

                }
            }

        }
        fclose(archi);

    }
int retornaPosConsumo(char nombreArchivo[],stConsumos c)
{/** \brief Esta funci�n nos indica la posici�n de un consumo en el archivo.
 *
 * \param el archivo a consultar.
 * \param un dato de tipo stConsumo.
 * \return dato de tipo entero que indica la posici�n de un consumo.
 *
 */

    FILE *archi=fopen(nombreArchivo,"rb");
    rewind(archi);
    stConsumos aux;
    int pos=-1;

    if(archi)
    {
        while(fread(&aux,sizeof(stConsumos),1,archi)>0 && pos==-1)
        {
            if(c.anio==aux.anio && c.dia==aux.dia && c.mes==aux.mes && c.idCliente==aux.idCliente)
            {
                pos=ftell(archi)-sizeof(stConsumos);
            }
        }
        fclose(archi);
    }

    return pos;
}
void modificaConsumoExistente(char nombreArchivo[], int nuevoConsumo, int pos)
{/** \brief Suma el consumo ingresado por par�metro al existente en un archivo.
 *
 * \param archivo de consumo a modificar
 * \param el nuevo consumo y la posici�n del consumo a modificar.
 * \return no retorna nada.
 *
 */
    FILE *archi=fopen(nombreArchivo, "r+b");
    stConsumos c;

    fseek(archi,pos, SEEK_SET);

    fread(&c, sizeof(stConsumos), 1, archi);
    c.datosConsumidos = c.datosConsumidos + nuevoConsumo;
    fseek(archi,sizeof(stConsumos)*-1, SEEK_CUR);
    fwrite(&c, sizeof(stConsumos), 1, archi);
    fclose(archi);
}
void cargarArchivoConsumoManual(char nombreArchivo[])
{/** \brief Esta funci�n registra un consumo manual en un archivo imput�ndolo a un cliente en una fecha determinada.
     *
     * \param se pasa el archivo en el cual se carga el consumo.
     * \return No retorna nada.
     *
     */

    FILE *archi=fopen(nombreArchivo, "a+b");
    stConsumos c;
    char opcion=0;
    int datos=0;
    int idConsumo=ultimoIdConsumo(nombreArchivo);

    if(archi)
    {
        do
        {
            c=cargaUnConsumoManual();
            int pos=retornaPosConsumo(nombreArchivo, c);

            if(pos ==-1)
            {
                fseek(archi,0,SEEK_END);
                idConsumo++;
                c.id=idConsumo;
                fwrite(&c,sizeof(stConsumos),1,archi);
            }
            else
            {
                modificaConsumoExistente(nombreArchivo,c.datosConsumidos,pos);
            }


            printf("\n\t\t\t\t\tDESEA CARGAR OTRO CONSUMO? ESC PARA SALIR\n");
            opcion=getch();
            fclose(archi);
        }
        while(opcion!=27);
    }
}
void muestraArchivoConsumo(char nombreArchivo[])
{/** \brief imprime por pantalla un archivo.
     *
     * \param el archivo a mostrar
     * \return no retorna nada
     *
     */

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
{/** \brief Esta funcion devuelve el id del cliente en la �ltima posici�n del archivo.
     *
     * \param el archivo donde se guardan los clientes.
     * \return el �ltimo id del cliente.
     *
     */

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
{/** \brief Esta funcion devuelve el id del consumo en la �ltima posici�n del archivo.
 *
 * \param Se pasa el archivo de consumos.
 * \return La �ltima posici�n del id del consumo.
 *
 */
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
{/** \brief Esta funci�n verifica si el dato ingresado existe o no en el archivo de clientes.
     *
     * \param Se pasa la direcci�n de memoria del archivo a consultar.
     * \param Se pasa el dato del dni a buscar en el archivo.
     * \return Devuelve un 1 si el dni existe en el archivo o un 0 si no existe.
     *
     */

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
{/** \brief Esta funci�n verifica si el dato ingresado existe o no en el archivo de clientes.
     *
     * \param Se pasa el id del cliente a verificar.
     * \return Devuelve 1 si el id existe en el archivo o 0 si no existe.
     *
     */

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
{/** \brief Esta funci�n cambia el estado (activo/inactivo) de un cliente en el archivo.
 *
 * \param recibe archivo donde se encuentra cargado el nro del cliente.
 * \param recibe el n�mero del cliente que se quiere modificar el estado.
 * \return No devuelve nada.
 *
 */

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
                ///system("pause");

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
{/** \brief Imprime por pantalla los datos de un cliente.
     *
     * \param Recibe el archivo de clientes.
     * \param Recibe el n�mero de cliente a mostrar.
     * \return No devuelve nada.
     *
     */


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
{/** \brief Esta funci�n muestra por pantalla un listado de todos los clientes activos.
     *
     * \param Recibe el archivo de clientes.
     * \return No retorna nada.
     *
     */

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
{/** \brief Esta funcion muestra por pantalla el listado de clientes inactivos.
     *
     * \param Recibe el archivo de clientes.
     * \return No retorna nada.
     *
     */

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
{/** \brief Esta funci�n cambia el nombre y apellido de un cliente.
     *
     * \param Recibe el archivo de clientes.
     * \param Recibe el n�mero del cliente a modificar.
     * \return No devuelve nada.
     *
     */

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
                printf("\n\t\t\t\t\tINGRESE NUEVO NOMBRE: ");
                fflush(stdin);
                gets(e.nombre);
                printf("\n\t\t\t\t\tINGRESE NUEVO APELLIDO: ");
                fflush(stdin);
                gets(e.apellido);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("\n\t\t\t\t\tSE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}
void modificarDNICliente(char nombreArchivo[], int nrCliente)
{/** \brief Esta funcion cambia el dni de un cliente.
 *
 * \param Recibe el archivo de clientes.
 * \param Recibe el n�mero del cliente a modificar.
 * \return No retorna nada.
 *
 */
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
                printf("\n\t\t\t\t\tINGRESE NUEVO DNI: ");
                fflush(stdin);
                gets(e.dni);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("\n\t\t\t\t\tSE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                ///system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarEmailCliente(char nombreArchivo[], int nrCliente)
{/** \brief Esta funcion cambia el mail de un cliente.
 *
 * \param recibe archivo de clientes.
 * \param recibe el n�mero del cliente a modificar.
 * \return no retorna nada.
 *
 */
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
                printf("\n\t\t\t\t\tINGRESE NUEVO EMAIL: ");
                fflush(stdin);
                gets(e.email);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("\n\t\t\t\t\tSE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                ///system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarTelefonoCliente(char nombreArchivo[], int nrCliente)
{/** \brief Cambia el n�mero de tel�fono de un cliente.
     *
     * \param Recibe el archivo de clientes.
     * \param Recibe el n�mero de cliente a modificar.
     * \return No retorna nada.
     *
     */

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
                printf("\n\t\t\t\t\tINGRESE NUEVO Nr DE TELEFONO: ");
                fflush(stdin);
                gets(e.movil);

                int pos=ftell(archi)-sizeof(stCliente);
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("\n\t\t\t\t\tSE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                ///system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarDomicilioCliente(char nombreArchivo[], int nrCliente)
{/** \brief Esta funci�n cambia el domicilio de un cliente.
     *
     * \param Archivo de clientes.
     * \param n�mero del cliente a modificar.
     * \return No retorna nada.
     *
     */

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
                printf("\n\t\t\t\t\tINGRESE NUEVA DIRECCION: ");
                fflush(stdin);
                gets(e.domicilio);

                int pos=ftell(archi)-sizeof(stCliente); /// pasar a dividir
                fseek(archi,pos,SEEK_SET);
                fwrite(&e, sizeof(stCliente), 1, archi);
                printf("\n\t\t\t\t\tSE ACTUALIZO EL DATO DE CLIENTE.\n\n");
                ///system("pause");
                existe=1;
                break;
            }
            fread(&e, sizeof(stCliente), 1, archi);
        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE NR DE CLIENTE.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarEstadoConsumo(char nombreArchivo[], int idConsumo)
{/** \brief Esta funci�n cambia el estado (baja/alta) de un consumo.
     *
     * \param Arhivo de consumos
     * \param id del consumo a modificar.
     * \return no retorna nada.
     *
     */


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
                printf("\n\t\t\t\t\tSE MODIFICO EL STATUS DEL CONSUMO.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }
}

void mostrarConsumoPorIdConsumo(char nombreArchivo[],int idConsumo)
{/** \brief Imprime por pantalla el consumo de un idconsumo.
     *
     * \param Recibe el archivo de consumos.
     * \param Recibe el id del consumo a mostrar.
     * \return No retorna nada
     *
     */


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
            printf("\n\t\t\t\t\tNO EXISTE ESE ID DE CONSUMO.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarConsumo(char nombreArchivo[], int idConsumo, int nuevoConsumo)
{/** \brief Cambia el valor de un consumo.
     *
     * \param recibe el archivo de consumos.
     * \param Recibe el id del consumo a modificar
     *\param Recibe el nuevo valor del consumo.
     * \return No retorna nada.
     *
     */

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
                printf("\n\t\t\t\t\tSE MODIFICO LA CANTIDAD CONSUMIDA.\n\n");

                existe=1;
                break;

            }
            fread(&c, sizeof(stConsumos), 1, archi);

        }
        if (existe==0)
            printf("\n\t\t\t\t\tNO EXISTE ESE ID DE CONUSMO.\n");
        system("pause");
        fclose(archi);
    }
}

void modificarFechaConsumo(char nombreArchivo[], int idConsumo, int dia, int mes, int anio)
{/** \brief Esta funcion cambia la fecha de un consumo.
 *
 * \param Recibe el archivo de consumos, el id del consumo a modificar y la nueva fecha del consumo.
 * \return No devuelve nada
 *
 */

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
            printf("\n\t\t\t\t\tSE MODIFICO LA FECHA DEL CONSUMO.\n\n");

            existe=1;
            break;

        }
        fread(&c, sizeof(stConsumos), 1, archi);

    }
    if (existe==0)
        printf("\n\t\t\t\t\tNO EXISTE ESE ID DE CONUSMO.\n");
    system("pause");
    fclose(archi);
}

void muestraConsumosCliente(char nombreArchivo[], int idCliente)
{/** \brief  Imprime por consola todos los consumos de un cliente.
 *
 * \param Recibe el archivo de consumos.
 * \param Recibe el id del cliente a consultar.
 * \return No retorna nada.
 *
 */
    FILE *archi=fopen(nombreArchivo,"r+b");
    stConsumos c;
    int flag=0;

    if (archi)
    {
        while(fread(&c,sizeof(stConsumos),1,archi)>0)
        {
            if(idCliente==c.idCliente)
            {
                flag=1;
                muestraUnConsumo(c);
            }
        }
        fclose(archi);
    }
    if (flag==0)
    {
        printf("\n\t\t\t\t\tNO EXISTE CLIENTE CON ESE NUMERO\n ");
    }
}

void mostrarPorFecha(char nombreArchivo[])
{/** \brief Esta funci�n imprime por pantalla todos los consumos de una fecha.
     *
     * \param Recibe archivo de consumos.
     * \return No devuelve nada.
     *
     */

    stConsumos fecha;
    stConsumos a;
    int flag=0;
    system("cls");

    printf("\n\t\t\t\t\tIngrese la fecha a buscar consumos \n");
    printf("\n\t\t\t\t\tIngrese el a%co\n",164);
    scanf("%d", &fecha.anio);
    printf("\n\t\t\t\t\tIngrese el mes\n");
    scanf(" %d", &fecha.mes);
    printf("\n\t\t\t\t\tIngrese un dia\n");
    scanf(" %d", &fecha.dia);

    FILE *archi=fopen (nombreArchivo, "rb");
    if (archi)
    {
        while (fread(&a, sizeof(stConsumos), 1, archi)>0)
        {
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia)
            {
                muestraUnConsumo(a);
                flag=1;
            }
        }
        fclose(archi);
    }
    if (flag==0)
    {
        printf("\n\t\t\t\t\tEn la fecha ingresada NO existen consumos\n");
    }
}
