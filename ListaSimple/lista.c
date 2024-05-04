#include "lista.h"

void crearLista(tLista* pl)
{
    *pl = NULL;
}

int listaVacia(const tLista* pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista* pl, unsigned cantBytes)
{
    return 0;
}

int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nodoAInsertar;

    if((nodoAInsertar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAInsertar->info = malloc(cantBytes)) == NULL)
    {
        free(nodoAInsertar);
        return MEM_ERR;
    }

    memcpy(nodoAInsertar->info, info, cantBytes);
    nodoAInsertar->tamInfo = cantBytes;

    nodoAInsertar->sig = *pl;
    *pl = nodoAInsertar;

    return OK;
}

int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nodoAInsertar;

    while(*pl)
        pl = &(*pl)->sig;


    if((nodoAInsertar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAInsertar->info = malloc(cantBytes)) == NULL)
    {
        free(nodoAInsertar);
        return MEM_ERR;
    }

    memcpy(nodoAInsertar->info, info, cantBytes);
    nodoAInsertar->tamInfo = cantBytes;

    nodoAInsertar->sig = NULL;
    *pl = nodoAInsertar;

    return OK;
}

int insertarAlFinalOAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                              void(*acumular)(void* infoEnLista, void* tamInfo,
                                              const void* info, unsigned cantBytes))
{
    tNodo* nodoAInsertar;
    int comparacion;

    while(*pl && (comparacion = cmp((*pl)->info, info)))
        pl = &(*pl)->sig;

    if(comparacion == 0)
    {
        if(acumular)
            acumular(&(*pl)->info, &(*pl)->tamInfo, info, cantBytes);

        return CLAVE_DUP;
    }


    if((nodoAInsertar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAInsertar->info = malloc(cantBytes)) == NULL)
    {
        free(nodoAInsertar);
        return MEM_ERR;
    }

    memcpy(nodoAInsertar->info, info, cantBytes);
    nodoAInsertar->tamInfo = cantBytes;

    nodoAInsertar->sig = NULL;
    *pl = nodoAInsertar;

    return OK;
}

int buscarInfoPorClave(const tLista* pl, void* info, unsigned cantBytes, const void* clave)
{
    return OK;
}

int cmpEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
void acumularSumando(void* infoEnLista, const void* info)
{

}
