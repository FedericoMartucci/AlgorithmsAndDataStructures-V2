#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include "../Bibliotecas/productos.h"
#include "../ListaSimple/lista.h"
#include "../Bibliotecas/archivos.h"

#define FIL 5
#define COL 5

typedef struct
{
    int fila;
    int columna;
    int valor;
} tElementoMatriz;

void ejercicios();


int ejercicio3();
int cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                               void (*acumular)(void**, const void*));
int cargarArchivoProductosEnListaOrdenadoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                      void (*acumular)(void**, const void*));
int cmpProductoReducido (const void* prodA, const void* prodB);
int cmpCodigoProductoReducido (const void* prodA, const void* prodB);


int ejercicio5();
void generarMatriz(int filas, int columnas, int matriz[filas][columnas], float densidad);
void insertarMatrizEnterosEnLista(tLista* pl, int filas, int columnas, int matriz[filas][columnas]);
int cmpElemMatriz(const void* elem1, const void* elem2);
void imprimirElementoMatrizPorConsola(const void* elementoMatriz);
void acumularElementoMatriz(void* elemAcumulado, const void* elemAcumular);
void mostrarMenuEj5(const tLista* pl, int filas, int columnas);
void mostrarValor(const tLista* pl, int filas, int columnas);
void mostrarFila(const tLista* pl, int filas, int columnas);
void mostrarColumna(const tLista* pl, int filas, int columnas);
void imprimirMatriz(const tLista* pl, int filas, int columnas);


int ejercicio6();
int ejercicio7();

#endif // EJERCICIOS_H_INCLUDED
