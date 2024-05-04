//#include "archivos.h"
#include "curlReducido.h"
#include "pregunta.h"
int main(void) {
    CURL *curl;
//    CURLcode res;

    tPregunta preguntas[100]; // Suponiendo que almacenarás un máximo de 100 preguntas

    if (cargarCURL(&curl) != OK)
    {
        return -1;
    }

//    if(verificarConectividad(&curl) != OK ){
//        return -2;
//    }

    if (curl) {

        obtenerPreguntas(&curl, preguntas, 1, 8); // Cambia los parámetros según tus necesidades
        puts("\n\n\n");
        obtenerPreguntas(&curl, preguntas, 3, 1); // Cambia los parámetros según tus necesidades
    }
//    for (int i = 0; i < 3; i++) {
//            imprimirPregunta(stdout, &preguntas[i]);
//        }
    liberarCurl(&curl);

    return 0;
}
