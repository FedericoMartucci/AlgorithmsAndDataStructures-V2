#include "archivos.h"

void generarCodigo(char* codigo)
{
    int i;
    for (i = 0; i < MAX_COD - 1; i++)
    {
        codigo[i] = 'A' + rand() % 26; // Genera letras aleatorias
    }
    codigo[MAX_COD - 1] = '\0';
}

void generarDescripcion(char* descripcion)
{
    int i;
    for (i = 0; i < MAX_DESC - 1; i++)
    {
        descripcion[i] = 'a' + rand() % 26; // Genera letras aleatorias
    }
    descripcion[MAX_DESC - 1] = '\0';
}

int crearLoteTxt(const char* nombreArch, int cantProductos)
{
    FILE* archLote;
    tProducto producto;
    int i;

    if ((archLote = fopen(nombreArch, "wt")) == NULL)
    {
        perror("Error al abrir el archivo");
        return -1;
    }


    for (i = 0; i < cantProductos; i++)
    {
        generarCodigo(producto.codigo);
        generarDescripcion(producto.descripcion);
        producto.proveedor = rand() % 1000 + 1; // Proveedor entre 1 y 1000
        producto.precioCompra = (float)(rand() % 10000) / 100; // Precio compra entre 0.00 y 99.99
        producto.precioVenta = producto.precioCompra * ((rand() % 50 + 100) / 100.0); // Precio venta entre 1.00 y 1.50 veces el precio de compra
        imprimirProducto(archLote, &producto);
    }

    fclose(archLote);
    return 0;
}

int mergeArchivosTxt(const char* nombreArch1, const char* nombreArch2, )



void imprimirProducto(void* salida, const void* producto)
{
    fprintf((FILE*)salida, "%s|%s|%d|%.2f|%.2f\n",
            ((tProducto*)producto)->codigo,
            ((tProducto*)producto)->descripcion,
            ((tProducto*)producto)->proveedor,
            ((tProducto*)producto)->precioCompra,
            ((tProducto*)producto)->precioVenta);
}
