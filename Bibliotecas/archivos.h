#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FILE_ERR -3
#define FILE_OPEN_MODE_ERR -4

int generarArchivoProductos(const char* nombre, const char* tipo);
int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo);

#endif // ARCHIVOS_H_INCLUDED
