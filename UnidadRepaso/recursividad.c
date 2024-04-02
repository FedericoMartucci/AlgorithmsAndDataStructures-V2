#include "recursividad.h"

unsigned factorial(unsigned n)
{
    return n < 2? 1 : n * factorial(n-1);
}

void mostrarContenidoArrayChar(const char* str)
{
    if(*str == '\0')
        return;
    printf("'%c' ", *str);
    mostrarContenidoArrayChar(str + 1);
}

void mostrarContenidoArrayCharInverso(const char* str)
{
    if(*str != '\0'){
        mostrarContenidoArrayCharInverso(str + 1);
        printf("'%c' ", *str);
    }
}

void mostrarCadenaConLetraMenos(const char* str)
{
    if(*str != '\0'){
        printf("%s\n", str);
        mostrarCadenaConLetraMenos(str + 1);
    }
}

void mostrarCadenaConLetraMenosInversa(const char* str)
{
    if(*str != '\0'){
//        printf("%s\n", str); Muestra de ambas formas
        mostrarCadenaConLetraMenosInversa(str + 1);
        printf("%s\n", str);
    }
}

void mostrarCadenaPorLetraMasWrapper(const char* str)
{
    mostrarCadenaPorLetraMas(str, 1);
}

void mostrarCadenaPorLetraMas(const char* str, int length)
{
    if(length <= strlen(str)){
        mostrarNLetras(str, length);
        puts("");
        mostrarCadenaPorLetraMas(str, length + 1);
    }
}

void mostrarCadenaPorLetraMasInversaWrapper(const char* str)
{
    mostrarCadenaPorLetraMasInversa(str, 1);
}

void mostrarCadenaPorLetraMasInversa(const char* str, int length)
{
    if(length <= strlen(str)){
        mostrarCadenaPorLetraMasInversa(str, length + 1);
        mostrarNLetras(str, length);
        puts("");
    }
}

void mostrarNLetras(const char *str, int n)
{
    if(n > 0){
        printf("%c", *str);
        mostrarNLetras(str + 1, n - 1);

    }
}
