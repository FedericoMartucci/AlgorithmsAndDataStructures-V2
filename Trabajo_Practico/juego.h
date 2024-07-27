#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlReducido.h"
#include "pregunta.h"
#include "jugador.h"
#include "estructuras.h"
#include "teclado.h"

#define SIN_JUGADORES -4

char mostrarMenu();
int iniciarJuego();
int configurarJuego(tJuego* juego);
void elegirDificultad(tJuego* juego);
void mezclar(void* item, int cantElementos, void(*mezclarImpl)(void*, int));
void mostrarOrdenJuego(const tJuego* juego);
void mostrarInformacionJuego(const tJuego* juego);
void iniciarTrivia(tJuego* juego);
void realizarRondas(tJuego* juego, int jugador);

void determinarPuntos(tJuego* juego);
int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores, int nroRonda, int menorTiempo);

#endif // JUEGO_H_INCLUDED
