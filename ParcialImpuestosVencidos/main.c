#include "arbol.h"
#include "deuda.h"

int main()
{
    tArbol pa;

    crearArbol(&pa);
    srand(time(NULL));

    generarArchBinImpuestosVencidos("impuestosVencidos.dat");
    iniciarMenu(&pa);

    vaciarArbol(&pa);
    return 0;
}
