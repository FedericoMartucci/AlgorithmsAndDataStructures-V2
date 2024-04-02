#include "../TDA/TDAVector.h"
#include "recursividad.h"
#include "tests.h"

int main()
{
    testFactorial();
    mostrarContenidoArrayChar("Hola grupo");
    puts("");
    mostrarContenidoArrayCharInverso("Hola grupo");
    puts("");
    puts("");
    mostrarCadenaConLetraMenos("Hola grupo");
    puts("");
    mostrarCadenaConLetraMenosInversa("Hola grupo");
    puts("");    puts("");
    mostrarCadenaPorLetraMasWrapper("Hola grupo");
    puts("");
    mostrarCadenaPorLetraMasInversaWrapper("Hola grupo");
    return 0;
}
