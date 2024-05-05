#include "juego.h"

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
    tPregunta preguntas[100];
    char opcion;
    int estado;

    opcion = mostrarMenu();

    switch(opcion)
    {
    case 'A':
        printf("¡Comencemos a jugar!\n");
        estado = configurarJuego(preguntas);
//        cargarJugadores();
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

int configurarJuego(tPregunta* bufferPreguntas)
{
    CURL *curl;
    int estado;

    if ((estado = cargarCURL(&curl)) != OK)
        return estado;

    ///TODO: chequear las siguientes 3 lineas
    //    if((estado = verificarConectividad(&curl)) != OK ){
    //        return estado;
    //    }

    if (curl)
        estado = obtenerPreguntas(&curl, bufferPreguntas, 1, 8);

    liberarCurl(&curl);

    return estado;
}

