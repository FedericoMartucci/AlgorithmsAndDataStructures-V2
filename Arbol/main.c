#include "arbol.h"

int main()
{

//    int vec[TAM_VEC];
int vec[] = {6, 9, 7, 2, 4, 1, 3, 13, 11, 12};
    int i;
    int altura;
    tArbol pa;


    srand(time(NULL));
    crearArbol(&pa);
//    generarVectorEnteros(vec, TAM_VEC);

    for(i = 0; i < sizeof(vec)/sizeof(vec[i]); i++)
    {
////        printf("%d ", vec[i]);
        insertarEnArbol_I(&pa, &vec[i], sizeof(vec[i]), cmpEnteros, mostrarEnteroPorConsola);
    }

    imprimirArbol(&pa, 1, mostrarEnteroPorConsola);
    altura = alturaArbol(&pa);
    printf("\n\nAltura: %d", altura);
    puts("\n\nPREORDEN: ");
    recorrerPreOrden(&pa, mostrarEnteroPorConsola);
    puts("\nINORDEN: ");
    recorrerInOrden(&pa, mostrarEnteroPorConsola);
    puts("\nPOSTORDEN: ");
    recorrerPosOrden(&pa, mostrarEnteroPorConsola);

    return 0;
}
