#ifndef RECURSIVIDAD_H_INCLUDED
#define RECURSIVIDAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned factorial(unsigned n);
void mostrarContenidoArrayChar(const char* str);
void mostrarContenidoArrayCharInverso(const char* str);
void mostrarCadenaConLetraMenos(const char* str);
void mostrarCadenaConLetraMenosInversa(const char* str);
void mostrarCadenaPorLetraMasWrapper(const char* str);
void mostrarCadenaPorLetraMas(const char* str, int length);
void mostrarCadenaPorLetraMasInversaWrapper(const char* str);
void mostrarCadenaPorLetraMasInversa(const char* str, int length);
void mostrarNLetras(const char *str, int n);
#endif // RECURSIVIDAD_H_INCLUDED
