#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "curlReducido.h"
#include "pregunta.h"

#define MIN_TIEMPO_RONDA 1
#define MIN_RONDAS 4
#define MAX_RONDAS 7
#define MAX_PREGUNTAS 100

typedef struct
{
    int cantRondas;
    int tiempoRonda;
    tPregunta preguntas[MAX_PREGUNTAS]; //Cambiar a tArbol
} tJuego;

char mostrarMenu();
int iniciarJuego();
int configurarJuego(tJuego* juego);

#endif // JUEGO_H_INCLUDED
