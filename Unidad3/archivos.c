#include "archivos.h"

int generarArchivoProductos(const char* nombre, const char* tipo)
{
    int error;
    int i;

    FILE* archivoProductos;
    tProducto loteProductos[CANT_PRODUCTOS];

    generarProductos(loteProductos, CANT_PRODUCTOS);

    if(strcmpi(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wb")) != OK)
            return error;
        fwrite(loteProductos, sizeof(tProducto), CANT_PRODUCTOS, archivoProductos);
    }
    else if(strcmpi(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_PRODUCTOS; i++)
            mostrarProducto(archivoProductos, &loteProductos[i]);
    }
    else
        return FILE_OPEN_MODE_ERR;

    fclose(archivoProductos);
    return OK;
}

int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo)
{
    if(!(*archivoAAbrir = fopen(nombre, tipo)))
    {
        perror("The file could not be opened");
        return FILE_ERR;
    }

    return OK;
}

int generarArchivoTextoFiltrado(const char* nombreArchOrigen, const char* nombreArchDestino,
                                const void* claveComp, void* registro,
                                void(*trozar)(char* buffer, void* destino),
                                int(*cmp)(const void*, const void*),
                                void(*mostrar)(FILE*, const void*))
{
    FILE* archOrigen;
    FILE* archDestino;
    char buffer[TAM_BUFFER];

    if(abrirArchivo(&archOrigen, nombreArchOrigen, "rt") != OK)
        return FILE_ERR;

    if(abrirArchivo(&archDestino, nombreArchDestino, "wt") != OK){
        fclose(archOrigen);
        return FILE_ERR;
    }

    while(fgets(buffer, TAM_BUFFER, archOrigen)){
        trozar(buffer, registro);
        if(cmp(registro, claveComp))
            mostrar(archDestino, registro);
    }

    fclose(archOrigen);
    fclose(archDestino);
    return OK;
}
