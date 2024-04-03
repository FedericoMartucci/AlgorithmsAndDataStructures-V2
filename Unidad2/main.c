//#include "../TDA/pilaEstatica.h"
#include "../TDA/pilaDinamica.h"
#include "../Bibliotecas/productos.h"
#include "../Bibliotecas/archivos.h"

int main()
{
    int error;

    if((error = generarArchivoProductos("datos.txt", "BINARIO")) != OK){
        fprintf(stderr, "Error al abrir el archivo: %d", error);
        return error;
    }

//    ordenarArchivoTexto("datos.txt", cmpCodigo);
//    ordenarArchivoBinario("datos.bin", cmpCodigo);

//    cargarPilaConNumeros(&sumando1);
//    cargarPilaConNumeros(&sumando2);
//    sumarPilas(&sumando1, &sumando2);


    return 0;
}
