#include "archivos.h"

int abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo, const char* modoApertura)
{
    if((*archivoAAbrir = fopen(nombreArchivo, modoApertura)) == NULL)
    {
        perror("No se pudo abrir/crear el archivo");
        return FILE_ERR;
    }

    return OK;
}
