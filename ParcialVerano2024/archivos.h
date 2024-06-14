#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "palabra.h"
#include "arbol.h"

#define FILE_ERR -3

int recorrerArchivoTexto(tArbol* pa, const char* nombreArch, tAccion2 accion);

#endif // ARCHIVOS_H_INCLUDED
