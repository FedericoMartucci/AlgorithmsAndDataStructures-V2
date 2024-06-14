#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#include "arbol.h"
#include <ctype.h>

#define ES_LETRA(X) (((X) >= 'a' && (X) <= 'z') || ((X) >= 'A' && (X) <= 'Z'))

#define TAM_MAX_PALABRA 100
#define TAM_MAX_LINEA 1024

#define VER_PALABRA_ASCENDENTE 1
#define VER_PALABRA_DESCENDENTE 2
#define VER_PALABRA_MAYOR_REPETICIONES 3
#define VER_PALABRA_MENOR_REPETICIONES 4
#define SALIR 5

typedef struct
{
    char palabra[TAM_MAX_PALABRA];
    int cantRepeticiones;
} tPalabra;

void procesarOpcion(const tArbol* pa, int opcion);
int insertarPalabrasEnArbol(tArbol* pa, char* linea, unsigned tamLinea);
int proximaPalabra(char** palabra, char** linea);

int esLetra(char letra);

/// Funciones de acumular
void reemplazarPalabra(void* palAReemplazar, const void* pal);
void acumularPalabras(void* palAcumular, const void* pal);

/// Funciones de mostrar
void mostrarPalabra(const void* palabra);

/// Funciones de comparacion
int cmpPalabra(const void* p1, const void* p2);
int cmpRepeticiones(const void* p1, const void* p2);

#endif // PALABRA_H_INCLUDED
