#include "arbol.h"
//#include "lista.h"
#include "vehiculos.h"


int main()
{
    tArbol pa;

    crearArbol(&pa);

//    tLista pa;

//    crearLista(&pa);

    generarArchBinVehiculos("vehiculos.dat"); // genero lote
    recorrerArchBin(&pa, "vehiculos.dat", sizeof(tVehiculo), insertarVehiculoEnArbol); //cargo en arbol
//    recorrerLista(&pa, mostrarPromedio);
//    recorrerInOrden(&pa, mostrarPromedio); //recorro arbol

    vaciarArbol(&pa);
//    vaciarLista(&pa);

    return 0;
}
