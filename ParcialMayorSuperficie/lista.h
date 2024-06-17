#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define MEM_ERR -1
#define FILE_ERR -2
#define FUERA_DE_RANGO -3

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(const void*);

typedef struct sNodoLista
{
    void* info;
    unsigned tamInfo;
    struct sNodoLista* sig;
} tNodoLista;

typedef tNodoLista* tLista;

void crearLista(tLista* pl);
int insertarOrdenadoConLimite(tLista* pl, const void* info, unsigned cantBytes,
                              unsigned limite, tComparacion cmp);
void vaciarLista(tLista* pl);
void mostrarYVaciarLista(tLista* pl, tAccion accion);

#endif // LISTA_H_INCLUDED
