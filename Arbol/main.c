#include "arbol.h"

int main()
{

    int vec[TAM_VEC];

    int i;
    int altura;
    tArbol pa;


    srand(time(NULL));
    crearArbol(&pa);
    generarVectorEnteros(vec, TAM_VEC);

    for(i = 0; i < sizeof(vec)/sizeof(vec[i]); i++)
    {
        printf("%d ", vec[i]);
        insertarEnArbol_I(&pa, &vec[i], sizeof(vec[i]), cmpEnteros, mostrarEnteroPorConsola);
    }

    imprimirArbol(&pa, 0, mostrarEnteroPorConsola);
    altura = alturaArbol(&pa);
    printf("\n\nAltura: %d", altura);
    puts("\n\n");
//    recorrerPreOrden(&pa, mostrarEnteroPorConsola);
//    puts("");
//    recorrerInOrden(&pa, mostrarEnteroPorConsola);
//    puts("");
//    recorrerPosOrden(&pa, mostrarEnteroPorConsola);

    return 0;
}
