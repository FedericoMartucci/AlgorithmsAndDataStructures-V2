#include "archivos.h"
#include "productos.h"

int generarArchivoProductos(const char* nombre, const char* tipo)
{
    int error;
    int i;

    FILE* archivoProductos;
    tProducto loteProductos[CANT_PRODUCTOS];

    generarProductos(loteProductos, CANT_PRODUCTOS);

    if((error = abrirArchivo(&archivoProductos, nombre, tipo)) != OK)
        return error;

    if(strcmp(tipo, "BINARIO") == 0)
        fwrite(loteProductos, sizeof(tProducto), CANT_PRODUCTOS, archivoProductos);
    else if(strcmp(tipo, "TEXTO") == 0)
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

    fclose(archivoProductos);
    return OK;
}

int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo)
{
    if(strcmp(tipo, "BINARIO") == 0)
    {
        if(!(*archivoAAbrir = fopen(nombre, "wb")))
        {
            perror("The file could not be opened");
            return FILE_ERR;
        }
    }
    else if(strcmp(tipo, "TEXTO") == 0)
    {
        if(!(*archivoAAbrir = fopen(nombre, "wt")))
        {
            perror("The file could not be opened");
            return FILE_ERR;
        }
    }
    else
    {
        return FILE_OPEN_MODE_ERR;
    }

    return OK;
}
