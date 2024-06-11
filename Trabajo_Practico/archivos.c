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

int leerArchivoConfig(tJuego* juego)
{
    FILE* archConfig;
    char linea[MAX_LINEA_CONFIG];

    if(abrirArchivo(&archConfig, "config.txt", "rt") != OK)
        return FILE_ERR;

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea, "Rounds: %d", &juego->cantRondas);

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea, "Tiempo por round: %d", &juego->tiempoRonda);

    fclose(archConfig);

    if(juego->cantRondas < MIN_RONDAS ||
            juego->cantRondas > MAX_RONDAS ||
            juego->tiempoRonda < MIN_TIEMPO_RONDA)
        return ERROR_PARAMETROS;

    return OK;
}

int imprimirResultados(const tJuego* juego)
{
    FILE* archInforme;
    int estado;
    time_t tiempoTranscurrido;
    struct tm* fechaHora;
    char nombreArch[TAM_NOMBRE_INFORME];

    generarImpresion(stdout, juego);

    tiempoTranscurrido = time(NULL);
    fechaHora = localtime(&tiempoTranscurrido);

    snprintf(nombreArch, sizeof(nombreArch),
             "informe-juego_%4d-%02d-%02d-%02d-%02d.txt",
             fechaHora->tm_year + 1900,
             fechaHora->tm_mon + 1,
             fechaHora->tm_mday,
             fechaHora->tm_hour,
             fechaHora->tm_min);

    if((estado = abrirArchivo(&archInforme, nombreArch, "wt") != OK))
        return estado;

    generarImpresion(archInforme, juego);

    fclose(archInforme);

    return OK;
}

void generarImpresion(FILE* salida, const tJuego* juego)
{
    int ronda;
    int jugador;
    int puntajeMaximo;

    calcularPuntajeMaximo(juego->jugadores, &puntajeMaximo, juego->cantJugadores);

    for (ronda = 0; ronda < juego->cantRondas; ronda++)
    {
        fprintf(salida, "%d- %s\n", ronda + 1, juego->preguntas[ronda].pregunta);
        fprintf(salida, "\tA) %s\n", juego->preguntas[ronda].opcion_1);
        fprintf(salida, "\tB) %s\n", juego->preguntas[ronda].opcion_2);
        fprintf(salida, "\tC) %s\n", juego->preguntas[ronda].opcion_3);
        fprintf(salida, "\tD) %s (Correcta)\n", juego->preguntas[ronda].resp_correcta);
        fprintf(salida, "Respuestas:\n");

        for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        {
            if(strcmp(juego->jugadores[jugador].respuestas[ronda].opcion, "") != 0)
            {
                fprintf(salida, "%s: %d segundos en contestar\t",
                        juego->jugadores[jugador].nombre,
                        juego->jugadores[jugador].respuestas[ronda].tiempoDeRespuesta);
                fprintf(salida, "%c ", obtenerLetra(juego->jugadores[jugador].respuestas[ronda].opcion, juego->preguntas[ronda]));
                if (juego->jugadores[jugador].respuestas[ronda].puntaje > 0)
                    fprintf(salida, "(+%d)\n", juego->jugadores[jugador].respuestas[ronda].puntaje);
                else
                    fprintf(salida, "(%d)\n", juego->jugadores[jugador].respuestas[ronda].puntaje);
            }
            else
                fprintf(salida, "%s: No contesta\t\t0 puntos\n", juego->jugadores[jugador].nombre);
        }
        printf("\n");
    }

    fprintf(salida, "Total\n");
    for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        fprintf(salida, "\t%s:\t%4d puntos\n",
                juego->jugadores[jugador].nombre,
                juego->jugadores[jugador].puntaje);

    fprintf(salida, "Ganador/es:\n");
    for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        if (juego->jugadores[jugador].puntaje == puntajeMaximo)
            fprintf(salida, "\t%s\n", juego->jugadores[jugador].nombre);

}

void calcularPuntajeMaximo(const tJugador* jugadores, int* puntajeMaximo, int cantJugadores)
{
    int jugador;

    *puntajeMaximo = jugadores[0].puntaje;

    for (jugador = 1; jugador < cantJugadores; jugador++)
        if (jugadores[jugador].puntaje > *puntajeMaximo)
            *puntajeMaximo = jugadores[jugador].puntaje;
}
