#ifndef RECURSIVIDAD_H_INCLUDED
#define RECURSIVIDAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ATOI(X) (X - '0')
#define ES_LETRA(X) (((X) >= 'a' && (X) <= 'z') || ((X) >= 'A' && (X) <= 'Z'))
#define A_MAYUS(X) (((X) >= 'a' && (X) <= 'z')? (X - ('a' - 'A')) : (X))

#define PHI ((1 + sqrt(5)) / 2)
#define NO_ES_PALINDROMO 0
#define ES_PALINDROMO 1

unsigned factorialRecCola(unsigned n, unsigned acumulador);
unsigned factorialRec(unsigned n);

unsigned fibonacci(unsigned n);
unsigned fibonacciRec(unsigned n);
unsigned fibonacciRecCopia(unsigned n, int* contador);
unsigned fibonacciProgDin(unsigned n);
unsigned fibonacciProgDinCopia(unsigned n, long long unsigned* contador);

void mostrarCadPorLetra(const char* cad);
void mostrarCadPorLetraInv(const char* cad);
void mostrarCadPorLetraIdaYVuelta(const char* cad);

void mostrarCadConLetraMenos(const char* cad);
void mostrarCadConLetraMenosInv(const char* cad);
void mostrarCadConLetraMenosIdaYVuelta(const char* cad);

void mostrarCadConLetraFinalMenosEnvoltorio(const char* cad);
void mostrarCadConLetraFinalMenosInvEnvoltorio(const char* cad);
void mostrarCadConLetraFinalMenosIdaYVueltaEnvoltorio(const char* cad);
void mostrarCadConLetraFinalMenos(const char* cad, int longitud);
void mostrarCadConLetraFinalMenosInv(const char* cad, int longitud);
void mostrarCadConLetraFinalMenosIdaYVuelta(const char* cad, int longitud);

void mostrarEnteroPorDigito(int num);
void mostrarEnteroPorDigitoInv(int num);
void mostrarEnteroPorDigitoIdaYVuelta(int num);

void mostrarEnteroConDigitoMenos(int num, int modulo);
void mostrarEnteroConDigitoMenosInv(int num, int modulo);
void mostrarEnteroConDigitoMenosIdaYVuelta(int num, int modulo);

void mostrarEnteroConDigitoFinalMenos(int num);
void mostrarEnteroConDigitoFinalMenosInv(int num);
void mostrarEnteroConDigitoFinalMenosIdaYVuelta(int num);

int sumarDigitosEntero(int num);
int sumarDigitosCadena(const char* cadNumeros);
void mapArrayRec(int* vec, int ce, int* acumulador, void(*accion)(void*, const void*));
void mapArrayRecInv(int* vec, int ce, int* acumulador, void(*accion)(void*, const void*));
void sumarNumerosPosParesArray(const int* vec, int ce, int* acumulador);

void mostrarNCaracteres(const char* cad, int n);

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes);
int insertarAlFinalRec(tLista* pl, const void* info, unsigned cantBytes);
void mapRecursivo(const tLista* pl, void(*accion)(void*));
void mapRecursivoInv(const tLista* pl, void(*accion)(void*));

void imprimirEnteroPorConsola(void* num);

void imprimirEnteroPorConsola2(void* salida, const void* num);
void sumarEntero(void* acc, const void* num);
void sumarEnteroPar(void* acc, const void* num);

int strlenRec(const char* cad);
char* strchrRec(const char* cad, char val);
char* strrchrRecWrapper(const char* cad, char val);
char* strrchrRec(const char* cad, char val, int longitud);

int calcularPotencia(int base, int exponente);
int calcularProducto(int factor1, int factor2);
int decimalABinarioWrapper(int num);
int decimalABinario(int num, int factor);
int algoritmoAckerman(int m, int n);

int esPalindromoWrapper(const char* cad);
int esPalindromo(const char* ini, const char* fin);

void* binarySearchRec(const void *key, const void *base, size_t nitems,
                     size_t size, int (*cmp)(const void *, const void*));
int cmpEnteros(const void* a, const void* b);

#endif // RECURSIVIDAD_H_INCLUDED
