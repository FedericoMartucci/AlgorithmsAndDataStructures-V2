#include "reservas.h"
#include "cartelera.h"

int main()
{
    FILE* fp;

    generarCartelera();
    generarReservas();

    fp = fopen(PATH_CARTELERA, "rb");
    mostrarCartelera(fp);
    fclose(fp);
    actualizarCartelera();
    fp = fopen(PATH_CARTELERA, "rb");
    mostrarCartelera(fp);
    fclose(fp);
    return 0;
}
