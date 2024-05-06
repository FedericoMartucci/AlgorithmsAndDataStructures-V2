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

void mezclarJugadores(tJuego* juego)
{
    int i, j;

    for(i = juego->cantJugadores - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        printf("numero rand: %d\n", j);
        if (i != j) // Verifica que los índices no sean iguales antes de intercambiar
        {
            intercambiarJugadores(&juego->jugadores[i], &juego->jugadores[j]);
        }
    }
}


void intercambiarJugadores(tJugador* jugadorA, tJugador* jugadorB)
{
    tJugador temp;

    memcpy(&temp, jugadorA, sizeof(tJugador));
    memcpy(jugadorA, jugadorB, sizeof(tJugador));
    memcpy(jugadorB, &temp, sizeof(tJugador));
}
