#ifndef EJERCICIOS_H_INCLUDED
#define EJERCICIOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Arbol/arbol.h"

#define NOMBRE_MAX 30
#define APELLIDO_MAX 30

#define CANT_PERSONAS 100000

typedef struct
{
    int dni;
    int edad;
    char nombre[NOMBRE_MAX];
    char apellido[APELLIDO_MAX];
} tPersona;

typedef struct
{
    int dni;
    unsigned nroReg;
}tIndice;

void generarNombreAleatorio(char* nombre);
void generarApellidoAleatorio(char* apellido);
int generarArchivoLotePersonas(const char* nombreArch, const char* modoApertura);
void generarIndicePersona(void* indice, const void* regLeido, int nroReg);

void mostrarPersonaPorConsola(const void* persona);
void mostrarDNIPersonaPorConsola(const void* persona);
void mostrarIndicePersona(const void* persona);
void mostrarIndicePersona2(const void* persona);
void mostrarIndicePersona3(void* salida, const void* persona);

int cmpPersonas(const void* persona1, const void* persona2);
int cmpIndPersonas(const void* persona1, const void* persona2);

/// Tests
void testear_si_el_indice_se_condice_con_el_registro_correspondiente();

#endif // EJERCICIOS_H_INCLUDED
