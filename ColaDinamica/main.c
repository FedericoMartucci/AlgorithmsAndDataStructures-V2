#include "cola.h"

int main()
{
    int i;
    int elementoSacado;
    int elemsAInsertar[] = {1, 2, 3, 4, 5};
    tCola cola;
    crearCola(&cola);

    if(colaVacia(&cola))
        puts("Cola vacia");
    else
        puts("Cola con elemento");

    if(colaLlena(&cola, sizeof(int )))
        puts("Cola llena");
    else
        puts("Cola sin llenar");

    for(i = 0; i < sizeof(elemsAInsertar)/sizeof(elemsAInsertar[0]); i++)
    {
        ponerEnCola(&cola, &elemsAInsertar[i], sizeof(elemsAInsertar[i]));
        printf("%d ", elemsAInsertar[i]);
    }

    if(colaVacia(&cola))
        puts("\nCola vacia");
    else
        puts("\nCola con elemento");

    while(!colaVacia(&cola))
    {
        sacarDeCola(&cola, &elementoSacado, sizeof(elementoSacado));
        printf("%d ", elementoSacado);
    }
    if(colaVacia(&cola))
        puts("\nCola vacia");
    else
        puts("\nCola con elemento");

    return 0;
}
