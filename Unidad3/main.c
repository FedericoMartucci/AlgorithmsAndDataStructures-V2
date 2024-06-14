#include "colaDinamica.h"
#include "../Bibliotecas/productos.h"
#include "archivos.h"
#include <time.h>

/**
    <"datos1"> con los registros cuya clave comience o termine con un carácter
    representativo de un dígito, pero en orden contrario al del archivo original, valiéndose de una Pila; y
    en <"datos2"> en el mismo orden en que estaban grabados.
    El proceso debe ser resuelto con una única lectura del archivo de entrada, mostrando por pantalla
    cada registro leído, para luego a la vez que se genera cada archivo de salida, mostrar qué se graba en
    cada uno
*/


int main()
{
    tProducto prod;
    tCola cola;
    char claveComp[] = "1004664";

    srand(time(NULL));

    crearCola(&cola);
    generarArchivoProductos("datos.txt", "TEXTO");

    generarArchivoTextoFiltrado("datos.txt", "datos1.txt", claveComp, &prod,
                                trozarProducto, filtrarCodigo, mostrarProducto);
    generarArchivoTextoFiltrado("datos.txt", "datos2.txt", claveComp, &prod,
                                trozarProducto, filtrarCodigo, mostrarProducto);
    colaCajero(&cola);
    vaciarCola(&cola);
    return 0;
}
