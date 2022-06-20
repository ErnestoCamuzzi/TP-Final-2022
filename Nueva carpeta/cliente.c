#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define DIM 100
#define ESC 27

stCliente cargaUnCliente()
{/** \brief  carga un solo cliente
 *
 * \param no recibe
 * \return  retorna un cliente de tipo stCliente.
 *
 */
    stCliente c;
    int dni;

    printf("\n\t\t\t\t\t==========================\n");
    printf("\n\t\t\t\t\tCARGA CLIENTE\n");
    printf("\n\t\t\t\t\t==========================\n\n\n");
    fflush(stdin);
    printf("\n\t\t\t\t\tDni.............: ");
    gets(c.dni);
    fflush(stdin);
    printf("\n\t\t\t\t\tApellido........: ");
    gets(c.apellido);

    fflush(stdin);
    printf("\n\t\t\t\t\tNombre..........: ");
    gets(c.nombre);

    do{
    printf("\n\t\t\t\t\tE-Mail..........: ");
    gets(c.email);
    if ((strchr(c.email, 64)==0)){
        printf("\nFomato incorrecto\n");
    }
    }while (strchr(c.email, 64)==0);

    fflush(stdin);
    printf("\n\t\t\t\t\tDomicilio.......: ");
    gets(c.domicilio);

    fflush(stdin);
    printf("\n\t\t\t\t\tTelefono movil..: ");
    gets(c.movil);

    c.eliminado = 0; /// si está en cero está activo por defecto.
    ///  Para eliminar se le asigna valor 1 desde el menu

    return c;
}

void muestraUnCliente(stCliente c)
{ /** \brief Imprime en pantalla datos de cliente y además informa si está activo o no
   *
   * \param recibe un dato de tipo stCliente
   * \return no retorna nada
   *
   */
    printf("\n\t\t\t\t\tID.................: %d", c.id);
    printf("\n\t\t\t\t\tN* de cliente......: %d", c.nroCliente);
    printf("\n\t\t\t\t\tApellido y Nombres.: %s, %s",c.apellido, c.nombre);
    printf("\n\t\t\t\t\tDNI................: %s", c.dni);
    printf("\n\t\t\t\t\tE-mail.............: %s", c.email);
    printf("\n\t\t\t\t\tDomicilio..........: %s", c.domicilio);
    printf("\n\t\t\t\t\tMovil..............: %s", c.movil);

    if(c.eliminado == 0)
    {
        printf("\n\t\t\t\t\tCLIENTE ACTIVO.\n\n");
    }
    else
    {
        printf("\n\t\t\t\t\tCLIENTE INACTIVO.\n\n");
    }
    printf("\n\t\t\t\t\t===================================================");

}
printf

