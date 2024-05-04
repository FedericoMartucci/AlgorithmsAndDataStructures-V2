#include "curlReducido.h"

size_t WriteCallback(void* contents, size_t tamanyo, size_t nmemb, void *userp)
{
    size_t totalSize  = tamanyo * nmemb;
    char* responseBuffer = (char*)userp;
    printf("%u\t", totalSize);
    printf("%s\n\n", (char*)contents);
    strncpy(responseBuffer, (char*)contents, totalSize);
    responseBuffer[totalSize+1] = '\0';

    return totalSize;
}

int cargarCURL(CURL** cURL)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    *cURL = curl_easy_init();

    if(cURL == NULL)
        return NO_PUDO_CARGAR;

    struct curl_slist *headers = NULL;

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
    char url[TAM_MAX_URL];
    char response[TAM_MAX_RESPONSE];
    FILE* arch;

    abrirArchivo(&arch, "prueba.txt", "wt");

    snprintf(url, TAM_MAX_URL, "https://6636843b415f4e1a5e279b90.mockapi.io/api/v1/preguntas?nivel=%d&p=1&l=%d", dificultad, cantRounds);

    curl_easy_setopt(*cURL, CURLOPT_URL, url);
    curl_easy_setopt(*cURL, CURLOPT_TIMEOUT, 30L); // Establecer un tiempo de espera de 30 segundos
    curl_easy_setopt(*cURL, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(*cURL, CURLOPT_WRITEDATA, response);

    res = curl_easy_perform(*cURL);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));
        return ERROR_SOLICITUD;
    }
    fprintf(arch, "%s", response);
//    printf("%s", response);
    parsearPregunta(response, preguntas);

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

