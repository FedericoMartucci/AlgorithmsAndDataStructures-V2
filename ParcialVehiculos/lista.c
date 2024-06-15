#include "lista.h"

void crearLista(tLista* pa)
{
    *pa = NULL;
}

int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes, tComparacion cmp, tAccion acumular)
{
    tNodo* nue;
    int rc;

    while(*pl && (rc = cmp((*pl)->info, info)) < 0)
        pl = &(*pl)->sig;

    if(*pl && rc == 0)
    {
        if(acumular)
            acumular((*pl)->info, info);
        return CLA_DUP;
    }

    if((nue = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return MEM_ERR;
    }

    memcpy(nue->info, info, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *pl;
    *pl = nue;

    return OK;
}

void recorrerLista(const tLista* pl, tAccion2 accion)
{
    while(*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }
}

void vaciarLista(tLista* pl)
{
    tNodo* elim;

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}
