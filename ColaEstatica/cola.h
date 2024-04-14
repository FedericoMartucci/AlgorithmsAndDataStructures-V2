#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLA_LLENA 0
#define COLA_VACIA 0
#define SIN_MEM 0
#define OK 1
#define TAM_COLA 100

#define MINIMO(X, Y) (X < Y? X : Y)

typedef struct
{
    char cola[TAM_COLA];
    unsigned pri;
    unsigned ult;
    unsigned tamDisp;
}tCola;

void crearCola(tCola* pc);
int colaVacia(const tCola* pc);
int colaLlena(const tCola* pc, unsigned tamDato);
int ponerEnCola(tCola* pc, const void* info, unsigned cantBytes);
int sacarDeCola(tCola* pc, void* info, unsigned cantBytes);
int verTope(const tCola* pc, void* info, unsigned cantBytes);
void vaciarCola(tCola* pc);

#endif // COLA_H_INCLUDED
