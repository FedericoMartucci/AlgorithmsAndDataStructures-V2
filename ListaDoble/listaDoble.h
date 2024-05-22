#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))

#define OK 0
#define MEM_ERR -1
#define CLA_DUP -2
#define LISTA_VACIA -35

#define ELEMENTO_ENCONTRADO 1
#define ELEMENTO_NO_ENCONTRADO 0

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(FILE*, const void*);
typedef void(*tAccion2)(void*, const void*);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* ant;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tListaDoble;

void crearLista(tListaDoble* pl);
int insertarOrdenado(tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp);
int recorrerIzqADer(tListaDoble* pl, tAccion accion);
int recorrerDerAIzq(tListaDoble* pl, tAccion accion);
void vaciarLista(tListaDoble* pl);

int buscarElementoListaOrdenada(const tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp);
int buscarElementoListaDesordenada(const tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp);

int eliminarClaveListaOrdenadaSinDup(tListaDoble* pl, void* clave, tComparacion cmp);

int eliminarOcurrenciasClaveListaDesordenada(tListaDoble* pl, void* clave, tComparacion cmp);
int resumirOcurrenciasClaveListaDesordenada(tListaDoble* pl, void* clave, tComparacion cmp);

void mapC(tListaDoble* pl, tAccion accion);
void filterC(tListaDoble* pl, tComparacion cmp);
void reduceC(tListaDoble* pl, void* acumulador, tAccion2 accion);

void acumularSumaEnteros(void* acc, const void* info);

#endif // LISTADOBLE_H_INCLUDED
