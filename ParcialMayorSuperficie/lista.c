#include "lista.h"

void crearLista(tLista* pl)
{
    *pl = NULL;
}

int insertarOrdenadoConLimite(tLista* pl, const void* info, unsigned cantBytes,
                              unsigned limite, tComparacion cmp)
{
    tNodoLista* nodoNueOElim;

    while(*pl && limite > 0 && cmp((*pl)->info, info) > 0)
    {
        pl = &(*pl)->sig;
        limite--;
    }

    if(limite == 0)
        return FUERA_DE_RANGO;

    if((nodoNueOElim = (tNodoLista*) malloc(sizeof(tNodoLista))) == NULL ||
       (nodoNueOElim->info = malloc(cantBytes)) == NULL)
    {
        free(nodoNueOElim);
        return MEM_ERR;
    }

    memcpy(nodoNueOElim->info, info, cantBytes);
    nodoNueOElim->tamInfo = cantBytes;
    nodoNueOElim->sig = *pl;
    *pl = nodoNueOElim;

    while(*pl)
    {
        if(limite <= 0)
        {
            nodoNueOElim = *pl;
            *pl = nodoNueOElim->sig;
            free(nodoNueOElim->info);
            free(nodoNueOElim);
        }
        else
            pl = &(*pl)->sig;
        limite--;
    }

    return OK;
}

void vaciarLista(tLista* pl)
{
    tNodoLista* elim;

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

void mostrarYVaciarLista(tLista* pl, tAccion accion)
{
    tNodoLista* elim;

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        accion(elim->info);
        free(elim->info);
        free(elim);
    }
}
