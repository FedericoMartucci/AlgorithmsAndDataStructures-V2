#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FILE_ERR -3
#define FILE_OPEN_MODE_ERR -4

#define TAM_BUFFER 1000

int generarArchivoProductos(const char* nombre, const char* tipo);
int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo);
int ordenarArchivoTexto(const char* nombre, int(*cmp)(const void*, const void*));
int ordenarArchivoBinario(const char* nombre, int(*cmp)(const void*, const void*));

#endif // ARCHIVOS_H_INCLUDED
