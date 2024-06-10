#include "pregunta.h"
#include "juego.h"

void parsearPregunta(char* json, void* preguntas)
{

    cJSON* json_array = cJSON_Parse(json);
    cJSON* item;
    tPregunta* preguntaAux;
    int i;
    int cantPreguntas;

    cantPreguntas = cJSON_GetArraySize(json_array);
    preguntaAux = (tPregunta*) preguntas;
    if (json_array == NULL)
    {
        fprintf(stderr, "Error al parsear el JSON.\n");
        return;
    }


    for (i = 0; i < cantPreguntas; i++)
    {
        item = cJSON_GetArrayItem(json_array, i);
        if (item == NULL)
        {
            fprintf(stderr, "Error al obtener el item %d del vector del JSON.\n", i);
            return;
        }

        strcpy(preguntaAux->id, cJSON_GetObjectItem(item, "id")->valuestring);
        strcpy(preguntaAux->pregunta, cJSON_GetObjectItem(item, "pregunta")->valuestring);
        strcpy(preguntaAux->resp_correcta, cJSON_GetObjectItem(item, "resp_correcta")->valuestring);
        strcpy(preguntaAux->opcion_1, cJSON_GetObjectItem(item, "opcion_1")->valuestring);
        strcpy(preguntaAux->opcion_2, cJSON_GetObjectItem(item, "opcion_2")->valuestring);
        strcpy(preguntaAux->opcion_3, cJSON_GetObjectItem(item, "opcion_3")->valuestring);
        preguntaAux->nivel = cJSON_GetObjectItem(item, "nivel")->valueint;

        preguntaAux++;
    }

    cJSON_Delete(json_array);
}

void imprimirPregunta(FILE* salida, const void* pregunta)
{
    fprintf(salida, "ID: %s\nPregunta: %s\nRespuesta Correcta: %s\n"
            "Opción 1: %s\nOpción 2: %s\nOpción 3: %s\nNivel: %d\n\n",
            ((tPregunta*)pregunta)->id,
            ((tPregunta*)pregunta)->pregunta,
            ((tPregunta*)pregunta)->resp_correcta,
            ((tPregunta*)pregunta)->opcion_1,
            ((tPregunta*)pregunta)->opcion_2,
            ((tPregunta*)pregunta)->opcion_3,
            ((tPregunta*)pregunta)->nivel);
}

void mezclarPreguntas(void* preguntas, int cantPreguntas)
{
    int i;
    int j;

    for(i = cantPreguntas - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        if (i != j)
            intercambiarPreguntas(&((tPregunta*)preguntas)[i], &((tPregunta*)preguntas)[j]);
    }
}

void intercambiarPreguntas(tPregunta* preguntaA, tPregunta* preguntaB)
{
    tPregunta temp;

    memcpy(&temp, preguntaA, sizeof(tPregunta));
    memcpy(preguntaA, preguntaB, sizeof(tPregunta));
    memcpy(preguntaB, &temp, sizeof(tPregunta));
}

void cargarYMezclarOpciones(char opciones[][TAM_OPCION], const tPregunta* pregunta)
{
    strcpy(opciones[0], pregunta->resp_correcta);
    strcpy(opciones[1], pregunta->opcion_1);
    strcpy(opciones[2], pregunta->opcion_2);
    strcpy(opciones[3], pregunta->opcion_3);

    mezclar(opciones, CANT_OPCIONES, mezclarOpciones);
}

void mezclarOpciones(void* opciones, int cantOpciones)
{
    int i;
    int j;

    for(i = cantOpciones - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        if (i != j)
            intercambiarOpciones(opciones + TAM_OPCION * i, opciones + TAM_OPCION * j);
    }
}

void intercambiarOpciones(char* opcionA, char* opcionB)
{
    char temp[TAM_OPCION];

    strcpy(temp, opcionA);
    strcpy(opcionA, opcionB);
    strcpy(opcionB, temp);
}

void realizarPregunta(tJuego* juego, int jugador, int rondaActual)
{
    char opciones[CANT_OPCIONES][TAM_OPCION];
    int opcion;
    int tiempoDeRespuesta;
    char respuesta;

    cargarYMezclarOpciones(opciones, &juego->preguntas[rondaActual]);

    for (opcion = 0; opcion < CANT_OPCIONES; opcion++)
        printf("%c- %s\n", 'A' + opcion, opciones[opcion]);
    printf("Respuesta: ");
    tiempoDeRespuesta = iniciarTemporizador(&respuesta, juego->tiempoRonda);

    procesarRespuesta(juego, jugador, rondaActual, opciones, respuesta, tiempoDeRespuesta);
}

void procesarRespuesta(tJuego* juego, int jugador, int rondaActual,
                       char opciones[][TAM_OPCION], char respuesta,
                       int tiempoDeRespuesta)
{
    if(respuesta == '\0')
        juego->jugadores[jugador].respuestas[rondaActual].esCorrecta = 0;
    else
        juego->jugadores[jugador].respuestas[rondaActual].esCorrecta = strcmp(opciones[toupper(respuesta) - 'A'], juego->preguntas[rondaActual].resp_correcta) == 0;

    if(juego->jugadores[jugador].respuestas[rondaActual].esCorrecta == 1)
    {
        if(juego->menorTiempoRespuesta[rondaActual] == -1 || tiempoDeRespuesta < juego->menorTiempoRespuesta[rondaActual])
            juego->menorTiempoRespuesta[rondaActual] = tiempoDeRespuesta;
    }
    else
        if(juego->menorTiempoRespuesta[rondaActual] == -1)
            juego->menorTiempoRespuesta[rondaActual] = juego->tiempoRonda;

    juego->jugadores[jugador].respuestas[rondaActual].tiempoDeRespuesta = tiempoDeRespuesta;
    strcpy(juego->jugadores[jugador].respuestas[rondaActual].opcion, respuesta == '\0' ? "" : opciones[toupper(respuesta) - 'A']);
    juego->jugadores[jugador].respuestas[rondaActual].puntaje = 0;
}
