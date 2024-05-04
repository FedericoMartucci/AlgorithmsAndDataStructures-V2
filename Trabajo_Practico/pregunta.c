#include "pregunta.h"

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
//        imprimirPregunta(stdout, preguntaAux);
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
