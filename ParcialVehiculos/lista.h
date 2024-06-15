#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEM_ERR -1
#define CLA_DUP -2
#define FILE_ERR -3

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(void*, const void*);
typedef void(*tAccion2)(const void*);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pa);
int insertarOrdenado(tLista* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion acumular);
void recorrerLista(const tLista* pa, tAccion2 accion);
void vaciarLista(tLista* pa);

#endif // LISTA_H_INCLUDED
