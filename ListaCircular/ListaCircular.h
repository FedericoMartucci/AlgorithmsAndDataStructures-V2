#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEM_ERR -1
#define PILA_VACIA -2
#define COLA_VACIA -2

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tListaCircular;

/// Pila implementada en lista circular
void crearPila(tListaCircular* pl);
int pilaLlena(const tListaCircular* pl, unsigned cantBytes);
int pilaVacia(const tListaCircular* pl);
int apilar(tListaCircular* pl, const void* info, unsigned cantBytes);
int desapilar(tListaCircular* pl, void* info, unsigned cantBytes);
int verUltimo(const tListaCircular* pl, void* info, unsigned cantBytes);
void vaciarPila(tListaCircular* pl);

/// Cola implementada en lista circular
void crearCola(tListaCircular* pl);
int colaLlena(const tListaCircular* pl, unsigned cantBytes);
int colaVacia(const tListaCircular* pl);
int acolar(tListaCircular* pl, const void* info, unsigned cantBytes);
int desacolar(tListaCircular* pl, void* info, unsigned cantBytes);
int verPrimero(const tListaCircular* pl, void* info, unsigned cantBytes);
void vaciarCola(tListaCircular* pl);

/// Funciones utiles
void mostrarEnteroPorConsola(const void* num);

#endif // LISTACIRCULAR_H_INCLUDED
