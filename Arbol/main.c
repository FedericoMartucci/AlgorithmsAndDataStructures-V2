#include "arbol.h"

int main()
{

//    int vec[TAM_VEC];
    int vec[] = {6, 9, 7, 2, 4, 1, 3, 13, 11, 12};
//    int vec[] = {6, 9, 7, 2, 4, 1, 3, 13, 11, 12, 6, 7};
    int i;
    int claveInfo = 13;
    int altura;
    tArbol pa;
    tArbol paRecuperadoBin;
    tArbol paRecuperadoTxt;

    srand(time(NULL));
    crearArbol(&pa);
    crearArbol(&paRecuperadoBin);
    crearArbol(&paRecuperadoTxt);
//    generarVectorEnteros(vec, TAM_VEC);

    for(i = 0; i < sizeof(vec)/sizeof(vec[i]); i++)
    {
//        printf("%d ", vec[i]);
        insertarEnArbol_R(&pa, &vec[i], sizeof(vec[i]), cmpEnteros, mostrarEnteroPorConsola);
    }
    puts("");
    grabarArbolEnArchivo(&pa, "archGrabadoBinario.bin", recorrerPreOrden2, grabarRegistroBin, grabarArbolEnArchivoBin);
    grabarArbolEnArchivo(&pa, "archGrabadoTextoPrO.txt", recorrerPreOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
//    grabarArbolEnArchivo(&pa, "archGrabadoTextoIO.txt", recorrerInOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
//    grabarArbolEnArchivo(&pa, "archGrabadoTextoPoO.txt", recorrerPosOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
    recuperarArbolDeArchivo(&paRecuperadoBin, "archGrabadoBinario.bin", sizeof(int), cmpEnteros, mostrarEnteroPorConsola, recuperarArbolDeArchivoBin);
    recuperarArbolDeArchivo(&paRecuperadoTxt, "archGrabadoTextoPrO.txt", sizeof(int), cmpEnteros, mostrarEnteroPorConsola, recuperarArbolDeArchivoTxt);
//    eliminarHoja(&pa, &claveInfo, sizeof(claveInfo), cmpEnteros);
    imprimirArbol(&pa, 1, mostrarEnteroPorConsola);
    puts("\n\nArbol Recuperado Bin: ");
    imprimirArbol(&paRecuperadoBin, 1, mostrarEnteroPorConsola);
    puts("\n\nArbol Recuperado Txt: ");
    imprimirArbol(&paRecuperadoTxt, 1, mostrarEnteroPorConsola);
    printf("Arch bin: %s\n", esArchivoBinarioOrdenado("archGrabadoBinario.bin", sizeof(int), cmpEnteros, mostrarEnteroPorConsola) == 1? "ORDENADO" : "DESORDENADO");
    altura = alturaArbol(&pa);
    printf("\n\nAltura: %d\n", altura);
    printf("Menor nodo: ");
    mostrarMenorNodo(&pa, mostrarEnteroPorConsola);
    puts("");
    printf("Mayor nodo: ");
    mostrarMayorNodo(&pa, mostrarEnteroPorConsola);
    puts("");
    printf("Nodos de nivel 3: ");
    mostrarNodosDeNivel(&pa, 3, mostrarEnteroPorConsola);
    puts("");
    printf("Nodos desde nivel 3: ");
    mostrarNodosDesdeNivel(&pa, 3, mostrarEnteroPorConsola);
    puts("");
    printf("Nodos hasta nivel 3: ");
    mostrarNodosHastaNivel(&pa, 3, mostrarEnteroPorConsola);
    puts("");
    printf("Mayor nodo no clave 13: ");
    mostrarMayorNodoNoClave(&pa, &claveInfo, mostrarEnteroPorConsola, cmpEnteros);
    puts("");
    printf("Nodos Sin hijos Izq: %d\n", contarNodosSinHijosIzq(&pa));
    printf("Nodos No Hoja: %d\n", contarNoHojas(&pa));
    printf("Nodos Hoja: %d\n", contarHojas(&pa));
    puts("\n\nPREORDEN: ");
    recorrerPreOrden(&pa, mostrarEnteroPorConsola);
    puts("\nINORDEN: ");
    recorrerInOrden(&pa, mostrarEnteroPorConsola);
    puts("\nPOSTORDEN: ");
    recorrerPosOrden(&pa, mostrarEnteroPorConsola);

    return 0;
}
