#include "reservas.h"

int generarReservas()
{
    int i;
    FILE* archReserva;
//    tReserva reservas[] = {
//        {421, 10},
//        {194, 250},
//        {421, 0},
//        {205, 20},
//        {271, -1},
//        {271, 151},
//        {930, 100},
//        {271, 149},
//        {194, 250},
//        {271, 1},
//    };
    tReserva reservas[] = {
        {421, 50},
        {205, 130},
        {930, 90},
        {999, 10},
        {271, 190}
    };

    if((archReserva = fopen(PATH_RESERVAS, "wt")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    for( i = 0; i < sizeof(reservas)/sizeof(tReserva); i ++)
        imprimirReserva(archReserva, &reservas[i]);

    fclose(archReserva);
    return OK;
}

void imprimirReserva(FILE* archReserva, const void* reserva)
{
    fprintf(archReserva, "%d %d\n",
            ((tReserva*)reserva)->id,
            ((tReserva*)reserva)->cantReservas);
}
