#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion)
{
    int resultadoComparacion;

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
        (*pa)->der = NULL;
        (*pa)->izq = NULL;

        return OK;
    }

    if((resultadoComparacion = cmp((*pa)->info, info)) > 0)
        return insertarEnArbol(&(*pa)->izq, info, cantBytes, cmp, accion);
    if(resultadoComparacion < 0)
        return insertarEnArbol(&(*pa)->der, info, cantBytes, cmp, accion);
    if(accion)
        accion((*pa)->info, info);
    return CLA_DUP;
}

void* buscarMenorNoClaveEnvoltorio(const tArbol* pa, tComparacion cmp)
{
    return *pa == NULL? *pa : buscarMenorNoClave(pa, (*pa)->info, cmp);
}

void* buscarMenorNoClave(const tArbol* pa, void* menor, tComparacion cmp)
{
    if(*pa == NULL)
        return menor;

    menor = buscarMenorNoClave(&(*pa)->izq, menor, cmp);
    if(cmp((*pa)->info, menor) < 0)
        menor = (*pa)->info;
    menor = buscarMenorNoClave(&(*pa)->der, menor, cmp);

    return menor;
}
