#include "../Bibliotecas/archivos.h"
#include "../Bibliotecas/productos.h"
#include "../ListaSimple/lista.h"
#include "ejercicios.h"

int main()
{
    tLista pl;
    tLista pl2;
    tProductoReducido producto;
    FILE* depurado;
    FILE* depurado2;

    if(abrirArchivo(&depurado, "depurado.txt", "wt") != OK ||
       abrirArchivo(&depurado2, "depurado2.txt", "wt") != OK)
    {
        fclose(depurado);
        return FILE_ERR;
    }

    crearLista(&pl);
    crearLista(&pl2);

    generarArchivoProductos("datos.txt", "TEXTO");

    //Ejercicio a:
    cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor("datos.txt", &pl, cmpProductoReducido, acumularProductosReducidos);
    mostrarYEliminarDuplicados(&pl, "errores.txt",cmpCodigoProductoReducido);
    ordenarPorSeleccion(&pl, cmpProductoReducido);

    //Ejercicio b:
    cargarArchivoProductosEnListaOrdenadoSinProveedor("datos.txt", &pl2, cmpProductoReducido, acumularProductosReducidos);
    mostrarYEliminarDuplicados(&pl2, "errores2.txt",cmpCodigoProductoReducido);

    while(!listaVacia(&pl))
    {
        eliminarPorPosicion(&pl, &producto, sizeof(tProductoReducido), 1);
        mostrarProductoSinProveedor(depurado, &producto);
    }

    while(!listaVacia(&pl2))
    {
        eliminarPorPosicion(&pl2, &producto, sizeof(tProductoReducido), 1);
        mostrarProductoSinProveedor(depurado2, &producto);
    }

    fclose(depurado);
    fclose(depurado2);
    //vaciarLista(&pl);
    return 0;
}
