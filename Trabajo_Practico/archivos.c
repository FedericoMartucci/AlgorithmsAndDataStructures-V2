#include "archivos.h"


int abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo, const char* modoApertura)
{
    if((*archivoAAbrir = fopen(nombreArchivo, modoApertura)) == NULL)
    {
        perror("No se pudo abrir/crear el archivo");
        return FILE_ERR;
    }

    return OK;
}

int cargarConfiguracion(tJuego* juego, char *x_secret)
{
    FILE* archConfig;
    char linea[MAX_LINEA_CONFIG];

    if(abrirArchivo(&archConfig, "config.txt", "rt") != OK)
        return FILE_ERR;

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea,"Rounds: %d", &juego->cantRondas);

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea,"Tiempo por round: %d", &juego->tiempoRound);

    fclose(archConfig);

//    if (cargarCurl(&juego->curl,x_secret) == NO_PUDO_CARGAR)
//    {
//        juego->codigoError = ERROR_CARGA_CURL;
//        return ERROR_CARGA_CURL;
//    }
//
//    if(verificarConectividad(&juego->curl) != TODO_OK )
//    {
//        juego->codigoError = ERROR_API_NO_CONECTADA;
//        return ERROR_API_NO_CONECTADA;
//    }
//
//
//    if(juego->cantRondas <= 0 || juego->cantRondas > ('Z'-'A') || juego->tiempoRound<=0 )
//    {
//        juego->codigoError = ERROR_PARAMETROS;
//        return ERROR_PARAMETROS;
//    }
//
//    if( !(juego->letras = malloc(juego->cantRondas*sizeof(char))) )
//    {
//        juego->codigoError = MEMORIA_LLENA;
//        return MEMORIA_LLENA;
//    }
//
//    ingresarLetrasAleatoriamente(juego->letras, juego->cantRondas);

    return OK;
}
