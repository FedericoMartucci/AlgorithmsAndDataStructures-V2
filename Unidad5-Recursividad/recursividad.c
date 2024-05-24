#include "recursividad.h"

unsigned factorialRecCola(unsigned n, unsigned acumulador)
{
    if(n == 1)
        return acumulador;
    return factorialRecCola(n - 1, acumulador * n);
}

unsigned factorialRec(unsigned n)
{
    if(n == 0)
        return 1;

    return factorialRec(n - 1) * n;
}

unsigned fibonacci(unsigned n)
{
    return (unsigned) round((pow(PHI, n) - pow(1 - PHI, n)) / sqrt(5));
}

unsigned fibonacciRec(unsigned n)
{
    if(n <= 2)
        return 1;

    return fibonacciRec(n - 1) + fibonacciRec(n - 2);
}

unsigned fibonacciRecCopia(unsigned n, int* contador)
{
    (*contador)++;
//    printf("Llamado: %d\n", *contador);
    if(n <= 2)
        return 1;

    return fibonacciRecCopia(n - 1, contador) + fibonacciRecCopia(n - 2, contador);
}

unsigned fibonacciProgDin(unsigned n)
{
    int ultValor;
    int valorActual;
    int valorAux;
    int i;

    if(n <= 2)
        return 1;

    ultValor = 1;
    valorActual = 1;

    for(i = 1; i < n - 1; i ++)
    {
        valorAux = valorActual;
        valorActual += ultValor;
        ultValor = valorAux;
    }

    return valorActual;
}

unsigned fibonacciProgDinCopia(unsigned n, long long unsigned* contador)
{
    int ultValor;
    int valorActual;
    int valorAux;
    int i;

    (*contador)++;
    if(n <= 2)
        return 1;

    ultValor = 1;
    valorActual = 1;

    for(i = 1; i < n - 1; i ++)
    {
        valorAux = valorActual;
        valorActual += ultValor;
        ultValor = valorAux;
        (*contador)++;
    }

    return valorActual;
}

void mostrarCadPorLetra(const char* cad)
{
    if(*cad == '\0')
        return;
    printf("%c\n", *cad);
    mostrarCadPorLetra(cad + 1);
}

void mostrarCadPorLetraInv(const char* cad)
{
    if(*cad == '\0')
        return;
    mostrarCadPorLetraInv(cad + 1);
    printf("%c\n", *cad);
}

void mostrarCadPorLetraIdaYVuelta(const char* cad)
{
    if(*cad == '\0')
        return;
    printf("%c\n", *cad);
    mostrarCadPorLetraIdaYVuelta(cad + 1);
    printf("%c\n", *cad);
}

void mostrarCadConLetraMenos(const char* cad)
{
    if(*cad == '\0')
        return;
    printf("%s\n", cad);
    mostrarCadConLetraMenos(cad + 1);
}

void mostrarCadConLetraMenosInv(const char* cad)
{
    if(*cad == '\0')
        return;

    mostrarCadConLetraMenosInv(cad + 1);
    printf("%s\n", cad);
}

void mostrarCadConLetraMenosIdaYVuelta(const char* cad)
{
    if(*cad == '\0')
        return;

    printf("%s\n", cad);
    mostrarCadConLetraMenosIdaYVuelta(cad + 1);
    printf("%s\n", cad);
}

void mostrarCadConLetraFinalMenosEnvoltorio(const char* cad)
{
    mostrarCadConLetraFinalMenos(cad, strlen(cad));
}

void mostrarCadConLetraFinalMenosInvEnvoltorio(const char* cad)
{
    mostrarCadConLetraFinalMenosInv(cad, strlen(cad));
}

void mostrarCadConLetraFinalMenosIdaYVueltaEnvoltorio(const char* cad)
{
    mostrarCadConLetraFinalMenosIdaYVuelta(cad, strlen(cad));
}

void mostrarCadConLetraFinalMenos(const char* cad, int longitud)
{
    if(longitud == 0)
        return;

    mostrarCadConLetraFinalMenos(cad, longitud - 1);
    printf("%.*s\n", longitud, cad);
}

void mostrarCadConLetraFinalMenosInv(const char* cad, int longitud)
{
    if(longitud == 0)
        return;

    printf("%.*s\n", longitud, cad);
    mostrarCadConLetraFinalMenosInv(cad, longitud - 1);
}

void mostrarCadConLetraFinalMenosIdaYVuelta(const char* cad, int longitud)
{
    if(longitud == 0)
        return;

    printf("%.*s\n", longitud, cad);
    mostrarCadConLetraFinalMenosIdaYVuelta(cad, longitud - 1);
    printf("%.*s\n", longitud, cad);
}

void mostrarEnteroPorDigito(int num)
{
    if(num == 0)
        return;

    printf("%d\n", num % 10);
    mostrarEnteroPorDigito(num / 10);
}

void mostrarEnteroPorDigitoInv(int num)
{
    if(num == 0)
        return;

    mostrarEnteroPorDigitoInv(num / 10);
    printf("%d\n", num % 10);
}

void mostrarEnteroPorDigitoIdaYVuelta(int num)
{
    if(num == 0)
        return;

    printf("%d\n", num % 10);
    mostrarEnteroPorDigitoIdaYVuelta(num / 10);
    printf("%d\n", num % 10);
}

void mostrarEnteroConDigitoMenos(int num, int modulo)
{
    if(num * 10 / modulo == 0)
        return;

    printf("%d\n", num % modulo);
    mostrarEnteroConDigitoMenos(num, modulo * 10);
}

void mostrarEnteroConDigitoMenosInv(int num, int modulo)
{
    if(num * 10 / modulo == 0)
        return;

    mostrarEnteroConDigitoMenosInv(num, modulo * 10);
    printf("%d\n", num % modulo);
}

void mostrarEnteroConDigitoMenosIdaYVuelta(int num, int modulo)
{
    if(num * 10 / modulo == 0)
        return;

    printf("%d\n", num % modulo);
    mostrarEnteroConDigitoMenosIdaYVuelta(num, modulo * 10);
    printf("%d\n", num % modulo);
}

void mostrarEnteroConDigitoFinalMenos(int num)
{
    if(num == 0)
        return;

    printf("%d\n", num);
    mostrarEnteroConDigitoFinalMenos(num / 10);
}

void mostrarEnteroConDigitoFinalMenosInv(int num)
{
    if(num == 0)
        return;

    mostrarEnteroConDigitoFinalMenosInv(num / 10);
    printf("%d\n", num);
}

void mostrarEnteroConDigitoFinalMenosIdaYVuelta(int num)
{
    if(num == 0)
        return;

    printf("%d\n", num);
    mostrarEnteroConDigitoFinalMenosIdaYVuelta(num / 10);
    printf("%d\n", num);
}



void mostrarNCaracteres(const char* cad, int n)
{
    if(n == 0)
        return;

    printf("%c", *cad);
    mostrarNCaracteres(cad + 1, n - 1);
}

void mapRecursivo(const tLista* pl, void(*accion)(void*))
{
    if(*pl == NULL)
        return;
    accion((*pl)->info);
    mapRecursivo(&(*pl)->sig, accion);
}

void mapRecursivoInv(const tLista* pl, void(*accion)(void*))
{
    if(*pl == NULL)
        return;
    mapRecursivoInv(&(*pl)->sig, accion);
    accion((*pl)->info);
}

void crearLista(tLista* pl)
{
    *pl = NULL;
}

int insertarAlInicio(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevo;
    if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
            (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return -1;
    }

    memcpy(nuevo->info, info, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *pl;
    *pl = nuevo;

    return 0;
}

int insertarAlFinalRec(tLista* pl, const void* info, unsigned cantBytes)
{
    tNodo* nuevo;

    if(*pl)
    {
        insertarAlFinalRec(&(*pl)->sig, info, cantBytes);
    }
    else
    {
        if((nuevo = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
                (nuevo->info = malloc(cantBytes)) == NULL)
        {
            free(nuevo);
            return -1;
        }

        memcpy(nuevo->info, info, cantBytes);
        nuevo->tamInfo = cantBytes;
        nuevo->sig = *pl;
        *pl = nuevo;
    }

    return 0;
}

void imprimirEnteroPorConsola(void* num)
{
    printf("%d ", *(int*)num);
}

int sumarDigitosEntero(int num)
{
    if(num == 0)
        return 0;
    return sumarDigitosEntero(num / 10) + num % 10;
}

int sumarDigitosCadena(const char* cadNumeros)
{
    if(*cadNumeros == '\0')
        return 0;
    return sumarDigitosCadena(cadNumeros + 1) + ATOI(*cadNumeros);
}

void mapArrayRec(int* vec, int ce, int* acumulador, void(*accion)(void*, const void*))
{
    if(ce == 0)
        return;
    accion(acumulador, vec);
    mapArrayRec(vec + 1, ce - 1, acumulador, accion);
}

void mapArrayRecInv(int* vec, int ce, int* acumulador, void(*accion)(void*, const void*))
{
    if(ce == 0)
        return;
    mapArrayRecInv(vec + 1, ce - 1, acumulador, accion);
    accion(&acumulador, vec);
}

void sumarNumerosPosParesArray(const int* vec, int ce, int* acumulador)
{
    if(ce == 0)
        return;
    if(ce % 2 == 0)
        *acumulador = *acumulador + *vec;
    sumarNumerosPosParesArray(vec + 1, ce - 1, acumulador);
}

void imprimirEnteroPorConsola2(void* salida, const void* num)
{
    fprintf(stdout, "%d ", *(int*)num);
}
void sumarEntero(void* acc, const void* num)
{
    *(int*)acc = *(int*)acc + *(int*)num;
}
void sumarEnteroPar(void* acc, const void* num)
{
    if(*(int*)num % 2 == 0)
        *(int*)acc = *(int*)acc + *(int*)num;
}

int strlenRec(const char* cad)
{
    return *cad == '\0'? 0 : strlenRec(cad + 1) + 1;
}

char* strchrRec(const char* cad, char val)
{
    if(*cad == '\0')
        return NULL;
    if(*cad == val)
        return (char*) cad;
    return strchrRec(cad + 1, val);
}

char* strrchrRecWrapper(const char* cad, char val)
{
    return strrchrRec(cad, val, strlenRec(cad) - 1);
}

char* strrchrRec(const char* cad, char val, int longitud)
{
    if(longitud == 0)
        return NULL;
    if(*(cad + longitud) == val)
        return (char*) (cad + longitud);
    return strrchrRec(cad, val, longitud - 1);
}

int calcularPotencia(int base, int exponente)
{
    if(exponente == 0)
        return 1;
    return calcularPotencia(base, exponente - 1) * base;
}

int calcularProducto(int factor1, int factor2)
{
    if(factor2 == 0)
        return 0;
    return calcularProducto(factor1, factor2 - 1) + factor1;
}

int decimalABinarioWrapper(int num)
{
    return decimalABinario(num, 1);
}

int decimalABinario(int num, int factor)
{
    if(num < 2)
        return (num % 2) * factor;
    return decimalABinario(num / 2, factor * 10) + (num % 2) * factor;
}

int algoritmoAckerman(int m, int n)
{
    if(m == 0)
        return n + 1;
    if(n == 0)
        return algoritmoAckerman(m - 1, 1);
    return algoritmoAckerman(m - 1, algoritmoAckerman(m, n - 1));
}

int esPalindromoWrapper(const char* cad)
{
    return esPalindromo(cad, cad + strlen(cad) - 1);
}

int esPalindromo(const char* ini, const char* fin)
{
    if(ini >= fin)
        return ES_PALINDROMO;
    if(!ES_LETRA(*ini))
        return esPalindromo(ini + 1, fin);
    if(!ES_LETRA(*fin))
        return esPalindromo(ini, fin - 1);
    if(A_MAYUS(*ini) != A_MAYUS(*fin))
        return NO_ES_PALINDROMO;
    return esPalindromo(ini + 1, fin - 1);
}

void* binarySearchRec(const void *key, const void *base, size_t nitems,
                     size_t size, int (*cmp)(const void *, const void*))
{
    int resultadoComparacion;

    resultadoComparacion = cmp(key, base + ((nitems / 2) * size));

    if(nitems == 0)
        return NULL;
    if(resultadoComparacion > 0)
        return binarySearchRec(key, base + size + ((nitems / 2) * size), (nitems / 2) - !(nitems % 2), size, cmp);
    if(resultadoComparacion < 0)
        return binarySearchRec(key, base, nitems / 2, size, cmp);
    return (void*) base + (nitems * size) / 2;
}

void* binarySearchRec2(const void *key, const void *base, size_t nitems, int iteraciones,
                     size_t size, int (*cmp)(const void *, const void*))
{
    int resultadoComparacion;
    printf("Iteracion: %d\n", iteraciones);
    resultadoComparacion = cmp(key, base + ((nitems / 2) * size));

    if(nitems == 0)
        return NULL;
    if(resultadoComparacion > 0)
        return binarySearchRec2(key, base + size + ((nitems / 2) * size), (nitems / 2) - !(nitems % 2), iteraciones + 1, size, cmp);
    if(resultadoComparacion < 0)
        return binarySearchRec2(key, base, nitems / 2, iteraciones + 1, size, cmp);
    return (void*) base + (nitems * size) / 2;
}


int cmpEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
