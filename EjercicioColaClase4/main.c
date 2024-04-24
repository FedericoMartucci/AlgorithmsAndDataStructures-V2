#include "archivos.h"

/**
    {[(-3 )+ (2 * [x - 4/2]+7} (como ejemplo) la idea es saber si esta bien o mal mi expresion algebraica.
    No me interesan las operaciones, me interesa saber si esta bien parentizada o no.
    No me interesa tampoco cuantos caracteres tiene.
    El archivo tiene expresiones separadas por ‘||’ y tengo que generar un archivo de texto que me diga si la expresion esta bien generada o no.
    Puedo hacer que se imprima la expresion solamente hasta el caracter anterior al error.
    Como evaluo solo los parentesis, imprimo solo los parentesis a la salida.
*/

int main()
{
    int error;

    if((error = generarArchivoCalculos("calculos.txt", "TEXTO")) != OK)
        return error;

    if((error = recorrerArchivoTextoDepurando("calculos.txt", TAM_CALCULO_MAX,
                                              trozarCalculos)) != OK)
        return error;

    return 0;
}
