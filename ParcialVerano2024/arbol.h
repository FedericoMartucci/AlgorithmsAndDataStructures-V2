#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))

#define OK 0
#define MEM_ERR -1
#define CLA_DUP -2

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

typedef void (*tAccion)(const void*);
typedef int (*tAccion2)(tArbol*, char*, unsigned);
typedef void (*tAccion3)(void*, const void*);
typedef int (*tComparacion)(const void*, const void*);

void crearArbol(tArbol* pa);
int insertarEnArbol(tArbol* pa, const void* dato, unsigned tamDato, tComparacion cmp, tAccion3 acumular);
void vaciarArbol(tArbol* pa);

/// Funciones de recorrido
void recorrerInorden(const tArbol* pa, tAccion accion);
void recorrerInordenInveso(const tArbol* pa, tAccion accion);

/// Funciones de busqueda
void buscarMenorNoClave(const tArbol* pa, void* key, tComparacion cmp, tAccion3 accion);
void buscarMayorNoClave(const tArbol* pa, void* key, tComparacion cmp, tAccion3 accion);

#endif // ARBOL_H_INCLUDED
