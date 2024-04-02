#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CODIGO 8
#define TAM_DESCRIPCION 16
#define TAM_PROVEEDOR 16

typedef struct {
    int dia;
    int mes;
    int anio;
} tFecha;

typedef struct {
    char codigo[TAM_CODIGO];
    char descripcion[TAM_DESCRIPCION];
    char proveedor[TAM_PROVEEDOR];
    tFecha fechaCompra;
    tFecha fechaVencimiento;
    int cantidad;
    float precioCompra;
    float precioVenta;
} tProducto;

void imprimirProducto(const void* p);
void generarProductos(tProducto* vecProductos, int cantidad);

#endif // PRODUCTOS_H_INCLUDED
