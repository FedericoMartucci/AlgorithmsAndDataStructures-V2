#include "pilaDinamica.h"

void crearPila(tPila* pp)
{
    *pp = NULL;
}

int pilaVacia(const tPila* pp)
{
    return *pp == NULL;
}

int pilaLlena(const tPila* pp, unsigned cantBytes)
{
    tNodo* nodoAInsertar = (tNodo*) malloc(sizeof(tNodo));
    void* datoAInsertar = malloc(cantBytes);

    free(nodoAInsertar);
    free(datoAInsertar);

    return !nodoAInsertar || !datoAInsertar;
}

int apilar(tPila* pp, const void* dato, unsigned cantBytes)
{
    tNodo* nodoAInsertar;

    if((nodoAInsertar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAInsertar->info = malloc(cantBytes)) == NULL){
        free(nodoAInsertar);
        return PILA_LLENA;
    }

    memcpy(nodoAInsertar->info, dato, cantBytes);
    nodoAInsertar->tamInfo = cantBytes;
    nodoAInsertar->sig = *pp;

    *pp = nodoAInsertar;

    return OK;
}

int desapilar(tPila* pp, void* dato, unsigned cantBytes)
{
    tNodo* nodoAEliminar;

    if(*pp == NULL)
        return PILA_VACIA;

    nodoAEliminar = *pp;

    memcpy(dato, nodoAEliminar->info, MIN(cantBytes, nodoAEliminar->tamInfo));
    *pp = nodoAEliminar->sig;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    return OK;
}

int verTope(const tPila* pp, void* dato, unsigned cantBytes)
{
    if(*pp == NULL)
        return PILA_VACIA;

    memcpy(dato, (*pp)->info, MIN(cantBytes, (*pp)->tamInfo));

    return OK;
}

void vaciarPila(tPila* pp)
{
    tNodo* nodoAEliminar;

    while(*pp){
        nodoAEliminar = *pp;
        *pp = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
}
