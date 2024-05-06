#ifndef CURLREDUCIDO_H_INCLUDED
#define CURLREDUCIDO_H_INCLUDED

#include <curl/curl.h>

#include "pregunta.h"
#include "estructuras.h"

#define NO_PUDO_CARGAR -1
#define OK 0
#define ERROR_SOLICITUD 500

#define TAM_MAX_URL 100
#define TAM_BUFFER_JSON 10000

typedef struct
{
    char json[TAM_BUFFER_JSON];
    char* buffer;
    size_t cantBytesCargados;
}tUserDataWriteCallback;

size_t WriteCallback(void* contents, size_t tamanyo, size_t nmemb, void *userp);
int cargarCURL(CURL** curl);
int verificarConectividad(CURL** curl);
int obtenerPreguntas(CURL** cURL, tPregunta* preguntas, int dificultad, int cantRounds);
void liberarCurl(CURL** curl);

#endif // CURLREDUCIDO_H_INCLUDED
