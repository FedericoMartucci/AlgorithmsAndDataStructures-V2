#include "archivos.h"

int main()
{
    int codigoError;

    if((codigoError = crearLoteDistribuidores()) != OK)
        return codigoError;
    if((codigoError = crearLoteModificaciones()) != OK)
        return codigoError;
    puts("----------ARCHIVO DISTRIBUIDORES---------------");
    mostrarArchivoBin(NOMBRE_ARCH_DISTRIBUIDORES, sizeof(tCliente), imprimirCliente);
    puts("----------ARCHIVO MODIFICACIONES---------------");
    mostrarArchivoBin(NOMBRE_ARCH_MODIFICACIONES, sizeof(tCliente), imprimirCliente);

    if((codigoError = actualizarArchivosBin(NOMBRE_ARCH_DISTRIBUIDORES,
                                         NOMBRE_ARCH_MODIFICACIONES,
                                         sizeof(tCliente),
                                         cmpCodCliente,
                                         cmpNombreFantasia,
                                         imprimirCliente)) != OK)
        return codigoError;
    puts("----------ARCHIVO DISTRIBUIDORES ACTUALIZADO---------------");
    mostrarArchivoBin(NOMBRE_ARCH_DISTRIBUIDORES, sizeof(tCliente), imprimirCliente);

    return OK;
}
