#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "juego.h"
#include "estructuras.h"

#define MAX_LINEA_CONFIG 255

#define TAM_NOMBRE_INFORME 100
#define ERROR_PARAMETROS -2
#define FILE_ERR -1
#define OK 0

int abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo, const char* modoApertura);
int leerArchivoConfig(tJuego* juego);
int imprimirResultados(const tJuego* juego);
void generarImpresion(FILE* salida, const tJuego* juego);

#endif // ARCHIVOS_H_INCLUDED
