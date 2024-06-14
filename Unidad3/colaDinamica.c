#include "colaDinamica.h"

void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}

int colaVacia(const tCola* pc)
{
    return pc->pri == NULL;
}

int colaLlena(const tCola* pc, unsigned cantBytes)
{
    tNodo* nodoAAcolar = (tNodo*) malloc(sizeof(tNodo));
    void* info = malloc(cantBytes);

    free(nodoAAcolar);
    free(info);

    return nodoAAcolar == NULL || info == NULL;
}

int acolar(tCola* pc, const void* info, unsigned cantBytes)
{
    tNodo* nodoAAcolar;

    if((nodoAAcolar = (tNodo*) malloc(sizeof(tNodo))) == NULL ||
       (nodoAAcolar->info = malloc(cantBytes)) == NULL){
       free(nodoAAcolar);
       return MEM_ERR;
    }

    memcpy(nodoAAcolar->info, info, cantBytes);
    nodoAAcolar->tamInfo = cantBytes;
    nodoAAcolar->sig = NULL;

    if(pc->pri)
        pc->ult->sig = nodoAAcolar;
    else
        pc->pri = nodoAAcolar;

    pc->ult = nodoAAcolar;

    return OK;
}

int desacolar(tCola* pc, void* info, unsigned cantBytes)
{
    tNodo* elim;

    if(pc->pri == NULL)
       return COLA_VACIA;

    elim = pc->pri;

    memcpy(info, elim->info, MIN(elim->tamInfo, cantBytes));
    pc->pri = elim->sig;

    free(elim->info);
    free(elim);

    if(pc->pri == NULL)
        pc->ult = NULL;

    return OK;
}

int verPrimero(const tCola* pc, void* info, unsigned cantBytes)
{
    if(pc->pri == NULL)
       return COLA_VACIA;

    memcpy(info, pc->pri->info, MIN(pc->pri->tamInfo, cantBytes));

    return OK;
}

void vaciarCola(tCola* pc)
{
    tNodo* nodoAEliminar;

    while(pc->pri){
        nodoAEliminar = pc->pri;
        pc->pri = nodoAEliminar->sig;
        free(nodoAEliminar->info);
        free(nodoAEliminar);
    }
    pc->ult = NULL;
}


void colaCajero(tCola *pc)
{
    int tiempoArribo[3] = {1,5,9};
    int tiempoUso[3] = {1,3,5};
    int tiempoLlegada;
    int cantColasVacias;
    int nroCliente;
    tCliente cli;
    tCliente cliAux;

    tiempoLlegada = tRandom(tiempoArribo);
    cantColasVacias = 0;
    nroCliente = 1;

    while(cantColasVacias < COLASVACIAS)
    {

        llegaCliente(&cli, tiempoUso);
        acolar(pc, &cli, sizeof(tCliente));
        while(!colaVacia(pc))
        {
            if(cli.tiempoUsoCajero != 0)
                printf("Cliente n:%d tiempo de uso restante: %d\n", nroCliente, cli.tiempoUsoCajero);
            if(tiempoLlegada == 0)
            {
                tiempoLlegada = tRandom(tiempoArribo);
                llegaCliente(&cliAux, tiempoUso);
                acolar(pc, &cliAux, sizeof(tCliente));
            }
            if(cli.tiempoUsoCajero == 0)
            {
                desacolar(pc, &cli, sizeof(tCliente));
                nroCliente++;
            }
            else
            {
                cli.tiempoUsoCajero -= 1;
                tiempoLlegada -= 1;
            }
        }
        cantColasVacias++;
        printf("La cola se vacio por %d vez\n", cantColasVacias);
    }
}

int tRandom(int* tiempoArribo)
{
    tiempoArribo += rand() % 3;;
    return *tiempoArribo;
}

void llegaCliente(tCliente* cli, int* tiempoUso)
{
    tiempoUso += rand() % 3;
    cli->tiempoUsoCajero = *tiempoUso;
}
