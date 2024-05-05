#include "curlReducido.h"

///PROBLEMA, LAS SOLICITUDES HTTP MANDAN DATOS DE A PARTES  -> SOLUCION, ESPERAR A RECIBIR TODO Y DESPUÉS PARSEAR
///La función write_callback se llama cada vez que libcurl recibe datos del servidor

size_t WriteCallback(void* contents, size_t tamanyo, size_t nmemb, void *userp)
{
    size_t totalSize = tamanyo * nmemb;

    memcpy(((tUserDataWriteCallback*)userp)->buffer, contents, totalSize);

    ((tUserDataWriteCallback*)userp)->buffer += totalSize;
    ((tUserDataWriteCallback*)userp)->cantBytesCargados += totalSize;

    return totalSize;
}

int cargarCURL(CURL** cURL)
{
    struct curl_slist* headers;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    *cURL = curl_easy_init();

    if(cURL == NULL)
        return NO_PUDO_CARGAR;

    headers = NULL;

    curl_easy_setopt(*cURL, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(*cURL, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(*cURL, CURLOPT_WRITEFUNCTION, WriteCallback);

    return OK;
}
//TODO: VERIFICAR QUE FUNCIONE
int verificarConectividad(CURL** cURL)
{
    CURLcode res;
    char url[TAM_MAX_URL]="https://www.google.com.ar";

    curl_easy_setopt(*cURL, CURLOPT_URL, url);
    res = curl_easy_perform(*cURL);

    if(res != CURLE_OK)
        return ERROR_SOLICITUD;

    return OK;
}

int obtenerPreguntas(CURL** cURL, tPregunta* preguntas, int dificultad, int cantRounds)
{
    CURLcode res;
    tUserDataWriteCallback userData;
    char url[TAM_MAX_URL];

    userData.buffer = userData.json;
    userData.cantBytesCargados = 0;

    snprintf(url, TAM_MAX_URL, "https://6636843b415f4e1a5e279b90.mockapi.io/api/v1/preguntas?nivel=%d&p=1&l=%d", dificultad, cantRounds);

    curl_easy_setopt(*cURL, CURLOPT_URL, url);
    curl_easy_setopt(*cURL, CURLOPT_TIMEOUT, 30L); // Establecer un tiempo de espera de 30 segundos
    curl_easy_setopt(*cURL, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(*cURL, CURLOPT_WRITEDATA, &userData);

    res = curl_easy_perform(*cURL);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));
        return ERROR_SOLICITUD;
    }

    parsearPregunta(userData.json, preguntas);

    return OK;
}

void liberarCurl(CURL** cURL)
{
    if(*cURL != NULL)
    {
        curl_easy_cleanup(*cURL);
        curl_global_cleanup();
    }
}

