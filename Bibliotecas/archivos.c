#include "archivos.h"
#include "productos.h"

int generarArchivoProductos(const char* nombre, const char* tipo)
{
    int error;
    int i;

    FILE* archivoProductos;
    tProducto loteProductos[CANT_PRODUCTOS];

    generarProductos(loteProductos, CANT_PRODUCTOS);

    if(strcmp(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wb")) != OK)
            return error;
        fwrite(loteProductos, sizeof(tProducto), CANT_PRODUCTOS, archivoProductos);
    }
    else if(strcmp(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_PRODUCTOS; i++)
        {
            fprintf(archivoProductos, "%s|%s|%s|%d/%d/%d|%d/%d/%d|%d|%.2f|%.2f\n",
                    loteProductos[i].codigo,
                    loteProductos[i].descripcion,
                    loteProductos[i].proveedor,
                    loteProductos[i].fechaCompra.dia,
                    loteProductos[i].fechaCompra.mes,
                    loteProductos[i].fechaCompra.anio,
                    loteProductos[i].fechaVencimiento.dia,
                    loteProductos[i].fechaVencimiento.mes,
                    loteProductos[i].fechaVencimiento.anio,
                    loteProductos[i].cantidad,
                    loteProductos[i].precioCompra,
                    loteProductos[i].precioVenta);
        }
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

int ordenarArchivoTexto(const char* nombre, int(*cmp)(const void*, const void*))
{
    int error;
    char buffer[TAM_BUFFER];
    FILE* archAOrdenar;

    if((error = abrirArchivo(&archAOrdenar, nombre, "rt")) != OK){
        return error;
    }

    while(fgets(buffer, sizeof(buffer), archAOrdenar)){
        printf("%s", buffer);
    }

    fclose(archAOrdenar);
    return OK;
}
int ordenarArchivoBinario(const char* nombre, int(*cmp)(const void*, const void*))
{


    return OK;
}
