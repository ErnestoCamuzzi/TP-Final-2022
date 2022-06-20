#include "consumo.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ESC 27
#define ARCHI_CONSUMOS "consumos.dat"

int generaMesRandom()
{/** \brief esta función genera un mes de forma aleatoria
 *
 * \return Retorna el mes creado.
 *
 */
    int mesRandom=0;

    mesRandom=rand()%6+1;

    return mesRandom;
}
int generaDiaRandom(int mes)
{/** \brief esta función genera un dia de forma aleatoria
 *
 * \param recibe por parámetro el mes para el cual queremos generar el día aleatorio.
 * \return devuelve el día creado.
 *
 */
    int diaRandom=0;

    if(mes==2)
    {
        diaRandom=rand()%28+1;
    }
    else if(mes == 1 ||mes == 3||mes == 5)
    {
        diaRandom=rand()%31+1;
    }
    else if(mes==4)
    {
        diaRandom=rand()%30+1;

    }
    else
    {

        diaRandom=rand()%21+1;

    }

    return diaRandom;
}
stConsumos cargaUnConsumo()
{/** \brief Imputa un consumo diario de un cliente
 *
 * \return devuelve un dato de tipo stConsumos
 *
 */
    stConsumos c;
    c.idCliente=rand()%54+4;
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
stConsumos cargaUnConsumoManual()
{/** \brief Imputa un consumo diario (de forma manual)a un cliente.
 *
 * \return devuelve un dato de tipo stConsumo
 *
 */
    stConsumos c;
    int dato;
    int control=0;
    char opcion=0;
    int ultimoID=ultimoIdConsumo(ARCHI_CONSUMOS);

    do
    {
        ultimoID++;
        system("cls");
        printf("\n\t\t\t\t\tINGRESE ID DE CLIENTE: ");
        scanf("%d", &dato);
        control = buscaIdClienteEnArchivo(dato);
        if(control==0)
        {
            printf("\n\t\t\t\t\tCLIENTE NO EXISTE\n");
            printf("\n\t\t\t\t\tDESEA VOLVER A INTENTAR? ESC PARA SALIR.\n");
            opcion=getch();
        }
        else
        {
            c.id=ultimoID;
            c.idCliente=dato;
            do{
                printf("\n\t\t\t\t\tINGRESE MES: ");
                scanf("%d", &c.mes);
            }
            while(validaMes(c.mes)==0);

            do{
            printf("\n\t\t\t\t\tINGRESE DIA: ");
            scanf("%d", &c.dia);
            }
            while(validaDia(c.mes, c.dia)==0);

            do{
            printf("\n\t\t\t\t\tINGRESE ANIO: ");
            scanf("%d", &c.anio);
            }
            while(validaAnio(c.anio)==0);

            do{
            printf("\n\t\t\t\t\tINGRESE DATOS CONSUMIDOS: ");
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
{/** \brief Pasa a un arreglo el consumo
 *
 * \param
 * \param
 * \return
 *
 */
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
{/** \brief imprime un consumo en pantalla
 *
 * \param recibe como parámetro un dato de tipo stConsumo
 * \return no retorna nada
 *
 */
    printf("\n\t\t\t\t\tID.................: %d", c.id);
    printf("\n\t\t\t\t\tID Cliente.........: %d", c.idCliente);
    printf("\n\t\t\t\t\tAnio...............: %d", c.anio);
    printf("\n\t\t\t\t\tMes................: %d", c.mes);
    printf("\n\t\t\t\t\tDia................: %d", c.dia);
    printf("\n\t\t\t\t\tDatos Consumidos...: %d", c.datosConsumidos);
    if(c.baja == 0)
    {
        printf("\n\t\t\t\t\tCONSUMO ACTIVO.\n\n");
    }
    else
    {
        printf("\n\t\t\t\t\tCONSUMO INACTIVO.\n\n");
    }
    printf("\n\t\t\t\t\t===================================================");
}
void muestraConsumos (stConsumos c[], int v)
{/** \brief imprime en pantalla los consumos de un arreglo de tipo stConsumos
 *
 * \param arreglo de tipo stConsumos
 * \param válidos del arreglo
 * \return no devuelve nada
 *
 */
    for(int i=0; i<v; i++)
    {
        printf("\n\t\t\t\t\tID.................: %d", c[i].id);
        printf("\n\t\t\t\t\tID Cliente.........: %d", c[i].idCliente);
        printf("\n\t\t\t\t\tAnio...............: %d", c[i].anio);
        printf("\n\t\t\t\t\tMes................: %d", c[i].mes);
        printf("\n\t\t\t\t\tDia................: %d", c[i].dia);
        printf("\n\t\t\t\t\tDatos Consumidos...: %d", c[i].datosConsumidos);
        if(c[i].baja == 0)
        {
            printf("\n\t\t\t\t\tCONSUMO ACTIVO.\n\n");
        }
        else
        {
            printf("\n\t\t\t\t\tCONSUMO INACTIVO.\n\n");
        }
        printf("\n\t\t\t\t\t===================================================");
    }
}
int validaMes(int mes)
{/** \brief verifica que el entero ingresado se corresponda a uno de los meses del año.
 *
 * \param se pasa por parámetro el número de mes.
 * \return devuelve 0 si el dato ingresado NO corresponde a un mes, y 1 si corresponde.
 *
 */

    int flag=0;

    if(mes>=1 && mes<=12)
    {
        flag=1;
    }

    if(flag==0)
    {
        printf("\n\t\t\t\t\tMES INCORRECTO\n");
    }

    return flag;
}
int validaDia(int mes, int dia)
 {/** \brief valida que el entero ingresado se corresponda a una fecha determinada.
 *
 * \param el mes del día a verificar.
 * \param el día a verificar.
 * \return devuelve 0 si el dato ingresado NO corresponde a un día del mes, 1 si corresponde.
 *
 */
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
        printf("\n\t\t\t\t\tDIA INCORRECTO\n");
    }

    return flag;
}
int validaAnio(int anio)
{/** \brief Verifica que el año ingresado se encuentre dentro de un parámetro.
     *
     * \param dato de tipo entero que refiere al año a verificar.
     * \return devuelve 0 si el dato no se encuentra dentro del parámetro,1 si está ok.
     *
     */

    int flag=0;

    if(anio>=2000 && anio<=2022)
    {
        flag=1;
    }

    if(flag==0)
    {
        printf("\n\t\t\t\t\tA%cIO INCORRECTO\n",165);
    }

    return flag;
}
int validaConsumo(int consumo)
{/** \brief verifica que el dato de tipo entero ingresado sea mayor a 0
 *
 * \param dato de tipo entero
 * \return devuelve 0 si el dato ingresado es menor o igual a 0 1 si es mayor.
 *
 */
    int flag=0;

    if(consumo>0)
    {
        flag=1;
    }
    if(flag==0)
    {
        printf("\n\t\t\t\t\tCONUSMO INCORRECTO\n");
    }
    return flag;
}

int sumaConsumoPorFecha(char nombreArchivo[], int dia, int mes, int anio)
{/** \brief Suma el consumo total de todos los clientes por fecha.
     *
     * \param el archivo de consumos
     * \param el día, mes y año a consultar.
     * \return devuelve el total de los datos consumidos.
     *
     */

    stConsumos fecha;
    int i=0;
    FILE *archi=fopen (nombreArchivo, "r+b");
    if (archi) {
        while (fread(&fecha, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== anio && fecha.mes==mes && fecha.dia ==dia){
                i=fecha.datosConsumidos+i;
                }
            }
            fclose(archi);
    }
    return i;
}


