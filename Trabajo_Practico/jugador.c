#include "jugador.h"

void cargarJugadores(tJuego* juego)
{
    int numJugador;
    tJugador jugadorActual;

    numJugador = 0;

    ingresarNombreJugador(numJugador + 1, &jugadorActual);

    while(strcmp(jugadorActual.nombre, "0") && numJugador < MAX_JUGADORES)
    {
        numJugador ++;
        juego->cantJugadores ++;
        memcpy(&juego->jugadores[numJugador - 1], &jugadorActual, sizeof(tJugador));
        ingresarNombreJugador(numJugador + 1, &jugadorActual);
    }
}

void ingresarNombreJugador(int numJugador, tJugador* jugadorActual)
{
    do
    {
        fprintf(stdout, "Ingrese el nombre del jugador %d o ingrese '0' para finalizar: ", numJugador);
        fflush(stdin);
        gets(jugadorActual->nombre);
    }
    while(strlen(jugadorActual->nombre) == 0);

    jugadorActual->turno = numJugador;

    system("cls");
}
