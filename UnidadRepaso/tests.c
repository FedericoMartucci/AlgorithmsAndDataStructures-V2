#include "tests.h"
#include "recursividad.h"

void testFactorial()
{
    printf("Factorial de 0 debe dar 1.\t");
    if(factorial(0) == 1)
        puts("Test passed.");
    else
        printf("Test failed.\n");

    printf("Factorial de 1 debe dar 1.\t");
    if(factorial(1) == 1)
        puts("Test passed.");
    else
        printf("Test failed.\n");

    printf("Factorial de 2 debe dar 2.\t");
    if(factorial(2) == 2)
        puts("Test passed.");
    else
        printf("Test failed.\n");

    printf("Factorial de 3 debe dar 6.\t");
    if(factorial(3) == 6)
        puts("Test passed.");
    else
        printf("Test failed.\n");

    printf("Factorial de 4 debe dar 24.\t");
    if(factorial(4) == 24)
        puts("Test passed.");
    else
        printf("Test failed.\n");

    printf("Factorial de 5 debe dar 120.\t");
    if(factorial(5) == 120)
        puts("Test passed.");
    else
        printf("Test failed.\n");

}
