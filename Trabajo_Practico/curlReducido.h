#ifndef CURLREDUCIDO_H_INCLUDED
#define CURLREDUCIDO_H_INCLUDED

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "pregunta.h"
#include "archivos.h"

#define NO_PUDO_CARGAR -1
#define OK 0
#define ERROR_SOLICITUD 500

#define TAM_MAX_URL 100
#define TAM_MAX_RESPONSE 100000

size_t WriteCallback(void* contents, size_t tamanyo, size_t nmemb, void *userp);
int cargarCURL(CURL** curl);
int verificarConectividad(CURL** curl);
int obtenerPreguntas(CURL** cURL, tPregunta* preguntas, int dificultad, int cantRounds);
void liberarCurl(CURL** curl);

#endif // CURLREDUCIDO_H_INCLUDED
