#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include "../Bibliotecas/productos.h"
#include "../ListaSimple/lista.h"
#include "../Bibliotecas/archivos.h"

int cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                               void (*acumular)(void**, const void*));
int cargarArchivoProductosEnListaOrdenadoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                      void (*acumular)(void**, const void*));
int cmpProductoReducido (const void* prodA, const void* prodB);
int cmpCodigoProductoReducido (const void* prodA, const void* prodB);

#endif // EJERCICIOS_H_INCLUDED
