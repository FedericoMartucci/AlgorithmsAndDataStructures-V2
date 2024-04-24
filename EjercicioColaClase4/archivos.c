#include "archivos.h"

int generarArchivoCalculos(const char* nombre, const char* tipo)
{
    int error;
    int i;

    FILE* archivoCalculos;
    char loteCalculos[CANT_CALCULOS][TAM_CALCULO_MAX] =
    {
        "3 + 5||||{[((3 + 2) * 4) - [5 + {6 * (4 - 2)}]}||{[4 * (3 + 5)] - (6 - 2)) * 7||"
        "{[(2 * 3) + 4] - (5 * 6)]}||"
        "{[8 - (4 * 2)] * 3 - {9 + (6 * 2)}}]||"
        "{[3 + {2 * (4 - 3)}]} * (5 - 2)||"
        "{[6 * 2) - {4 * (3 - 2)]}} * 5||"
        "{((3 + 2) * [4 - {5 + (6 * 2)}]}||"
        "{[2 * (3 + 4)] - (5 * 6))} * 7",
        "(8 - 4) * {2 * [3 - (9 * 2)]}]",
        "{[(3 * 2) - 4] * (5 + 6)}]",
        "(2 * 3) + {[4 * (5 - 2)] - 6}||"
        "(7 - {3 * (4 - 2)]}) * 5||"
        "{[8 - (4 * 2)] * 3 - {9 + (6 * 2)}}]||"
        "[3 + {2 * (4 - 3)}]} * (5 - 2)",
        "{[6 * 2) - {4 * (3 - 2)]}} * 5||"
        "{((3 + 2) * [4 - {5 + (6 * 2)}]}||"
        "{[2 * (3 + 4)] - (5 * 6))} * 7||"
        "(8 - 4) * {2 * [3 - (9 * 2)]}]",
        "{[(3 * 2) - 4] * (5 + 6)}]",
        "(2 * 3) + {[4 * (5 - 2)] - 6}",
        "(7 - {3 * (4 - 2)]}) * 5",
        "{((3 + 2) * [4 - {5 + (6 * 2)}]",
        "{[2 * (3 + 4)] - (5 * 6}",
        "(8 - 4) * {2 * [3 - (9 * 2)]}]",
        "{[(3 * 2) - 4] * (5 + 6)}",
        "(2 * 3) + {[4 * (5 - 2)] - 6}",
        "(7 - {3 * (4 - 2)]}) * 5",
        "[3 + {2 * (4 - 3)}]} * (5 - 2",
        "{[6 * 2) - {4 * (3 - 2)]}} * 5",
        "{((3 + 2) * 4 - {[5 + {6 * (4 - 2)}}}"
    };

    if(strcmpi(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoCalculos, nombre, "wb")) != OK)
            return error;
        fwrite(loteCalculos, TAM_CALCULO_MAX, CANT_CALCULOS, archivoCalculos);
    }
    else if(strcmpi(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoCalculos, nombre, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_CALCULOS; i++)
            mostrarCalculo(archivoCalculos, &loteCalculos[i]);
    }
    else
        return FILE_OPEN_MODE_ERR;

    fclose(archivoCalculos);
    return OK;
}

int recorrerArchivoTextoDepurando(const char* nombre, unsigned tamRegistro,
                                  void(*trozar)(char*, void*))
{
    int error;
    char calculo[TAM_CALCULO_MAX];
    char buffer[TAM_BUFFER];
    char* inicioCalculo;
    tCola calculos;
    FILE* archConCalculos;
    FILE* archResultado;
    FILE* archErrores;

    crearCola(&calculos);

    if((error = abrirArchivo(&archConCalculos, nombre, "rt")) != OK)
        return error;

    if((error = abrirArchivo(&archResultado, "depurado.txt", "wt")) != OK)
    {
        fclose(archConCalculos);
        return error;
    }

    if((error = abrirArchivo(&archErrores, "errores.txt", "wt")) != OK)
    {
        fclose(archConCalculos);
        fclose(archResultado);
        return error;
    }

    while(fgets(buffer, sizeof(buffer), archConCalculos))
    {
        trozar(buffer, &calculos);
        while(!colaVacia(&calculos))
        {
            sacarDeCola(&calculos, calculo, sizeof(calculo));
            inicioCalculo = calculo;
            if(depurarCalculos(inicioCalculo) == CALCULO_MAL_PARENTIZADO){
                eliminarCaracteresNoEspeciales(calculo);
                mostrarCalculo(archErrores, calculo);
            }
            else
                mostrarCalculo(archResultado, calculo);
        }
    }

    vaciarCola(&calculos);

    fclose(archConCalculos);
    fclose(archResultado);
    fclose(archErrores);
    return OK;
}

int depurarCalculos(char* inicioCalculo)
{
    char caracterEspecialApilado;
    tPila caracteresEspeciales;

    caracterEspecialApilado = '\0';
    crearPila(&caracteresEspeciales);

    while(*inicioCalculo != '\0')
    {
        while(!ES_CARACTER_ESPECIAL(*inicioCalculo) && *inicioCalculo != '\0')
            inicioCalculo++;
        if(ES_CARACTER_ESPECIAL_INICIAL(*inicioCalculo)){
            apilar(&caracteresEspeciales, inicioCalculo, sizeof(*inicioCalculo));
            inicioCalculo++;
        }
        else if(ES_CARACTER_ESPECIAL_FINAL(*inicioCalculo))
        {
            if(verTopePila(&caracteresEspeciales, &caracterEspecialApilado, sizeof(char)) == OK &&
                    esComplemento(*inicioCalculo, caracterEspecialApilado))
            {
                desapilar(&caracteresEspeciales, &caracterEspecialApilado, sizeof(char));
                inicioCalculo++;
            }
            else
            {
                vaciarPila(&caracteresEspeciales);
                inicioCalculo++;
                *inicioCalculo = '\0';
                return CALCULO_MAL_PARENTIZADO;
            }
        }
    }

    vaciarPila(&caracteresEspeciales);
    return CALCULO_BIEN_PARENTIZADO;
}

void eliminarCaracteresNoEspeciales(char* calculo)
{
    char* ini;
    char* aux;

    ini = calculo;
    aux = calculo;

    while(*aux != '\0')
    {
        if(ES_CARACTER_ESPECIAL(*aux)){
            *ini = *aux;
            ini ++;
        }
        aux++;
    }
    *ini = *aux;
}

int esComplemento(char caracterLeido, char caracterApilado)
{
    return (caracterLeido == ')' && caracterApilado == '(') ||
           (caracterLeido == ']' && caracterApilado == '[') ||
           (caracterLeido == '}' && caracterApilado == '{');
}

void trozarCalculos(char* cadena, void* destino)
{
    char* separador;
    char* calculo;

    separador = strrchr(cadena, '\n');
    *separador = '\0';

    separador = cadena;
    calculo = cadena;

    while((separador = strchr(separador, '|')) != NULL)
    {
        if(*(separador + 1) == '|')
        {
            *separador = '\0';
            separador++;
            *separador = '\0';
        }
        ponerEnCola((tCola*)destino, calculo, strlen(calculo) + 1);
        separador++;
        calculo = separador;
    }
    ponerEnCola((tCola*)destino, calculo, strlen(calculo) + 1);
}

void mostrarCalculo(FILE* destino, const void* p)
{
    fprintf(destino, "%s\n", (char*)p);
}

int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo)
{
    if(!(*archivoAAbrir = fopen(nombre, tipo)))
    {
        perror("The file could not be opened");
        return FILE_ERR;
    }

    return OK;
}


