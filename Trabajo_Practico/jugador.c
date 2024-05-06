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
        juego->jugadores[numJugador - 1].puntaje = 0;
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

void mezclarJugadores(void* juego, int cantJugadores)
{
    int i;
    int j;

    for(i = cantJugadores - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        if (i != j)
            intercambiarJugadores(&((tJuego*)juego)->jugadores[i],
                                  &((tJuego*)juego)->jugadores[j]);
    }
}

void intercambiarJugadores(tJugador* jugadorA, tJugador* jugadorB)
{
    tJugador temp;

    memcpy(&temp, jugadorA, sizeof(tJugador));
    memcpy(jugadorA, jugadorB, sizeof(tJugador));
    memcpy(jugadorB, &temp, sizeof(tJugador));
}

void calcularPuntajePorJugador(tJugador* jugador, int nroRonda, int menorTiempo,
                               int correctasEnMenorTiempoPorRonda)
{
    if (jugador->respuestas[nroRonda].esCorrecta)
    {
        if (jugador->respuestas[nroRonda].tiempoDeRespuesta == menorTiempo)
        {
            if(correctasEnMenorTiempoPorRonda <= 1)
            {
                jugador->respuestas[nroRonda].puntaje = PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
                jugador->puntaje += PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
            }
            else
            {
                jugador->respuestas[nroRonda].puntaje = PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
                jugador->puntaje += PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
            }
        }
        else
        {
            jugador->respuestas[nroRonda].puntaje = PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
            jugador->puntaje += PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
        }
    }
    else if (strcmp(jugador->respuestas[nroRonda].opcion, "") != 0)
    {
        jugador->respuestas[nroRonda].puntaje = PUNTOS_RESPUESTA_INCORRECTA;
        jugador->puntaje += PUNTOS_RESPUESTA_INCORRECTA;
    }
}
