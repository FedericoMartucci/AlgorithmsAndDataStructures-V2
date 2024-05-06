#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"

//typedef struct{
//    int posRealRegistro;
//    int posSorteado;
//} tOrden;


//int compararTurnos(const void* d1,const void* d2);
//void mostrarJugador(void* dato);
//
//void imprimirNombreJugador(void* jugador,void *salida);
//
//int inicializarOrden(tOrden** orden,int cant);
//void ramdomizarOrden(tOrden* orden,int cant);
//void ordenarPorInsercionPorDatoSorteo(tOrden* vec, int ce);
//void liberarOrden(tOrden* orden);

void cargarJugadores(tJuego* juego);
void ingresarNombreJugador(int numJugador, tJugador* jugadorActual);
void mezclarJugadores(void* juego, int cantJugadores);
void intercambiarJugadores(tJugador* jugadorA, tJugador* jugadorB);

#endif // JUGADOR_H_INCLUDED
