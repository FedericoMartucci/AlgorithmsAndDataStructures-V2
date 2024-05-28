#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_CODIGO 8
#define TAM_DESCRIPCION 16
#define TAM_PROVEEDOR 16

#define CANT_PRODUCTOS 100
#define CANT_NUMEROS 10

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

typedef struct
{
    char codigo[TAM_CODIGO];
    char descripcion[TAM_DESCRIPCION];
    tFecha fechaCompra;
    tFecha fechaVencimiento;
    int cantidad;
    float precioCompra;
    float precioVenta;
} tProductoReducido;

void mostrarProductoSinProveedor(FILE* destino, const void* p);
void mostrarProducto(FILE* destino, const void* p);
void generarProductos(tProducto* vecProductos, int cantidad);
void trozarProducto(char* cadena, void* destino);
void trozarProductoSinProveedor(char* cadena, void* destino);
int cmpCodigo(const void* a, const void* b);
int filtrarCodigo(const void* a, const void* b);
void acumularProductosReducidos(void**, const void*);

#endif // PRODUCTOS_H_INCLUDED
