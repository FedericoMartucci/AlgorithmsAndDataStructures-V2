#include "../include/ferreteria.h"
#include "../include/cola_dinamica.h"
#include <stdio.h>
#include "../include/utilitarias.h"

#define MAX_TAM_LINEA 30
#define MAX_RECURSO 20

int procesar_pedidos_propia(const char * path_prods, const char * path_pedidos, const char * path_indice)
{
    FILE *pfPedidos = fopen(path_pedidos, "rt"),
         *pfProds = fopen(path_prods, "rb");

    tArbolBinBusq Indices;
    tCola Pedidos;
    t_pedido regPedidoEntrante,
             regPedidoActual;
    t_reg_ind regIndice;
    char linea[MAX_TAM_LINEA];

    if(!pfPedidos)
        return ERROR_ARCHIVO;

    crearArbolBinBusq(&Indices);
    crear_cola(&Pedidos);

    cargarIndice(&Indices);

    if(fgets(linea, MAX_TAM_LINEA, pfPedidos))
    {
        formatearLineaPedido(linea, &regPedidoActual);
        poner_en_cola(&Pedidos, &regPedidoActual, sizeof(t_pedido));
        regPedidoEntrante = regPedidoActual;
        strcpy(regIndice.cod_prod, regPedidoActual.cod_prod);
        if(verificarStockPedido(&Indices, regIndice, regPedidoActual, pfProds))
            regPedidoActual.faltante = true;
    }

    while(fgets(linea, MAX_TAM_LINEA, pfPedidos))
    {
        if((regPedidoEntrante.cod_ped == regPedidoActual.cod_ped))
        {
            formatearLineaPedido(linea, &regPedidoEntrante);
            poner_en_cola(&Pedidos, &regPedidoEntrante, sizeof(t_pedido));
            strcpy(regIndice.cod_prod, regPedidoActual.cod_prod);
            if(verificarStockPedido(&Indices, regIndice, regPedidoEntrante, pfProds) && !regPedidoActual.faltante)
                regPedidoActual.faltante = true;
        }
        else
        {
            formatearLineaPedido(linea, &regPedidoEntrante);
            poner_en_cola(&Pedidos, &regPedidoEntrante, sizeof(t_pedido));
            regPedidoActual = regPedidoEntrante;
            strcpy(regIndice.cod_prod, regPedidoActual.cod_prod);
            if(verificarStockPedido(&Indices, regIndice, regPedidoEntrante, pfProds) && !regPedidoActual.faltante)
                regPedidoActual.faltante = true;
        }
    }

    realizarInforme(&Pedidos, &Indices, pfProds);

    actualizarIndices(&Indices);

    vaciar_cola(&Pedidos);
    eliminarArbol(&Indices);

    fclose(pfPedidos);
    fclose(pfProds);

    return TODO_OK;
}

int verificarStockPedido(tArbolBinBusq *Indices, t_reg_ind regIndice, t_pedido regPedidoEntrante, FILE *pfProds)
{
    int r = 0;
    t_producto_stock regProducto;

    fseek(pfProds, regIndice.nro_reg * sizeof(t_producto_stock), SEEK_SET);
    fread(&regProducto, sizeof(t_producto_stock), 1, pfProds);
    if((r = buscarElemArbolBinBusq(Indices, &regIndice, sizeof(t_reg_ind), compararIndices)))
    {
        fseek(pfProds, regIndice.nro_reg * sizeof(t_producto_stock), SEEK_SET);
        fread(&regProducto, sizeof(t_producto_stock), 1, pfProds);
        if(regProducto.stock < regPedidoEntrante.cant)
            r = 1;
    }

    return r;
}

void imprimirDetalleFaltante(tCola *Pedidos, FILE *pfImpr, FILE *pfProds)
{
    t_pedido regPedidoActual,
             regPedidoEntrante;

    frente_de_cola(Pedidos, &regPedidoActual, sizeof(t_pedido));

    while(frente_de_cola(Pedidos, &regPedidoEntrante, sizeof(t_pedido)) && (regPedidoActual.cod_ped == regPedidoEntrante.cod_ped))
    {
        sacar_de_cola(Pedidos, &regPedidoEntrante, sizeof(t_pedido));
        fprintf(pfImpr, "Pedido %d con faltantes:\n", regPedidoEntrante.cod_ped);
    }
}

void imprimirDetalleRealizado(tCola *Pedidos, FILE *pf)
{
    t_pedido regPedidoActual,
             regPedidoEntrante;

    frente_de_cola(Pedidos, &regPedidoActual, sizeof(t_pedido));

    while(frente_de_cola(Pedidos, &regPedidoEntrante, sizeof(t_pedido)) && !strcmpi(regPedidoActual.cod_prod, regPedidoEntrante.cod_prod))
    {
        sacar_de_cola(Pedidos, &regPedidoEntrante, sizeof(t_pedido));
        fprintf(pf, "Pedido %d realizado:\n", regPedidoActual.cod_ped);
    }
}

void formatearLineaPedido(char *linea, t_pedido *regPedidoActual)
{
    char recurso[MAX_RECURSO], *p;
    unsigned i = 0,
             cantItems = 0;

    if((p = strrchr(linea, '\n')))
        *p = '\0';
    p = linea;

    while( *p )
    {
        i = 0;
        while(ES_LETRA(*linea) || esNumero(*linea))
        {
            *(recurso + i) = *p;
            i++;
            p++;
        }
        if(cantItems == 0)
        {
            *(recurso + i) = '\0';
            regPedidoActual->cod_ped = atoi(recurso);
            cantItems++;
        }
        else if(cantItems == 1)
        {
            *(recurso + i) = '\0';
            strcpy(regPedidoActual->cod_prod, recurso);
            cantItems++;
        }
        else
        {
            *(recurso + i) = '\0';
            regPedidoActual->cant = atoi(recurso);
        }
    }
}

void realizarInforme(tCola *Pedidos, tArbolBinBusq *Indices, FILE *pfProds)
{
    FILE *pfFaltantes = fopen("pedidos_faltantes.txt", "wt"),
         *pfRealizados = fopen("pedidos_realizados.txt", "wt");
    t_pedido regPedidoEntrante;

    if(!pfFaltantes || !pfRealizados)
        return;

    while(frente_de_cola(Pedidos, &regPedidoEntrante, sizeof(t_pedido)))
    {
        if(regPedidoEntrante.faltante)
            imprimirDetalleFaltante(Pedidos, pfFaltantes, pfProds);
        else
            imprimirDetalleRealizado(Pedidos, pfRealizados);
    }

    fclose(pfFaltantes);
    fclose(pfRealizados);
}


int compararIndices(const void *reg1, const void *reg2)
{
    t_reg_ind *r1 = (t_reg_ind *)reg2, *r2 = (t_reg_ind *)reg2;
    return strcmpi(r1->cod_prod, r2->cod_prod);
}

int cargarIndice(tArbolBinBusq *pa)
{
    FILE *pfIndice = fopen(PATH_INDICE_PRODUCTOS, "rb");

    if(!pfIndice)
        return ERROR_ARCHIVO;

    return cargarArchivoBinOrdenadoAbiertoArbolBinBusq(pa, pfIndice, sizeof(t_reg_ind));
}

void actualizarIndices(tArbolBinBusq *pa)
{
    FILE *pfIndice = fopen(PATH_INDICE_PRODUCTOS, "wb");

    if(!pfIndice)
        return;

    recorrerEnOrdenSimpleArbolBinBusq(pa, pfIndice, escribirArchivoBin);

    fclose(pfIndice);
}

void escribirArchivoBin(void *info, unsigned tam, void *recurso)
{
    FILE *pf = (FILE *)recurso;
    t_reg_ind *reg = (t_reg_ind *)info;

    if(!info || !recurso)
        return;

    fseek(pf, reg->nro_reg * tam, SEEK_SET);
    fwrite(reg, tam, 1, pf);
}
