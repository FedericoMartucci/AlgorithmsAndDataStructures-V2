#include "cola.h"

void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

int colaVacia(const tCola* pc)
{
    return pc->pri == NULL;
}

int colaLlena(const tCola* pc, unsigned cantBytes)
{
    return 0;
}

int ponerEnCola(tCola* pc, const void* info, unsigned cantBytes)
{
    tNodo* nodoAInsertar;

    if((nodoAInsertar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAInsertar->info = malloc(cantBytes)) == NULL){
        free(nodoAInsertar);
        return COLA_LLENA;
    }

    memcpy(nodoAInsertar->info, info, cantBytes);
    nodoAInsertar->tamInfo = cantBytes;
    nodoAInsertar->sig = NULL;

    if(pc->pri == NULL)
        pc->pri = nodoAInsertar;
    else
        pc->ult->sig = nodoAInsertar;

    pc->ult = nodoAInsertar;
    return OK;
}

int sacarDeCola(tCola* pc, void* info, unsigned cantBytes)
{
    tNodo* nodoAEliminar;

    if(pc->pri == NULL)
        return COLA_VACIA;

    nodoAEliminar = pc->pri;
    memcpy(info, nodoAEliminar->info, MINIMO(cantBytes, nodoAEliminar->tamInfo));
    pc->pri = nodoAEliminar->sig;

    free(nodoAEliminar->info);
    free(nodoAEliminar);

    if(pc->pri == NULL)
        pc->ult = NULL;

    return OK;
}

int verTope(const tCola* pc, void* info, unsigned cantBytes)
{
    if(pc->pri == NULL)
        return COLA_VACIA;

    memcpy(info, pc->pri->info, MINIMO(cantBytes, pc->pri->tamInfo));

    return OK;
}

void vaciarCola(tCola* pc)
{
    tNodo* nodoAEliminar;

    while(pc->pri){
        nodoAEliminar = pc->pri;
        pc->pri = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
    pc->ult = NULL;
}
