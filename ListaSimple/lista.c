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

int insertarAlFinalOAcumulo(tLista* pl, const void* info, unsigned cantBytes,
                               int(*cmp)(const void*, const void*),
                               void(*acumular)(void**, const void*))
{
    tNodo* nodoAInsertar;
    int comparacion;

    while(*pl && (comparacion = cmp((*pl)->info, info)))
        pl = &(*pl)->sig;

    if(comparacion == 0)
    {
        if(acumular)
        {
            acumular(&(*pl)->info, info);
            return OK;
        }

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

void mostrarNumeroPorConsola(void* num)
{
    fprintf(stdout, "%d ", *(int*)num);
}


///Ejercicios de tarea
int insertarOrdenado(tLista* pl, const void* info, unsigned cantBytes, int(* cmp)(const void*, const void*))
{
    tNodo* nuevo;

    while(*pl && cmp((*pl)->info, info) < 0)
        pl = &(*pl)->sig;

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *pl;
    *pl = nuevo;

    return OK;
}

int insertarOrdenadoAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                               void(*acumular)(void**, const void*))
{
    tNodo* nuevo;
    int resultadoComparacion;

    while(*pl && (resultadoComparacion = cmp((*pl)->info, info)) < 0)
        pl = &(*pl)->sig;

    if(resultadoComparacion == 0)
    {
        if(acumular)
        {
            acumular(&(*pl)->info, info);
            return OK;
        }
        return CLAVE_DUP;
    }

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *pl;
    *pl = nuevo;

    return OK;
}

void ordenarPorSeleccion(tLista* pl, int(* cmp)(const void*, const void*))
{
    tNodo** menor;
    tNodo* aux;

    if(*pl == NULL)
        return;

    while((*pl)->sig)
    {
        menor = buscarMenor(pl, cmp);
        if(menor != pl)
        {
            aux = *menor;
            *menor = aux->sig;
            aux->sig = *pl;
            *pl = aux;
        }
        pl = &(*pl)->sig;
    }
}

tNodo** buscarMenor(const tLista* pl, int(* cmp)(const void*, const void*))
{
    tNodo** menor;

    if(*pl == NULL)
        return NULL;

    menor = (tLista*) pl;

    while((*pl)->sig)
    {
        pl = &(*pl)->sig;
        if(cmp((*menor)->info, (*pl)->info) > 0)
            menor = (tLista*) pl;
    }

    return menor;
}

int mostrarYEliminarDuplicados(tLista* pl, const char* nombreArch,
                                int(* cmp)(const void*, const void*))
{
    tLista* recorre;
    tNodo* elim;
    FILE* archSalida;
    int duplicado;

    if(abrirArchivo(&archSalida, nombreArch, "wt") != OK)
        return -2;

    while(*pl)
    {
        duplicado = 0;
        recorre = &(*pl)->sig;
        while(*recorre)
        {
            if(cmpCodigoProductoReducido((*pl)->info, (*recorre)->info) == 0)
            {
                mostrarProductoSinProveedor(stdout, (*recorre)->info);
                mostrarProductoSinProveedor(archSalida, (*recorre)->info);
                elim = *recorre;
                *recorre = elim->sig;
                free(elim->info);
                free(elim);
                duplicado = 1;
            }
            else
            {
                recorre = &(*recorre)->sig;
            }
        }
        if(duplicado)
        {
            mostrarProductoSinProveedor(stdout, (*pl)->info);
            mostrarProductoSinProveedor(archSalida, (*pl)->info);
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
        {
            pl = &(*pl)->sig;
        }
    }

    fclose(archSalida);

    return OK;
}

void eliminarPrimeraOcurrencia(tLista* pl, void* info, unsigned cantBytes, int(* cmp)(const void*, const void*))
{
    tNodo* elim;

    while(*pl && cmp((*pl)->info, info))
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return;

    elim = *pl;
    memcpy(info, elim->info, MIN(cantBytes, elim->tamInfo));
    *pl = elim->sig;

    free(elim->info);
    free(elim);
}

void eliminarOcurrencias(tLista* pl, const void* info, unsigned cantBytes, int(* cmp)(const void*, const void*))
{
    tNodo* elim;

    while(*pl)
    {
        if(cmp((*pl)->info, info) == 0)
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
            pl = &(*pl)->sig;
    }
}

void eliminarUltimaOcurrencia(tLista* pl, void* info, unsigned cantBytes, int(* cmp)(const void*, const void*))
{
    tNodo* elim;
    tNodo** dirElim;

    elim = NULL;

    while(*pl)
    {
        if(cmp((*pl)->info, info) == 0)
        {
            elim = *pl;
            dirElim = pl;
        }
        pl = &(*pl)->sig;
    }

    if(elim == NULL)
        return;

    memcpy(info, elim->info, MIN(cantBytes, elim->tamInfo));
    *dirElim = elim->sig;

    free(elim->info);
    free(elim);
}

void mapC(tLista* pl, void(* accion)(void*))
{
    while(*pl)
    {
        accion((*pl)->info);
        pl = &(*pl)->sig;
    }
}

int filterC(tLista* pl, const void* clave, int(* cmp)(const void*, const void*))
{
    tNodo* elim;
    int cantElementos;

    cantElementos = 0;

    while(*pl)
    {
        if(cmp((*pl)->info, clave))
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
            pl = &(*pl)->sig;
        cantElementos++;
    }

    return cantElementos;
}

void reduceC(tLista* pl, void* acumulador, void (*accion)(void*, const void*))
{
    while(*pl)
    {
        accion(acumulador, (*pl)->info);
        pl = &(*pl)->sig;
    }
}

void sumOperation(void* acc, const void* value)
{
    *(int*)acc = (*(int*)acc) + (*(int*)value);
}

tLista mapPython(tLista* pl, void(* accion)(void*))
{
    tLista listaClonada;

    crearLista(&listaClonada);

    while(*pl)
    {
        accion((*pl)->info);
        insertarAlFinal(&listaClonada, (*pl)->info, (*pl)->tamInfo);
        pl = &(*pl)->sig;
    }

    return listaClonada;
}

tLista filterPython(tLista* pl, const void* clave, int(* cmp)(const void*, const void*))
{
    tNodo* elim;
    tLista listaClonada;

    crearLista(&listaClonada);

    while(*pl)
    {
        if(cmp((*pl)->info, clave))
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
        {
            insertarAlFinal(&listaClonada, (*pl)->info, (*pl)->tamInfo);
            pl = &(*pl)->sig;
        }
    }

    return listaClonada;
}

void eliminarClaveSinDupYEjecutarAccionClavesDup(tLista* pl, void(* accion)(void*),
                                                int(* cmp)(const void*, const void*))
{
    tNodo* coincidencia;
    tNodo* elim;
    tLista* ini;

    ini = pl;

    while(*pl)
    {
        coincidencia = *ini;
        while(coincidencia)
        {
            if(coincidencia != *pl && cmp(coincidencia->info, (*pl)->info) == 0)
                break;
            coincidencia = coincidencia->sig;
        }

        if(coincidencia == NULL)
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
        else
        {
            accion((*pl)->info);
            pl = &(*pl)->sig;
        }
    }
}

int insertarEnPosicion(tLista* pl, const void* info, unsigned cantBytes, unsigned pos)
{
    int i;
    tNodo* nuevo;

    i = 1;

    while(*pl && i <= pos)
    {
        pl = &(*pl)->sig;
        i ++;
    }

    if(i < pos)
        return OVERFLOW_ERROR;

    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return MEM_ERR;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *pl;
    *pl = nuevo;

    return OK;
}

int eliminarPorPosicion(tLista* pl, void* info, unsigned cantBytes, unsigned pos)
{
    tNodo* elim;

    while(*pl && pos--)
    {
        if(pos == 0)
        {
            elim = *pl;
            memcpy(info, elim->info, MIN(elim->tamInfo, cantBytes));
            *pl = elim->sig;

            free(elim->info);
            free(elim);
            return OK;
        }
        pl = &(*pl)->sig;
    }
    return OVERFLOW_ERROR;
}

int eliminarNDespuesDeUnaClave(tLista* pl, const void* clave, int n,
                                      int (*cmp)(const void*, const void*))
{
    tNodo* elim;
    tNodo* sublista;

    while(*pl && cmp(clave, (*pl)->info))
        pl = &(*pl)->sig;

    if(*pl == NULL)
        return CLAVE_NO_ENCONTRADA;
    else
        pl = &(*pl)->sig;

    sublista = *pl;

    while(sublista && n-- > 0)
        sublista = sublista->sig;

    if(n > 0)
        return NO_EXISTEN_N_ELEMENTOS;

    while(*pl && *pl != sublista)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    return OK;
}

int eliminarNUltimos(tLista* pl, int n)
{
    tNodo* elim;
    tNodo* sublista;

    sublista = *pl;

    while(sublista && n-- > 0)
        sublista = sublista->sig;

    if(n > 0)
        return NO_EXISTEN_N_ELEMENTOS;

    while(sublista)
    {
        sublista = sublista->sig;
        pl = &(*pl)->sig;
    }

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    return OK;
}

