#ifndef FERRETERIA_H_INCLUDED
#define FERRETERIA_H_INCLUDED

#define PATH_PRODUCTOS "../Archivos/productos.dat"
#define PATH_INDICE_PRODUCTOS "../Archivos/productos.idx"
#define PATH_PEDIDOS "../Archivos/pedidos.txt"

#include "../include/arbol.h"
#include "../include/cola_dinamica.h"
#include <stdbool.h>

typedef struct {
    char cod [10];
    char descripcion[20];
    unsigned stock;
    float precio;
} t_producto_stock;

typedef struct {
    unsigned cod_ped;
    char cod_prod [11];
    unsigned cant;
    bool faltante;
} t_pedido;

typedef struct {
    char cod_prod [11];
    unsigned nro_reg;
} t_reg_ind;

void realizarInforme(tCola *Pedidos, tArbolBinBusq *Indices, FILE *pfProds);

int verificarStockPedido(tArbolBinBusq *Indices, t_reg_ind regIndice, t_pedido regPedido, FILE *pf);

int compararIndices(const void *reg1, const void *reg2);

void formatearLineaPedido(char *linea, t_pedido *regPedidoActual);

int cargarIndice(tArbolBinBusq *pa);

void actualizarIndices(tArbolBinBusq *pa);

void escribirArchivoBin(void *info, unsigned tam, void *recurso);

int procesar_pedidos_propia(const char * path_prods, const char * path_pedidos, const char * path_indice);

int procesar_pedidos(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_res(const char * path_prods, const char * path_pedidos, const char * path_indice);


int procesar_pedidos_simple(const char * path_prods, const char * path_pedidos, const char * path_indice);
int procesar_pedidos_simple_res(const char * path_prods, const char * path_pedidos, const char * path_indice);

#endif // FERRETERIA_H_INCLUDED
