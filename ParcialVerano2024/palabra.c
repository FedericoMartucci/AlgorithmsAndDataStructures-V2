#include "palabra.h"

void procesarOpcion(const tArbol* pa, int opcion)
{
    tPalabra pal;

    strcpy(pal.palabra, "");

    switch(opcion)
    {
        case VER_PALABRA_ASCENDENTE:
            recorrerInorden(pa, mostrarPalabra);
            break;
        case VER_PALABRA_DESCENDENTE:
            recorrerInordenInveso(pa, mostrarPalabra);
            break;
        case VER_PALABRA_MAYOR_REPETICIONES:
            pal.cantRepeticiones = 0;
            buscarMayorNoClave(pa, &pal, cmpRepeticiones, reemplazarPalabra);
            mostrarPalabra(&pal);
            break;
        case VER_PALABRA_MENOR_REPETICIONES:
            pal.cantRepeticiones = INT_MIN;
            buscarMenorNoClave(pa, &pal, cmpRepeticiones, reemplazarPalabra);
            mostrarPalabra(&pal);
            break;
        default: break;
    }
}

int insertarPalabrasEnArbol(tArbol* pa, char* linea, unsigned tamLinea)
{
    int cantLetras;
    tPalabra palabra;
    char* palAux;

    palabra.cantRepeticiones = 1;

    while((cantLetras = proximaPalabra(&palAux, &linea)))
    {
        strcpy(palabra.palabra, palAux);
        insertarEnArbol(pa, &palabra, sizeof(tPalabra), cmpPalabra, acumularPalabras);
    }

    return OK;
}

int proximaPalabra(char** palabra, char** linea)
{
    int cantCaracteres;

    cantCaracteres = 0;

    while(**linea && !esLetra(**linea))
        (*linea)++;

    *palabra = *linea;


    while(esLetra(**linea))
    {
        cantCaracteres++;
        (*linea)++;
    }

    if(**linea)
    {
        **linea = '\0';
        (*linea)++;
    }

    return cantCaracteres;
}

int esLetra(char letra)
{
    return ((letra) >= 'a' && (letra) <= 'z') ||
           ((letra) >= 'A' && (letra) <= 'Z') ||
           ((letra) == 'Ú') ||
           ((letra) == 'Ó') ||
           ((letra) == 'Í') ||
           ((letra) == 'É') ||
           ((letra) == 'ú') ||
           ((letra) == 'í') ||
           ((letra) == 'é') ||
           ((letra) == 'á') ||
           ((letra) == 'Ñ') ||
           ((letra) == 'ñ');
}


/// Funciones de acumular
void reemplazarPalabra(void* palAReemplazar, const void* pal)
{
    strcpy(((tPalabra*)palAReemplazar)->palabra, ((tPalabra*)pal)->palabra);
    ((tPalabra*)palAReemplazar)->cantRepeticiones = ((tPalabra*)pal)->cantRepeticiones;
}

void acumularPalabras(void* palAcumular, const void* pal)
{
    ((tPalabra*)palAcumular)->cantRepeticiones += 1;
}

/// Funciones de mostrar
void mostrarPalabra(const void* palabra)
{
    printf("PALABRA: %-20s - OCURRENCIAS: %4d\n",
           ((tPalabra*)palabra)->palabra,
           ((tPalabra*)palabra)->cantRepeticiones);
}

/// Funciones de comparar
int cmpPalabra(const void* p1, const void* p2)
{
    return strcmpi(((tPalabra*)p1)->palabra, ((tPalabra*)p2)->palabra);
}

int cmpRepeticiones(const void* p1, const void* p2)
{
    return ((tPalabra*)p1)->cantRepeticiones - ((tPalabra*)p2)->cantRepeticiones;
}
