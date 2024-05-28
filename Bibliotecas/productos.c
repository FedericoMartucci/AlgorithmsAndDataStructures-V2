#include "productos.h"

void mostrarProductoSinProveedor(FILE* destino, const void* p) {
    fprintf(destino, "%s|%s|%d/%d/%d|%d/%d/%d|%d|%.2f|%.2f\n",
            ((tProductoReducido*)p)->codigo,
            ((tProductoReducido*)p)->descripcion,
            ((tProductoReducido*)p)->fechaCompra.dia,
            ((tProductoReducido*)p)->fechaCompra.mes,
            ((tProductoReducido*)p)->fechaCompra.anio,
            ((tProductoReducido*)p)->fechaVencimiento.dia,
            ((tProductoReducido*)p)->fechaVencimiento.mes,
            ((tProductoReducido*)p)->fechaVencimiento.anio,
            ((tProductoReducido*)p)->cantidad,
            ((tProductoReducido*)p)->precioCompra,
            ((tProductoReducido*)p)->precioVenta);
}

void mostrarProducto(FILE* destino, const void* p) {
    fprintf(destino, "%s|%s|%s|%d/%d/%d|%d/%d/%d|%d|%.2f|%.2f\n",
            ((tProducto*)p)->codigo,
            ((tProducto*)p)->descripcion,
            ((tProducto*)p)->proveedor,
            ((tProducto*)p)->fechaCompra.dia,
            ((tProducto*)p)->fechaCompra.mes,
            ((tProducto*)p)->fechaCompra.anio,
            ((tProducto*)p)->fechaVencimiento.dia,
            ((tProducto*)p)->fechaVencimiento.mes,
            ((tProducto*)p)->fechaVencimiento.anio,
            ((tProducto*)p)->cantidad,
            ((tProducto*)p)->precioCompra,
            ((tProducto*)p)->precioVenta);
}

void generarProductos(tProducto* vecProductos, int cantidad)
{
    int i;

    for (i = 0; i < cantidad; i++) {
        sprintf(vecProductos[i].codigo, "%07d", 1 + rand() % 9849156);
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
    return strcmp(((tProducto*)b)->codigo, ((tProducto*)a)->codigo);
//    return ((tProducto*)a)->cantidad - ((tProducto*)b)->cantidad;
}
int filtrarCodigo(const void* a, const void* b)
{
    return strcmp(((tProducto*)b)->codigo, ((tProducto*)a)->codigo) > 0;
}

void trozarProductoSinProveedor(char* cadena, void* destino)
{
    tProductoReducido* producto = (tProductoReducido*)destino;
    char* aux;

    aux = strrchr(cadena, '\n');
    *aux = '\0';

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->precioVenta = atof(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->precioCompra = atof(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->cantidad = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.anio = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.mes = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.dia = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.anio = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.mes = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.dia = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

//    strcpy(producto->proveedor, aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    strcpy(producto->descripcion, aux);

    strcpy(producto->codigo, cadena);

}

void trozarProducto(char* cadena, void* destino)
{
    tProducto* producto = (tProducto*)destino;
    char* aux;

    aux = strrchr(cadena, '\n');
    *aux = '\0';

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->precioVenta = atof(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->precioCompra = atof(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->cantidad = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.anio = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.mes = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->fechaVencimiento.dia = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.anio = atoi(aux);

    aux = strrchr(cadena, '/');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.mes = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    producto->fechaCompra.dia = atoi(aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    strcpy(producto->proveedor, aux);

    aux = strrchr(cadena, '|');
    *aux = '\0';
    aux ++;

    strcpy(producto->descripcion, aux);

    strcpy(producto->codigo, cadena);

}

void acumularProductosReducidos(void** prodAcumulado, const void* prodAAcumular) {
    tProductoReducido* acumulado = *(tProductoReducido**)prodAcumulado;
    const tProductoReducido* aAcumular = (const tProductoReducido*)prodAAcumular;

    acumulado->cantidad += aAcumular->cantidad;

    if (aAcumular->fechaCompra.anio > acumulado->fechaCompra.anio ||
        (aAcumular->fechaCompra.anio == acumulado->fechaCompra.anio && aAcumular->fechaCompra.mes > acumulado->fechaCompra.mes) ||
        (aAcumular->fechaCompra.anio == acumulado->fechaCompra.anio && aAcumular->fechaCompra.mes == acumulado->fechaCompra.mes && aAcumular->fechaCompra.dia > acumulado->fechaCompra.dia)) {
        acumulado->fechaCompra = aAcumular->fechaCompra;
    }

    if (aAcumular->fechaVencimiento.anio > acumulado->fechaVencimiento.anio ||
        (aAcumular->fechaVencimiento.anio == acumulado->fechaVencimiento.anio && aAcumular->fechaVencimiento.mes > acumulado->fechaVencimiento.mes) ||
        (aAcumular->fechaVencimiento.anio == acumulado->fechaVencimiento.anio && aAcumular->fechaVencimiento.mes == acumulado->fechaVencimiento.mes && aAcumular->fechaVencimiento.dia > acumulado->fechaVencimiento.dia)) {
        acumulado->fechaVencimiento = aAcumular->fechaVencimiento;
    }

    if (aAcumular->precioCompra > acumulado->precioCompra) {
        acumulado->precioCompra = aAcumular->precioCompra;
    }

    if (aAcumular->precioVenta > acumulado->precioVenta) {
        acumulado->precioVenta = aAcumular->precioVenta;
    }
}

