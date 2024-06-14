#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol(tArbol* pa, const void* dato, unsigned tamDato, tComparacion cmp, tAccion3 acumular)
{
    int rc;

    if(*pa == NULL)
    {
        if((*pa = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
           ((*pa)->info = malloc(tamDato)) == NULL)
        {
            free(*pa);
            return MEM_ERR;
        }

        memcpy((*pa)->info, dato, tamDato);
        (*pa)->tamInfo = tamDato;
        (*pa)->izq = NULL;
        (*pa)->der = NULL;

        return OK;
    }

    rc = cmp((*pa)->info, dato);
    if(rc > 0)
        return insertarEnArbol(&(*pa)->izq, dato, tamDato, cmp, acumular);
    if(rc < 0)
        return insertarEnArbol(&(*pa)->der, dato, tamDato, cmp, acumular);
    if(acumular)
        acumular((*pa)->info, dato);
    return CLA_DUP;
}

void vaciarArbol(tArbol* pa)
{
    if(*pa == NULL)
        return;

    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}

void recorrerInorden(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    recorrerInorden(&(*pa)->izq, accion);
    accion((*pa)->info);
    recorrerInorden(&(*pa)->der, accion);
}

void recorrerInordenInveso(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    recorrerInordenInveso(&(*pa)->der, accion);
    accion((*pa)->info);
    recorrerInordenInveso(&(*pa)->izq, accion);
}

void buscarMenorNoClave(const tArbol* pa, void* key, tComparacion cmp, tAccion3 accion)
{
    if(*pa == NULL)
        return;

    buscarMenorNoClave(&(*pa)->izq, key, cmp, accion);
    if(cmp((*pa)->info, key) < 0)
        accion(key, (*pa)->info);
    buscarMenorNoClave(&(*pa)->der, key, cmp, accion);
}

void buscarMayorNoClave(const tArbol* pa, void* key, tComparacion cmp, tAccion3 accion)
{
    if(*pa == NULL)
        return;

    buscarMayorNoClave(&(*pa)->izq, key, cmp, accion);
    if(cmp((*pa)->info, key) > 0)
        accion(key, (*pa)->info);
    buscarMayorNoClave(&(*pa)->der, key, cmp, accion);
}
