#include "archivos.h"

int recorrerArchivoTexto(tArbol* pa, const char* nombreArch, tAccion2 accion)
{
    FILE* archLectura;
    char linea[TAM_MAX_LINEA];

    if((archLectura = fopen(nombreArch, "rt")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    while(fgets(linea, TAM_MAX_LINEA, archLectura))
        accion(pa, linea, TAM_MAX_LINEA);

    fclose(archLectura);
    return OK;
}
