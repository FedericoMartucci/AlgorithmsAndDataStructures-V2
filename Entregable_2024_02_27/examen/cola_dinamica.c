#include "../include/cola_dinamica.h"
#include <stdlib.h>
#include <string.h>

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) (    !( (nodo) = (tNodo *) malloc(tamNodo) )     \
                                                              || !( (info) = malloc(tamInfo) ) ?             \
                                                                     free(nodo), SIN_MEM : TODO_OK           )


void crear_cola(tCola *pc)
{
    pc->pri = pc->ult = NULL;
}

int poner_en_cola(tCola * pc, const void * pd, unsigned tam)
{
    tNodo *nue;

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tam))
        return SIN_MEM;

    memcpy(nue->info, pd, (nue->tamInfo = tam));
    nue->sig = NULL;
    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;
    pc->ult = nue;

    return TODO_OK;
}

int sacar_de_cola(tCola * pc, void * pd, unsigned tam)
{
    tNodo *elim;

    if(!pc->pri)
        return COLA_VACIA;

    memcpy(pd, pc->pri->info, MINIMO(tam, pc->pri->tamInfo));
    elim = pc->pri;
    if(pc->ult == elim)
        pc->ult = NULL;
    pc->pri = elim->sig;
    free(elim->info);
    free(elim);

    return TODO_OK;
}

int frente_de_cola(const tCola * pc, void * pd, unsigned tam)
{
    if(!pc->pri)
        return COLA_VACIA;

    memcpy(pd, pc->pri->info, MINIMO(tam, pc->pri->tamInfo));

    return TODO_OK;
}

int cola_llena(const tCola * pc, unsigned tam)
{
    tNodo *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodo), nue->info, tam))
    {
        free(nue->info);
        free(nue);
    }

    return !nue || !(nue->info);
}

int cola_vacia(const tCola * pc)
{
    return pc->pri == NULL;
}

void vaciar_cola(tCola * pc)
{
    while(pc->pri)
    {
        tNodo *elim = pc->pri;
        pc->pri = elim->sig;
        free(elim->info);
        free(elim);
    }

    pc->ult = NULL;
}
