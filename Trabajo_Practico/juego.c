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
        estado = configurarJuego(&juego);
        mostrarOrdenJuego(&juego);
        mostrarInformacionJuego(&juego);
        iniciarTrivia(&juego);
        determinarPuntos(&juego);
        estado = imprimirResultados(&juego);
        break;
    case 'B':
        printf("¡Hasta luego!\n");
        estado = OK;
        break;
    }

    return estado;
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

    return estado;
}

void elegirDificultad(tJuego* juego)
{
    int i;
    char dificultad;
    tMapeoDificultad mapeo[] =
    {
        {"FACIL", FACIL},
        {"MEDIO", MEDIO},
        {"DIFICIL", DIFICIL}
    };

    fprintf(stdout, "Ingrese la dificultad deseada:\n");
    for(i = 0; i < sizeof(mapeo) / sizeof(tMapeoDificultad); i ++)
        printf("%2c: %15s\n", mapeo[i].nombre[0], mapeo[i].nombre);
    dificultad = captarIngresoDificultad(mapeo, sizeof(mapeo) / sizeof(tMapeoDificultad));

    for (i = 0; i < sizeof(mapeo) / sizeof(mapeo[0]); ++i)
    {
        if (dificultad == mapeo[i].nombre[0])
        {
            juego->dificultad = mapeo[i].valor;
            system("cls");
            return;
        }
    }
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
    printf("Tiempo por ronda: %d\n\n", juego->tiempoRonda);
}

void iniciarTrivia(tJuego* juego)
{
    int jugador;

    for(jugador = 0; jugador < juego->cantJugadores; jugador++)
    {
        printf("%s, ¿estás listo para iniciar el juego?\n", juego->jugadores[jugador].nombre);
        printf("Si esta listo, ingrese una tecla para comenzar...\n");
        getch();
        fflush(stdin);
        system("cls");
        printf("Jugador actual: %s", juego->jugadores[jugador].nombre);

        realizarRondas(juego, jugador);

        printf("\n\nSu turno ha finalizado, ingrese una tecla para continuar");
        getch();
        system("cls");
    }
    puts("Juego terminado, ingrese cualquier tecla para continuar");
    getch();
    system("cls");
}

void realizarRondas(tJuego* juego, int jugador)
{
    int rondaActual;

    for(rondaActual = 0; rondaActual < juego->cantRondas; rondaActual++)
    {
        printf("\n\nPregunta %d: %s\n", rondaActual + 1,
               juego->preguntas[rondaActual].pregunta);
        realizarPregunta(juego, jugador, rondaActual);
    }
}

void determinarPuntos(tJuego* juego)
{
    int ronda;
    int jugador;
    int correctasEnMenorTiempoPorRonda;

    for (ronda = 0; ronda < juego->cantRondas; ronda++)
    {
        correctasEnMenorTiempoPorRonda = obtenerCorrectasEnMenorTiempo(juego->jugadores, juego->cantJugadores, ronda, juego->menorTiempoRespuesta[ronda]);
        for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        {
            calcularPuntajePorJugador(&juego->jugadores[jugador], ronda,
                                      juego->menorTiempoRespuesta[ronda],
                                      correctasEnMenorTiempoPorRonda);
        }
    }
}

int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores,
                                  int nroRonda, int menorTiempo)
{
    int jugador;
    int correctasEnMenorTiempo;

    correctasEnMenorTiempo = 0;

    for (jugador = 0; jugador < cantJugadores; jugador++)
        if(jugadores[jugador].respuestas[nroRonda].esCorrecta &&
                jugadores[jugador].respuestas[nroRonda].tiempoDeRespuesta ==  menorTiempo)
            correctasEnMenorTiempo++;

    return correctasEnMenorTiempo;
}
