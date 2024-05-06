#include "juego.h"

int main()
{
    int estado;
    srand(time(NULL));

    estado = iniciarJuego();

    return estado;
}
