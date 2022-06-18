#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "cliente.h"
#include "consumo.h"
#include "archivos.h"
#include "menu.h"
#include <string.h>
#include "gotoxy.h"

#define DIM 100
#define DIM_CONSUMOS 10
#define ESC 27
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CONSUMOS "consumos.dat"



int main()
{

    char archivoCliente[]= {"clientes.dat"};
    char archivoConsumo[]= {"consumos.dat"};

    stCliente clientes[DIM];
    stConsumos consumos[DIM_CONSUMOS];

    int validos=0;
    int nrCliente;
    int vConsumo =0;
    int idConsumo=0;
    int nuevoConsumo=0;
    int nuevoDia=0;
    int nuevoMes=0;
    int nuevoAnio=0;

    char opcion;
    int opcionCliente;
    int opcionConsumo;
    int opcionModificaCliente;
    do
    {
        system("cls");
        muestraMenu();
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case 48: ///TECLA 0
            opcionCliente=MenuCliente();
            switch (opcionCliente)
            {
            case 48: ///TECLA 0
                cargaArchivoClientes(ARCHI_CLIENTES);
                system("pause");
                break;
            case 49: ///TECLA 1
                muestraArchivoClientes(ARCHI_CLIENTES);
                system("pause");
                break;
            case 50: ///TECLA 2
                printf("INGRE NR CLIENTE: ");
                scanf("%d", &nrCliente);
                modificarEstadoCliente(ARCHI_CLIENTES, nrCliente);
                break;

            case 51: ///TECLA 3
                printf("INGRE NR CLIENTE: ");
                scanf("%d", &nrCliente);
                mostrarClientePorNrCliente(ARCHI_CLIENTES, nrCliente);
                break;

            case 52: ///TECLA 4
                mostrarClientesActivos(ARCHI_CLIENTES);
                break;

            case 53: ///TECLA 5
                mostrarClientesInactivos(ARCHI_CLIENTES);
                break;

            case 54: ///TECLA 6
                opcionModificaCliente=MenuModificarCliente();
                switch(opcionModificaCliente)
                {

                case 48:
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarNombreCliente(ARCHI_CLIENTES, nrCliente);
                    break;
                case 49:
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarTelefonoCliente(ARCHI_CLIENTES, nrCliente);
                    break;
                case 50:
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarDNICliente(ARCHI_CLIENTES, nrCliente);
                    break;
                case 51:
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarEmailCliente(ARCHI_CLIENTES, nrCliente);
                    break;
                case 52:
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarDomicilioCliente(ARCHI_CLIENTES, nrCliente);
                    break;
                case 53:
                    ///system("cls");
                    printf("INGRESE UN NUMERO DE CLIENTE: ");
                    scanf("%d", &nrCliente);
                    modificarEstadoCliente(ARCHI_CLIENTES, nrCliente);
                    break;
                }
                break;
            }
            break;
        case 49:
            opcionConsumo=MenuConsumo();
            switch (opcionConsumo)
            {
            case 48: ///TECLA 0
                cargaArchivoConsumosRandom(ARCHI_CONSUMOS);
                system("pause");
                break;

            case 49: ///TECLA 1
                cargarArchivoConsumoManual(ARCHI_CONSUMOS);
                system("pause");
                break;

            case 50: ///TECLA 2
                muestraArchivoConsumo(ARCHI_CONSUMOS);
                system("pause");
                break;

            case 51: ///tecla 3
                printf("\n\nINGRESE ID CONSUMO A MODIFICAR: ");
                scanf("%d", &idConsumo);
                modificarEstadoConsumo(ARCHI_CONSUMOS, idConsumo);
                break;

            case 52: ///tecla 4
                printf("\n\nINGRESE ID CONSUMO A MOSTRAR: ");
                scanf("%d", &idConsumo);
                mostrarConsumoPorIdConsumo(ARCHI_CONSUMOS, idConsumo);
                break;

            case 53:
                ///system("cls");
                printf("\nINGRESE ID DE CONSUMO A MODIFICAR ");
                scanf("%d", &idConsumo);
                printf("\nINGRESE NUEVO CONSUMO: ");
                scanf("%d", &nuevoConsumo);
                modificarConsumo(ARCHI_CONSUMOS,idConsumo,nuevoConsumo);
                break;

        case 54:
            ///system("cls");
            printf("\nINGRESE ID DE CONSUMO A MODIFICAR ");
            scanf("%d", &idConsumo);
            do{
            system("cls");
            printf("\nINGRESE DIA: ");
            scanf("%d", &nuevoDia);
            printf("\nINGRESE MES: ");
            scanf("%d", &nuevoMes);
            printf("\nINGRESE ANIO: ");
            scanf("%d", &nuevoAnio);
            }while(validaDia(nuevoMes,nuevoDia)==0 || validaMes(nuevoMes)==0 || validaAnio(nuevoAnio)==0);
            system("pause");
            modificarFechaConsumo(ARCHI_CONSUMOS,idConsumo,nuevoDia,nuevoMes,nuevoAnio);
            break;

        case 55:
            printf("\nINGRESE EL NRO DEL CLIENTE ");
            scanf("%d", &nrCliente);
            muestraConsumosCliente(ARCHI_CONSUMOS, nrCliente);
            system("pause");

        case 56:
            mostrarPorFecha(archivoConsumo);
           // system("cls");
            system("pause");

        }

    }
}



while (opcion!=27);
return 0;
}













