#include "ListaCircular.h"

int main()
{
    int vec[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int elim;
    tListaCircular pila;
    tListaCircular cola;

    crearPila(&pila);
    crearCola(&cola);

    printf("Apilando y acolando:\n");
    for(i = 0; i < sizeof(vec)/sizeof(int); i ++)
    {
        apilar(&pila, &vec[i], sizeof(vec[i]));
        acolar(&cola, &vec[i], sizeof(vec[i]));
        printf("Numero: %d\n", vec[i]);
    }

    printf("\nDesapilando:\n");
    for(i = 0; i < sizeof(vec)/sizeof(int); i ++)
    {
        desapilar(&pila, &elim, sizeof(elim));
        printf("Numero desapilado: %d\n", elim);
    }

    printf("\nDesacolando:\n");
    for(i = 0; i < sizeof(vec)/sizeof(int); i ++)
    {
        desacolar(&cola, &elim, sizeof(elim));
        printf("Numero desacolado: %d\n", elim);
    }

    vaciarPila(&pila);
    vaciarCola(&cola);
    return 0;
}
