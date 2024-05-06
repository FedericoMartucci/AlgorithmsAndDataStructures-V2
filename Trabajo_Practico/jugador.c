#include "jugador.h"

int cargarJugadores(tJuego* juego)
{
    int numJugador;
    tJugador jugadorActual;

    numJugador = 1;

    ingresarNombreJugador(numJugador, &jugadorActual);

    while(strcmp(jugadorActual.nombre, "0"))
    {
        memcpy(&juego->jugadores[numJugador - 1], &jugadorActual, sizeof(tJugador));
        juego->cantJugadores ++;
        numJugador ++;
        ingresarNombreJugador(numJugador, &jugadorActual);
    }

    return OK;
}

void ingresarNombreJugador(int numJugador, tJugador* jugadorActual)
{
    fprintf(stdout, "Ingrese el nombre del jugador %d o ingrese '0' para finalizar: ", numJugador);
    fflush(stdin);
    scanf("%s", jugadorActual->nombre);

    jugadorActual->turno = numJugador;

    system("cls");
}
