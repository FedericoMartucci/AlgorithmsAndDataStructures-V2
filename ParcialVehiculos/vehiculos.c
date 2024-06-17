#include "vehiculos.h"

void generarPatenteAleatoria(char* patente) {
    const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 3; i++) {
        patente[i] = letras[rand() % 26];
    }
    for (int i = 3; i < 6; i++) {
        patente[i] = '0' + rand() % 10;
    }
    patente[6] = '\0';
}


int generarArchBinVehiculos(const char* nombreArch)
{
    int i;
    FILE* archVehiculos;
    tVehiculo vehiculo;
    tVehiculo vehiculos[] = {
        {"AAA111", 10, 200},
        {"BBB111", 5 , 100},
        {"AAA222", 10, 300},
        {"CCC111", 1 , 100},
        {"DDD111", 5 , 500}
    };

    if((archVehiculos = fopen(nombreArch, "wb")) == NULL)
    {
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

//    for(i = 0; i < sizeof(vehiculos)/sizeof(tVehiculo); i ++)
//        fwrite(&vehiculos[i], sizeof(tVehiculo), 1, archVehiculos);

    for(i = 0; i < 200000; i ++)
    {
        generarPatenteAleatoria(vehiculo.dominio);
        vehiculo.antiguedad = rand() % 10000 + 1;  // Cantidad entre 1 y 100
        vehiculo.kmRecorridos = rand() % 1000 + 100; // Precio entre 100 y 1099

        fwrite(&vehiculo, sizeof(tVehiculo), 1, archVehiculos);
    }


    fclose(archVehiculos);
    return OK;
}

int recorrerArchBin(tArbol* pa, const char* nombreArch, unsigned tamInfo, tAccion3 accion)
{
    void* reg;
    FILE* archLectura;

    if((reg = malloc(tamInfo)) == NULL)
    {
        perror("Error en la apertura del archivo");
        return MEM_ERR;
    }

    if((archLectura = fopen(nombreArch, "rb")) == NULL )
    {
        free(reg);
        perror("Error en la apertura del archivo");
        return FILE_ERR;
    }

    fread(reg, tamInfo, 1, archLectura);
    while(!feof(archLectura))
    {
        accion(pa, reg);
        fread(reg, tamInfo, 1, archLectura);
    }

    free(reg);
    fclose(archLectura);
    return OK;
}

int insertarVehiculoEnArbol(tArbol* pa, const void* vehiculo)
{
    tPromedio prom;

    prom.antiguedad = ((tVehiculo*)vehiculo)->antiguedad;
    prom.kmRecorridos = ((tVehiculo*)vehiculo)->kmRecorridos;
    prom.cantVehiculos = 1;
    insertarEnArbol(pa, &prom, sizeof(tPromedio), cmpAntiguedad, acumularPromedio);

    return OK;
}

//int insertarVehiculoEnLista(tLista* pa, const void* vehiculo)
//{
//    tPromedio prom;
//
//    prom.antiguedad = ((tVehiculo*)vehiculo)->antiguedad;
//    prom.kmRecorridos = ((tVehiculo*)vehiculo)->kmRecorridos;
//    prom.cantVehiculos = 1;
//    insertarOrdenado(pa, &prom, sizeof(tPromedio), cmpAntiguedad, acumularPromedio);
//
//    return OK;
//}

void mostrarPromedio(const void* registro)
{
    printf("ANTIGUEDAD: %-3d PROMEDIO KM RECORRIDOS: %7.2f\n",
           ((tPromedio*)registro)->antiguedad,
           ((tPromedio*)registro)->kmRecorridos / ((tPromedio*)registro)->cantVehiculos);
}

void acumularPromedio(void* prom, const void* registro)
{
    ((tPromedio*)prom)->kmRecorridos += ((tPromedio*)registro)->kmRecorridos;
    ((tPromedio*)prom)->cantVehiculos ++;
}

int cmpAntiguedad(const void* prom1, const void* prom2)
{
    return ((tPromedio*)prom1)->antiguedad - ((tPromedio*)prom2)->antiguedad;
}
