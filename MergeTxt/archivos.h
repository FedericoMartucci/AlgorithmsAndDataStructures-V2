#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_ERR -1
#define OK 0

#define MAX_COD 8
#define MAX_DESC 16

#define NUM_PRODUCTOS_LOTE_1 20
#define NUM_PRODUCTOS_LOTE_2 22

typedef struct
{
    char codigo[MAX_COD];
    char descripcion[MAX_DESC];
    int proveedor;
    float precioCompra;
    float precioVenta;
} tProducto;

void generarCodigo(char* codigo);
void generarDescripcion(char* descripcion);
int crearLoteTxt(const char* nombreArch, int cantProductos);
void imprimirProducto(void* salida, const void* producto);


#endif // ARCHIVOS_H_INCLUDED
