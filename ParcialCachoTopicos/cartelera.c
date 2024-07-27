#include "cartelera.h"

int generarCartelera()
{
    int i;
    FILE* archCartelera;
    tPelicula peliculas[] =
    {
        {421, "Avengers: Endgame", 10, 00, 150},
        {205, "Matrix", 15, 00, 120},
        {930, "Spider-Man: Far From Home", 12, 30, 100},
        {271, "Toy Story 4", 17, 30, 180},
        {194, "Interstellar", 20, 00, 200},
    };

    if((archCartelera = fopen(PATH_CARTELERA, "wb")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    for( i = 0; i < sizeof(peliculas)/sizeof(tPelicula); i ++)
        fwrite(&peliculas[i], sizeof(tPelicula), 1, archCartelera);

    fclose(archCartelera);
    return OK;
}

int actualizarCartelera()
{
    FILE* archCartelera;
    FILE* archReservas;
    FILE* archNoEncontrado;
    FILE* archSinDisp;
    char linea[MAX_LINEA];
    tReserva reserva;
    tPelicula pelicula;
    int rc;
    int cantReg;

    if((archCartelera = fopen(PATH_CARTELERA, "r+b")) == NULL ||
            (archReservas = fopen(PATH_RESERVAS, "rt")) == NULL ||
            (archNoEncontrado = fopen(PATH_RESERVAS_NO_ENCONTRADO, "wt")) == NULL ||
            (archSinDisp = fopen(PATH_RESERVAS_SIN_DISPONIBLIDAD, "wt")) == NULL)
    {
        fclose(archCartelera);
        fclose(archReservas);
        fclose(archNoEncontrado);
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    while(fgets(linea, MAX_LINEA, archReservas))
    {
        sscanf(linea, "%d %d", &reserva.id, &reserva.cantReservas);
        cantReg = 0;
        fread(&pelicula, sizeof(tPelicula), 1, archCartelera);
        while(!feof(archCartelera) && (rc = compararCarteleraPorId(&pelicula, &reserva)))
        {
            cantReg++;
            fread(&pelicula, sizeof(tPelicula), 1, archCartelera);
        }
        if(rc == 0)
        {
            if(reserva.cantReservas > pelicula.asientosDisponibles)
                imprimirReserva(archSinDisp, &reserva);
            else
            {
                pelicula.asientosDisponibles -= reserva.cantReservas;
                fseek(archCartelera, cantReg * sizeof(tPelicula), SEEK_SET);
                fwrite(&pelicula, sizeof(tPelicula), 1, archCartelera);
                fseek(archCartelera, 0L, SEEK_CUR);
            }
        }
        else
        {
            imprimirReserva(archNoEncontrado, &reserva);
        }
        rewind(archCartelera);
    }

    fclose(archCartelera);
    fclose(archReservas);
    fclose(archNoEncontrado);
    fclose(archSinDisp);
    return OK;
}

void mostrarCartelera(FILE* fp)
{
    tPelicula pel;

    printf("%-5s%-32s%-7s%8s\n", "Id", "Nombre", "Hora", "Butacas");
    fread(&pel, sizeof(tPelicula), 1, fp);
    while(!feof(fp))
    {
        printf("%-5d%-32s%2d:%02d%8d\n", pel.id, pel.nombre, pel.horas, pel.minutos, pel.asientosDisponibles);
        fread(&pel, sizeof(tPelicula), 1, fp);
    }

}
int compararCarteleraPorId(const void* a, const void* b)
{
    return ((tPelicula*)a)->id - ((tReserva*)b)->id;
}
int compararCarteleraPorHora(const void* a, const void* b)
{
    int rc;

    rc = ((tPelicula*)a)->horas - ((tPelicula*)b)->horas;

    return rc == 0? ((tPelicula*)a)->minutos - ((tPelicula*)b)->minutos: rc;
}
