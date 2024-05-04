#include "colaDinamica.h"

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
    tNodo* nodoAAcolar = (tNodo*) malloc(sizeof(tNodo));
    void* info = malloc(cantBytes);

    free(nodoAAcolar);
    free(info);

    return nodoAAcolar == NULL || info == NULL;
}

int acolar(tCola* pc, const void* info, unsigned cantBytes)
{
    tNodo* nodoAAcolar;

    if((nodoAAcolar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAAcolar->info = malloc(cantBytes)) == NULL){
       free(nodoAAcolar);
       return MEM_ERR;
    }

    memcpy(nodoAAcolar->info, info, cantBytes);
    nodoAAcolar->tamInfo = cantBytes;
    nodoAAcolar->sig = NULL;

    if(pc->pri)
        pc->ult->sig = nodoAAcolar;
    else
        pc->pri = nodoAAcolar;

    pc->ult = nodoAAcolar;

    return OK;
}

int desacolar(tCola* pc, void* info, unsigned cantBytes)
{
    tNodo* elim;

    if(pc->pri == NULL)
       return COLA_VACIA;

    elim = pc->pri;

    memcpy(info, elim->info, MIN(elim->tamInfo, cantBytes));
    pc->pri = elim->sig;

    free(elim->info);
    free(elim);

    if(pc->pri == NULL)
        pc->ult = NULL;

    return OK;
}

int verPrimero(const tCola* pc, void* info, unsigned cantBytes)
{
    if(pc->pri == NULL)
       return COLA_VACIA;

    memcpy(info, pc->pri->info, MIN(pc->pri->tamInfo, cantBytes));

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
