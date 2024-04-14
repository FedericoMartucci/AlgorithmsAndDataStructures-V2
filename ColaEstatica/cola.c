#include "cola.h"

void crearCola(tCola* pc)
{
    pc->tamDisp = TAM_COLA;
    pc->pri = 0;
    pc->ult = 0;
}

int colaVacia(const tCola* pc)
{
    return pc->tamDisp == TAM_COLA;
}

int colaLlena(const tCola* pc, unsigned tamDato)
{
    return pc->tamDisp < tamDato + sizeof(unsigned);
}

int ponerEnCola(tCola* pc, const void* info, unsigned cantBytes)
{
    unsigned ini;
    unsigned fin;

    if(pc->tamDisp < cantBytes + sizeof(cantBytes))
        return COLA_LLENA;

    pc->tamDisp -= cantBytes + sizeof(cantBytes);

    ini = MINIMO(TAM_COLA - pc->ult, sizeof(cantBytes));
    if(ini)
        memcpy(pc->cola + pc->ult, &cantBytes, ini);

    fin = sizeof(cantBytes) - ini;
    if(fin)
        memcpy(pc->cola, ((char*)&cantBytes) + ini, fin);

    pc->ult = fin? fin : pc->ult + ini;

    ini = MINIMO(TAM_COLA - pc->ult, cantBytes);
    if(ini)
        memcpy(pc->cola + pc->ult, info, ini);

    fin = cantBytes - ini;
    if(fin)
        memcpy(pc->cola, ((char*)info) + ini, fin);

    pc->ult = fin? fin : pc->ult + ini;

    return OK;
}

int sacarDeCola(tCola* pc, void* info, unsigned cantBytes)
{
    unsigned ini;
    unsigned fin;
    unsigned tamEnCola;
    unsigned tamInfo;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    ini = MINIMO(TAM_COLA - pc->pri, sizeof(cantBytes));
    if(ini)
        memcpy(&tamEnCola, pc->cola + pc->pri, ini);

    fin = sizeof(cantBytes) - ini;
    if(fin)
        memcpy(((char*)&tamEnCola) + ini, pc->cola, fin);

    pc->tamDisp += tamEnCola + sizeof(cantBytes);
    pc->pri = fin? fin : pc->pri + ini;

    tamInfo = MINIMO(cantBytes, tamEnCola); //Se utilizan 2 tamAuxiliares para no perder el tamaño original del dato.
    ini = MINIMO(TAM_COLA - pc->pri, tamInfo);
    if(ini)
        memcpy(info, pc->cola + pc->pri, ini);

    fin = tamInfo - ini;
    if(fin)
        memcpy(((char*)info) + ini, pc->cola, fin);

    pc->pri = (pc->pri + tamEnCola) % TAM_COLA; //Por lo anterior como fin depende de tamInfo y no de tamEnCOla tenemos que hacerlo de esta forma

    return OK;
}

int verTope(const tCola* pc, void* info, unsigned cantBytes)
{
    unsigned ini;
    unsigned fin;
    unsigned tamInfo;
    unsigned primero;

    primero = pc->pri;

    if(pc->tamDisp == TAM_COLA)
        return COLA_VACIA;

    ini = MINIMO(TAM_COLA - primero, sizeof(cantBytes));
    if(ini)
        memcpy(&tamInfo, pc->cola + primero, ini);

    fin = sizeof(cantBytes) - ini;
    if(fin)
        memcpy(((char*)&tamInfo) + ini, pc->cola, fin);

    primero = fin? fin : primero + ini;

    tamInfo = MINIMO(cantBytes, tamInfo);
    ini = MINIMO(TAM_COLA - primero, tamInfo);
    if(ini)
        memcpy(info, pc->cola + primero, ini);

    fin = tamInfo - ini;
    if(fin)
        memcpy(((char*)info) + ini, pc->cola, fin);

    return OK;
}

void vaciarCola(tCola* pc)
{
    pc->tamDisp = TAM_COLA;
    pc->pri = pc->ult;
}
