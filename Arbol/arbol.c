#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion)
{
    tNodo* nuevo;
    int rc;

    while(*pa)
    {
        rc = cmp((*pa)->info, info);

        if(rc == 0)
        {
            accion((*pa)->info);
            return CLA_DUP;
        }
        else if(rc > 0)//me muevo a la izq
        {
            pa = &(*pa)->izq;
        }
        else//me muevo a la der
        {
            pa = &(*pa)->der;
        }
    }


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

int insertarEnArbol_R(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion)
{
    int resultadoComparacion;
    tNodo* nuevo;

    if(*pa == NULL)
    {
        if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
                (nuevo->info = malloc(cantBytes)) == NULL)
        {
            free(nuevo);
            return MEM_ERR;
        }
        memcpy(nuevo->info, info, cantBytes);
        nuevo->tamInfo = cantBytes;
        nuevo->der = NULL;
        nuevo->izq = NULL;
        *pa = nuevo;

        return OK;
    }

    if((resultadoComparacion = cmp((*pa)->info, info)) > 0)
        return insertarEnArbol_R(&(*pa)->izq, info, cantBytes, cmp, accion);
    if(resultadoComparacion < 0)
        return insertarEnArbol_R(&(*pa)->der, info, cantBytes, cmp, accion);
    if(accion)
        accion(info);
    return CLA_DUP;
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
    if(*pa != NULL)
    {
        recorrerInOrden(&(*pa)->izq, accion);
        accion((*pa)->info);
        recorrerInOrden(&(*pa)->der, accion);
    }
}

void recorrerPosOrden(tArbol* pa, tAccion accion)
{
    if(*pa != NULL)
    {
        recorrerPosOrden(&(*pa)->izq, accion);
        recorrerPosOrden(&(*pa)->der, accion);
        accion((*pa)->info);
    }
}

int contarNodos(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;
    return contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1;
}

//int contarNodos
//mostrar hojas
//mostrar nodos no hojas
//mostrar nodos que cumplan una condicion
//mostrar nodos hasta un nivel
//mostrar nodos de un nivel
//mostrar nodos desde un nivel
//mostrar mayor nodo
//mostrar menor nodo
//mostrar menor nodo no clave
//mostrar mayor nodo no clave
//buscar nodo devuelve:
//        - informacion
//        - nodo
//        - subarbol que tenga como raiz ese nodo



int alturaArbol(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;

    return 1 + MAX(alturaArbol(&(*pa)->izq), alturaArbol(&(*pa)->der));
}


///
void generarVectorEnteros(int* vec, int tam)
{
    int i;

    for(i = 0; i < tam; i ++)
    {
        *vec = 1 + rand() % 50;
        vec++;
    }
}

/// Funciones de mostrar
void imprimirArbol(tArbol* pa, int nivel, tAccion accion)
{
    int i;

    if (*pa == NULL)
        return;

    imprimirArbol(&(*pa)->der, nivel + 1, accion);

    for (i = 0; i < nivel; i++)
        printf("    ");

    accion((*pa)->info);
    printf("\n");

    imprimirArbol(&(*pa)->izq, nivel + 1, accion);
}

void mostrarEnteroPorConsola(const void* num)
{
    printf("%3d ", *(int*)num);
}

/// Funciones de comparacion
int cmpEnteros(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
