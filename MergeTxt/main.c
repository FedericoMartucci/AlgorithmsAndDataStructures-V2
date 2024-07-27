#include "archivos.h"

int main()
{
    srand(time(NULL));
    crearLoteTxt("lote1.txt", NUM_PRODUCTOS_LOTE_1);
    crearLoteTxt("lote2.txt", NUM_PRODUCTOS_LOTE_2);
    return 0;
}
