#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

enum eDificultad
{
    FACIL = 1,
    MEDIO = 2,
    DIFICIL = 3
};

#define TAM_ID 4
#define TAM_PREGUNTA 256
#define TAM_OPCION 256
#define CANT_OPCIONES 4

typedef struct
{
    char id[TAM_ID];
    char pregunta[TAM_PREGUNTA];
    char resp_correcta[TAM_OPCION];
    char opcion_1[TAM_OPCION];
    char opcion_2[TAM_OPCION];
    char opcion_3[TAM_OPCION];
    enum eDificultad nivel;
} tPregunta;

typedef struct
{
    int id;
    int puntaje;
    int tiempoDeRespuesta;
    char opcion;
} tRespuesta;

#define NOMBRE_MAX 48
#define MAX_PREGUNTAS 100

typedef struct
{
    char nombre[NOMBRE_MAX];
    int turno;
    tRespuesta respuestas[MAX_PREGUNTAS]; //utilizar lista o cola
} tJugador;

#define MIN_TIEMPO_RONDA 1
#define MIN_RONDAS 4
#define MAX_RONDAS 7
#define MAX_PREGUNTAS 100
#define MAX_JUGADORES 100

typedef struct
{
    int cantRondas;
    int tiempoRonda;
    int cantJugadores;
    enum eDificultad dificultad;
    tPregunta preguntas[MAX_PREGUNTAS]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
    tJugador jugadores[MAX_JUGADORES]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
} tJuego;

#endif // ESTRUCTURAS_H_INCLUDED
