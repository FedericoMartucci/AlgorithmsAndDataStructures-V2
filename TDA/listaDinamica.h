#ifndef LISTADINAMICA_H_INCLUDED
#define LISTADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (X < Y? X : Y)

#define OK 0
#define MEM_ERR -1

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(tLista* pl, unsigned cantBytes);

int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes);
int insertarPorPosicion(tLista* pl, const void* info, unsigned cantBytes, unsigned posicion);
int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes, int(*cmp)(const void*, const void*));
int insertarAcumulando(tLista* pl, const void* info, unsigned cantBytes, int(*cmp)(const void*, const void*));//agregar funcion de accion para acumular
int insertarOrdenadoAcumulando(tLista* pl, const void* info, unsigned cantBytes, int(*cmp)(const void*, const void*));

int verPrimerElemento(const tLista* pl, void* info, unsigned cantBytes);
int verUltimoElemento(const tLista* pl, void* info, unsigned cantBytes);
int verNElemento(const tLista* pl, void* info, unsigned cantBytes, unsigned n);

int eliminarPrimero(tLista* pl, void* info, unsigned cantBytes);
int eliminarUltimo(tLista* pl, void* info, unsigned cantBytes);
int eliminarPorPosicion(tLista* pl, void* info, unsigned cantBytes, unsigned posicion);
int eliminarNUltimos(tLista* pl, unsigned n);

tLista* buscarMenor(const tLista* pl, int(*cmp)(const void*, const void*));
tLista* buscarMayor(const tLista* pl, int(*cmp)(const void*, const void*));
int buscarElemento(const tLista* pl, void* info, unsigned cantBytes, int(*cmp)(const void*, const void*));

int ordenarPorSeleccion(tLista* pl, int(*cmp)(const void*, const void*));

void vaciarLista(tLista* pl);

void mostrarLista(const tLista* pl, FILE* destino, void(*mostrar)(FILE*, const void*));
void mostrarListaInversa(const tLista* pl, FILE* destino, void(*mostrar)(FILE*, const void*));

#endif // LISTADINAMICA_H_INCLUDED
