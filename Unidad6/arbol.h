#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))
#define MAX(X, Y) ((X) > (Y)? (X) : (Y))

#define ARBOL_VACIO -1
#define MEM_ERR -2
#define CLA_DUP -3
#define ELEMENTO_ENCONTRADO 1
#define ELEMENTO_NO_ENCONTRADO 0
#define OK 0

#define TAM_VEC 8

// Ejercicio 6.5
#define ES_COMPLETO 2
#define ES_BALANCEADO 3
#define ES_AVL 4
#define ES_OTRO 5

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(const void*);
typedef void(*tAccion2)(void*, const void*);
typedef void(*tAccion3)(FILE*, const void*);

void crearArbol(tArbol* pa);
int insertarEnArbol_R(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion);
int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion);

/// Recorridos
void recorrerPreOrden(tArbol* pa, tAccion accion);
void recorrerInOrden(tArbol* pa, tAccion accion);
void recorrerPosOrden(tArbol* pa, tAccion accion);

/// Funciones de contar
int contarHojas(const tArbol* pa);
int contarYMostrarHojas(const tArbol* pa, tAccion accion);
int alturaArbol(const tArbol* pa);

/// Funciones de mostrar
void mostrarEntero(void*, const void*);
void mostrarEnteroPorConsola(const void*);
void mostrarHojas(const tArbol* pa, tAccion accion);

/// Funciones de comparacion
int cmpEnteros(const void*, const void*);

#endif // ARBOL_H_INCLUDED
