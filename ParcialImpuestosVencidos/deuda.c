#include "deuda.h"

void iniciarMenu(tArbol* pa)
{
    int opcion;

    opcion = 0;

    while(opcion != 3)
    {
        do
        {
            system("cls");
            puts("OPCIONES DE ORDENAMIENTO");
            puts("1- DNI");
            puts("2- DNI + PATENTE");
            puts("3- Salir");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
        } while(opcion < 1 || opcion > 3);
        switch(opcion)
        {
        case 1:
            cargarArchTxtEnArbol(pa, "impuestosVencidos.dat", sizeof(tDeuda), cmpDni, acumularImportes);
            generarArchTxtRecorriendoArbol(pa, "deuda.txt", grabarDeudaPorDNI, acumularImportes2);
            break;
        case 2:
            cargarArchTxtEnArbol(pa, "impuestosVencidos.dat", sizeof(tDeuda), cmpDniYPatente, acumularImportes);
            generarArchTxtRecorriendoArbol(pa, "deuda.txt", grabarDeudaPorDNIYPatente, acumularImportes2);
            break;
        default: break;
        }
        vaciarArbol(pa);
        system("pause");
    }
}

int generarArchBinImpuestosVencidos(const char* path)
{
    int i;
    FILE* archGrabar;
    tDeuda deuda;

    if((archGrabar = fopen(path, "wb")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    for(i = 0; i < CANT_REGISTROS; i ++)
    {
        deuda.dni = rand() % 2 + 1;
        deuda.nroCuota = rand() % 6 + 1;
        snprintf(deuda.titular, MAX_TITULAR, "Titular %d", i);
        snprintf(deuda.patente, MAX_PATENTE, "AB%03dCD", rand() % 999);
        deuda.importe = rand() % 99999 + 1.99;
        deuda.vencimiento.dia = rand() % 31 + 1;
        deuda.vencimiento.mes = rand() % 12 + 1;
        deuda.vencimiento.anio = rand() % 2023 + 2020;
        fwrite(&deuda, sizeof(tDeuda), 1, archGrabar);
    }

    fclose(archGrabar);
    return OK;
}

int cargarArchTxtEnArbol(tArbol* pa, const char* path, unsigned tamReg,
                         tComparacion cmp, tAccion2 acumular)
{
    FILE* archLectura;
    void* reg;

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
        insertarEnArbol(pa, reg, tamReg, cmp, acumular);
        fread(reg, tamReg, 1, archLectura);
    }

    free(reg);
    fclose(archLectura);

    return OK;
}

int generarArchTxtRecorriendoArbol(tArbol* pa, const char* path,
                                   tAccion2 imprimir, tAccion2 acumular)
{
    FILE* archDeuda;
    float acum;

    if((archDeuda = fopen(path, "wt")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    grabarArchTxtOrdenadoConReduce(pa, archDeuda, &acum, imprimir, acumular);
    fprintf(archDeuda, "%.2f\n", acum);

    fclose(archDeuda);
    return OK;
}

int cmpDni(const void* deuda1, const void* deuda2)
{
    return ((tDeuda*)deuda1)->dni - ((tDeuda*)deuda2)->dni;
}

int cmpDniYPatente(const void* deuda1, const void* deuda2)
{
    int rc;

    rc = ((tDeuda*)deuda1)->dni - ((tDeuda*)deuda2)->dni;

    return rc != 0? rc : strcmpi(((tDeuda*)deuda1)->patente, ((tDeuda*)deuda2)->patente);
}

void acumularImportes(void* acumulado, const void* acumular)
{
    ((tDeuda*)acumulado)->importe += ((tDeuda*)acumular)->importe;
}

void acumularImportes2(void* acumulado, const void* acumular)
{
    *((float*)acumulado) += ((tDeuda*)acumular)->importe;
}

void grabarDeudaPorDNI(void* salida, const void* deuda)
{
    fprintf((FILE*) salida, "%d|%.2f\n",
            ((tDeuda*)deuda)->dni,
            ((tDeuda*)deuda)->importe);
}

void grabarDeudaPorDNIYPatente(void* salida, const void* deuda)
{
    fprintf((FILE*) salida, "%d|%s|%.2f\n",
            ((tDeuda*)deuda)->dni,
            ((tDeuda*)deuda)->patente,
            ((tDeuda*)deuda)->importe);
}
