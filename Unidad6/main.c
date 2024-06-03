#include "ejercicios.h"




int main()
{
    const char* nombreArchivo = "personas.dat";
    tArbol indice;

    crearArbol(&indice);
    srand(time(NULL));

    if(generarArchivoLotePersonas(nombreArchivo, "wb") != OK)
        printf("Error al generar el archivo.\n");

    recuperarIndiceDeArchivo(&indice, nombreArchivo, sizeof(tPersona), sizeof(tIndice), cmpIndPersonas, NULL, generarIndicePersona, recuperarIndiceDeArchivoBin);
    grabarArbolEnArchivo(&indice, "personas.idx", recorrerInOrden2, mostrarIndicePersona3, grabarArbolEnArchivoBin);
    vaciarArbol(&indice);

    testear_si_el_indice_se_condice_con_el_registro_correspondiente();

    return 0;
}
