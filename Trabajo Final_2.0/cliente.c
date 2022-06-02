#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define DIM 100
#define ESC 27



stCliente cargaUnCliente(){

    stCliente c;


    printf("N° Cliente.......:");
    scanf("%d", &c.nroCliente);

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

    c.eliminado = 0; /// si está en cero está activo por defecto.
    ///  Para eliminar se le asigna valor 1 desde el menu

    return c;
}


void muestraUnCliente(stCliente c) /// Imprime en pantalla datos de cliente y además informa si está activo o no
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

int cargaArregloCliente(stCliente e[], int dim){
    char opcion = 0;
    int i = 0;

    while(i<dim && opcion != ESC){
        system("cls");
        e[i] = cargaUnCliente();
        i++;

        printf("\n ESC para salir o cualquier tecla para continuar ");
        opcion = getch();
    }

    return i;
}
