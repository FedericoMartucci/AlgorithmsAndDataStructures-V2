#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "curlReducido.h"
#include "pregunta.h"
#include "jugador.h"
#include "estructuras.h"

char mostrarMenu();
int iniciarJuego();
int configurarJuego(tJuego* juego);

#endif // JUEGO_H_INCLUDED
