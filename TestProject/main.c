//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//#define MAX_AGRUPACIONES 25
//#define MAX_NOMBRE_AGRUPACION 30
//#define MAX_REGIONES 9
//#define MAX_DISTRITOS 20
//
//typedef struct {
//    int numAgrupacion;
//    char nombreAgrupacion[MAX_NOMBRE_AGRUPACION];
//} Agrupacion;
//
//typedef struct {
//    int numAgrupacion;
//    int region;
//    int distrito;
//    int votos;
//} Voto;
//
//void generarArchivoAgrupaciones(const char* nombreArchivo) {
//    FILE *archivo = fopen(nombreArchivo, "w");
//    if (!archivo) {
//        perror("Error al crear el archivo de agrupaciones");
//        exit(EXIT_FAILURE);
//    }
//
//    const char* nombres[] = {"Celeste y Blanca", "Verde", "Unión por Todos y Para Todos",
//                             "Frente de la Esperanza", "Movimiento Solidario", "Partido del Progreso",
//                             "Libres del Sur", "Acción Ciudadana", "Renovación Popular", "Nuevo Amanecer"};
//
//    for (int i = 0; i < MAX_AGRUPACIONES; i++) {
//        fprintf(archivo, "%d%s\n", i, nombres[rand() % 10]);
//    }
//
//    fclose(archivo);
//}
//
//void generarArchivoVotos(const char* nombreArchivo, int cantidadVotos) {
//    FILE *archivo = fopen(nombreArchivo, "wb");
//    if (!archivo) {
//        perror("Error al crear el archivo de votos");
//        exit(EXIT_FAILURE);
//    }
//
//    Voto voto;
//    for (int i = 0; i < cantidadVotos; i++) {
//        voto.numAgrupacion = rand() % MAX_AGRUPACIONES;
//        voto.region = rand() % MAX_REGIONES + 1;
//        voto.distrito = rand() % MAX_DISTRITOS + 1;
//        voto.votos = rand() % 1000; // votos aleatorios entre 0 y 999
//        fwrite(&voto, sizeof(Voto), 1, archivo);
//    }
//
//    fclose(archivo);
//}
//
//void leerAgrupaciones(const char* nombreArchivo, Agrupacion* agrupaciones, int* cantidadAgrupaciones) {
//    FILE *archivo = fopen(nombreArchivo, "r");
//    if (!archivo) {
//        perror("Error al abrir el archivo de agrupaciones");
//        exit(EXIT_FAILURE);
//    }
//
//    *cantidadAgrupaciones = 0;
//    while (fscanf(archivo, "%d%29[^\n]", &agrupaciones[*cantidadAgrupaciones].numAgrupacion, agrupaciones[*cantidadAgrupaciones].nombreAgrupacion) == 2) {
//        (*cantidadAgrupaciones)++;
//        if (*cantidadAgrupaciones > MAX_AGRUPACIONES) {
//            fprintf(stderr, "Error: Se ha excedido el máximo de agrupaciones permitidas.\n");
//            exit(EXIT_FAILURE);
//        }
//    }
//
//    fclose(archivo);
//}
//
//void leerVotos(const char* nombreArchivo, int votos[MAX_AGRUPACIONES][MAX_DISTRITOS], int cantidadAgrupaciones) {
//    FILE *archivo = fopen(nombreArchivo, "rb");
//    if (!archivo) {
//        perror("Error al abrir el archivo de votos");
//        exit(EXIT_FAILURE);
//    }
//
//    Voto voto;
//    while (fread(&voto, sizeof(Voto), 1, archivo) == 1) {
//        if (voto.numAgrupacion < 0 || voto.numAgrupacion >= cantidadAgrupaciones || voto.distrito < 1 || voto.distrito > MAX_DISTRITOS || voto.region < 1 || voto.region > MAX_REGIONES) {
//            fprintf(stderr, "Error: Registro de voto con datos inválidos.\n");
//            continue;
//        }
//        votos[voto.numAgrupacion][voto.distrito - 1] += voto.votos;
//    }
//
//    fclose(archivo);
//}
//
//void imprimirResultados(Agrupacion* agrupaciones, int votos[MAX_AGRUPACIONES][MAX_DISTRITOS], int cantidadAgrupaciones) {
//    int totalVotos[MAX_AGRUPACIONES] = {0};
//
//    for (int i = 0; i < cantidadAgrupaciones; i++) {
//        printf("Agrupacion: %d - %s\n", agrupaciones[i].numAgrupacion, agrupaciones[i].nombreAgrupacion);
//        for (int j = 0; j < MAX_DISTRITOS; j++) {
//            if (votos[i][j] > 0) {
//                printf("  Distrito %d: %d votos\n", j + 1, votos[i][j]);
//                totalVotos[i] += votos[i][j];
//            }
//        }
//        printf("  Total: %d votos\n\n", totalVotos[i]);
//    }
//
//    printf("Agrupaciones ordenadas por cantidad total de votos:\n");
//    for (int i = 0; i < cantidadAgrupaciones; i++) {
//        for (int j = i + 1; j < cantidadAgrupaciones; j++) {
//            if (totalVotos[i] < totalVotos[j]) {
//                int tempVotos = totalVotos[i];
//                totalVotos[i] = totalVotos[j];
//                totalVotos[j] = tempVotos;
//
//                Agrupacion tempAgrupacion = agrupaciones[i];
//                agrupaciones[i] = agrupaciones[j];
//                agrupaciones[j] = tempAgrupacion;
//            }
//        }
//    }
//
//    for (int i = 0; i < cantidadAgrupaciones; i++) {
//        printf("%s: %d votos\n", agrupaciones[i].nombreAgrupacion, totalVotos[i]);
//    }
//}
//
//int main() {
//    Agrupacion agrupaciones[MAX_AGRUPACIONES];
//    int cantidadAgrupaciones;
//    int votos[MAX_AGRUPACIONES][MAX_DISTRITOS] = {0};
//
//    // Generar archivos de prueba con datos aleatorios
//    generarArchivoAgrupaciones("agrupaciones.txt");
//    generarArchivoVotos("votos.dat", 1000); // 1000 registros de votos aleatorios
//
//    leerAgrupaciones("agrupaciones.txt", agrupaciones, &cantidadAgrupaciones);
//    leerVotos("votos.dat", votos, cantidadAgrupaciones);
//    imprimirResultados(agrupaciones, votos, cantidadAgrupaciones);
//
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTOS 100
#define MAX_DENOMINACION 100
#define MAX_ZONAS 20
#define MAX_ENCUESTADORES 50
#define MAX_CODIGO_PRODUCTO 8

typedef struct {
    char codigo[MAX_CODIGO_PRODUCTO + 1];
    char denominacion[MAX_DENOMINACION];
} Producto;

typedef struct {
    char codigoProducto[MAX_CODIGO_PRODUCTO + 1];
    int encuestador;
    int zona;
} Encuesta;

typedef struct {
    char codigoProducto[MAX_CODIGO_PRODUCTO + 1];
    int cantidad;
} Preferencia;

void generarArchivoProductos(const char* nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        perror("Error al crear el archivo de productos");
        exit(EXIT_FAILURE);
    }

    const char* nombres[] = {
        "Balizas Verde Agua", "Cereales Rellenos de Dulce con Chispas de Chocolate",
        "Cable de Yeso", "Galletas de Frutas", "Bebida Energizante",
        "Jugo Natural", "Chocolate Amargo", "Turron de Mani",
        "Leche Deslactosada", "Te Verde", "Cafe Orgánico",
        "Mermelada de Fresa", "Pan Integral", "Yogurt Natural",
        "Queso Vegano", "Cereal Integral", "Snacks de Frutas",
        "Jugo de Naranja", "Barras de Proteínas", "Helado de Yogurt"};

    int cantidadNombres = sizeof(nombres) / sizeof(nombres[0]);

    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        fprintf(archivo, "P%04d-%s\n", i + 1, nombres[rand() % cantidadNombres]);
    }

    fclose(archivo);
}

void generarArchivoEncuestas(const char* nombreArchivo, int cantidadEncuestas) {
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        perror("Error al crear el archivo de encuestas");
        exit(EXIT_FAILURE);
    }

    Encuesta encuesta;
    for (int i = 0; i < cantidadEncuestas; i++) {
        snprintf(encuesta.codigoProducto, sizeof(encuesta.codigoProducto), "P%04d", rand() % MAX_PRODUCTOS + 1);
        encuesta.encuestador = rand() % MAX_ENCUESTADORES + 1;
        encuesta.zona = rand() % MAX_ZONAS + 1;
        fwrite(&encuesta, sizeof(Encuesta), 1, archivo);
    }

    fclose(archivo);
}

void leerArchivoTexto(const char* nombreArchivo, Producto* productos, int* cantidadProductos) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo de productos");
        exit(EXIT_FAILURE);
    }

    *cantidadProductos = 0;
    while (fscanf(archivo, "%8s-%99[^\n]", productos[*cantidadProductos].codigo, productos[*cantidadProductos].denominacion) == 2) {
        (*cantidadProductos)++;
        if (*cantidadProductos >= MAX_PRODUCTOS) {
            fprintf(stderr, "Error: Se ha excedido el máximo de productos permitidos.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
}

void leerArchivoBinario(const char* nombreArchivo, Encuesta* encuestas, int* cantidadEncuestas) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (!archivo) {
        perror("Error al abrir el archivo de encuestas");
        exit(EXIT_FAILURE);
    }

    *cantidadEncuestas = 0;
    while (fread(&encuestas[*cantidadEncuestas], sizeof(Encuesta), 1, archivo) == 1) {
        (*cantidadEncuestas)++;
        if (*cantidadEncuestas >= MAX_PRODUCTOS * MAX_ZONAS * MAX_ENCUESTADORES) {
            fprintf(stderr, "Error: Se ha excedido el máximo de encuestas permitidas.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
}

void acumularPreferencias(Encuesta* encuestas, int cantidadEncuestas, Preferencia preferencias[MAX_ZONAS][MAX_PRODUCTOS], int* productosPorZona) {
    for (int i = 0; i < cantidadEncuestas; i++) {
        int zona = encuestas[i].zona - 1;
        int j;
        for (j = 0; j < productosPorZona[zona]; j++) {
            if (strcmp(preferencias[zona][j].codigoProducto, encuestas[i].codigoProducto) == 0) {
                preferencias[zona][j].cantidad++;
                break;
            }
        }
        if (j == productosPorZona[zona]) {
            strcpy(preferencias[zona][productosPorZona[zona]].codigoProducto, encuestas[i].codigoProducto);
            preferencias[zona][productosPorZona[zona]].cantidad = 1;
            productosPorZona[zona]++;
        }
    }
}

void generarInforme(Producto* productos, int cantidadProductos, Preferencia preferencias[MAX_ZONAS][MAX_PRODUCTOS], int* productosPorZona) {
    for (int zona = 0; zona < MAX_ZONAS; zona++) {
        printf("Zona %d:\n", zona + 1);
        for (int i = 0; i < productosPorZona[zona]; i++) {
            for (int j = i + 1; j < productosPorZona[zona]; j++) {
                if (preferencias[zona][i].cantidad < preferencias[zona][j].cantidad) {
                    Preferencia temp = preferencias[zona][i];
                    preferencias[zona][i] = preferencias[zona][j];
                    preferencias[zona][j] = temp;
                }
            }
        }

        for (int i = 0; i < 3 && i < productosPorZona[zona]; i++) {
            for (int j = 0; j < cantidadProductos; j++) {
                if (strcmp(preferencias[zona][i].codigoProducto, productos[j].codigo) == 0) {
                    printf("  %s: %d votos\n", productos[j].denominacion, preferencias[zona][i].cantidad);
                    break;
                }
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    Producto productos[MAX_PRODUCTOS];
    Encuesta encuestas[MAX_PRODUCTOS * MAX_ZONAS * MAX_ENCUESTADORES];
    Preferencia preferencias[MAX_ZONAS][MAX_PRODUCTOS] = {0};
    int cantidadProductos;
    int cantidadEncuestas;
    int productosPorZona[MAX_ZONAS] = {0};

    // Generar archivos de prueba con datos aleatorios
    generarArchivoProductos("productos.txt");
    generarArchivoEncuestas("encuestas.dat", 1000); // Generar 1000 encuestas aleatorias

    // Leer los archivos
    leerArchivoTexto("productos.txt", productos, &cantidadProductos);
    leerArchivoBinario("encuestas.dat", encuestas, &cantidadEncuestas);

    // Depuración: Mostrar cantidad de productos y encuestas leídas
    printf("Cantidad de productos leídos: %d\n", cantidadProductos);
    printf("Cantidad de encuestas leídas: %d\n", cantidadEncuestas);

    // Acumular las preferencias
    acumularPreferencias(encuestas, cantidadEncuestas, preferencias, productosPorZona);

    // Depuración: Mostrar acumulación de preferencias por zona
    for (int zona = 0; zona < MAX_ZONAS; zona++) {
        printf("Zona %d, productos acumulados: %d\n", zona + 1, productosPorZona[zona]);
    }

    // Generar el informe
    generarInforme(productos, cantidadProductos, preferencias, productosPorZona);

    return 0;
}
