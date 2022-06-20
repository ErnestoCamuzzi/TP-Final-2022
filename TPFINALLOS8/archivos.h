#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

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
void muestraConsumosCliente(char nombreArchivo[], int idCliente);
void mostrarPorFecha(char nombreArchivo[]);
void modificarEstadoConsumo(char nombreArchivo[], int idConsumo);
void mostrarConsumoPorIdConsumo(char nombreArchivo[],int idConsumo);
void modificarConsumo(char nombreArchivo[], int idConsumo, int nuevoConsumo);
void modificarFechaConsumo(char nombreArchivo[], int idConsumo, int dia, int mes, int anio);
int ultimoIdCliente(char nombreArchivo[]);

#endif // ARCHIVOS_H_INCLUDED
