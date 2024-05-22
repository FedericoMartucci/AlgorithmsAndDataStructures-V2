#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) ((X) < (Y)? (X) : (Y))

#define CLAVE_NO_ENCONTRADA -6
#define NO_EXISTEN_N_ELEMENTOS -5
#define OVERFLOW_ERROR -4
#define LISTA_VACIA -3
#define CLAVE_DUP -2
#define MEM_ERR -1
#define OK 0

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int listaVacia(const tLista* pl);
int listaLlena(const tLista* pl, unsigned cantBytes);
int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinal(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinalOAcumulando(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*),
                              void(*acumular)(void* infoEnLista, void* tamInfo,
                                              const void* info, unsigned cantBytes));
int buscarInfoPorClave(const tLista* pl, void* info, unsigned cantBytes, const void* clave);

void mostrarNumeroPorConsola(void* num);
int cmpEnteros(const void*, const void*);
void acumularSumando(void* infoEnLista, const void* info);

/// Ejercicios de tarea
int insertarEnOrden(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*));
void ordenarPorSeleccion(tLista* pl, int(*cmp)(const void*, const void*));
tNodo** buscarMenor(const tLista* pl, int(* cmp)(const void*, const void*));
void eliminarPrimeraOcurrencia(tLista* pl, void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*));
void eliminarOcurrencias(tLista* pl, const void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*));
void eliminarUltimaOcurrencia(tLista* pl, void* info, unsigned cantBytes,
                              int(*cmp)(const void*, const void*));
void mapC(tLista* pl, void(*accion)(void*));
int filterC(tLista* pl, const void* clave,int(*cmp)(const void*, const void*));

void reduceC(tLista* pl, void* acumulador, void (*accion)(void*, const void*));
void sumOperation(void* acc, const void* value);

tLista mapPython(tLista* pl, void(*accion)(void*));
tLista filterPython(tLista* pl, const void* clave,int(*cmp)(const void*, const void*));
void eliminarClaveSinDupYEjecutarAccionClavesDup(tLista* pl, void(* accion)(void*),
                                                int(* cmp)(const void*, const void*));
int insertarEnPosicion(tLista* pl, const void* info, unsigned cantBytes, unsigned pos);
int eliminarPorPosicion(tLista* pl, void* info, unsigned cantBytes, unsigned pos);
//insertar después de una clave "n" nodos
///Si no hay "n" últimos no hago nada...
int eliminarNDespuesDeUnaClave(tLista* pl, const void* clave, int n,
                                      int (*comparar)(const void*, const void*));
int eliminarNUltimos(tLista* pl, int n);

#endif // LISTA_H_INCLUDED
