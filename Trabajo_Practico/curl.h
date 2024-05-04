#ifndef CURL_H_INCLUDED
#define CURL_H_INCLUDED

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"
#include "pregunta.h"

#define NO_PUDO_CARGAR -1
#define OK 0
#define ERROR_SOLICITUD 500
#define PALABRA_ENCONTRADA 200
#define PALABRA_NO_ENCONTRADA 204

#define TAM_MAX_URL 100
#define TAM_MAX_RESPONSE 100000

// Función que maneja la respuesta de la solicitud HTTP
size_t WriteCallback(void *contents, size_t tamanyo, size_t nmemb, void *userp);

int cargarCURL(CURL** curl);
int verificarConectividad(CURL** curl);
int enviarPalabra(CURL** curl, char* palabra);
int obtenerRespuestaPalabra(CURL** curl);
void liberarCurl(CURL** curl);

#endif // CURL_H_INCLUDED
