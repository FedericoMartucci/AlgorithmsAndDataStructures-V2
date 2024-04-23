#include "archivos.h"
#include "productos.h"

int generarArchivoProductos(const char* nombre, const char* tipo)
{
    int error;
    int i;

    FILE* archivoProductos;
    tProducto loteProductos[CANT_PRODUCTOS];

    generarProductos(loteProductos, CANT_PRODUCTOS);

    if(strcmpi(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wb")) != OK)
            return error;
        fwrite(loteProductos, sizeof(tProducto), CANT_PRODUCTOS, archivoProductos);
    }
    else if(strcmpi(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoProductos, nombre, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_PRODUCTOS; i++)
            mostrarProducto(archivoProductos, &loteProductos[i]);
    }
    else
        return FILE_OPEN_MODE_ERR;

    fclose(archivoProductos);
    return OK;
}

void generarNumeros(int* vecNumeros, int cantidad)
{
    int i;

    for (i = 0; i < cantidad; i++)
        vecNumeros[i] = rand() % 10;

}

int generarArchivoNumeros(const char* nombre, const char* tipo)
{
    int error;
    int i;

    int loteNumeros[CANT_NUMEROS];
    FILE* archivoNumeros;

    generarNumeros(loteNumeros, CANT_NUMEROS);

    if(strcmpi(tipo, "BINARIO") == 0)
    {
        if((error = abrirArchivo(&archivoNumeros, nombre, "wb")) != OK)
            return error;
        fwrite(loteNumeros, sizeof(tProducto), CANT_NUMEROS, archivoNumeros);
    }
    else if(strcmpi(tipo, "TEXTO") == 0)
    {
        if((error = abrirArchivo(&archivoNumeros, nombre, "wt")) != OK)
            return error;
        for (i = 0; i < CANT_NUMEROS; i++)
            mostrarNumero(archivoNumeros, &loteNumeros[i]);
    }
    else
        return FILE_OPEN_MODE_ERR;

    fclose(archivoNumeros);
    return OK;
}

void mostrarNumero(FILE* destino, const void* p) {
    fprintf(destino, "%d", *(int*)p);
}

int abrirArchivo(FILE** archivoAAbrir, const char* nombre, const char* tipo)
{
    if(!(*archivoAAbrir = fopen(nombre, tipo)))
    {
        perror("The file could not be opened");
        return FILE_ERR;
    }

    return OK;
}

int ordenarArchivoTexto(const char* nombre, unsigned tamRegistro,
                        int(*cmp)(const void*, const void*),
                        void(*trozar)(char*, void*))
{
    int error;
    int comparacion;
    char buffer[TAM_BUFFER];
    tPila pila1;
    tPila pila2;
    void* auxPila;
    void* registro;
    FILE* archAOrdenar;
    FILE* archOrdenado;

    crearPila(&pila1);
    crearPila(&pila2);

    if((auxPila = malloc(tamRegistro)) == NULL)
        return MEM_ERR;

    if((registro = malloc(tamRegistro)) == NULL)
    {
        free(auxPila);
        return MEM_ERR;
    }

    if((error = abrirArchivo(&archAOrdenar, nombre, "rt")) != OK)
    {
        free(auxPila);
        free(registro);
        return error;
    }

    if((error = abrirArchivo(&archOrdenado, "ordenado.txt", "wt")) != OK)
    {
        free(auxPila);
        free(registro);
        fclose(archAOrdenar);
        return error;
    }

    while(fgets(buffer, sizeof(buffer), archAOrdenar))
    {
        trozar(buffer, registro);
        if(verTope(&pila1, auxPila, tamRegistro) != OK)
            apilar(&pila1, registro, tamRegistro);
        else if((comparacion = cmp(auxPila, registro) > 0)){
            while(verTope(&pila1, auxPila, tamRegistro) == OK &&
                  (comparacion = cmp(auxPila, registro) > 0))
            {
                desapilar(&pila1, auxPila, tamRegistro);
                apilar(&pila2, auxPila, tamRegistro);
            }
            apilar(&pila1, registro, tamRegistro);
        }
        else if(verTope(&pila2, auxPila, tamRegistro) != OK)
            apilar(&pila2, registro, tamRegistro);
        else if((comparacion = cmp(auxPila, registro) > 0))
            apilar(&pila2, registro, tamRegistro);
        else
        {
            while(verTope(&pila2, auxPila, tamRegistro) == OK &&
                  (comparacion = cmp(auxPila, registro) <= 0))
            {
                desapilar(&pila2, auxPila, tamRegistro);
                apilar(&pila1, auxPila, tamRegistro);
            }
            apilar(&pila2, registro, tamRegistro);
        }
    }

    while(!pilaVacia(&pila2))
    {
        desapilar(&pila2, auxPila, tamRegistro);
        apilar(&pila1, auxPila, tamRegistro);
    }

    while(!pilaVacia(&pila1))
    {
        desapilar(&pila1, auxPila, tamRegistro);
        mostrarProducto(archOrdenado, auxPila);
    }

    vaciarPila(&pila1);
    vaciarPila(&pila2);

    free(auxPila);
    free(registro);
    fclose(archAOrdenar);
    fclose(archOrdenado);
    return OK;
}
int ordenarArchivoBinario(const char* nombre, unsigned tamRegistro,
                        int(*cmp)(const void*, const void*))
{
    int error;
    int comparacion;
    tPila pila1;
    tPila pila2;
    void* auxPila;
    void* registro;
    FILE* archAOrdenar;
    FILE* archOrdenado;

    crearPila(&pila1);
    crearPila(&pila2);

    if((auxPila = malloc(tamRegistro)) == NULL)
        return MEM_ERR;

    if((registro = malloc(tamRegistro)) == NULL)
    {
        free(auxPila);
        return MEM_ERR;
    }

    if((error = abrirArchivo(&archAOrdenar, nombre, "rb")) != OK)
    {
        free(auxPila);
        free(registro);
        return error;
    }
    if((error = abrirArchivo(&archOrdenado, "ordenado.dat", "wb")) != OK)
    {
        free(auxPila);
        free(registro);
        fclose(archAOrdenar);
        return error;
    }

    fread(registro, tamRegistro, 1, archAOrdenar);
    while(!feof(archAOrdenar))
    {
        if(verTope(&pila1, auxPila, tamRegistro) != OK)
            apilar(&pila1, registro, tamRegistro);
        else if((comparacion = cmp(auxPila, registro) > 0)){
            while(verTope(&pila1, auxPila, tamRegistro) == OK &&
                  (comparacion = cmp(auxPila, registro) > 0))
            {
                desapilar(&pila1, auxPila, tamRegistro);
                apilar(&pila2, auxPila, tamRegistro);
            }
            apilar(&pila1, registro, tamRegistro);
        }
        else if(verTope(&pila2, auxPila, tamRegistro) != OK)
            apilar(&pila2, registro, tamRegistro);
        else if((comparacion = cmp(auxPila, registro) > 0))
            apilar(&pila2, registro, tamRegistro);
        else
        {
            while(verTope(&pila2, auxPila, tamRegistro) == OK &&
                  (comparacion = cmp(auxPila, registro) <= 0))
            {
                desapilar(&pila2, auxPila, tamRegistro);
                apilar(&pila1, auxPila, tamRegistro);
            }
            apilar(&pila2, registro, tamRegistro);
        }
        fread(registro, tamRegistro, 1, archAOrdenar);
    }

    while(!pilaVacia(&pila2))
    {
        desapilar(&pila2, auxPila, tamRegistro);
        apilar(&pila1, auxPila, tamRegistro);
    }

    while(!pilaVacia(&pila1))
    {
        desapilar(&pila1, auxPila, tamRegistro);
        fwrite(auxPila, tamRegistro, 1, archOrdenado);
    }

    vaciarPila(&pila1);
    vaciarPila(&pila2);

    free(auxPila);
    free(registro);
    fclose(archAOrdenar);
    fclose(archOrdenado);
    return OK;
}

int cargarPilaConNumerosDeUnArchTexto(tPila* sumando, const char* nombreArch,
                                      unsigned tamRegistro)
{
    int error;
    int numero;
    char buffer[TAM_SUMANDO_MAX];
    char* elementoBuffer;
    FILE* archivoDeCarga;

    elementoBuffer = buffer;

    if((error = abrirArchivo(&archivoDeCarga, nombreArch, "rt")) != OK)
        return error;

    fgets(buffer, TAM_SUMANDO_MAX, archivoDeCarga);
    printf("%s", buffer);
    while(*elementoBuffer != '\0'){
        numero = ATOI(*elementoBuffer);
        printf("\n%d", numero);
        apilar(sumando, &numero, sizeof(numero));
        elementoBuffer++;
    }

    fclose(archivoDeCarga);
    return OK;
}

int sumarPilas(tPila* sumando1, tPila* sumando2)
{
    tPila pilaResultado;
    int sumandoPila1;
    int sumandoPila2;
    int resultado;
    int carry;
    int proximoCarry;
    FILE* archResultado;

    if(abrirArchivo(&archResultado, "resultado.txt", "wt") != OK)
        return FILE_ERR;

    crearPila(&pilaResultado);

    carry = 0;

    while(desapilar(sumando1, &sumandoPila1, sizeof(sumandoPila1)) == OK &&
          desapilar(sumando2, &sumandoPila2, sizeof(sumandoPila2)) == OK){
        proximoCarry = (carry + sumandoPila1 + sumandoPila2) / 10;
        resultado = (carry + sumandoPila1 + sumandoPila2) - proximoCarry * 10;
        carry = proximoCarry;

        apilar(&pilaResultado, &resultado, sizeof(resultado));
    }

    while(!pilaVacia(sumando1)){
        desapilar(sumando1, &sumandoPila1, sizeof(sumandoPila1));
        proximoCarry = (carry + sumandoPila1) / 10;
        resultado = (carry + sumandoPila1) - proximoCarry * 10;
        carry = proximoCarry;
        apilar(&pilaResultado, &resultado, sizeof(resultado));
    }

    while(!pilaVacia(sumando2)){
        desapilar(sumando2, &sumandoPila2, sizeof(sumandoPila2));
        proximoCarry = (carry + sumandoPila2) / 10;
        resultado = (carry + sumandoPila2) - proximoCarry * 10;
        carry = proximoCarry;
        apilar(&pilaResultado, &resultado, sizeof(resultado));
    }

    if(carry)
        apilar(&pilaResultado, &carry, sizeof(carry));

    while(!pilaVacia(&pilaResultado)){
        desapilar(&pilaResultado, &resultado, sizeof(resultado));
        fprintf(archResultado, "%d", resultado);
    }

    fclose(archResultado);
    return OK;
}