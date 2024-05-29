#include "listaDoble.h"

void crearLista(tListaDoble* pl)
{
    *pl = NULL;
}

int insertarOrdenado(tListaDoble* pl, const void* dato, unsigned tamDato, tComparacion cmp)
{
    tNodo* auxSig;
    tNodo* auxAnt;
    tNodo* nuevo;

    if(*pl == NULL)
        auxSig = auxAnt = NULL;
    else
    {
        while(cmp((*pl)->info, dato) < 0 && (*pl)->sig)
            *pl = (*pl)->sig;
        while(cmp((*pl)->info, dato) > 0 && (*pl)->ant)
            *pl = (*pl)->ant;

        if(cmp((*pl)->info, dato) > 0)
        {
            auxAnt = (*pl)->ant;
            auxSig = *pl;
        }
        else if(cmp((*pl)->info, dato) < 0)
        {
            auxAnt = *pl;
            auxSig = (*pl)->sig;
        }
        else return CLA_DUP;
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

void eliminarClaveListaOrdenadaSinDup(tListaDoble* pl, void* clave, tComparacion cmp)
{
    int resultadoComparacion;
    tNodo* elim;

    if(*pl == NULL)
        return;

    while((resultadoComparacion = cmp((*pl)->info, clave) > 0) && (*pl)->ant)
        pl = &(*pl)->ant;

    if(resultadoComparacion == 0)
    {
        elim = *pl;
        *pl = elim->ant;
        if(*pl != NULL)
            (*pl)->sig = elim->sig;
        free(elim->info);
        free(elim);
        return;
    }

    while((resultadoComparacion = cmp((*pl)->info, clave) < 0) && (*pl)->sig)
        pl = &(*pl)->sig;


    if(resultadoComparacion == 0)
    {
        elim = *pl;
        *pl = elim->sig;
        if(*pl != NULL)
            (*pl)->ant = elim->ant;
        free(elim->info);
        free(elim);
    }
}

int eliminarOcurrenciasClaveListaDesordenada(tListaDoble* pl, void* clave, tComparacion cmp)
{
    tListaDoble* inicio;
    tNodo* elim;

    if(!*pl)
        return LISTA_VACIA;

    inicio = &(*pl)->sig;

    while(*pl && (*pl)->ant)
    {
        if(cmp((*pl)->info, clave) == 0)
        {
            elim = *pl;
            *pl = elim->ant;
            if(*pl != NULL)
                (*pl)->sig = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
            pl = &(*pl)->ant;
    }

    while(*inicio && (*inicio)->sig)
    {
        if(cmp((*inicio)->info, clave) == 0)
        {
            elim = *inicio;
            *inicio = elim->sig;
            if(*inicio != NULL)
                (*inicio)->ant = elim->ant;
            free(elim->info);
            free(elim);
        }
        else
            inicio = &(*inicio)->sig;
    }

    return OK;
}

int resumirOcurrenciasClaveListaDesordenada(tListaDoble* pl, tComparacion cmp, tAccion2 accion)
{
    tNodo** recorre;
    tNodo* elim;

    if(*pl == NULL)
        return LISTA_VACIA;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl && (*pl)->sig)
    {
        recorre = &(*pl)->sig;
        while(*recorre)
        {
            if(cmp((*pl)->info, (*recorre)->info) == 0)
            {
                accion((*pl)->info, (*recorre)->info);
                elim = *recorre;
                *recorre = elim->sig;
                if(*recorre)
                    (*recorre)->ant = elim->ant;
                free(elim->info);
                free(elim);
            }
            else
                recorre = &(*recorre)->sig;
        }
        pl = &(*pl)->sig;
    }

    return OK;
}

void mapC(tListaDoble* pl, tAccion accion)
{
    tListaDoble* ini;

    ini = pl;

    while(*pl && (*pl)->ant)
    {
        accion(stdout, (*pl)->info);
        pl = &(*pl)->ant;
    }

    while(*ini && (*ini)->sig)
    {
        accion(stdout, (*ini)->info);
        ini = &(*ini)->sig;
    }
}

void filterC(tListaDoble* pl, const void* key, tComparacion cmp)
{
    tListaDoble* ini;
    tNodo* elim;

    ini = pl;

    while(*pl && (*pl)->ant)
    {
        if(cmp((*pl)->info, key) != 0)
        {
            elim = *pl;
            *pl = elim->ant;
            if(*pl != NULL)
                (*pl)->sig = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
            pl = &(*pl)->ant;
    }

    while(*ini && (*ini)->sig)
    {
        if(cmp((*ini)->info, key) != 0)
        {
            elim = *ini;
            *ini = elim->sig;
            if(*ini != NULL)
                (*ini)->ant = elim->ant;
            free(elim->info);
            free(elim);
        }
        else
            ini = &(*ini)->sig;
    }
}

void reduceC(tListaDoble* pl, void* acumulador, tAccion2 accion)
{
    tListaDoble* ini;

    ini = pl;

    while(*pl && (*pl)->ant)
    {
        accion(acumulador, (*pl)->info);
        pl = &(*pl)->ant;
    }

    while(*ini && (*ini)->sig)
    {
        accion(acumulador, (*ini)->info);
        ini = &(*ini)->sig;
    }
}

int insertar(tListaDoble* pl, const void* dato, unsigned tamDato)
{
    tNodo* auxSig;
    tNodo* auxAnt;
    tNodo* nuevo;

    if(*pl == NULL)
    {
        auxSig = NULL;
        auxAnt = NULL;
    }
    else
    {
        auxAnt = *pl;
        auxSig = (*pl)->sig;
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

int insertarAlInicio(tListaDoble* pl, const void* dato, unsigned tamDato)
{
    tNodo* auxSig;
    tNodo* nuevo;

    if(*pl == NULL)
        auxSig = NULL;
    else
    {
        while((*pl)->ant)
            pl = &(*pl)->ant;
        auxSig = *pl;
    }

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nuevo->info = malloc(tamDato)) == NULL){
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->ant = NULL;
    nuevo->sig = auxSig;
    if(auxSig != NULL)
        auxSig->ant = nuevo;
    *pl = nuevo;

    return OK;
}

int insertarAlFinal(tListaDoble* pl, const void* dato, unsigned tamDato)
{
    tNodo* auxAnt;
    tNodo* nuevo;

    if(*pl == NULL)
        auxAnt = NULL;
    else
    {
        while((*pl)->sig)
            pl = &(*pl)->sig;
        auxAnt = *pl;
    }

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nuevo->info = malloc(tamDato)) == NULL){
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->sig = NULL;
    nuevo->ant = auxAnt;
    if(auxAnt != NULL)
        auxAnt->sig = nuevo;
    *pl = nuevo;

    return OK;
}

int eliminarPrimerElemento(tListaDoble* pl, void* dato, unsigned tamDato)
{
    tNodo* elim;

    if(*pl == NULL)
        return LISTA_VACIA;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    elim = *pl;

    memcpy(dato, elim->info, MIN(tamDato, elim->tamInfo));
    *pl = NULL;
    free(elim->info);
    free(elim);

    return OK;
}

int eliminarUltimoElemento(tListaDoble* pl, void* dato, unsigned tamDato)
{
    tNodo* elim;

    if(*pl == NULL)
        return LISTA_VACIA;

    while((*pl)->sig)
        pl = &(*pl)->sig;

    elim = *pl;

    memcpy(dato, elim->info, MIN(tamDato, elim->tamInfo));
    *pl = NULL;
    free(elim->info);
    free(elim);

    return OK;
}

void ordenarLista(tListaDoble* pl, tComparacion cmp)
{
    tNodo** menor;
    tNodo* aux;

    if(*pl == NULL)
        return;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        menor = buscarMenor(pl, cmp);
        if(pl != menor)
        {
            aux = *menor;
            *menor = aux->sig;
            if(*menor)
                (*menor)->ant = aux->ant;
            aux->sig = *pl;
            aux->ant = (*pl)->ant;
            (*pl)->ant = aux;
            *pl = aux;
        }
        pl = &(*pl)->sig;
    }
}

tNodo** buscarMenor(const tListaDoble* pl, tComparacion cmp)
{
    tNodo** menor;

    menor = (tListaDoble*) pl;

    while(*pl)
    {
        if(cmp((*pl)->info, (*menor)->info) < 0)
            menor = (tListaDoble*) pl;
        pl = &(*pl)->sig;
    }

    return menor;
}

void acumularSumaEnteros(void* acc, const void* info)
{
    *(int*)acc = *(int*)acc + *(int*)info;
}

int cmpEnteros(const void* num1, const void* num2)
{
    return *(int*)num1 - *(int*)num2;
}

void mostrarEnteros(FILE* salida, const void* info)
{
    fprintf(salida, "%d ", *(int*)info);
}

void acumularMultEnteros(void* acc, const void* info)
{
    *(int*)acc = (*(int*)acc) * (*(int*)info);
}

int cmpNumeros(const void* num1, const void* num2)
{
    return ((tNumero*)num1)->valor - ((tNumero*)num2)->valor;
}

void mostrarNumeros(FILE* salida, const void* info)
{
    fprintf(salida, "VALOR: %3d - COINCIDENCIAS: %3d\n", ((tNumero*)info)->valor, ((tNumero*)info)->coincidencias);
}

void acumularMultNumeros(void* acc, const void* info)
{
    ((tNumero*)acc)->coincidencias = ((tNumero*)acc)->coincidencias + 1;
}
