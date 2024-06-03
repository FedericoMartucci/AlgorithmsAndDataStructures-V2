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

int cargarArchivoBinarioEnArbol(tArbol* pa, const char* nombreArch,
                                unsigned cantBytes, tComparacion cmp)
{
    FILE* archLectura;
    int cantReg;
    void* reg;

    if((reg = malloc(cantBytes)) == NULL)
        return MEM_ERR;

    if((archLectura = fopen(nombreArch, "rb")) == NULL)
    {
        free(reg);
        return FILE_ERR;
    }

    fseek(archLectura, 0L, SEEK_END);
    cantReg = ftell(archLectura)/cantBytes;
    fseek(archLectura, -0L, SEEK_CUR);

    insertarBalanceadoDesdeArchOrdenado(pa, archLectura, reg, 0, cantReg - 1, cantReg, cantBytes, cmp);

    free(reg);
    fclose(archLectura);
    return OK;
}
int insertarBalanceadoDesdeArchOrdenado(tArbol* pa, FILE* archLectura, void* buffer,
                                        int li, int ls, int cantReg,
                                        unsigned cantBytes, tComparacion cmp)
{
    int regMedio;

    regMedio = (ls + li) / 2;

    if(li > ls)
        return OK;

    fseek(archLectura, regMedio * cantBytes, SEEK_SET);
    fread(buffer, cantBytes, 1, archLectura);
    fseek(archLectura, -0L, SEEK_CUR);

    insertarEnArbol_R(pa, buffer, cantBytes, cmp, NULL);

    insertarBalanceadoDesdeArchOrdenado(pa, archLectura, buffer, li, regMedio - 1, cantReg, cantBytes, cmp);//izq
    insertarBalanceadoDesdeArchOrdenado(pa, archLectura, buffer, regMedio + 1, ls, cantReg, cantBytes, cmp);//der

    return OK;
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

int eliminarRaiz(tArbol* pa)
{
    int hi;
    int hd;
    tArbol* nuevaRaiz;

    if(*pa == NULL)
        return ARBOL_VACIO;

    free((*pa)->info);

    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);

    if((*pa)->izq == NULL && (*pa)->der == NULL)
    {
        free(*pa);
        *pa = NULL;
        return OK;
    }

    nuevaRaiz = hi > hd? buscarMayor(&(*pa)->izq) : buscarMenor(&(*pa)->der);

    //elim = *nuevaRaiz
    (*pa)->info = (*nuevaRaiz)->info;
    (*pa)->tamInfo = (*nuevaRaiz)->tamInfo;
    free(*nuevaRaiz);
    if(hi > hd)
        *nuevaRaiz = (*nuevaRaiz)->izq;
    else
        *nuevaRaiz = (*nuevaRaiz)->der;
    //free(elim);
    return OK;
}

int eliminarNodo(tArbol* pa, void* claveInfo, unsigned cantBytes, tComparacion cmp)
{
    if(*pa == NULL)
        return ARBOL_VACIO;

    pa = buscarNodoRetornandoSubarbol(pa, claveInfo, cmp);
    eliminarRaiz(pa);

    return OK;
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
int esArbolCompleto(const tArbol* pa)
{
    return contarNodos(pa) == (pow(2, alturaArbol(pa)) - 1);
}
int esCompletoANivel(const tArbol* pa, int nivel)
{
    return contarNodosANivel(pa, nivel) == (pow(2, nivel) - 1);
}
int esArbolBalanceado(const tArbol* pa)
{
    return esCompletoANivel(pa, alturaArbol(pa) - 1);
}
int esArbolAVL(const tArbol* pa)
{
    int hi;
    int hd;

    if(*pa == NULL)
        return ES_AVL;

    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);

    if(abs(hi - hd) > 1)
        return !ES_AVL;

    return esArbolAVL(&(*pa)->izq) && esArbolAVL(&(*pa)->der);
}
int esArbolAVL2(const tArbol* pa, int* altura, int* cantNodos)
{
    int hi;
    int hd;
    int ni;
    int nd;
    int avlIzq;
    int avlDer;

    if(*pa == NULL)
    {
        *altura = 0;
        *cantNodos = 0;
        return ES_AVL;
    }

    avlIzq = esArbolAVL2(&(*pa)->izq, &hi, &ni);
    avlDer = esArbolAVL2(&(*pa)->der, &hd, &nd);

    *altura = 1 + MAX(hi, hd);
    *cantNodos = 1 + ni + nd;

    if (abs(hi - hd) > 1)
        return !ES_AVL;

    return avlIzq && avlDer;
}
int determinarTipoDeArbol(const tArbol* pa)
{
    int altura;
    int cantNodos;

    if (esArbolAVL2(pa, &altura, &cantNodos))
    {
        if (cantNodos == (pow(2, altura) - 1))
            return ES_COMPLETO;
        if (esCompletoANivel(pa, altura - 1))
            return ES_BALANCEADO;
        return ES_AVL;
    }

    return ES_OTRO;
}

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

tNodo** buscarMenor(const tArbol* pa)
{
    if(*pa == NULL)
        return NULL;
    if((*pa)->izq == NULL)
        return (tArbol*) pa;
    return buscarMenor(&(*pa)->izq);
}
tNodo** buscarMayor(const tArbol* pa)
{
    if(*pa == NULL)
        return NULL;
    if((*pa)->der == NULL)
        return (tArbol*) pa;
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
int contarNodosANivel(const tArbol* pa, int nivel)
{
    if(*pa == NULL)
        return 0;

    return nivel < 1? 0 : contarNodosANivel(&(*pa)->izq, nivel - 1) + contarNodosANivel(&(*pa)->der, nivel - 1) + 1;
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

    if((*pa)->der && (*pa)->der->der == NULL)
    {
        if(cmp((*pa)->der->info, clave) != 0)
            accion((*pa)->der->info);
        else if((*pa)->der->izq)
            mostrarMayorNodoNoClave(&(*pa)->der->izq, clave, accion, cmp);
        else
            accion((*pa)->info);
        return;
    }
    mostrarMayorNodoNoClave(&(*pa)->der, clave, accion, cmp);
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

    if((*pa)->izq && (*pa)->izq->izq == NULL)
    {
        if(cmp((*pa)->izq->info, clave) != 0)
            accion((*pa)->izq->info);
        else if((*pa)->izq->der)
            mostrarMayorNodoNoClave(&(*pa)->izq->der, clave, accion, cmp);
        else
            accion((*pa)->info);
        return;
    }
    mostrarMenorNodoNoClave(&(*pa)->izq, clave, accion, cmp);
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
