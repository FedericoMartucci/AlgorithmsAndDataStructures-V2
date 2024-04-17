#include "archivo.h"

int abrirArchivo(FILE** archivoAAbrir, const char* nombreArch, const char* modoApertura)
{
    *archivoAAbrir = fopen(nombreArch, modoApertura);
    if(*archivoAAbrir == NULL){
        perror("No se pudo abrir el archivo");
        return FILE_ERR;
    }

    return OK;
}

int generarArchivoProductos(const char* nombreArchivo, const char* tipo)
{
    int error;
    int i;

    FILE* archivoProductos;
    tProducto loteProductos[] =
    {
        {"a", 'e', "x1", 3},
        {"a", 's', "x2", 2},
        {"a", 'e', "x3", 3},
        {"a", 's', "x2", 1 + rand() % 100},
        {"b", 's', "x2", 1 + rand() % 100},
        {"b", 's', "x3", 1 + rand() % 100},
        {"b", 'e', "x2", 1 + rand() % 100},
        {"c", 'e', "x1", 1 + rand() % 100},
        {"c", 'e', "x1", 1 + rand() % 100},
        {"c", 's', "x2", 1 + rand() % 100},
        {"d", 'e', "x5", 1 + rand() % 100},
        {"d", 'e', "x2", 1 + rand() % 100},
    };

    if(strcmp(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombreArchivo, "wb")) != OK)
            return error;
        fwrite(loteProductos, sizeof(tProducto), sizeof(loteProductos)/sizeof(tProducto), archivoProductos);
    }
    else if(strcmp(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombreArchivo, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_PRODUCTOS; i++)
        {
            fprintf(archivoProductos, "%s|%c|%s|%d\n",
                    loteProductos[i].codigo,
                    loteProductos[i].movimiento,
                    loteProductos[i].deposito,
                    loteProductos[i].cantidad);
        }
    }
    else
        return FILE_OPEN_MODE_ERR;

    fclose(archivoProductos);
    return OK;
}

int recorrerArchivoBinario(const char* nombreArch, unsigned tamRegistro,
                           FILE** arch1, FILE** arch2,
                           int(*accion)(void*, const void*, unsigned,
                                        int* , FILE**, FILE**))
{
    int codigoError;
    int acumulador;
    FILE* archivoARecorrer;
    tCola colaDeDatos;
    void* registro;

    crearCola(&colaDeDatos);

    if((codigoError = abrirArchivo(&archivoARecorrer, nombreArch, "rb")) != OK)
        return codigoError;

    if((registro = malloc(tamRegistro)) == NULL){
        fclose(archivoARecorrer);
        return MEM_ERR;
    }

    fread(registro, tamRegistro, 1, archivoARecorrer);
    while(!feof(archivoARecorrer))
    {
        codigoError = accion(&colaDeDatos, registro, tamRegistro, &acumulador, arch1, arch2);

        if(codigoError != OK)
        {
            vaciarCola(&colaDeDatos);
            fclose(archivoARecorrer);
            free(registro);
            return codigoError;
        }
        mostrarProducto((tProducto*) registro);
        fread(registro, tamRegistro, 1, archivoARecorrer);
    }

    cargarArchivoTextoDesacolando(acumulador > TOL_MOVIMIENTOS? arch1 : arch2, &colaDeDatos); /// rever esto

    vaciarCola(&colaDeDatos);
    fclose(archivoARecorrer);
    free(registro);

    return OK;
}

int acomodarProductos(void* cola, const void* registro, unsigned tamRegistro,
                      int* acumulador, FILE** archMuchosMov, FILE** archPocosMov)
{
    int codigoError;
    tProducto registroAComparar;

    if(colaVacia((tCola*)cola))
        codigoError = insertarYAcumular((tCola*)cola, registro, tamRegistro, acumulador);
    else if((codigoError = verTope((tCola*)cola, &registroAComparar, tamRegistro)) != OK)
        return codigoError;
    else if(cmpCodigoProducto((const void*)&registroAComparar, registro) == 0)
            codigoError = insertarYAcumular((tCola*)cola, registro, tamRegistro, acumulador);
    else if(codigoError != OK)
        return codigoError;
    else
    {
        cargarArchivoTextoDesacolando(*acumulador > TOL_MOVIMIENTOS? archMuchosMov : archPocosMov, (tCola*)cola);
        *acumulador = 0;
        codigoError = insertarYAcumular((tCola*)cola, registro, tamRegistro, acumulador);
    }

    return codigoError != OK? codigoError : OK;
}

int insertarYAcumular(tCola* cola, const void* registro, unsigned tamRegistro, int* acumulador)
{
    int codigoError;

    if((codigoError = ponerEnCola(cola, registro, tamRegistro)) != OK)
        return codigoError;

    if(*acumulador <= TOL_MOVIMIENTOS)
        *acumulador += ((tProducto*)registro)->cantidad;

    return OK;
}

int cargarArchivoTextoDesacolando(FILE** archivoACargar, tCola* cola) //TODO: hacer la funcion generica
{
    int codigoError;
    tProducto producto;

    while(!colaVacia(cola))
    {
        codigoError = sacarDeCola(cola, &producto, sizeof(producto));
        if(codigoError != OK)
            return codigoError;
        fprintf(*archivoACargar, "%s|%c|%s|%d\n", producto.codigo,
                producto.movimiento,
                producto.deposito,
                producto.cantidad);
    }

    return OK;
}

int cmpCodigoProducto(const void* a, const void* b)
{
    return strcmp(((tProducto*)a)->codigo, ((tProducto*)b)->codigo);
}

void mostrarProducto(tProducto* producto)
{
    fprintf(stdout, "%s|%c|%s|%d\n", producto->codigo,
                producto->movimiento,
                producto->deposito,
                producto->cantidad);
}

