#include "arbol.h"
#include <locale.h>
//TODO:
//    - ejercicio indices (6.7)
//    - verificar tp
int main()
{
//    int vec[TAM_VEC];
    int vec[] = {6, 9, 8, 2, 4, 1, 3, 13, 11, 12, 8, 14, 7};
//    int vec[] = {6, 9, 7, 2, 4, 1, 3, 13, 11, 12, 6, 7};
    int i;
    int claveInfo = 14;
    int claveInfo2 = 13;
    int altura;
    int tipoDeArbol;
    tArbol pa;
    tArbol pa2;
    tArbol paRecuperadoBin;
    tArbol paRecuperadoTxt;

    srand(time(NULL));
    crearArbol(&pa);
    crearArbol(&pa2);
    crearArbol(&paRecuperadoBin);
    crearArbol(&paRecuperadoTxt);
//    generarVectorEnteros(vec, TAM_VEC);

    for(i = 0; i < sizeof(vec)/sizeof(vec[i]); i++)
    {
//        printf("%d ", vec[i]);
        insertarEnArbol_R(&pa, &vec[i], sizeof(vec[i]), cmpEnteros, mostrarEnteroPorConsola);
    }
    puts("");
    grabarArbolEnArchivo(&pa, "archGrabadoBinario.bin", recorrerInOrden2, grabarRegistroBin, grabarArbolEnArchivoBin);
    grabarArbolEnArchivo(&pa, "archGrabadoTextoPrO.txt", recorrerPreOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
//    grabarArbolEnArchivo(&pa, "archGrabadoTextoIO.txt", recorrerInOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
//    grabarArbolEnArchivo(&pa, "archGrabadoTextoPoO.txt", recorrerPosOrden2, grabarEnteroTxt, grabarArbolEnArchivoTxt);
    recuperarArbolDeArchivo(&paRecuperadoBin, "archGrabadoBinario.bin", sizeof(int), cmpEnteros, mostrarEnteroPorConsola, recuperarArbolDeArchivoBin);
    recuperarArbolDeArchivo(&paRecuperadoTxt, "archGrabadoTextoPrO.txt", sizeof(int), cmpEnteros, mostrarEnteroPorConsola, recuperarArbolDeArchivoTxt);
//    eliminarHoja(&pa, &claveInfo, sizeof(claveInfo), cmpEnteros);
    cargarArchivoBinarioEnArbol(&pa2, "archGrabadoBinario.bin", sizeof(int), cmpEnteros, mostrarEnteroPorConsola);
    imprimirArbol(&pa, 1, mostrarEnteroPorConsola);
    eliminarRaiz(&pa);
    puts("\n\nArbol con raiz eliminada: ");
    imprimirArbol(&pa, 1, mostrarEnteroPorConsola);
    eliminarNodo(&pa, &claveInfo2, sizeof(claveInfo2), cmpEnteros);
    puts("\n\nArbol con 13 eliminado: ");
    imprimirArbol(&pa, 1, mostrarEnteroPorConsola);
    puts("\n\nArbol balanceado recuperado de arch: ");
    imprimirArbol(&pa2, 1, mostrarEnteroPorConsola);
    puts("\n\nArbol Recuperado Bin: ");
    imprimirArbol(&paRecuperadoBin, 1, mostrarEnteroPorConsola);
    puts("\n\nArbol Recuperado Txt: ");
    imprimirArbol(&paRecuperadoTxt, 1, mostrarEnteroPorConsola);
    printf("Arch bin: %s\n", esArchivoBinarioOrdenado("archGrabadoBinario.bin", sizeof(int), cmpEnteros, mostrarEnteroPorConsola) == 1? "ORDENADO" : "DESORDENADO");
    altura = alturaArbol(&pa);
    printf("Altura: %d\n", altura);
    tipoDeArbol = determinarTipoDeArbol(&pa);
    printf("Tipo de arbol: %s\n", tipoDeArbol == ES_COMPLETO? "COMPLETO" : tipoDeArbol == ES_BALANCEADO? "BALANCEADO" : tipoDeArbol == ES_AVL? "AVL" : "OTRO");
    printf("Nodos a nivel 3: %d\n", contarNodosANivel(&pa, 4));
    printf("Es balanceado: %s\n", esArbolBalanceado(&pa)? "SI" : "NO");
    printf("Es AVL: %s\n", esArbolAVL(&pa)? "SI" : "NO");
    printf("Es completo: %s\n", esArbolCompleto(&pa)? "SI" : "NO");
    printf("Es completo a nivel 3: %s\n", esCompletoANivel(&pa, 3)? "SI" : "NO");
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
    printf("Mayor nodo no clave 14: ");
    mostrarMayorNodoNoClave(&pa, &claveInfo, mostrarEnteroPorConsola, cmpEnteros);
    puts("");
    printf("Menor nodo no clave 1: ");
    claveInfo = 1;
    mostrarMenorNodoNoClave(&pa, &claveInfo, mostrarEnteroPorConsola, cmpEnteros);
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
