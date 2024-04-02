#include "pilaEstatica.h"

//void crearPila(tPila* pp)
//{
//    pp->tope = TAM_PILA;
//}
//
//int pilaVacia(const tPila* pp)
//{
//    return pp->tope == TAM_PILA;
//}
//
//int pilaLlena(const tPila* pp, unsigned cantBytes)
//{
//    return pp->tope < cantBytes + sizeof(unsigned);
//}
//
//int apilar(tPila* pp, const void* dato, unsigned cantBytes)
//{
//    if(pp->tope < cantBytes + sizeof(unsigned))
//        return PILA_LLENA;
//
//    pp->tope -= cantBytes;
//    memcpy(pp->pila + pp->tope, dato, cantBytes);
//
//    pp->tope -= sizeof(unsigned);
//    memcpy(pp->pila + pp->tope, &cantBytes, sizeof(unsigned));
//
//    return OK;
//}
//
//int desapilar(tPila* pp, void* dato, unsigned cantBytes)
//{
//    unsigned tamInfoApilada;
//
//    if(pp->tope == TAM_PILA)
//        return PILA_VACIA;
//
//    memcpy(&tamInfoApilada, pp->pila + pp->tope, sizeof(unsigned));
//    pp->tope += sizeof(unsigned);
//
//    memcpy(dato, pp->pila + pp->tope, MIN(cantBytes, tamInfoApilada));
//    pp->tope += tamInfoApilada;
//
//    return OK;
//}
//
//int verTope(const tPila* pp, void* dato, unsigned cantBytes)
//{
//    unsigned tamInfoApilada;
//
//    if(pp->tope == TAM_PILA)
//        return PILA_VACIA;
//
//    memcpy(&tamInfoApilada, pp->pila + pp->tope, sizeof(unsigned));
//    memcpy(dato, pp->pila + pp->tope, MIN(cantBytes, tamInfoApilada));
//
//    return OK;
//}
//
//void vaciarPila(tPila* pp)
//{
//    pp->tope = TAM_PILA;
//}
