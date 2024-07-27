#ifndef CARTELERA_H_INCLUDED
#define CARTELERA_H_INCLUDED

#include "reservas.h"

#define MAX_NOMBRE 31
#define MAX_LINEA 200

#define PATH_CARTELERA "cartelera.bin"

typedef int(*tComparacion)(const void*, const void*);

typedef struct
{
    int id;
    char nombre[MAX_NOMBRE];
    char horas;
    char minutos;
    int asientosDisponibles;
} tPelicula;

int generarCartelera();
void mostrarCartelera(FILE* fp);
int actualizarCartelera();
int compararCarteleraPorId(const void* a, const void* b);
int compararCarteleraPorHora(const void* a, const void* b);

#endif // CARTELERA_H_INCLUDED
