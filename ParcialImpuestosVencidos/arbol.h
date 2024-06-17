#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OK 0
#define MEM_ERR -1
#define FILE_ERR -2
#define CLA_DUP -3

typedef int(*tComparacion)(const void*, const void*);
typedef void(tAccion)(const void*);
typedef void(tAccion2)(void*, const void*);
typedef void(tAccion3)(void*, const void*);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* pa);
int insertarEnArbol(tArbol* pa, const void* info, unsigned cantBytes,
                    tComparacion cmp, tAccion2 acumular);
void grabarArchTxtOrdenadoConReduce(tArbol* pa, FILE* archDeuda, void* acum,
                                    tAccion2 imprimir, tAccion2 acumular);
void vaciarArbol(tArbol* pa);

#endif // ARBOL_H_INCLUDED
