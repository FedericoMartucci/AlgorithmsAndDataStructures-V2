#include "ejercicios.h"

int cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                               void (*acumular)(void**, const void*))
{
    FILE* archProductos;
    tProductoReducido productoLeido;
    char buffer[TAM_BUFFER];

    if(abrirArchivo(&archProductos, nombre, "rt") != OK)
        return FILE_ERR;

    while(fgets(buffer, TAM_BUFFER, archProductos))
    {
        trozarProductoSinProveedor(buffer, &productoLeido);
        insertarAlFinalOAcumulo(pl, &productoLeido, sizeof(productoLeido), cmp, acumular);
    }

    fclose(archProductos);

    return OK;
}
int cargarArchivoProductosEnListaOrdenadoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
                                                      void (*acumular)(void**, const void*))
{
    FILE* archProductos;
    tProductoReducido productoLeido;
    char buffer[TAM_BUFFER];

    if(abrirArchivo(&archProductos, nombre, "rt") != OK)
        return FILE_ERR;

    while(fgets(buffer, TAM_BUFFER, archProductos))
    {
        trozarProductoSinProveedor(buffer, &productoLeido);
//        mostrarProductoSinProveedor(stdout, &productoLeido);
        insertarOrdenadoAcumulando(pl, &productoLeido, sizeof(productoLeido), cmp, acumular);
    }

    fclose(archProductos);

    return OK;
}

int cmpProductoReducido (const void* prodA, const void* prodB)
{
    int resultadoComparacion;
    resultadoComparacion = strcmp(((tProductoReducido*)prodA)->codigo,
                  ((tProductoReducido*)prodB)->codigo);
    return  resultadoComparacion == 0?
                  strcmp(((tProductoReducido*)prodA)->descripcion,
                  ((tProductoReducido*)prodB)->descripcion)
                  : resultadoComparacion;
}

int cmpCodigoProductoReducido (const void* prodA, const void* prodB)
{
    return strcmp(((tProductoReducido*)prodA)->codigo,
                  ((tProductoReducido*)prodB)->codigo);
}

/**

     a. Insertar los nuevos nodos al final de la lista, salvo que la clave ya estuviera cargada y la
     descripción coincide, con lo cual se acumula la cantidad, se retiene la última fecha de compra
     y la fecha de vencimiento más vieja, el mayor precio de compra y de venta; si la descripción
     no coincidiera, se genera un nuevo nodo. Eliminar todos los nodos cuya clave está más de
     una vez, mostrando su información por pantalla y grabándolos en un archivo de texto
     <“errores2”> (tienen distinta descripción). Ordenar la lista resultante, y luego grabar esta
     información en un nuevo archivo binario <”depurado”>.

     b. Insertar los nuevos nodos ordenados por clave y a igualdad de clave por descripción, salvo
     que esta clave compuesta coincida con lo que se procede a acumular igual que antes.
     Eliminar todos los nodos cuya clave está más de una vez, mostrando su información por
     pantalla y grabándolos en un archivo de texto <”errores2”> (tienen distinta descripción).
     Grabar esta información en un nuevo archivo <”depurado2”>.

*/
