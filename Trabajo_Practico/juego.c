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

int configurarJuego(tJuego* juego)
{
    CURL* cURL;
    int estado;

//        cargarJugadores(juego);
//        elegirDificultad();
    if((estado = leerArchivoConfig(juego)) != OK)
        return estado;

    if ((estado = cargarCURL(&cURL)) != OK)
        return estado;

    ///TODO: chequear las siguientes 3 lineas
    //    if((estado = verificarConectividad(&cURL)) != OK ){
    //        return estado;
    //    }

    if (cURL)
        estado = obtenerPreguntas(&cURL, juego->preguntas, 1, juego->cantRondas);

    liberarCurl(&cURL);
    return estado;
}

//int cargarJugadores(tJuego* juego)
//{
//    int numJugador = 1;
//    tJugador jugadorActual;
//
//    ingresarNombreJugador(numJugador, &jugadorActual);
//
//    while(*(jugadorActual.nombre) != '0')
//    {
//        if(juego->jugadoresCargados == NULL)
//        {
//            if((juego->jugadoresCargados = malloc(sizeof(tJugador))) == NULL)
//            {
//                juego->codigoError = SIN_MEMORIA;
//                return SIN_MEMORIA;
//            }
//        }
//        else if((juego->jugadoresCargados = (tJugador *)realloc(juego->jugadoresCargados,
//                                            sizeof(tJugador)*numJugador )) == NULL)
//        {
//            juego->codigoError = SIN_MEMORIA;
//            return SIN_MEMORIA;
//        }
//
//        memcpy(&juego->jugadoresCargados[numJugador - 1], &jugadorActual, sizeof(tJugador));
//        juego->cantJugadores ++;
//        numJugador ++;
//        ingresarNombreJugador(numJugador, &jugadorActual);
//    }
//    return TODO_OK;
//}
//
//void ingresarNombreJugador(int numJugador, tJugador* jugadorActual)
//{
//    fprintf(stdout, "Ingrese el nombre del jugador %d o ingrese '0' para finalizar\n", numJugador);
//    scanf("%s", jugadorActual->nombre);
//
//    jugadorActual->turno = numJugador;
//    fflush(stdin);
//
//    system("cls");
//}

