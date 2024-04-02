#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PILA_VACIA -1
#define PILA_LLENA -2
#define OK 0

#define MIN(X, Y) (X < Y? X : Y)

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pp);
int pilaVacia(const tPila* pp);
int pilaLlena(const tPila* pp, unsigned cantBytes);
int apilar(tPila* pp, const void* dato, unsigned cantBytes);
int desapilar(tPila* pp, void* dato, unsigned cantBytes);
int verTope(const tPila* pp, void* dato, unsigned cantBytes);
void vaciarPila(tPila* pp);

#endif // PILADINAMICA_H_INCLUDED
