#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEM_ERR -1
#define FILE_ERR -2
#define CLA_DUP -3

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(void*, const void*);
typedef void(*tAccion2)(const void*);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* pa);
int insertarEnArbol(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion acumular);
void recorrerInOrden(const tArbol* pa, tAccion2 accion);
void recorrerInOrden2(const tArbol* pa, FILE* arch, tAccion accion);
void vaciarArbol(tArbol* pa);

#endif // ARBOL_H_INCLUDED
