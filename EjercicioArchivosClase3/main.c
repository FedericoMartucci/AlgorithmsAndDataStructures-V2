#include "../ColaEstatica/cola.h"
#include "archivo.h"

int main()
{
    FILE* archivoMuchosMov;
    FILE* archivoPocosMov;
    int codigoError;


    if((codigoError = generarArchivoProductos("movimientos.bin", "BINARIO")) != OK)
        return codigoError;

    if((codigoError = abrirArchivo(&archivoMuchosMov, "muchosMovimientos.txt", "wt")) != OK)
        return codigoError;

    if((codigoError = abrirArchivo(&archivoPocosMov, "pocosMovimientos.txt", "wt")) != OK)
    {
        fclose(archivoMuchosMov);
        return codigoError;
    }

    if((codigoError = recorrerArchivoBinario("movimientos.bin", sizeof(tProducto),
                      &archivoMuchosMov, &archivoPocosMov, acomodarProductos)) != OK)
    {
        fclose(archivoMuchosMov);
        fclose(archivoPocosMov);
        return codigoError;
    }

    fclose(archivoMuchosMov);
    fclose(archivoPocosMov);

    return 0;
}
