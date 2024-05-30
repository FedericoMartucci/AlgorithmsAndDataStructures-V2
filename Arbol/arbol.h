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

#define TAM_VEC 30

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
int insertarEnArbol_R(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion); //Ejercicio 6.1
int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion); //Ejercicio 6.1

void recorrerPreOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1
void recorrerInOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1
void recorrerPosOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1

int alturaArbol(const tArbol* pa); //Ejercicio 6.1
void mostrarNodosHoja(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosNoHoja(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosSoloIzq(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosIzq(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosDer(const tArbol* pa, tAccion accion); //Ejercicio 6.1

//'pode' las ramas de un árbol de modo que no supere una altura determinada. //Ejercicio 6.1
// 'pode' las ramas de un árbol de una altura determinada o inferior. //Ejercicio 6.1

int esArchivoBinarioOrdenado(const char* nombreArch, tArbol* pa, const void* ultimoValor, tComparacion cmp); //Ejercicio 6.3

int esArbolCompleto(const tArbol* pa); //Ejercicio 6.4
int esArbolBalanceado(const tArbol* pa); //Ejercicio 6.4
int esArbolAVL(const tArbol* pa); //Ejercicio 6.4
int determinarTipoDeArbol(const tArbol* pa); //Ejercicio 6.5

int arbolVacio(const tArbol* pa);

void vaciarArbol(tArbol* pa); //Ejercicio 6.1

/// Generar datos random
void generarVectorEnteros(int* vec, int tam);

/// Funciones de mostrar
void mostrarEnteroPorConsola(const void* num);
void imprimirArbol(tArbol* pa, int nivel, tAccion accion);

/// Funciones de comparacion
int cmpEnteros(const void* a, const void* b);

#endif // ARBOL_H_INCLUDED
