#ifndef VEHICULOS_H_INCLUDED
#define VEHICULOS_H_INCLUDED

#include "arbol.h"
//#include "lista.h"

#define MAX_DOMINIO 8

typedef int(*tAccion3)(tArbol*, const void*);

typedef struct
{
    char dominio[MAX_DOMINIO];
    int antiguedad;
    float kmRecorridos;
} tVehiculo;

typedef struct
{
    int antiguedad;
    float kmRecorridos;
    int cantVehiculos;
} tPromedio;

int generarArchBinVehiculos(const char* nombreArch);
int recorrerArchBin(tArbol* pa, const char* nombreArch, unsigned tamInfo, tAccion3 accion);
//int recorrerArchBin(tLista* pa, const char* nombreArch, unsigned tamInfo, tAccion3 accion);
int insertarVehiculoEnArbol(tArbol* pa, const void* vehiculo);
//int insertarVehiculoEnLista(tLista* pa, const void* vehiculo);
void mostrarPromedio(const void* registro);
void acumularPromedio(void* prom, const void* registro);
int cmpAntiguedad(const void*, const void*);

#endif // VEHICULOS_H_INCLUDED
