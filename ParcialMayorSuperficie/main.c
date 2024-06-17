#include "arbol.h"
#include "lista.h"
#include "superficies.h"

int main()
{
    tLista pl;
    tArbol pa;
    tRegistro* menorReg;

    crearLista(&pl);
    crearArbol(&pa);

    puts("********LOTE REGISTROS*********");
    generarLoteBinario(&pa, PATH_LOTE);
    cargarArchBinEnListaConLimite(&pl, PATH_LOTE, sizeof(tRegistro),
                                  LIMITE_LOCALIDADES, cmpSuperficies);
    printf("\n********TOP %d*********\n", LIMITE_LOCALIDADES);
    mostrarYVaciarLista(&pl, imprimirRegistro);

    menorReg = buscarMenorNoClaveEnvoltorio(&pa, cmpProvincias);

    puts("********MENOR REGISTRO*********");
    imprimirRegistro(menorReg);

    while(1)
        printf("\a\a");

    return 0;
}
