#include "../include/arbol.h"
#include <stdlib.h>
#include <string.h>

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) (    !( (nodo) = (tNodoArbol *) malloc(tamNodo) )     \
                                                              || !( (info) = malloc(tamInfo) ) ?                  \
                                                                     free(nodo), SIN_MEM : TODO_OK                )


void crearArbolBinBusq(tArbolBinBusq *pa)
{
    *pa = NULL;
}

int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                         int (*cmp)(const void *, const void *))
{
    tNodoArbol *nue;
    int rc;

    while(*p)
    {
        if((rc = cmp((*p)->info, d)) > 0)
            p = &((*p)->izq);
        if(rc < 0)
            p = &((*p)->der);
        else
            return DUPLICADO;
    }

    if(!RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoArbol), nue->info, tam))
        return SIN_MEM;

    memcpy(nue->info, d, (nue->tamInfo = tam));
    nue->izq = nue->der = NULL;

    *p = nue;

    return TODO_OK;
}

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void * params,
                                 void (*accion)(void *, unsigned, void *))
{
    if(!(*p))
        return;

    recorrerEnOrdenSimpleArbolBinBusq(&((*p)->izq), params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerEnOrdenSimpleArbolBinBusq(&((*p)->izq), params, accion);
}

unsigned leerArchivoBin(void **info, void *ds, unsigned tam, unsigned m, void *params)
{
    FILE *pf = (FILE *)ds;

    if(!ds)
        return ERROR_PARAMETROS;

    fseek(pf, m * tam, SEEK_SET);

    return fread(*info, tam, 1, pf) != EOF;
}



int cargarDesdeDatosOrdenadosArbolBinBusqPropio(tArbolBinBusq *p,
                        void *ds, unsigned tam, unsigned li, unsigned ls,
                        unsigned (*leer)(void **, void *, unsigned, unsigned, void *params),
                        void * params)
{
    int r;
    unsigned m = (li + ls) / 2;

    if(*p)
        return SIN_INICIALIZAR;

    if(li > ls)
        return TODO_OK;

    if(!RESERVAR_MEMORIA_NODO(*p, sizeof(tNodoArbol), (*p)->info, tam))
        return SIN_MEM;

    if(!leer(&((*p)->info), ds, tam, m, params))
    {
        free((*p)->info);
        free(*p);
        return ERROR_ARCHIVO;
    }

    (*p)->tamInfo = tam;
    (*p)->izq = (*p)->der = NULL;

    if(( r = cargarDesdeDatosOrdenadosArbolBinBusqPropio(&((*p)->izq), ds, tam, li, m - 1, leer, params)) != TODO_OK)
        return r;

    return cargarDesdeDatosOrdenadosArbolBinBusqPropio(&((*p)->der), ds, tam, li, m - 1, leer, params);
}

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(tArbolBinBusq *p, FILE *pf,
                                         unsigned tamInfo)
{
    unsigned cantRegs;

    if(!pf || !(*p))
        return ERROR_PARAMETROS;

    fseek(pf, 0l, SEEK_END);
    cantRegs = ftell(pf) / tamInfo;

    cargarDesdeDatosOrdenadosArbolBinBusqPropio(p, pf, tamInfo, 0, cantRegs - 1, leerArchivoBin, NULL);

    return TODO_OK;
}

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *))
{
    int r;

    while(*p && (r = cmp((*p)->info, d)))
    {
        if(r > 0)
            p = &((*p)->izq);
        else
            p = &((*p)->der);
    }
    if(!(*p))
        return NO_EXISTE;

    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));

    return TODO_OK;
}

void eliminarArbol(tArbolBinBusq *pa)
{
    if(!*pa)
        return;
    if((*pa)->izq)
        eliminarArbol(&((*pa)->izq));
    if(((*pa)->der))
        eliminarArbol(&((*pa)->der));
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}
