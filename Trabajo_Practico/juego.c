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
        mostrarOrdenJuego(&juego);
        mostrarInformacionJuego(&juego);
        iniciarTrivia(&juego);
//        mostrarResultado();
        break;
    case 'B':
        printf("¡Hasta luego!\n");
        estado = OK;
        break;
    }

    return estado;
}
/// Funcion de debugging
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

    if((estado = leerArchivoConfig(juego)) != OK)
        return estado;

    cargarJugadores(juego);
    mezclar(juego, juego->cantJugadores, mezclarJugadores);
    elegirDificultad(juego);

    if ((estado = cargarCURL(&cURL)) != OK)
        return estado;

    ///TODO: chequear las siguientes 3 lineas
    //    if((estado = verificarConectividad(&cURL)) != OK ){
    //        return estado;
    //    }

    if (cURL)
        estado = obtenerPreguntas(&cURL, juego->preguntas, juego->dificultad, juego->cantRondas);

    liberarCurl(&cURL);

//    imprimirDatosJuego(juego);

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

void mezclar(void* item, int cantElementos, void(*mezclarImpl)(void*, int))
{
    mezclarImpl(item, cantElementos);
}

void mostrarOrdenJuego(const tJuego* juego)
{
    int i;

    puts("Orden de juego:");
    for (i = 0; i < juego->cantJugadores; i++)
        printf("Turno %d: %s\n", i + 1, juego->jugadores[i].nombre);
}

void mostrarInformacionJuego(const tJuego* juego)
{
    printf("\nCantidad de rondas: %d\n", juego->cantRondas);
    printf("Tiempo por ronda: %d\n", juego->tiempoRonda);
}

void iniciarTrivia(tJuego* juego)
{
    int i;
    int rondaActual;
//    char respuesta;
    char opciones[CANT_OPCIONES][TAM_OPCION];

    for(i = 0; i < juego->cantJugadores; i++)
    {
        printf("\n%s, ¿estás listo para iniciar el juego?\n", juego->jugadores[i].nombre);
        printf("Si esta listo, ingrese una tecla para comenzar...\n");
        getch();
        fflush(stdin);
        system("cls");
        printf("Jugador actual: %s\n", juego->jugadores[i].nombre);

        for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual++)
        {
            cargarYMezclarOpciones(opciones, &juego->preguntas[rondaActual]);
            printf("Pregunta %d: %s\n", rondaActual + 1, juego->preguntas[rondaActual].pregunta);
            for (int i = 0; i < CANT_OPCIONES; i++)
                printf("%c- %s\n", 'A' + i, opciones[i]);
            printf("Respuesta: ");
//            obtenerPalabraduranteNSegundos(palabra,juego->tiempoRound);
//            memcpy(juego->tableroResp[i][rondaActual].palabra, respuesta, sizeof(char));
        }
        puts("Su turno a finalizado, ingrese una tecla para continuar");
        getch();
        system("cls");
    }
    puts("Juego terminado, ingrese cualquier tecla para continuar");
    getch();
    system("cls");
}
