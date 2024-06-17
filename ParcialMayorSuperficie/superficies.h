#ifndef SUPERFICIES_H_INCLUDED
#define SUPERFICIES_H_INCLUDED

#include "lista.h"
#include "arbol.h"

#define PATH_LOTE "lote.dat"

#define MAX_LOCALIDAD 51
#define CANT_REGISTROS 30
#define LIMITE_LOCALIDADES 5

typedef int(*tTipoInsercion)(tLista*, const void*, unsigned);

typedef struct
{
    int provincia;
    int poblacion;
    char localidad[MAX_LOCALIDAD];
    float superficie;
} tRegistro;

int generarLoteBinario(tArbol* pa, const char* path);
int cargarArchBinEnListaConLimite(tLista* pl, const char* path, unsigned tamReg,
                                  unsigned limite, tComparacion cmp);

void imprimirRegistro(const void* reg);

/// Funciones de comparacion
int cmpSuperficies(const void* reg1, const void* reg2);
int cmpProvincias(const void* reg1, const void* reg2);

#endif // SUPERFICIES_H_INCLUDED
