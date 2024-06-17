#ifndef DEUDA_H_INCLUDED
#define DEUDA_H_INCLUDED

#include "arbol.h"

#define MAX_PATENTE 8
#define MAX_TITULAR 26

#define CANT_REGISTROS 5

typedef struct
{
    int dia;
    int mes;
    int anio;
} tFecha;

typedef struct
{
    char patente[MAX_PATENTE];
    char titular[MAX_TITULAR];
    int nroCuota;
    unsigned dni;
    tFecha vencimiento;
    float importe;
} tDeuda;

void iniciarMenu(tArbol* pa);
int generarArchBinImpuestosVencidos(const char* path);
int cargarArchTxtEnArbol(tArbol* pa, const char* path, unsigned tamReg,
                         tComparacion cmp, tAccion2 acumular);
int generarArchTxtRecorriendoArbol(tArbol* pa, const char* path,
                                   tAccion2 imprimir, tAccion2 acumular);

/// Funciones de comparacion
int cmpDni(const void* deuda1, const void* deuda2);
int cmpDniYPatente(const void* deuda1, const void* deuda2);

/// Funciones de mostrar
void acumularImportes(void* acumulado, const void* acumular);
void acumularImportes2(void* acumulado, const void* acumular);

/// Funciones de grabado
void grabarDeudaPorDNI(void* salida, const void* deuda);
void grabarDeudaPorDNIYPatente(void* salida, const void* deuda);

#endif // DEUDA_H_INCLUDED
