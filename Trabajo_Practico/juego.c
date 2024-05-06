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

