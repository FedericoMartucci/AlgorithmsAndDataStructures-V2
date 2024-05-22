#include "listaDoble.h"

void crearLista(tListaDoble* pl)
{
    *pl = NULL;
}

int insertarOrdenado(tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp)
{
    tNodo* auxSig;
    tNodo* auxAnt;
    tNodo* nuevo;

    if(*pl == NULL)
        auxSig = auxAnt = NULL;
    else
    {
        while(cmp((*pl)->info, dato) > 0 && (*pl)->sig)
            *pl = (*pl)->sig;
        while(cmp((*pl)->info, dato) < 0 && (*pl)->ant)
            *pl = (*pl)->ant;

        if(cmp((*pl)->info, dato) < 0)
        {
            auxAnt = (*pl)->ant;
            auxSig = *pl;
        }
        if(cmp((*pl)->info, dato) > 0)
        {
            auxAnt = *pl;
            auxSig = (*pl)->sig;
        }
    }

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nuevo->info = malloc(tamDato)) == NULL){
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->sig = auxSig;
    nuevo->ant = auxAnt;

    if(auxAnt != NULL)
        auxAnt->sig = nuevo;
    if(auxSig != NULL)
        auxSig->ant = nuevo;

    *pl = nuevo;

    return OK;
}

int recorrerIzqADer(tListaDoble* pl, tAccion accion)
{
    if(!*pl)
        return LISTA_VACIA;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        accion(stdout, (*pl)->info);
        pl = &(*pl)->sig;
    }

    return OK;
}

int recorrerDerAIzq(tListaDoble* pl, tAccion accion)
{
    int cantElementos;

    cantElementos = 0;

    if(!*pl)
        return LISTA_VACIA;

    while((*pl)->sig)
        pl = &(*pl)->sig;

    while(*pl)
    {
        accion(stdout, (*pl)->info);
        cantElementos ++;
        pl = &(*pl)->ant;
    }

    return cantElementos;
}

void vaciarLista(tListaDoble* pl)
{
    tNodo* elim;

    if(!*pl)
        return;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        elim = *pl;
        *pl = elim ->sig;
        free(elim->info);
        free(elim);
    }
}

int buscarElementoListaOrdenada(const tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp)
{
    int resultadoComparacion;


    while(*pl && (resultadoComparacion = cmp((*pl)->info, dato)) > 0)
    {
        if((resultadoComparacion = cmp((*pl)->info, dato)) <= 0)
        {
            if(resultadoComparacion == 0)
            {
                memcpy(dato, (*pl)->info, MIN(tamDato, (*pl)->tamInfo));
                return ELEMENTO_ENCONTRADO;
            }
            else
                return ELEMENTO_NO_ENCONTRADO;
        }
        pl = &(*pl)->ant;
    }

    while(*pl && (resultadoComparacion = cmp((*pl)->info, dato)) < 0)
    {
        if((resultadoComparacion = cmp((*pl)->info, dato)) >= 0)
        {
            if(resultadoComparacion == 0)
            {
                memcpy(dato, (*pl)->info, MIN(tamDato, (*pl)->tamInfo));
                return ELEMENTO_ENCONTRADO;
            }
            else
                return ELEMENTO_NO_ENCONTRADO;
        }
        pl = &(*pl)->sig;
    }

    if( resultadoComparacion == 0)
    {
        memcpy(dato, (*pl)->info, MIN(tamDato, (*pl)->tamInfo));
        return ELEMENTO_ENCONTRADO;
    }

    return ELEMENTO_NO_ENCONTRADO;
}

int buscarElementoListaDesordenada(const tListaDoble* pl, void* dato, unsigned tamDato, tComparacion cmp)
{
    tNodo* inicio;

    if(!*pl)
        return LISTA_VACIA;

    inicio = (*pl)->sig;

    while(*pl && cmp((*pl)->info, dato) != 0)
        pl = &(*pl)->ant;

    if(*pl)
    {
        memcpy(dato, (*pl)->info, MIN(tamDato, (*pl)->tamInfo));
        return ELEMENTO_ENCONTRADO;
    }

    while(inicio && cmp(inicio->info, dato) != 0)
        inicio = inicio->sig;

    if(inicio)
    {
        memcpy(dato, inicio->info, MIN(tamDato, inicio->tamInfo));
        return ELEMENTO_ENCONTRADO;
    }

    return ELEMENTO_NO_ENCONTRADO;
}

int eliminarClaveListaOrdenadaSinDup(tListaDoble* pl, void* clave, tComparacion cmp)
{

}

int eliminarOcurrenciasClaveListaDesordenada(tListaDoble* pl, void* clave, tComparacion cmp)
{

}

int resumirOcurrenciasClaveListaDesordenada(tListaDoble* pl, void* clave, tComparacion cmp)
{

}

void mapC(tListaDoble* pl, tAccion accion)
{

}

void filterC(tListaDoble* pl, tComparacion cmp)
{

}

void reduceC(tListaDoble* pl, void* acumulador, tAccion2 accion)
{

}

void acumularSumaEnteros(void* acc, const void* info)
{
    *(int*)acc = *(int*)acc + *(int*)info;
}

