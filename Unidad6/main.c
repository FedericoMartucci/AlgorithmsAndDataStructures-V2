#include "arbol.h"

int main()
{
    int vec[] = {6, 9, 7, 2, 4, 1, 3, 13, 11, 12};
    int i;
    tArbol pa;

    crearArbol(&pa);
    for(i = 0; i < sizeof(vec)/sizeof(vec[i]); i ++)
        insertarEnArbol_R(&pa, &vec[i], sizeof(vec[i]), cmpEnteros, mostrarEntero);

//    mostrarHojas(&pa, mostrarEnteroPorConsola);
//    printf("Hojas: %d\n", contarHojas(&pa));
    printf("Hojas: %d\n", contarYMostrarHojas(&pa, mostrarEnteroPorConsola));
    printf("\nAltura: %d\n", alturaArbol(&pa));
//    vaciarArbol(&pa);

    return 0;
}
