#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "curlReducido.h"
#include "pregunta.h"
#include "jugador.h"
#include "estructuras.h"

#define RETORNO_DE_CARRO 13
#define BACKSPACE 8

char mostrarMenu();
int iniciarJuego();
int configurarJuego(tJuego* juego);
void elegirDificultad(tJuego* juego);
void mezclar(void* item, int cantElementos, void(*mezclarImpl)(void*, int));
void mostrarOrdenJuego(const tJuego* juego);
void mostrarInformacionJuego(const tJuego* juego);
void iniciarTrivia(tJuego* juego);
void realizarRondas(tJuego* juego, int jugador);
void realizarPregunta(tJuego* juego, int jugador, int rondaActual);
int iniciarTemporizador(char* respuesta, int tiempoLimite);
int esLetraValida(char key);
void determinarPuntos(tJuego* juego);
int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores,
                                  int nroRonda, int menorTiempo);

#endif // JUEGO_H_INCLUDED
