//#include "pilaEstatica.h"
#include "pilaDinamica.h"

int main()
{
    int vec[] = {1, 2, 3, 4, 5};
    int i;
    int tope;
    tPila pila;

    crearPila(&pila);

    if(pilaVacia(&pila))
        puts("Pila Vacia");
    else
        puts("Pila con elementos");

    for(i = 0; i < sizeof(vec)/sizeof(vec[0]); i ++){
        apilar(&pila, &vec[i], sizeof(vec[i]));
        printf("Apilo: %d\n", vec[i]);
    }

    while(!pilaVacia(&pila)){
        desapilar(&pila, &tope, sizeof(tope));
        printf("\nDesapilo: %d", tope);
    }

    return 0;
}
