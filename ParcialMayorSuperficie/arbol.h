#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEM_ERR -1
#define CLA_DUP -2

typedef int(*tComparacion)(const void*, const void*);
typedef int(*tAccion2)(void*, const void*);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* pa);
int insertarEnArbol(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion);


void* buscarMenorNoClaveEnvoltorio(const tArbol* pa, tComparacion cmp);
void* buscarMenorNoClave(const tArbol* pa, void* menor, tComparacion cmp);

#endif // ARBOL_H_INCLUDED
