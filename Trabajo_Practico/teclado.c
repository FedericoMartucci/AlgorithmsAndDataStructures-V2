#include "teclado.h"


int iniciarTemporizador(char* respuesta, int tiempoLimite)
{
    char key;
    time_t startTime;
    int cursorPosition ;  // Posición del cursor en el buffer

    *respuesta = '\0';
    startTime = time(NULL);
    cursorPosition = 0;

    while (difftime(time(NULL), startTime) < tiempoLimite)
    {
        usleep(1000);  // duerme la entrada cada 1 milisegundos, importante asi para no cargar al procesador en un bucle hiper rapido
        if (_kbhit())
        {
            // Si el usuario presiona una tecla, la almacenamos
            key = _getch();
            if (key == RETORNO_DE_CARRO)    // Tecla Enter
            {
                break;        // Salir si se presiona Enter
            }
            else if (key == BACKSPACE)      // Retroceso (Backspace)
            {
                if (cursorPosition > 0)
                {
                    // Solo retroceder si no estamos al principio del buffer
                    cursorPosition--;
                    printf("\b \b");  // Retrocede y borra un carácter en la pantalla
                    *respuesta = '\0';  // Borra el carácter retrocedido en el buffer
                }
            }
            else if (esLetraValida(toupper(key)) && cursorPosition == 0)
            {
                // Almacena el carácter en el buffer y muestra en pantalla
                *respuesta = key;
                printf("%c", toupper(key));
                cursorPosition++;
            }
        }
    }

    if(difftime(time(NULL), startTime) >= tiempoLimite)
        printf("- No puede contestar, el tiempo ha finalizado");
    fflush(stdin);
    return (int)difftime(time(NULL), startTime);
}

int esLetraValida(char key)
{
    return key >= PRIMERA_OPCION_VALIDA && key <= ULTIMA_OPCION_VALIDA;
}

char captarIngresoDificultad(const tMapeoDificultad* mapeoDificultades, int cantElementos)
{
    char key;
    char opcion;
    int cursorPosition ;  // Posición del cursor en el buffer

    cursorPosition = 0;
    opcion = '\0';

    while(key != RETORNO_DE_CARRO)
    {
        if (_kbhit())
        {
            key = _getch();
            if (key == BACKSPACE)
            {
                if (cursorPosition > 0)
                {
                    cursorPosition--;
                    printf("\b \b");
                    opcion = '\0';
                }
            }
            else if (esOpcionDificultad(toupper(key), mapeoDificultades, cantElementos) &&
                     cursorPosition == 0)
            {
                opcion = toupper(key);
                printf("%c", toupper(opcion));
                cursorPosition++;
            }
        }
    }
    return opcion;
}

int esOpcionDificultad(char key, const tMapeoDificultad* mapeo, int cantElementos)
{
    int i;

    for(i = 0; i < cantElementos; i ++)
        if(mapeo[i].nombre[0] == key)
            return OPCION_VALIDA;
    return OPCION_NO_VALIDA;
}

char obtenerLetra(const char* opcion, const tPregunta* pregunta)
{
    if (strcmp(opcion, pregunta->opcion_1) == 0)
        return 'A';
    else if (strcmp(opcion, pregunta->opcion_2) == 0)
        return 'B';
    else if (strcmp(opcion, pregunta->opcion_3) == 0)
        return 'C';
    return 'D';
}
