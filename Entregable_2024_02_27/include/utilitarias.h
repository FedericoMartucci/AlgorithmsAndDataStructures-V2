#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<ferreteria.h>
#include<stdio.h>
#define TAM_LINEA 50

#define ES_LETRA(x) ( ( (x) >= 65 && (x) <= 90 ) || ( (x) >= 97 && (x) <= 122 ) )

int esNumero(char car);

void crear_archivo_productos_res(const char * path);
void crear_archivo_pedidos_res(const char * path);
void generar_indice_productos_res(const char * path, const char * path_idx);

void mostrar_archivo_productos_res(const char * path);
void mostrar_archivo_pedidos_res(const char * path);
void mostrar_archivo_texto_res(const char * path);
void mostrar_indice_productos_res(const char * path);

int cmp_ind_cod_prod_res(const void *v1, const void *v2);



int leer_pedido_res(t_pedido * mov, FILE * arch_mov);
int leer_pedido(t_pedido * mov, FILE * arch_mov);

#endif // UTILITARIAS_H_INCLUDED
