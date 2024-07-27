#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "estructuras.h"

#define PRIMERA_OPCION_VALIDA 'A'
#define ULTIMA_OPCION_VALIDA 'D'
#define OPCION_VALIDA 1
#define OPCION_NO_VALIDA 0

#define RETORNO_DE_CARRO '\r'
#define BACKSPACE '\b'

int esLetraValida(char key);
char obtenerLetra(const char* opcion, const tPregunta pregunta);
int iniciarTemporizador(char* respuesta, int tiempoLimite);
char captarIngresoDificultad(const tMapeoDificultad* mapeoDificultades,
                             int cantElementos);
int esOpcionDificultad(char key, const tMapeoDificultad* mapeoDificultades,
                       int cantElementos);

#endif // TECLADO_H_INCLUDED
