//#include "../TDA/pilaEstatica.h"
#include "../TDA/pilaDinamica.h"
#include "../Bibliotecas/productos.h"
#include "../Bibliotecas/archivos.h"

int main()
{
    srand(time(NULL));
    int error;
    tPila sumando1;
    tPila sumando2;

    crearPila(&sumando1);
    crearPila(&sumando2);

//    if((error = generarArchivoProductos("datos.txt", "TEXTO")) != OK){
//        fprintf(stderr, "Error al abrir el archivo: %d", error);
//        return error;
//    }
//
//    if((error = generarArchivoProductos("datos.bin", "BINARIO")) != OK){
//        fprintf(stderr, "Error al abrir el archivo: %d", error);
//        return error;
//    }
//
//    if((error = ordenarArchivoTexto("datos.txt", sizeof(tProducto), cmpCodigo, trozarProducto)) != OK){
//        fprintf(stderr, "Error al abrir el archivo: %d", error);
//        return error;
//    }
//    if((error = ordenarArchivoBinario("datos.bin", sizeof(tProducto), cmpCodigo)) != OK){
//        fprintf(stderr, "Error al abrir el archivo: %d", error);
//        return error;
//    }
    if((error = generarArchivoNumeros("sumando1.txt", "TEXTO")) != OK){
        fprintf(stderr, "Error al abrir el archivo: %d", error);
        return error;
    }

    if((error = generarArchivoNumeros("sumando2.txt", "TEXTO")) != OK){
        fprintf(stderr, "Error al abrir el archivo: %d", error);
        return error;
    }
    cargarPilaConNumerosDeUnArchTexto(&sumando1, "sumando1.txt", TAM_PRIMER_SUMANDO);
    cargarPilaConNumerosDeUnArchTexto(&sumando2, "sumando2.txt", TAM_PRIMER_SUMANDO);

    sumarPilas(&sumando1, &sumando2);

    vaciarPila(&sumando1);
    vaciarPila(&sumando2);

    return 0;
}
