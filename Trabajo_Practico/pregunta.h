#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include <stdio.h>
#include <string.h>

#include "cJSON.h"

#define TAM_ID 4
#define TAM_PREGUNTA 256
#define TAM_RESPUESTA 256

enum eDificultad
{
    FACIL = 1,
    MEDIO = 2,
    DIFICIL = 3
};

typedef struct
{
    char id[TAM_ID];
    char pregunta[TAM_PREGUNTA];
    char resp_correcta[TAM_RESPUESTA];
    char opcion_1[TAM_RESPUESTA];
    char opcion_2[TAM_RESPUESTA];
    char opcion_3[TAM_RESPUESTA];
    enum eDificultad nivel;
} tPregunta;

void parsearPregunta(char* jsonString, void* preguntas);
void imprimirPregunta(FILE* salida, const void* pregunta);

#endif // PREGUNTA_H_INCLUDED
