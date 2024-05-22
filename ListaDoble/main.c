#include "listaDoble.h"
#include "../Bibliotecas/archivos.h"
#include "../Bibliotecas/productos.h"

int main()
{
    tListaDoble pl;
    srand(time(NULL));

    crearLista(&pl);

    generarArchivoProductos("lotePrueba.txt", "TEXTO");
    cargarArchivoProductosEnLista("lotePrueba.txt", &pl);
    recorrerIzqADer(&pl, mostrarProducto);
    puts("\n\n");
    recorrerDerAIzq(&pl, mostrarProducto);

    vaciarLista(&pl);

    return 0;
}
