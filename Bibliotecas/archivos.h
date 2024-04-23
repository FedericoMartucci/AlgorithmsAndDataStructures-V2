#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TDA/pilaDinamica.h"

#define OK 0
#define MEM_ERR -2
#define FILE_ERR -3
#define FILE_OPEN_MODE_ERR -4

#define TAM_BUFFER 1000

#define TAM_PRIMER_SUMANDO 10
#define TAM_SUMANDO_MAX 1000

#define ATOI(X) (X - '0')

int generarArchivoProductos(const char* nombre, const char* tipo);
int generarArchivoNumeros(const char* nombre, const char* tipo);
int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo);
int ordenarArchivoTexto(const char* nombre, unsigned tamRegistro,
                        int(*cmp)(const void*, const void*),
                        void(*trozar)(char*, void*));
int ordenarArchivoBinario(const char* nombre, unsigned tamRegistro,
                        int(*cmp)(const void*, const void*));
int cargarPilaConNumerosDeUnArchTexto(tPila* sumando, const char* nombreArch,
                                      unsigned tamRegistro);

void mostrarNumero(FILE* destino, const void* p);
int sumarPilas(tPila* sumando1, tPila* sumando2);

#endif // ARCHIVOS_H_INCLUDED
