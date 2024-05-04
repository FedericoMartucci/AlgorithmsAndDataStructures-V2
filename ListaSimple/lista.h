#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLAVE_DUP -2
#define MEM_ERR -1
#define OK 0

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, unsigned cantBytes);
int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinalOAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                              void(*acumular)(void* infoEnLista, void* tamInfo,
                                              const void* info, unsigned cantBytes));
int buscarInfoPorClave(const tLista* pl, void* info, unsigned cantBytes, const void* clave);


int cmpEnteros(const void*, const void*);
void acumularSumando(void* infoEnLista, const void* info);

#endif // LISTA_H_INCLUDED
