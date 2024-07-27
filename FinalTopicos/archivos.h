#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Nombres de archivos
#define NOMBRE_ARCH_DISTRIBUIDORES "distribuidores.bin"
#define NOMBRE_ARCH_MODIFICACIONES "modificaciones.bin"
#define NOMBRE_ARCH_TEMP "temp.bin"
#define NOMBRE_ARCH_ERRORES "errores.txt"

/// Codigos de retorno
#define OK 0
#define FILE_ERR -1
#define MEM_ERR -1

/// Constraints
#define MAX_APYN 31
#define MAX_NOM_FANTASIA 27

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(void*, const void*);

typedef struct
{
    int codCliente;
    char apyn[MAX_APYN];
    float saldo;
    char nombreFantasia[MAX_NOM_FANTASIA];
} tCliente;


/// Funciones de archivos
int crearLoteDistribuidores();
int crearLoteModificaciones();
int actualizarArchivosBin(const char* nombreArchLectura,
                          const char* nombreArchModificacion,
                          unsigned tamReg, tComparacion cmp, tComparacion cmp2,
                          tAccion imprimirError);
int mostrarArchivoBin(const char* nombreArch, unsigned tamReg, tAccion mostrar);

/// Funciones de impresion
void imprimirCliente(void* archDistribuidores, const void* distribuidor);

/// Funciones de comparacion
int cmpCodCliente(const void* c1, const void* c2);
int cmpSaldos(const void* c1, const void* c2);
int cmpNombreFantasia(const void* c1, const void* c2);
int cmpNombreYApellido(const void* c1, const void* c2);

#endif // ARCHIVOS_H_INCLUDED
