#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "pregunta.h"

#define MAX_LINEA_CONFIG 255

#define FILE_ERR -1
#define OK 0

int abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo, const char* modoApertura);

#endif // ARCHIVOS_H_INCLUDED
