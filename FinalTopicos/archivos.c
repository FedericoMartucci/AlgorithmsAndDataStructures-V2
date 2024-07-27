#include "archivos.h"

int crearLoteDistribuidores()
{
    int i;
    FILE* archDistribuidores;
    tCliente distribuidores[] =
    {
        {00000000, "Agus B", 000000.00, "Broca"},
        {11111111, "Federico Martucci", 111111.11, "fede"},
        {22222222, "Franco Ruggeri", 222222.22, ""},
        {33333333, "Maradona pa", 333333.33, "EL diego"},
        {44444444, "Pablito lezcano", 444444.44, "atr perro cumbia"},
        {55555555, "Otro cliente mas", 555555.55, "anawoindwaoi"},
        {66666666, "Se me terminaron las ideas", 666666.66, ""},
        {77777777, "Renata Guatelli", 777777.77, ""},
        {88888888, "Johgn Doe", 888888.88, "Johnny"},
        {99999999, "JAVIER GERARDO MILEI", 999999.99, "EL LEON"}
    };

    if((archDistribuidores = fopen(NOMBRE_ARCH_DISTRIBUIDORES, "wb")) == NULL)
    {
        perror("Error en la apertura de archivo");
        return FILE_ERR;
    }

    for(i = 0; i < sizeof(distribuidores)/sizeof(tCliente); i ++)
        fwrite(&distribuidores[i], sizeof(tCliente), 1, archDistribuidores);

    fclose(archDistribuidores);
    return OK;
}

int crearLoteModificaciones()
{
    int i;
    FILE* archModificaciones;
    tCliente distribuidores[] =
    {
        {00000000, "Agus B", 111111.11, "Broca"},
        {12345678, "Agus B", 123456.78, "Broca"},
        {22222222, "Franco Ruggeri", 111111.11, "El duenio de HSBC"},
        {33333333, "Maradona pa", 111111.11, "El Merquero"},
        {55555555, "Otro cliente mass", 555555.55, "anawoindwaoii"},
        {77777777, "Renata Guatelli", 777777.77, ""},
        {88888888, "Johgn Doe", 222222.22, "Johnny B Goode"},
        {98721441, "JAVIER GERARDO MILEI", 111111.11, "EL LEON"}
    };

    if((archModificaciones = fopen(NOMBRE_ARCH_MODIFICACIONES, "wb")) == NULL)
    {
        perror("Error en la apertura de archivo");
        return FILE_ERR;
    }

    for(i = 0; i < sizeof(distribuidores)/sizeof(tCliente); i ++)
        fwrite(&distribuidores[i], sizeof(tCliente), 1, archModificaciones);

    fclose(archModificaciones);
    return OK;
}

int actualizarArchivosBin(const char* nombreArchLectura,
                          const char* nombreArchModificacion,
                          unsigned tamReg, tComparacion cmp, tComparacion cmp2,
                          tAccion imprimirError)
{
    int rc;

    FILE* archLectura;
    FILE* archModificacion;
    FILE* archFinal;
    FILE* archErrores;

    void* bufferArchLectura;
    void* bufferArchModificacion;

    if((bufferArchLectura = malloc(tamReg)) == NULL ||
       (bufferArchModificacion = malloc(tamReg)) == NULL)
    {
        free(bufferArchLectura);
        return MEM_ERR;
    }

    if((archLectura = fopen(nombreArchLectura, "rb")) == NULL ||
       (archModificacion = fopen(nombreArchModificacion, "rb")) == NULL ||
       (archFinal = fopen(NOMBRE_ARCH_TEMP, "wb")) == NULL ||
       (archErrores = fopen(NOMBRE_ARCH_ERRORES, "wt")) == NULL)
    {
        perror("Error en la apertura de archivo");
        free(bufferArchLectura);
        free(bufferArchModificacion);
        fclose(archLectura);
        fclose(archModificacion);
        fclose(archFinal);
        return FILE_ERR;
    }

    fread(bufferArchLectura, tamReg, 1, archLectura);
    fread(bufferArchModificacion, tamReg, 1, archModificacion);
    while(!feof(archLectura) && !feof(archModificacion))
    {
        rc = cmp(bufferArchModificacion, bufferArchLectura);

        if(rc < 0)
        {
            fwrite(bufferArchModificacion, tamReg, 1, archFinal);
            fread(bufferArchModificacion, tamReg, 1, archModificacion);
        }
        else if(rc > 0)
        {
            fwrite(bufferArchModificacion, tamReg, 1, archFinal);
            fread(bufferArchLectura, tamReg, 1, archLectura);
        }
        else
        {
            if(cmp2(bufferArchModificacion, bufferArchLectura) != 0)// == 0 cambio nombre
                imprimirError(archErrores, bufferArchModificacion);
            else
                fwrite(bufferArchModificacion, tamReg, 1, archFinal);

            fread(bufferArchLectura, tamReg, 1, archLectura);
            fread(bufferArchModificacion, tamReg, 1, archModificacion);
        }
    }

    while(!feof(archLectura))
    {
        fwrite(bufferArchModificacion, tamReg, 1, archFinal);
        fread(bufferArchLectura, tamReg, 1, archLectura);
    }

    while(!feof(archModificacion))
    {
        fwrite(bufferArchModificacion, tamReg, 1, archFinal);
        fread(bufferArchModificacion, tamReg, 1, archModificacion);
    }

    free(bufferArchLectura);
    free(bufferArchModificacion);
    fclose(archLectura);
    fclose(archModificacion);
    fclose(archFinal);
    fclose(archErrores);

    remove(nombreArchLectura);
    rename(NOMBRE_ARCH_TEMP, nombreArchLectura);

    return OK;
}

int mostrarArchivoBin(const char* nombreArch, unsigned tamReg, tAccion mostrar)
{
    FILE* archLectura;
    void* registro;

    if((registro = malloc(tamReg)) == NULL)
        return MEM_ERR;

    if((archLectura = fopen(nombreArch, "rb")) == NULL)
    {
        perror("Error en la apertura de archivo");
        free(registro);
        return FILE_ERR;
    }

    fread(registro, tamReg, 1, archLectura);
    while(!feof(archLectura))
    {
        mostrar(stdout, registro);
        fread(registro, tamReg, 1, archLectura);
    }

    free(registro);
    fclose(archLectura);
    return OK;
}

void imprimirCliente(void* archDistribuidores, const void* distribuidor)
{
    fprintf((FILE*)archDistribuidores, "%08d,%s,%6.2f,%s\n",
            ((tCliente*)distribuidor)->codCliente,
            ((tCliente*)distribuidor)->apyn,
            ((tCliente*)distribuidor)->saldo,
            ((tCliente*)distribuidor)->nombreFantasia
           );
}

int cmpCodCliente(const void* c1, const void* c2)
{
    return ((tCliente*)c1)->codCliente - ((tCliente*)c2)->codCliente;
}

int cmpSaldos(const void* c1, const void* c2)
{
    return ((tCliente*)c1)->saldo - ((tCliente*)c2)->saldo;
}

int cmpNombreFantasia(const void* c1, const void* c2)
{
    return strcmp(((tCliente*)c1)->nombreFantasia, ((tCliente*)c2)->nombreFantasia) == 0? 0 : cmpNombreYApellido(c1, c2);
}

int cmpNombreYApellido(const void* c1, const void* c2)
{
    return strcmp(((tCliente*)c1)->apyn, ((tCliente*)c2)->apyn);
}

