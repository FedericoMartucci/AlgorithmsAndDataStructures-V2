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
    int esCorrecta;
    char opcion[TAM_OPCION];
} tRespuesta;

#define NOMBRE_MAX 48
#define MAX_PREGUNTAS 100

typedef struct
{
    char nombre[NOMBRE_MAX];
    int turno;
    int puntaje;
    tRespuesta respuestas[MAX_PREGUNTAS]; //utilizar lista o cola
} tJugador;

#define MIN_TIEMPO_RONDA 1
#define MIN_RONDAS 4
#define MAX_RONDAS 7
#define MAX_PREGUNTAS 100
#define MAX_JUGADORES 10

typedef struct
{
    int cantRondas;
    int tiempoRonda;
    int cantJugadores;
    int menorTiempoRespuesta[MAX_PREGUNTAS];
    enum eDificultad dificultad;
    tPregunta preguntas[MAX_PREGUNTAS]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
    tJugador jugadores[MAX_JUGADORES]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
} tJuego;

// PUNTAJES
#define PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA 3
#define PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA 2
#define PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA 1
#define PUNTOS_RESPUESTA_INCORRECTA -2

#endif // ESTRUCTURAS_H_INCLUDED
