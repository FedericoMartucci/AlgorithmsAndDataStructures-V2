#include "juego.h"
#include "archivos.h"
#include "curlReducido.h"

char mostrarMenu()
{
    char opcion;

    do
    {
        puts("Bienvenido al juego:");
        puts("[A] Jugar");
        puts("[B] Salir");
        printf("Ingrese su opción: ");
        fflush(stdin);
        scanf("%c", &opcion);
        system("cls");
        printf("Opción no válida. Por favor, ingrese A o B.\n");
    }
    while(toupper(opcion) != 'B' && toupper(opcion) != 'A');

    system("cls");

    return toupper(opcion);
}

int iniciarJuego()
{
    tJuego juego;
    char opcion;
    int estado;

    opcion = mostrarMenu();

    switch(opcion)
    {
    case 'A':
        printf("¡Comencemos a jugar!\n");
        estado = configurarJuego(&juego);
//        comenzarRondas();
//        mostrarResultado();
        break;
    case 'B':
        printf("¡Hasta luego!\n");
        estado = OK;
        break;
    }

    return estado;
}

void imprimirDatosJuego(tJuego* juego)
{
    printf("Rondas: %d\n", juego->cantRondas);
    printf("Tiempo ronda: %d\n", juego->tiempoRonda);
    printf("Cant jugadores: %d\n", juego->cantJugadores);
    for(int i = 0; i < juego->cantJugadores; i++)
        printf("Jugador %d: %s\n", i, juego->jugadores[i].nombre);
    for(int i = 0; i < juego->cantRondas; i++)
        imprimirPregunta(stdout, &juego->preguntas[i]);
    printf("Dificultad: %d\n", juego->dificultad);
}

int configurarJuego(tJuego* juego)
{
    CURL* cURL;
    int estado;

    cargarJugadores(juego);
    mezclarJugadores(juego);
    elegirDificultad(juego);

    if((estado = leerArchivoConfig(juego)) != OK)
        return estado;

    if ((estado = cargarCURL(&cURL)) != OK)
        return estado;

    ///TODO: chequear las siguientes 3 lineas
    //    if((estado = verificarConectividad(&cURL)) != OK ){
    //        return estado;
    //    }

    if (cURL)
        estado = obtenerPreguntas(&cURL, juego->preguntas, juego->dificultad, juego->cantRondas);

    liberarCurl(&cURL);

    imprimirDatosJuego(juego);

    return estado;
}

void elegirDificultad(tJuego* juego)
{
    char dificultad[8];

    fprintf(stdout, "Ingrese la dificultad deseada (FACIL - MEDIA - DIFICIL): ");
    fflush(stdin);
    scanf("%7s", dificultad);

    if (strcmpi(dificultad, "FACIL") == 0) {
        juego->dificultad = FACIL;
    } else if (strcmpi(dificultad, "MEDIO") == 0) {
        juego->dificultad = MEDIO;
    } else if (strcmpi(dificultad, "DIFICIL") == 0) {
        juego->dificultad = DIFICIL;
    } else {
        juego->dificultad = DIFICIL;
    }

    system("cls");
}



