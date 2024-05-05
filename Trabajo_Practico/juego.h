#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "archivos.h"
#include "curlReducido.h"
#include "pregunta.h"
#include <ctype.h>

typedef struct
{
    int cantRondas;
    int tiempoRound;
} tJuego;

char mostrarMenu();
int iniciarJuego();
int configurarJuego(tPregunta* bufferPreguntas);

#endif // JUEGO_H_INCLUDED
