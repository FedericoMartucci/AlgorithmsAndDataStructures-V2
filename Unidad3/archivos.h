#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colaDinamica.h"
#include "../Bibliotecas/productos.h"

#define OK 0
#define MEM_ERR -2
#define FILE_ERR -3
#define FILE_OPEN_MODE_ERR -4
#define TAM_BUFFER 1000

int generarArchivoProductos(const char* nombre, const char* tipo);
int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo);
int generarArchivoTextoFiltrado(const char* nombreArchOrigen, const char* nombreArchDestino,
                                const void* claveComp, void* registro,
                                void(*trozar)(char* buffer, void* destino),
                                int(*cmp)(const void*, const void*),
                                void(*mostrar)(FILE*, const void*));

#endif // ARCHIVOS_H_INCLUDED
