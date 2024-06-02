#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion)
{
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
        return insertarEnArbol_R(&(*pa)->izq, info, cantBytes, cmp, accion);
    if(resultadoComparacion < 0)
        return insertarEnArbol_R(&(*pa)->der, info, cantBytes, cmp, accion);
    if(accion)
        accion(info);
    return CLA_DUP;
}

/// Archivos
int grabarArbolEnArchivo(const tArbol* pa, const char* nombreArch,
                         tRecorrido recorrido, tAccion2 accion,
                         tGrabarArbol modoGrabado)
{
    return modoGrabado(pa, nombreArch, recorrido, accion);
}
int grabarArbolEnArchivoBin(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido, tAccion2 accion)
{
    FILE* archGrabar;

    if((archGrabar = fopen(nombreArch, "wb")) == NULL)
        return FILE_ERR;

    recorrido(pa, archGrabar, accion);

    fclose(archGrabar);
    return OK;
}
int grabarArbolEnArchivoTxt(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido, tAccion2 accion)
{
    FILE* archGrabar;

    if((archGrabar = fopen(nombreArch, "wt")) == NULL)
        return FILE_ERR;

    recorrido(pa, archGrabar, accion);

    fclose(archGrabar);
    return OK;
}

int recuperarArbolDeArchivo(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                            tComparacion cmp, tAccion accion, tRecuperarArbol modoRecuperado)
{
    return modoRecuperado(pa, nombreArch, cantBytes, cmp, accion);
}
int recuperarArbolDeArchivoBin(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion)
{
    FILE* archGrabar;
    void* registroLeido;

    if((registroLeido = malloc(cantBytes)) == NULL)
        return MEM_ERR;

    if((archGrabar = fopen(nombreArch, "rb")) == NULL)
    {
        free(registroLeido);
        return FILE_ERR;
    }

    fread(registroLeido, cantBytes, 1, archGrabar);
    while(!feof(archGrabar))
    {
        insertarEnArbol_R(pa, registroLeido, cantBytes, cmp, accion);
        fread(registroLeido, cantBytes, 1, archGrabar);
    }

    free(registroLeido);
    fclose(archGrabar);

    return OK;
}
//Consultar como pasar un trozar en esta strategy
int recuperarArbolDeArchivoTxt(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion)
{
    FILE* archGrabar;
    char registroLeido[TAM_BUFFER];
    int elem;

    if((archGrabar = fopen(nombreArch, "rt")) == NULL)
        return FILE_ERR;

    while(fgets(registroLeido, TAM_BUFFER, archGrabar))
    {
        elem = atoi(registroLeido);
        insertarEnArbol_R(pa, &elem, cantBytes, cmp, accion);
    }

    fclose(archGrabar);
    return OK;
}

void grabarRegistroBin(void* arch, const void* nodo)
{
    fwrite(((tNodo*)nodo)->info, ((tNodo*)nodo)->tamInfo, 1, (FILE*)arch);
}
void grabarEnteroTxt(void* arch, const void* nodo)
{
    fprintf((FILE*)arch, "%d\n", *((int*)(((tNodo*)nodo)->info)));
}
int esArchivoBinarioOrdenado(const char* nombreArch, unsigned cantBytes,
                             tComparacion cmp, tAccion accion)
{
    tArbol pa;
    FILE* archGrabar;
    void* registroLeido;
    int nodosSinHijoIzq;
    int totalNodos;

    crearArbol(&pa);

    if((registroLeido = malloc(cantBytes)) == NULL)
        return MEM_ERR;

    if((archGrabar = fopen(nombreArch, "rb")) == NULL)
    {
        free(registroLeido);
        return FILE_ERR;
    }

    fread(registroLeido, cantBytes, 1, archGrabar);
    while(!feof(archGrabar))
    {
        insertarEnArbol_R(&pa, registroLeido, cantBytes, cmp, accion);
        fread(registroLeido, cantBytes, 1, archGrabar);
    }

    nodosSinHijoIzq = contarNodosSinHijosIzq(&pa);
    totalNodos = contarNodos(&pa);

    vaciarArbol(&pa);
    free(registroLeido);
    fclose(archGrabar);

    return nodosSinHijoIzq == totalNodos;//true: ordenado, false: no ordenado
}
int esArchivoBinarioConDuplicados(const char* nombreArch, unsigned cantBytes,
                                  tComparacion cmp, tAccion accion)
{
    tArbol pa;
    FILE* archGrabar;
    void* registroLeido;
    int cantRegistros;
    int cantNodos;

    crearArbol(&pa);

    if((registroLeido = malloc(cantBytes)) == NULL)
        return MEM_ERR;

    if((archGrabar = fopen(nombreArch, "rb")) == NULL)
    {
        free(registroLeido);
        return FILE_ERR;
    }

    fread(registroLeido, cantBytes, 1, archGrabar);
    while(!feof(archGrabar))
    {
        cantRegistros ++;
        insertarEnArbol_R(&pa, registroLeido, cantBytes, cmp, accion);
        fread(registroLeido, cantBytes, 1, archGrabar);
    }

    cantNodos = contarNodos(&pa);

    vaciarArbol(&pa);
    free(registroLeido);
    fclose(archGrabar);

    return cantNodos < cantRegistros;//true: duplicados, false: no duplicados
}

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

void recorrerPreOrden2(const tArbol* pa, void* contexto, tAccion2 accion)
{
    if(*pa == NULL)
        return;

    accion(contexto, *pa);
    recorrerPreOrden2(&(*pa)->izq, contexto, accion);
    recorrerPreOrden2(&(*pa)->der, contexto, accion);
}

void recorrerInOrden2(const tArbol* pa, void* contexto, tAccion2 accion)
{
    if(*pa != NULL)
    {
        recorrerInOrden2(&(*pa)->izq, contexto, accion);
        accion(contexto, *pa);
        recorrerInOrden2(&(*pa)->der, contexto, accion);
    }
}

void recorrerPosOrden2(const tArbol* pa, void* contexto, tAccion2 accion)
{
    if(*pa != NULL)
    {
        recorrerPosOrden2(&(*pa)->izq, contexto, accion);
        recorrerPosOrden2(&(*pa)->der, contexto, accion);
        accion(contexto, *pa);
    }
}

/// Eliminar
void eliminarHoja(tArbol* pa, void* claveInfo, unsigned cantBytes, tComparacion cmp)
{
    int rc;

    if(*pa == NULL)
        return;

    rc = cmp((*pa)->info, claveInfo);
    if(rc > 0)
        eliminarHoja(&(*pa)->izq, claveInfo, cantBytes, cmp);
    else if(rc < 0)
        eliminarHoja(&(*pa)->der, claveInfo, cantBytes, cmp);
    else if((*pa)->izq == NULL && (*pa)->der == NULL)
    {
        memcpy(claveInfo, (*pa)->info, MIN((*pa)->tamInfo, cantBytes));
        free((*pa)->info);
        free(*pa);
        *pa = NULL;
    }
}
void podarArbolHastaAltura(tArbol* pa, int altura)
{
    if(*pa == NULL)
        return;
    podarArbolHastaAltura(&(*pa)->izq, altura - 1);
    podarArbolHastaAltura(&(*pa)->der, altura - 1);

    if(altura < 0)
    {
        free((*pa)->info);
        free(*pa);
        *pa = NULL;
    }
}
void podarArbolHastaAlturaInclusive(tArbol* pa, int altura)
{
    if(*pa == NULL)
        return;

    podarArbolHastaAlturaInclusive(&(*pa)->izq, altura - 1);
    podarArbolHastaAlturaInclusive(&(*pa)->der, altura - 1);

    if(altura <= 0)
    {
        free((*pa)->info);
        free(*pa);
        *pa = NULL;
    }
}

/// Primitivas clasicas
int alturaArbol(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;

    return 1 + MAX(alturaArbol(&(*pa)->izq), alturaArbol(&(*pa)->der));
}

int arbolVacio(const tArbol* pa)
{
    return *pa == NULL;
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

/// Clasificacion arbol
int esArbolCompleto(const tArbol* pa); //Ejercicio 6.4
int esArbolBalanceado(const tArbol* pa); //Ejercicio 6.4
int esArbolAVL(const tArbol* pa); //Ejercicio 6.4
int determinarTipoDeArbol(const tArbol* pa); //Ejercicio 6.5

/// Funciones de busqueda
void* buscarNodoRetornandoInfo(const tArbol* pa, const void* key, tComparacion cmp)
{
    int rc;

    if(*pa == NULL)
        return NULL;

    rc = cmp((*pa)->info, key);
    if(rc > 0)
        return buscarNodoRetornandoInfo(&(*pa)->izq, key, cmp);
    if(rc < 0)
        return buscarNodoRetornandoInfo(&(*pa)->der, key, cmp);
    return (*pa)->info;
}
tNodo* buscarNodoRetornandoNodo(const tArbol* pa, const void* key, tComparacion cmp)
{
    int rc;

    if(*pa == NULL)
        return NULL;

    rc = cmp((*pa)->info, key);
    if(rc > 0)
        return buscarNodoRetornandoNodo(&(*pa)->izq, key, cmp);
    if(rc < 0)
        return buscarNodoRetornandoNodo(&(*pa)->der, key, cmp);
    return *pa;
}
tArbol* buscarNodoRetornandoSubarbol(const tArbol* pa, const void* key, tComparacion cmp)
{
    int rc;

    if(*pa == NULL)
        return NULL;

    rc = cmp((*pa)->info, key);
    if(rc > 0)
        return buscarNodoRetornandoSubarbol(&(*pa)->izq, key, cmp);
    if(rc < 0)
        return buscarNodoRetornandoSubarbol(&(*pa)->der, key, cmp);
    return (tArbol*) pa;
}

tNodo* buscarMenor(const tArbol* pa)
{
    if(*pa == NULL)
        return NULL;
    if((*pa)->izq == NULL)
        return *pa;
    return buscarMenor(&(*pa)->izq);
}
tNodo* buscarMayor(const tArbol* pa)
{
    if(*pa == NULL)
        return NULL;
    if((*pa)->der == NULL)
        return *pa;
    return buscarMayor(&(*pa)->der);
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
void sumarHojas(const tArbol* pa, void* acc, tAccion2 accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->izq == NULL && (*pa)->der == NULL)
        accion(acc, (*pa)->info);

    sumarHojas(&(*pa)->izq, acc, accion);
    sumarHojas(&(*pa)->der, acc, accion);
}

int contarNoHojas(const tArbol* pa)
{
    int noHojasIzq;
    int noHojasDer;

    if(*pa == NULL)
        return 0;

    noHojasIzq = contarNoHojas(&(*pa)->izq);
    noHojasDer = contarNoHojas(&(*pa)->der);

    if((*pa)->izq || (*pa)->der)
        return 1 + noHojasIzq + noHojasDer;
    return noHojasIzq + noHojasDer;
}
int contarYMostrarNoHojas(const tArbol* pa, tAccion accion)
{
    int noHojasIzq;
    int noHojasDer;

    if(*pa == NULL)
        return 0;

    noHojasIzq = contarNoHojas(&(*pa)->izq);
    noHojasDer = contarNoHojas(&(*pa)->der);

    if((*pa)->izq || (*pa)->der)
    {
        accion((*pa)->info);
        return 1 + noHojasIzq + noHojasDer;
    }
    return noHojasIzq + noHojasDer;
}

void sumarNoHojas(const tArbol* pa, void* acc, tAccion2 accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->izq || (*pa)->der)
        accion(acc, (*pa)->info);

    sumarNoHojas(&(*pa)->izq, acc, accion);
    sumarNoHojas(&(*pa)->der, acc, accion);
}

int contarNodos(const tArbol* pa)
{
    if(*pa == NULL)
        return 0;
    return contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1;
}

int contarNodosSinHijosIzq(const tArbol* pa)
{
    int tieneHijoIzq;

    if(*pa == NULL)
        return 0;
    tieneHijoIzq = (*pa)->izq == NULL? 1 : 0;
    return contarNodosSinHijosIzq(&(*pa)->izq) + contarNodosSinHijosIzq(&(*pa)->der) + tieneHijoIzq;
}

/// Map - Filter - Reduce
void mapArbol(tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return
    mapArbol(&(*pa)->izq, accion);
    mapArbol(&(*pa)->der, accion);
    accion((*pa)->info);
}
void filterArbol(tArbol* pa, void* filtro, tComparacion cmp, tAccion accion)
{
    if(*pa == NULL)
        return
    filterArbol(&(*pa)->izq, filtro, cmp, accion);
    filterArbol(&(*pa)->der, filtro, cmp, accion);
    if(cmp((*pa)->info, filtro) == 0)
        accion((*pa)->info);
    else
    {
        free((*pa)->info);
        free(*pa);
        *pa = NULL;
    }
}
void reduceArbol(const tArbol* pa, void* acc, tAccion2 accion)
{
    if(*pa == NULL)
        return
    reduceArbol(&(*pa)->izq, acc, accion);
    reduceArbol(&(*pa)->der, acc, accion);
    accion(acc, (*pa)->info);
}

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
void mostrarNodosNoHoja(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->izq || (*pa)->der)
        accion((*pa)->info);

    mostrarNodosNoHoja(&(*pa)->izq, accion);
    mostrarNodosNoHoja(&(*pa)->der, accion);
}
void mostrarNodosHijosSoloIzq(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->izq || (*pa)->der == NULL)
        accion((*pa)->info);

    mostrarNodosHijosSoloIzq(&(*pa)->izq, accion);
    mostrarNodosHijosSoloIzq(&(*pa)->der, accion);
}
void mostrarNodosHijosIzq(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->izq)
        accion((*pa)->info);

    mostrarNodosHijosIzq(&(*pa)->izq, accion);
    mostrarNodosHijosIzq(&(*pa)->der, accion);
}
void mostrarNodosHijosDer(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    if((*pa)->der)
        accion((*pa)->info);

    mostrarNodosHijosDer(&(*pa)->izq, accion);
    mostrarNodosHijosDer(&(*pa)->der, accion);
}
void mostrarNodosHastaNivel(const tArbol* pa, int nivel, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarNodosHastaNivel(&(*pa)->izq, nivel - 1, accion);
    if(nivel > 0)
        accion((*pa)->info);
    mostrarNodosHastaNivel(&(*pa)->der, nivel - 1, accion);
}
void mostrarNodosDeNivel(const tArbol* pa, int nivel, tAccion accion)
{
    if(*pa == NULL)
        return;
    if(nivel > 0)
    {
        mostrarNodosDeNivel(&(*pa)->izq, nivel - 1, accion);
        mostrarNodosDeNivel(&(*pa)->der, nivel - 1, accion);
    }
    if(nivel == 1)
        accion((*pa)->info);
}
void mostrarNodosDesdeNivel(const tArbol* pa, int nivel, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarNodosDesdeNivel(&(*pa)->izq, nivel - 1, accion);
    mostrarNodosDesdeNivel(&(*pa)->der, nivel - 1, accion);
    if(nivel <= 1)
        accion((*pa)->info);
}

void mostrarMayorNodo(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarMayorNodo(&(*pa)->der, accion);

    if((*pa)->der == NULL)
        accion((*pa)->info);
}
void mostrarMayorNodoNoClave(const tArbol* pa, void* clave, tAccion accion,
                             tComparacion cmp)
{
    if(*pa == NULL)
        return;

    mostrarMayorNodoNoClave(&(*pa)->der, clave, accion, cmp);

    if((*pa)->der == NULL)
    {
        if(cmp((*pa)->info, clave) != 0)
            accion((*pa)->info);
        else
            mostrarMayorNodoNoClave(&(*pa)->izq, clave, accion, cmp);
    }
}
void mostrarMenorNodo(const tArbol* pa, tAccion accion)
{
    if(*pa == NULL)
        return;

    mostrarMenorNodo(&(*pa)->izq, accion);

    if((*pa)->izq == NULL)
        accion((*pa)->info);
}
void mostrarMenorNodoNoClave(const tArbol* pa, void* clave, tAccion accion,
                             tComparacion cmp)
{
        if(*pa == NULL)
        return;

    mostrarMenorNodoNoClave(&(*pa)->izq, clave, accion, cmp);

    if((*pa)->izq == NULL)
    {
        if(cmp((*pa)->info, clave) != 0)
            accion((*pa)->info);
        else
            mostrarMenorNodoNoClave(&(*pa)->der, clave, accion, cmp);
    }
}

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
