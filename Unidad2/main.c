//#include "../TDA/pilaEstatica.h"
#include "../TDA/pilaDinamica.h"
#include "../Bibliotecas/productos.h"

int main()
{
    tProducto loteProductos[30];

    generarProductos(loteProductos, 30);

    printf("Productos desordenados:\n");
    for (int i = 0; i < 30; i++) {
        imprimirProducto(&loteProductos[i]);
    }

    return 0;
}
