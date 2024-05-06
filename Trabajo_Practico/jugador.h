#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"

void cargarJugadores(tJuego* juego);
void ingresarNombreJugador(int numJugador, tJugador* jugadorActual);
void mezclarJugadores(void* juego, int cantJugadores);
void intercambiarJugadores(tJugador* jugadorA, tJugador* jugadorB);
void calcularPuntajePorJugador(tJugador* jugador, int nroRonda, int menorTiempo,
                               int correctasEnMenorTiempoPorRonda);

#endif // JUGADOR_H_INCLUDED
