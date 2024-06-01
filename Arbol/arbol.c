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

/// Archivos
int grabarArbolEnArchivo(const tArbol* pa, const char* nombreArch,
                         tRecorrido recorrido, tGrabarArbol modoGrabado);
int grabarArbolEnArchivoBin(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido);
int grabarArbolEnArchivoTxt(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido);

int recuperarArbolDeArchivo(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                            tComparacion cmp, tAccion accion, tRecuperarArbol modoRecuperado);
int recuperarArbolDeArchivoBin(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion);
int recuperarArbolDeArchivoTxt(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion);

int esArchivoBinarioOrdenado(const char* nombreArch, tArbol* pa, const void* ultimoValor, tComparacion cmp); //Ejercicio 6.3

/// Recorridos
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

/// Eliminar
void eliminarHoja(tArbol* pa, void* claveInfo, unsigned cantBytes, tComparacion cmp);
void podarArbolHastaAltura(tArbol* pa, int altura); //Ejercicio 6.1
void podarArbolHastaAlturaInclusive(tArbol* pa, int altura); //Ejercicio 6.1

/// Primitivas clasicas
int alturaArbol(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;

    return 1 + MAX(alturaArbol(&(*pa)->izq), alturaArbol(&(*pa)->der));
}

int arbolVacio(const tArbol* pa);
void vaciarArbol(tArbol* pa); //Ejercicio 6.1

/// Clasificacion arbol
int esArbolCompleto(const tArbol* pa); //Ejercicio 6.4
int esArbolBalanceado(const tArbol* pa); //Ejercicio 6.4
int esArbolAVL(const tArbol* pa); //Ejercicio 6.4
int determinarTipoDeArbol(const tArbol* pa); //Ejercicio 6.5

/// Funciones de busqueda
void* buscarNodoRetornandoInfo(const tArbol* pa, const void* key, tComparacion cmp);
tNodo* buscarNodoRetornandoNodo(const tArbol* pa, const void* key, tComparacion cmp);
tArbol* buscarNodoRetornandoSubarbol(const tArbol* pa, const void* key, tComparacion cmp);

tNodo* buscarMenor(const tArbol* pa);
tNodo* buscarMayor(const tArbol* pa);

/// Funciones de contar
int contarHojas(const tArbol* pa);
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
void sumarHojas(const tArbol* pa, void* acc, tAccion2 accion);

int contarNoHojas(const tArbol* pa);
int contarYMostrarNoHojas(const tArbol* pa, tAccion accion);
void sumarNoHojas(const tArbol* pa, void* acc, tAccion2 accion);

int contarNodos(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;
    return contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1;
}

/// Map - Filter - Reduce
void mapArbol(tArbol* pa, tAccion accion);
void filterArbol(const tArbol* pa, void* filtro, tComparacion cmp, tAccion accion);
void reduceArbol(const tArbol* pa, void* acc, tAccion2 accion);

/// Generar datos random
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
void mostrarEntero(void* salida, const void* num)
{
    fprintf((FILE*)salida, "%3d ", *(int*)num);
}
void mostrarEnteroPorConsola(const void* num)
{
    printf("%3d ", *(int*)num);
}


void mostrarNodosHojas(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarNodosHojas(&(*pa)->izq, accion);
    mostrarNodosHojas(&(*pa)->der, accion);

    if((*pa)->izq == NULL && (*pa)->der == NULL)
        accion((*pa)->info);
}
void mostrarNodosNoHoja(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosSoloIzq(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosIzq(const tArbol* pa, tAccion accion); //Ejercicio 6.1
void mostrarNodosHijosDer(const tArbol* pa, tAccion accion); //Ejercicio 6.1

void mostrarNodosHastaNivel(const tArbol* pa, int nivel, tAccion accion);
void mostrarNodosDeNivel(const tArbol* pa, int nivel, tAccion accion);
void mostrarNodosDesdeNivel(const tArbol* pa, int nivel, tAccion accion);

void mostrarMayorNodo(const tArbol* pa, tAccion accion);
void mostrarMayorNodoNoClave(const tArbol* pa, void* clave, tAccion accion,
                             tComparacion cmp);
void mostrarMenorNodo(const tArbol* pa, tAccion accion);
void mostrarMenorNodoNoClave(const tArbol* pa, void* clave, tAccion accion,
                             tComparacion cmp);

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

/// Funciones de comparacion
int cmpEnteros(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
