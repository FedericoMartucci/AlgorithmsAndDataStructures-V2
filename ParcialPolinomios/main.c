#include "arbol.h"
#include "polinomios.h"

int main()
{
    tArbol pa;
    FILE* polinomioResultado;

    crearArbol(&pa);

    generarArchTextoPolinomio("p1.txt");
    generarArchTextoPolinomio("p2.txt");
    recorrerArchTexto(&pa, "p1.txt", insertarPolinomioEnArbol);
    recorrerArchTexto(&pa, "p2.txt", insertarPolinomioEnArbol);

    if((polinomioResultado = fopen("pr.txt", "wt")) == NULL)
        return FILE_ERR;
    recorrerInOrden2(&pa, polinomioResultado, grabarTermino);

    fclose(polinomioResultado);
    vaciarArbol(&pa);
    return 0;
}
