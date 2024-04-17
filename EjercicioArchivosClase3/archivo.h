#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ColaEstatica/cola.h"

#define FILE_ERR -1
#define FILE_OPEN_MODE_ERR -2
#define MEM_ERR -3

#define TAM_CODIGO 10
#define TAM_DEPOSITO 10

#define CANT_PRODUCTOS 30
#define TOL_MOVIMIENTOS 50

typedef struct
{
    char codigo[TAM_CODIGO];
    char movimiento;
    char deposito[TAM_DEPOSITO];
    int cantidad;
}tProducto;

int abrirArchivo(FILE** archivoAAbrir, const char* nombreArch, const char* modoApertura);
int generarArchivoProductos(const char* nombreArchivo, const char* tipo);
// o uso el int de retorno pero llevaria mucho proceso por ver el codigo de error cada vuelta o uso una variable mas
int recorrerArchivoBinario(const char* nombreArch, unsigned tamRegistro,
                           FILE** arch1, FILE** arch2,
                           int(*accion)(void*, const void*, unsigned,
                                        int* , FILE**, FILE**));//podrian ser todas void*
int recorrerArchivoTexto(const char* nombreArch);

/// Acciones
int acomodarProductos(void* cola, const void* registro, unsigned tamRegistro,
                      int* acumulador, FILE** archMuchosMov, FILE** archPocosMov);

int insertarYAcumular(tCola* cola, const void* registro, unsigned tamRegistro, int* acumulador);
int cargarArchivoTextoDesacolando(FILE** archivoACargar, tCola* cola);

/// Comparaciones
int cmpCodigoProducto(const void* a, const void* b);

/// Mostrar
void mostrarProducto(tProducto* registro);

#endif // ARCHIVO_H_INCLUDED
