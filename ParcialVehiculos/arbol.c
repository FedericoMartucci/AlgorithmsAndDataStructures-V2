#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion acumular)
{
    int rc;

    if(*pa == NULL)
    {
        if((*pa = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
           ((*pa)->info = malloc(cantBytes)) == NULL)
        {
            free(*pa);
            return MEM_ERR;
        }
        memcpy((*pa)->info, info, cantBytes);
        (*pa)->tamInfo = cantBytes;
        (*pa)->izq = NULL;
        (*pa)->der = NULL;
        return OK;
    }

    rc = cmp((*pa)->info, info);
    if(rc > 0)
        return insertarEnArbol(&(*pa)->izq, info, cantBytes, cmp, acumular);
    if(rc < 0)
        return insertarEnArbol(&(*pa)->der, info, cantBytes, cmp, acumular);
    if(acumular)
        acumular((*pa)->info, info);
    return CLA_DUP;
}

void recorrerInOrden(const tArbol* pa, tAccion2 accion)
{
    if(*pa == NULL)
        return;

    recorrerInOrden(&(*pa)->izq, accion);
    accion((*pa)->info);
    recorrerInOrden(&(*pa)->der, accion);
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
