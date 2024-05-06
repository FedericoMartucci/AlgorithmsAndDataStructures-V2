#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "estructuras.h"

void parsearPregunta(char* jsonString, void* preguntas);
void imprimirPregunta(FILE* salida, const void* pregunta);

#endif // PREGUNTA_H_INCLUDED
