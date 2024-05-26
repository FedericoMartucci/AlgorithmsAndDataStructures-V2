#include "ListaCircular.h"

/// Pila implementada en lista circular

void crearPila(tListaCircular* pl)
{
    *pl = NULL;
}

int pilaLlena(const tListaCircular* pl, unsigned cantBytes)
{
    tNodo* nuevoNodo;
    void* info;

    nuevoNodo = (tNodo*) malloc(sizeof(tNodo));
    info = malloc(cantBytes);

    free(nuevoNodo);
    free(info);

    return nuevoNodo == NULL || info == NULL;
}

int pilaVacia(const tListaCircular* pl)
{
    return *pl == NULL;
}

int apilar(tListaCircular* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevo;

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;

    if(*pl == NULL)
    {
        nuevo->sig = nuevo;
        *pl = nuevo;
    }
    else
    {
        nuevo->sig = (*pl)->sig;
        (*pl)->sig = nuevo;
    }

    return OK;
}

int desapilar(tListaCircular* pl, void* info, unsigned cantBytes)
{
    tNodo* elim;

    if(*pl == NULL)
        return PILA_VACIA;

    elim = (*pl)->sig;
    memcpy(info, elim->info, MIN(cantBytes, elim->tamInfo));

    if(*pl == elim)
        *pl = NULL;
    else
        (*pl)->sig = elim->sig;

    free(elim->info);
    free(elim);

    return OK;
}

int verUltimo(const tListaCircular* pl, void* info, unsigned cantBytes)
{
    if(*pl == NULL)
        return PILA_VACIA;

    memcpy(info, (*pl)->sig->info, MIN(cantBytes, (*pl)->sig->tamInfo));

    return OK;
}

void vaciarPila(tListaCircular* pl)
{
    tNodo* nodoAEliminar;

    while(*pl)
    {
        nodoAEliminar = (*pl)->sig;
        if(*pl == nodoAEliminar->sig)
            *pl = NULL;
        else
            (*pl)->sig = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
}


/// Cola implementada en lista circular

void crearCola(tListaCircular* pl)
{
    *pl = NULL;
}

int colaLlena(const tListaCircular* pl, unsigned cantBytes)
{
    tNodo* nuevoNodo;
    void* info;

    nuevoNodo = (tNodo*) malloc(sizeof(tNodo));
    info = malloc(cantBytes);

    free(nuevoNodo);
    free(info);

    return nuevoNodo == NULL || info == NULL;
}

int colaVacia(const tListaCircular* pl)
{
    return *pl == NULL;
}

int acolar(tListaCircular* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevo;

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;

    if(*pl == NULL)
    {
        nuevo->sig = nuevo;
    }
    else
    {
        nuevo->sig = (*pl)->sig;
        (*pl)->sig = nuevo;
    }

    *pl = nuevo;

    return OK;
}

int desacolar(tListaCircular* pl, void* info, unsigned cantBytes)
{
    tNodo* elim;

    if(*pl == NULL)
        return COLA_VACIA;

    elim = (*pl)->sig;
    memcpy(info, elim->info, MIN(cantBytes, elim->tamInfo));

    if(*pl == elim)
        *pl = NULL;
    else
        (*pl)->sig = elim->sig;

    free(elim->info);
    free(elim);

    return OK;
}

int verPrimero(const tListaCircular* pl, void* info, unsigned cantBytes)
{
    if(*pl == NULL)
        return COLA_VACIA;

    memcpy(info, (*pl)->sig->info, MIN(cantBytes, (*pl)->sig->tamInfo));

    return OK;
}

void vaciarCola(tListaCircular* pl)
{
    tNodo* nodoAEliminar;

    while(*pl)
    {
        nodoAEliminar = (*pl)->sig;
        if(*pl == nodoAEliminar->sig)
            *pl = NULL;
        else
            (*pl)->sig = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
}

/// Funciones utiles
void mostrarEnteroPorConsola(const void* num)
{
    fprintf(stdout, "%d ", *(int*)num);
}
