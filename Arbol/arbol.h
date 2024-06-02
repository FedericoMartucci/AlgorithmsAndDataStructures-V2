#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))
#define MAX(X, Y) ((X) > (Y)? (X) : (Y))

#define ARBOL_VACIO -1
#define MEM_ERR -2
#define CLA_DUP -3
#define FILE_ERR -4
#define ELEMENTO_ENCONTRADO 1
#define ELEMENTO_NO_ENCONTRADO 0
#define OK 0

#define TAM_VEC 8
#define TAM_BUFFER 1000

// Ejercicio 6.5
#define ES_COMPLETO 2
#define ES_BALANCEADO 3
#define ES_AVL 4
#define ES_OTRO 5

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
} tNodo;

typedef tNodo* tArbol;

typedef int(*tComparacion)(const void*, const void*);
typedef void(*tAccion)(const void*);
typedef void(*tAccion2)(void*, const void*);
typedef void(*tAccion3)(FILE*, const void*);
typedef void(*tRecorrido)(const tArbol*, void*, tAccion2);
typedef int(*tGrabarArbol)(const tArbol*, const char*, tRecorrido, tAccion2);
typedef int(*tRecuperarArbol)(tArbol* pa, const char* nombreArch, unsigned cantBytes, tComparacion cmp, tAccion accion);

void crearArbol(tArbol* pa);
int insertarEnArbol_R(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion); //Ejercicio 6.1
int insertarEnArbol_I(tArbol* pa, const void* info, unsigned cantBytes, tComparacion cmp, tAccion accion); //Ejercicio 6.1

/// Archivos
int grabarArbolEnArchivo(const tArbol* pa, const char* nombreArch,
                         tRecorrido recorrido, tAccion2 accion,
                         tGrabarArbol modoGrabado);
int grabarArbolEnArchivoBin(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido, tAccion2 accion);
int grabarArbolEnArchivoTxt(const tArbol* pa, const char* nombreArch,
                            tRecorrido recorrido, tAccion2 accion);

int recuperarArbolDeArchivo(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                            tComparacion cmp, tAccion accion, tRecuperarArbol modoRecuperado);
int recuperarArbolDeArchivoBin(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion);
int recuperarArbolDeArchivoTxt(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                               tComparacion cmp, tAccion accion);

void grabarRegistroBin(void*, const void*);
void grabarEnteroTxt(void*, const void*);
int esArchivoBinarioOrdenado(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                             tComparacion cmp, tAccion accion); //Ejercicio 6.3
int esArchivoBinarioConDuplicados(tArbol* pa, const char* nombreArch, unsigned cantBytes,
                                  tComparacion cmp, tAccion accion);
/// Recorridos
void recorrerPreOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1
void recorrerInOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1
void recorrerPosOrden(tArbol* pa, tAccion accion); //Ejercicio 6.1

void recorrerPreOrden2(const tArbol* pa, void* contexto, tAccion2 accion);
void recorrerInOrden2(const tArbol* pa, void* contexto, tAccion2 accion);
void recorrerPosOrden2(const tArbol* pa, void* contexto, tAccion2 accion);

/// Eliminar
void eliminarHoja(tArbol* pa, void* claveInfo, unsigned cantBytes, tComparacion cmp);
void podarArbolHastaAltura(tArbol* pa, int altura); //Ejercicio 6.1
void podarArbolHastaAlturaInclusive(tArbol* pa, int altura); //Ejercicio 6.1

/// Primitivas clasicas
int alturaArbol(const tArbol* pa); //Ejercicio 6.1
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
int contarYMostrarHojas(const tArbol* pa, tAccion accion);
void sumarHojas(const tArbol* pa, void* acc, tAccion2 accion);

int contarNoHojas(const tArbol* pa);
int contarYMostrarNoHojas(const tArbol* pa, tAccion accion);
void sumarNoHojas(const tArbol* pa, void* acc, tAccion2 accion);

int contarNodos(const tArbol* pa);
int contarNodosSinHijosIzq(const tArbol* pa);

/// Map - Filter - Reduce
void mapArbol(tArbol* pa, tAccion accion);
void filterArbol(const tArbol* pa, void* filtro, tComparacion cmp, tAccion accion);
void reduceArbol(const tArbol* pa, void* acc, tAccion2 accion);

/// Generar datos random
void generarVectorEnteros(int* vec, int tam);

/// Funciones de mostrar
void mostrarEntero(void*, const void*);
void mostrarEnteroPorConsola(const void*);

void mostrarNodosHoja(const tArbol* pa, tAccion accion); //Ejercicio 6.1
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

void imprimirArbol(tArbol* pa, int nivel, tAccion accion);

/// Funciones de comparacion
int cmpEnteros(const void* a, const void* b);

#endif // ARBOL_H_INCLUDED
