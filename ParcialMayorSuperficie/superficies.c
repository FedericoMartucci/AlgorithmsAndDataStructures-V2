#include "superficies.h"

int generarLoteBinario(tArbol* pa, const char* path)
{
    int i;
    FILE* archGrabar;
    tRegistro reg;

    if((archGrabar = fopen(path, "wb")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    for(i = 0; i < CANT_REGISTROS; i ++)
    {
        reg.provincia = rand() % 23 + 1;
        snprintf(reg.localidad, MAX_LOCALIDAD, "Localidad %d", i);
        reg.superficie = rand() % 99999 + 0.99;
        reg.poblacion = rand() % 9999 + 1;
        fwrite(&reg, sizeof(tRegistro), 1, archGrabar);
        imprimirRegistro(&reg);
        insertarEnArbol(pa, &reg, sizeof(tRegistro), cmpSuperficies, NULL);
    }

    fclose(archGrabar);
    return OK;
}

int cargarArchBinEnListaConLimite(tLista* pl, const char* path, unsigned tamReg,
                                  unsigned limite, tComparacion cmp)
{
    void* reg;
    FILE* archLectura;

    if((reg = malloc(tamReg)) == NULL)
        return MEM_ERR;

    if((archLectura = fopen(path, "rb")) == NULL)
    {
        free(reg);
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    fread(reg, tamReg, 1, archLectura);
    while(!feof(archLectura))
    {
        insertarOrdenadoConLimite(pl, reg, tamReg, limite, cmp);
        fread(reg, tamReg, 1, archLectura);
    }

    free(reg);
    fclose(archLectura);
    return OK;
}

void imprimirRegistro(const void* reg)
{
    printf("%d|%s|%f|%d\n",
           ((tRegistro*)reg)->provincia,
           ((tRegistro*)reg)->localidad,
           ((tRegistro*)reg)->superficie,
           ((tRegistro*)reg)->poblacion);
}

/// Funciones de comparacion
int cmpSuperficies(const void* reg1, const void* reg2)
{
    return ((tRegistro*)reg1)->superficie - ((tRegistro*)reg2)->superficie;
}

int cmpProvincias(const void* reg1, const void* reg2)
{
    return ((tRegistro*)reg1)->provincia - ((tRegistro*)reg2)->provincia;
}
