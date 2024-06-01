#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol_R(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion)
{
    int rCmp;

    if(*pa != NULL)
    {
        rCmp = cmp((*pa)->info, info);

        if(rCmp > 0)
            return insertarEnArbol_R(&(*pa)->izq, info, cantBytes, cmp, accion);
        else if(rCmp < 0)
            return insertarEnArbol_R(&(*pa)->der, info, cantBytes, cmp, accion);
        else
        {
            if(accion)
                accion((*pa)->info, info);
            return CLA_DUP;
        }
    }

    if(((*pa) = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            ((*pa)->info = malloc(cantBytes)) == NULL)
    {
        free((*pa));
        return MEM_ERR;
    }

    memcpy((*pa)->info, info, cantBytes);
    (*pa)->tamInfo = cantBytes;
    (*pa)->izq = NULL;
    (*pa)->der = NULL;

    return OK;
}

int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion2 accion)
{
    int rCmp;

    while(*pa)
    {
        rCmp = cmp((*pa)->info, info);

        if(rCmp > 0)
            pa = &(*pa)->izq;
        else if(rCmp < 0)
            pa = &(*pa)->der;
        else
        {
            if(accion)
                accion((*pa)->info, info);
            return CLA_DUP;
        }
    }

    if(((*pa) = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            ((*pa)->info = malloc(cantBytes)) == NULL)
    {
        free((*pa));
        return MEM_ERR;
    }

    memcpy((*pa)->info, info, cantBytes);
    (*pa)->tamInfo = cantBytes;
    (*pa)->izq = NULL;
    (*pa)->der = NULL;

    return OK;
}

void recorrerPreOrden(tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    accion((*pa)->info);
    recorrerPreOrden(&(*pa)->izq, accion);
    recorrerPreOrden(&(*pa)->der, accion);
}

void recorrerInOrden(tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    recorrerInOrden(&(*pa)->izq, accion);
    accion((*pa)->info);
    recorrerInOrden(&(*pa)->der, accion);
}

void recorrerPosOrden(tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    recorrerPosOrden(&(*pa)->izq, accion);
    recorrerPosOrden(&(*pa)->der, accion);
    accion((*pa)->info);
}

/// Funciones de contar
int contarHojas(const tArbol* pa)
{
    int hi;
    int hd;

    if(*pa == NULL)
        return 0;

    hi = contarHojas(&(*pa)->izq);
    hd = contarHojas(&(*pa)->der);

    if(!hi && !hd)
        return 1;

    return hi + hd;
}

int contarYMostrarHojas(const tArbol* pa, tAccion accion)
{
    int hi;
    int hd;

    if(*pa == NULL)
        return 0;

    hi = contarYMostrarHojas(&(*pa)->izq, accion);
    hd = contarYMostrarHojas(&(*pa)->der, accion);

    if(!hi && !hd)
    {
        accion((*pa)->info);
        return 1;
    }

    return hi + hd;
}

int alturaArbol(const tArbol* pa)
{
    return *pa? MAX(alturaArbol(&(*pa)->izq), alturaArbol(&(*pa)->der)) + 1 : 0;
}

/// Funciones de mostrar
void mostrarEntero(void* salida, const void* info)
{
    printf("%d ", *(int*)info);
//    fprintf((FILE*)salida, "%d ", *(int*)info);
}

void mostrarHojas(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarHojas(&(*pa)->izq, accion);
    mostrarHojas(&(*pa)->der, accion);

    if((*pa)->izq == NULL && (*pa)->der == NULL)
        accion((*pa)->info);
}

void mostrarEnteroPorConsola(const void* info)
{
    printf("%d ", *(int*)info);
}
/// Funciones de comparacion
int cmpEnteros(const void* num1, const void* num2)
{
    return *(int*)num1 - *(int*)num2;
}
