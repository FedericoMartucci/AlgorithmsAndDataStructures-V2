#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (X < Y? X : Y)

#define OK 0
#define COLA_VACIA -1
#define MEM_ERR -2

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef struct
{
    tNodo* pri;
    tNodo* ult;
} tCola;

void crearCola(tCola* pc);
int colaVacia(const tCola* pc);
int colaLlena(const tCola* pc, unsigned cantBytes);
int acolar(tCola* pc, const void* info, unsigned cantBytes);
int desacolar(tCola* pc, void* info, unsigned cantBytes);
int verPrimero(const tCola* pc, void* info, unsigned cantBytes);
void vaciarCola(tCola* pc);


#endif // COLADINAMICA_H_INCLUDED
