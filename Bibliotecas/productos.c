#include "productos.h"

void imprimirProducto(const void* p) {
    printf("Código: %s\n", ((tProducto*)p)->codigo);
    printf("Descripción: %s\n", ((tProducto*)p)->descripcion);
    printf("Proveedor: %s\n", ((tProducto*)p)->proveedor);
    printf("Fecha de compra: %02d/%02d/%d\n", ((tProducto*)p)->fechaCompra.dia, ((tProducto*)p)->fechaCompra.mes, ((tProducto*)p)->fechaCompra.anio);
    printf("Fecha de vencimiento: %02d/%02d/%d\n", ((tProducto*)p)->fechaVencimiento.dia, ((tProducto*)p)->fechaVencimiento.mes, ((tProducto*)p)->fechaVencimiento.anio);
    printf("Cantidad: %d\n", ((tProducto*)p)->cantidad);
    printf("Precio de compra: %.2f\n", ((tProducto*)p)->precioCompra);
    printf("Precio de venta: %.2f\n", ((tProducto*)p)->precioVenta);
    printf("\n");
}

void generarProductos(tProducto* vecProductos, int cantidad)
{
    int i;

    for (i = 0; i < cantidad; i++) {
        sprintf(vecProductos[i].codigo, "%07d", 1000000 + rand() % 915654);
        sprintf(vecProductos[i].descripcion, "Producto %d", i + 1);
        sprintf(vecProductos[i].proveedor, "Proveedor%d", i + 1);
        vecProductos[i].fechaCompra.dia = 1 + rand() % 31;
        vecProductos[i].fechaCompra.mes = 1 + rand() % 12;
        vecProductos[i].fechaCompra.anio = 2020 + rand() % 5; // Año entre 2020 y 2024
        vecProductos[i].fechaVencimiento.dia = 1 + rand() % 31;
        vecProductos[i].fechaVencimiento.mes = 1 + rand() % 12;
        vecProductos[i].fechaVencimiento.anio = vecProductos[i].fechaCompra.anio + rand() % 3; // Vencimiento entre 0 y 2 años después de la compra
        vecProductos[i].cantidad = 1 + rand() % 100;
        vecProductos[i].precioCompra = 10 + rand() % 1000; // Precio de compra entre 10 y 1009
        vecProductos[i].precioVenta = vecProductos[i].precioCompra * 1.5; // Precio de venta es 50% más que el de compra
    }

}

int cmpCodigo(const void* a, const void* b)
{
    return strcmp(((tProducto*)a)->codigo, ((tProducto*)b)->codigo);
}
