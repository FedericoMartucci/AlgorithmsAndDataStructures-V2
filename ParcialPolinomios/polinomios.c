#include "polinomios.h"

int generarArchTextoPolinomio(const char* nombreArch)
{
    int i;
    tTermino termino;
    FILE* archEscritura;

    if((archEscritura = fopen(nombreArch, "wt")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    for(i = 0; i < CANT_TERMINOS; i ++)
    {
        termino.potencia = rand() % 10000 + 1;
        termino.coeficiente = (rand() % 100 + 1) * (((i % 2) == 0)? (-1) : (1));
        grabarTermino(archEscritura, &termino);
    }

    fclose(archEscritura);
    return OK;
}

int recorrerArchTexto(tArbol* pa, const char* nombreArch, tAccion3 accion)
{
    FILE* archLeer;
    tTermino termino;
    char linea[TAM_LINEA];

    if((archLeer = fopen(nombreArch, "rt")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    /// Pasar a funcion
    while(fgets(linea, TAM_LINEA, archLeer))
    {
        sscanf(linea, "X(%d)(%d)", &termino.potencia, &termino.coeficiente);
        insertarEnArbol(pa, &termino, sizeof(tTermino), cmpTerminos, acumularTermino);
    }

    fclose(archLeer);
    return OK;
}

int insertarPolinomioEnArbol(tArbol* pa)
{
    return OK;
}

void grabarTermino(void* salida, const void* termino)
{
    fprintf((FILE*)salida, "X(%d)(%d)\n",
            ((tTermino*)termino)->potencia,
            ((tTermino*)termino)->coeficiente);
}

void acumularTermino(void* acumular, const void* acumulado)
{
    ((tTermino*)acumular)->coeficiente += ((tTermino*)acumulado)->coeficiente;
}

int cmpTerminos(const void* t1, const void* t2)
{
    return ((tTermino*)t1)->potencia - ((tTermino*)t2)->potencia;
}
