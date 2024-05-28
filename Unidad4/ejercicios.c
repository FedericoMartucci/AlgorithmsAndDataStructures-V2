#include "ejercicios.h"

void ejercicios()
{
    int opcion;

    do
    {
        system("cls");
        printf("Ejercicio 3\nImplemente un programa que le permita cargar el archivo <”datos”> en una Lista dinámica. En la información a cargar no se debe incluir el nombre del proveedor. Pruebe las siguientes alternativas:\n"
               "a. Insertar los nuevos nodos al final de la lista, salvo que la clave ya estuviera cargada y la"
               "descripción coincide, con lo cual se acumula la cantidad, se retiene la última fecha de compra"
               "y la fecha de vencimiento más vieja, el mayor precio de compra y de venta; si la descripción"
               "no coincidiera, se genera un nuevo nodo. Eliminar todos los nodos cuya clave está más de"
               "una vez, mostrando su información por pantalla y grabándolos en un archivo de texto"
               "<“errores2”> (tienen distinta descripción). Ordenar la lista resultante, y luego grabar esta"
               "información en un nuevo archivo binario <”depurado”>.\n"
               "b. Insertar los nuevos nodos ordenados por clave y a igualdad de clave por descripción, salvo"
               "que esta clave compuesta coincida con lo que se procede a acumular igual que antes."
               "Eliminar todos los nodos cuya clave está más de una vez, mostrando su información por"
               "pantalla y grabándolos en un archivo de texto <”errores2”> (tienen distinta descripción)."
               "Grabar esta información en un nuevo archivo <”depurado2”>.\n");
        printf("\nEjercicio 5\n"
               "Genere una matriz poco densa de FIL filas por COL columnas (con muchos ceros). A partir de la"
               "información cargada en la matriz, genere una lista simplemente enlazada con miembros de"
               "información para la fila, columna y valor (sólo si este es distinto de cero). Valiéndose de un menú que"
               "permita:\n"
               "a- el ingreso de fila y columna e informe el valor correspondiente, buscándolo en la lista.\n"
               "b- el ingreso de una fila, y muestre los elementos de la fila.\n"
               "c- el ingreso de una columna, y muestre los elementos de la columna.\n"
               "d- que muestre a partir de la lista los elementos de la matriz.\n"
               "Tenga en cuenta para los puntos [a-], [b-] y [d-] que debe disponer de la lista ordenada de modo que"
               "la búsqueda sea óptima.\n");
        printf("\n\nPresione 0 para salir.");
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 3:
            ejercicio3();
            system("pause");
            break;
        case 5:
            ejercicio5();
            system("pause");
            break;
        case 6:
            ejercicio6();
            system("pause");
            break;
        case 7:
            ejercicio7();
            system("pause");
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida.\n");
            system("pause");
            break;
        }
    }
    while(opcion != 0);

}

int ejercicio3()
{
    tLista pl;
    tLista pl2;
    tProductoReducido producto;
    FILE* depurado;
    FILE* depurado2;

    if(abrirArchivo(&depurado, "depurado.txt", "wt") != OK ||
            abrirArchivo(&depurado2, "depurado2.txt", "wt") != OK)
    {
        fclose(depurado);
        return FILE_ERR;
    }

    crearLista(&pl);
    crearLista(&pl2);

    generarArchivoProductos("datos.txt", "TEXTO");

    //Ejercicio a:
    cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor("datos.txt", &pl, cmpProductoReducido, acumularProductosReducidos);
    mostrarYEliminarDuplicados(&pl, "errores.txt",cmpCodigoProductoReducido);
    ordenarPorSeleccion(&pl, cmpProductoReducido);

    //Ejercicio b:
    cargarArchivoProductosEnListaOrdenadoSinProveedor("datos.txt", &pl2, cmpProductoReducido, acumularProductosReducidos);
    mostrarYEliminarDuplicados(&pl2, "errores2.txt",cmpCodigoProductoReducido);

    while(!listaVacia(&pl))
    {
        eliminarPorPosicion(&pl, &producto, sizeof(tProductoReducido), 1);
        mostrarProductoSinProveedor(depurado, &producto);
    }

    while(!listaVacia(&pl2))
    {
        eliminarPorPosicion(&pl2, &producto, sizeof(tProductoReducido), 1);
        mostrarProductoSinProveedor(depurado2, &producto);
    }

    fclose(depurado);
    fclose(depurado2);
    //vaciarLista(&pl);
    return OK;
}

int ejercicio5()
{
    int matriz[FIL][COL];
    float densidad = 0.3; // % matriz valores no nulos
    tElementoMatriz elementoMatriz;
    tLista pl;

    crearLista(&pl);

    generarMatriz(FIL, COL, matriz, densidad);
    insertarMatrizEnterosEnLista(&pl, FIL, COL, matriz);
    mostrarMenuEj5(&pl, FIL, COL);

    while(!listaVacia(&pl))
        eliminarPorPosicion(&pl, &elementoMatriz, sizeof(elementoMatriz), 1);

    return OK;
}

void generarMatriz(int filas, int columnas, int matriz[filas][columnas], float densidad)
{
    int i;
    int j;

    srand(time(NULL));

    for (i = 0; i < filas; i++)
    {
        for (j = 0; j < columnas; j++)
        {
            matriz[i][j] = (rand() / (float)RAND_MAX) < densidad? rand() % 100 + 1 : 0;
        }
    }
}

void insertarMatrizEnterosEnLista(tLista* pl, int filas, int columnas, int matriz[filas][columnas])
{
    int i;
    int j;
    tElementoMatriz elem;

    for (i = 0; i < filas; i++)
    {
        for (j = 0; j < columnas; j++)
        {
            if((elem.valor = matriz[i][j]) != 0)
            {
                elem.fila = i;
                elem.columna = j;
                insertarOrdenado(pl, &elem, sizeof(elem), cmpElemMatriz);
            }
        }
    }
}

int cmpElemMatriz(const void* elem1, const void* elem2)
{
    int comparacion;

    comparacion = ((tElementoMatriz*)elem1)->fila - ((tElementoMatriz*)elem2)->fila;

    return comparacion == 0? ((tElementoMatriz*)elem1)->columna - ((tElementoMatriz*)elem2)->columna : comparacion;
}

void imprimirElementoMatrizPorConsola(const void* elementoMatriz)
{
    printf("Fila: %d|Columna: %d|Valor: %d\n",
           ((tElementoMatriz*)elementoMatriz)->fila,
           ((tElementoMatriz*)elementoMatriz)->columna,
           ((tElementoMatriz*)elementoMatriz)->valor
          );
}

void acumularElementoMatriz(void* elemAcumulado, const void* elemAcumular)
{
    ((tElementoMatriz*)elemAcumulado)->valor = ((tElementoMatriz*)elemAcumular)->valor;
}

void mostrarMenuEj5(const tLista* pl, int filas, int columnas)
{
    int opcion;

    do
    {
        printf("Menu:\n");
        printf("1. Ingresar fila y columna e informar el valor correspondiente\n");
        printf("2. Ingresar una fila y mostrar los elementos de la fila\n");
        printf("3. Ingresar una columna y mostrar los elementos de la columna\n");
        printf("4. Mostrar todos los elementos de la matriz\n");
        printf("5. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarValor(pl, filas, columnas);
            system("pause");
            break;
        case 2:
            mostrarFila(pl, filas, columnas);
            system("pause");
            break;
        case 3:
            mostrarColumna(pl, filas, columnas);
            system("pause");
            break;
        case 4:
            imprimirMatriz(pl, filas, columnas);
            system("pause");
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida.\n");
            system("pause");
            break;
        }
    }
    while (opcion != 5);
}

void mostrarValor(const tLista* pl, int filas, int columnas)
{
    tElementoMatriz elemento;

    printf("Ingrese la fila: ");
    scanf("%d", &elemento.fila);
    printf("Ingrese la columna: ");
    scanf("%d", &elemento.columna);


    if(elemento.fila >= filas || elemento.columna >= columnas)
    {
        printf("Los valores ingresados exceden el rango de la matriz.");
        system("pause");
        return;
    }

    if(buscarInfoPorClaveListaOrdenada(pl, &elemento, cmpElemMatriz, acumularElementoMatriz) == CLAVE_NO_ENCONTRADA)
        elemento.valor = 0;

    imprimirElementoMatrizPorConsola(&elemento);
}

void mostrarFila(const tLista* pl, int filas, int columnas)
{
    int i;
    tElementoMatriz elem;

    printf("Ingrese la fila: ");
    scanf("%d", &elem.fila);


    if(elem.fila >= filas)
    {
        printf("El valor ingresado excede el rango de la matriz.");
        system("pause");
        return;
    }

    for (i = 0; i < columnas; i++)
    {
        elem.columna = i;
        elem.valor = 0;
        buscarInfoPorClaveListaOrdenada(pl, &elem, cmpElemMatriz, acumularElementoMatriz);
        printf("%4d", elem.valor);
    }
    puts("");
}

void mostrarColumna(const tLista* pl, int filas, int columnas)
{
    int i;
    tElementoMatriz elem;

    printf("Ingrese la columna: ");
    scanf("%d", &elem.columna);


    if(elem.columna >= columnas)
    {
        printf("El valor ingresado excede el rango de la matriz.");
        system("pause");
        return;
    }

    for (i = 0; i < filas; i++)
    {
        elem.fila = i;
        elem.valor = 0;
        buscarInfoPorClaveListaDesordenada(pl, &elem, cmpElemMatriz, acumularElementoMatriz);
        printf("%4d\n", elem.valor);
    }
}

void imprimirMatriz(const tLista* pl, int filas, int columnas)
{
    int i;
    int j;
    tElementoMatriz elem;

    for (i = 0; i < filas; i++)
    {
        for (j = 0; j < columnas; j++)
        {
            elem.fila = i;
            elem.columna = j;
            elem.valor = 0;
            buscarInfoPorClaveListaOrdenada(pl, &elem, cmpElemMatriz, acumularElementoMatriz);
            printf("%4d", elem.valor);
        }
        printf("\n");
    }
}

int ejercicio6()
{
    return OK;
}

int ejercicio7()
{
    return OK;
}

int cargarArchivoProductosEnListaAlFinalAcumulandoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
        void (*acumular)(void**, const void*))
{
    FILE* archProductos;
    tProductoReducido productoLeido;
    char buffer[TAM_BUFFER];

    if(abrirArchivo(&archProductos, nombre, "rt") != OK)
        return FILE_ERR;

    while(fgets(buffer, TAM_BUFFER, archProductos))
    {
        trozarProductoSinProveedor(buffer, &productoLeido);
        insertarAlFinalOAcumulo(pl, &productoLeido, sizeof(productoLeido), cmp, acumular);
    }

    fclose(archProductos);

    return OK;
}
int cargarArchivoProductosEnListaOrdenadoSinProveedor(const char* nombre, tLista* pl, int(*cmp)(const void*, const void*),
        void (*acumular)(void**, const void*))
{
    FILE* archProductos;
    tProductoReducido productoLeido;
    char buffer[TAM_BUFFER];

    if(abrirArchivo(&archProductos, nombre, "rt") != OK)
        return FILE_ERR;

    while(fgets(buffer, TAM_BUFFER, archProductos))
    {
        trozarProductoSinProveedor(buffer, &productoLeido);
//        mostrarProductoSinProveedor(stdout, &productoLeido);
        insertarOrdenadoAcumulando(pl, &productoLeido, sizeof(productoLeido), cmp, acumular);
    }

    fclose(archProductos);

    return OK;
}

int cmpProductoReducido (const void* prodA, const void* prodB)
{
    int resultadoComparacion;
    resultadoComparacion = strcmp(((tProductoReducido*)prodA)->codigo,
                                  ((tProductoReducido*)prodB)->codigo);
    return  resultadoComparacion == 0?
            strcmp(((tProductoReducido*)prodA)->descripcion,
                   ((tProductoReducido*)prodB)->descripcion)
            : resultadoComparacion;
}

int cmpCodigoProductoReducido (const void* prodA, const void* prodB)
{
    return strcmp(((tProductoReducido*)prodA)->codigo,
                  ((tProductoReducido*)prodB)->codigo);
}

/**

     a. Insertar los nuevos nodos al final de la lista, salvo que la clave ya estuviera cargada y la
     descripción coincide, con lo cual se acumula la cantidad, se retiene la última fecha de compra
     y la fecha de vencimiento más vieja, el mayor precio de compra y de venta; si la descripción
     no coincidiera, se genera un nuevo nodo. Eliminar todos los nodos cuya clave está más de
     una vez, mostrando su información por pantalla y grabándolos en un archivo de texto
     <“errores2”> (tienen distinta descripción). Ordenar la lista resultante, y luego grabar esta
     información en un nuevo archivo binario <”depurado”>.

     b. Insertar los nuevos nodos ordenados por clave y a igualdad de clave por descripción, salvo
     que esta clave compuesta coincida con lo que se procede a acumular igual que antes.
     Eliminar todos los nodos cuya clave está más de una vez, mostrando su información por
     pantalla y grabándolos en un archivo de texto <”errores2”> (tienen distinta descripción).
     Grabar esta información en un nuevo archivo <”depurado2”>.

*/
