#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ColaDinamica/cola.h"
#include "pila.h"

#define OK 0
#define MEM_ERR -2
#define FILE_ERR -3
#define FILE_OPEN_MODE_ERR -4

#define TAM_BUFFER 1000

#define ATOI(X) (X - '0')
#define ES_CARACTER_ESPECIAL(X) (X == '(' || X == ')' || X == '[' || X == ']' || X == '{' || X == '}')
#define ES_CARACTER_ESPECIAL_INICIAL(X) (X == '(' || X == '[' || X == '{')
#define ES_CARACTER_ESPECIAL_FINAL(X) (X == ')' || X == ']' || X == '}')

#define CANT_CALCULOS 17
#define TAM_CALCULO_MAX 500

#define CALCULO_MAL_PARENTIZADO 1
#define CALCULO_BIEN_PARENTIZADO 0

int generarArchivoCalculos(const char* nombre, const char* tipo);
int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo);
int recorrerArchivoTextoDepurando(const char* nombre, unsigned tamRegistro,
                                  void(*trozar)(char*, void*));

int depurarCalculos(char* inicioCalculo);
void eliminarCaracteresNoEspeciales(char* calculo);
int esComplemento(char inicioCalculo, char caracterEspecialApilado);
void mostrarCalculo(FILE* destino, const void* p);
void trozarCalculos(char* cadena, void* destino);

#endif // ARCHIVOS_H_INCLUDED
