#include "cola.h"

int main()
{
    int i;
    int elementoSacado;
    int elemsAInsertar[] = {1, 2, 3, 4, 5};
    tCola cola;
    crearCola(&cola);

    for(i = 0; i < sizeof(elemsAInsertar)/sizeof(elemsAInsertar[0]); i++)
        ponerEnCola(&cola, &elemsAInsertar[i], sizeof(elemsAInsertar[i]));

    sacarDeCola(&cola, &elementoSacado, sizeof(elementoSacado));
    sacarDeCola(&cola, &elementoSacado, sizeof(elementoSacado));
    sacarDeCola(&cola, &elementoSacado, sizeof(elementoSacado));
    verTope(&cola, &elementoSacado, sizeof(elementoSacado));
    verTope(&cola, &elementoSacado, sizeof(elementoSacado));
    printf("Elemento sacado: %d", elementoSacado);

    return 0;
}
