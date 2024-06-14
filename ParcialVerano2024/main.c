#include "arbol.h"
#include "archivos.h"
#include "palabra.h"

int main()
{
    int opcion;
    tArbol pa;

    opcion = 0;
    crearArbol(&pa);
    setlocale(LC_ALL, "Spanish");

    recorrerArchivoTexto(&pa, "quijote-es.txt", insertarPalabrasEnArbol);

    while(opcion != 5)
    {
        do
        {
            system("cls");
            puts("MENU");
            puts("1- Ver la lista de palabras con la cantidad de repeticiones en orden ascendente");
            puts("2- Ver la lista de palabras con la cantidad de repeticiones en orden descendente");
            puts("3- Indicar la palabra con mayor cantidad de repeticiones");
            puts("4- Indicar la palabra con menor cantidad de repeticiones");
            puts("5- Salir de la aplicacion");
            printf("Ingrese opcion: ");
            scanf("%d", &opcion);
        } while(opcion < 1 || opcion > 5);
        procesarOpcion(&pa, opcion);
        system("pause");
    }

    vaciarArbol(&pa);

    return 0;
}
