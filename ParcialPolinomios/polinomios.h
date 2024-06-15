#ifndef POLINOMIOS_H_INCLUDED
#define POLINOMIOS_H_INCLUDED

#include "arbol.h"

#define CANT_TERMINOS 99999
#define TAM_LINEA 200

typedef int(*tAccion3)(tArbol*);

typedef struct
{
    int potencia;
    int coeficiente;
} tTermino;

int generarArchTextoPolinomio(const char* nombreArch);
int recorrerArchTexto(tArbol* pa, const char* nombreArch, tAccion3 accion);
int insertarPolinomioEnArbol(tArbol* pa);

/// Funciones de mostrar
void grabarTermino(void* salida, const void* termino);

/// Funciones de acumular
void acumularTermino(void* acumular, const void* acumulado);

/// Funciones de comparacion
int cmpTerminos(const void* t1, const void* t2);

#endif // POLINOMIOS_H_INCLUDED
