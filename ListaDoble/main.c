#include "listaDoble.h"
#include "../Bibliotecas/archivos.h"
#include "../Bibliotecas/productos.h"

int main()
{
    tListaDoble listaDesordenada;
    tListaDoble listaOrdenada;
//    int vec[] = {8, 5, 3, 1, 9, 2, 6, 7, 22, 232, 2, 5, 8, 1, 9, 232, 2, 2, 1, 8, 2, 3, 2};
    tNumero numeros[] = {{8, 1}, {5, 1}, {3, 1}, {1, 1}, {9, 1}, {2, 1}, {6, 1}, {7, 1},
                        {22, 1}, {232, 1}, {2, 1}, {5, 1}, {8, 1}, {1, 1,}, {9, 1}, {232, 1},
                        {2, 1}, {2, 1}, {1, 1}, {8, 1}, {2, 1}, {4, 1}, {2, 1}};
    int i;

//    srand(time(NULL));

    crearLista(&listaDesordenada);
    crearLista(&listaOrdenada);

    for( i = 0; i < sizeof(numeros)/sizeof(tNumero); i++)
    {
//        insertar(&listaDesordenada, &vec[i], sizeof(vec[i]));
//        insertarAlInicio(&listaDesordenada, &vec[i], sizeof(vec[i]));
        insertarAlFinal(&listaDesordenada, &numeros[i], sizeof(numeros[i]));
        insertarOrdenado(&listaOrdenada, &numeros[i], sizeof(numeros[i]), cmpNumeros);
    }
//TODO: cmpNumeros, mostrarNumeros, acumularMultNumeros


//    generarArchivoProductos("lotePrueba.txt", "TEXTO");
//    cargarArchivoProductosEnLista("lotePrueba.txt", &pl);
    puts("LISTA ORDENADA");
    recorrerIzqADer(&listaOrdenada, mostrarNumeros);
    puts("\n\nLISTA DESORDENADA");
    recorrerIzqADer(&listaDesordenada, mostrarNumeros);
    resumirOcurrenciasClaveListaDesordenada(&listaDesordenada, cmpNumeros, acumularMultNumeros);
    puts("");
    recorrerIzqADer(&listaDesordenada, mostrarNumeros);
    ordenarLista(&listaDesordenada, cmpNumeros);
    puts("");
    recorrerIzqADer(&listaDesordenada, mostrarNumeros);
//    recorrerDerAIzq(&pl, mostrarProducto);

//    vaciarLista(&listaDesordenada);
//    vaciarLista(&listaOrdenada);

    return 0;
}
