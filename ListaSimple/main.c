#include "lista.h"

int main()
{
    int i;
    int vec[] = {33, 5, 259, 0, -3, 21, -33, 0, 89, 5, 8, 9, -33};
    int elim = 5;
    int clave = 33;
    tLista pl;
    tLista plClon;

    crearLista(&pl);

    for(i = 0; i < sizeof(vec)/sizeof(int); i ++) {
//        insertarEnOrden(&pl, &vec[i], sizeof(vec[i]), cmpEnteros);
        insertarAlFinal(&pl, &vec[i], sizeof(vec[i]));
    }

//    ordenarPorSeleccion(&pl, cmpEnteros);
//    eliminarPrimeraOcurrencia(&pl, &elim, sizeof(elim), cmpEnteros);
//    eliminarOcurrencias(&pl, &elim, sizeof(elim), cmpEnteros);
//    eliminarUltimaOcurrencia(&pl, &elim, sizeof(elim), cmpEnteros);
//    mapC(&pl, mostrarNumeroPorConsola);
//    plClon = filterPython(&pl, &elim, cmpEnteros);
//    reduceC(&pl, &result, sumOperation);
//    printf("Resultado reduce %d", result);
//    mapC(&plClon, mostrarNumeroPorConsola);

    mapC(&pl, mostrarNumeroPorConsola);
    puts("");
    eliminarClaveSinDupYEjecutarAccionClavesDup(&pl, mostrarNumeroPorConsola, cmpEnteros);
    puts("");
//    eliminarNDespuesDeUnaClave(&pl, &clave, 2, cmpEnteros);
//    eliminarNUltimos(&pl, -2);
    mapC(&pl, mostrarNumeroPorConsola);

    return 0;
}
