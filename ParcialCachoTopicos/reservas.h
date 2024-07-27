#ifndef RESERVAS_H_INCLUDED
#define RESERVAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FILE_ERR -1

#define PATH_RESERVAS "reservas.txt"
#define PATH_RESERVAS_NO_ENCONTRADO "reservas-no-encontrado.txt"
#define PATH_RESERVAS_SIN_DISPONIBLIDAD "reservas-sin-disp.txt"

typedef struct
{
    int id;
    int cantReservas;
} tReserva;

int generarReservas();
void imprimirReserva(FILE* archReserva, const void* reserva);

#endif // RESERVAS_H_INCLUDED
