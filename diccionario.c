/**
 * 
 * 
 */
#include "diccionario.h"

int crear_dic(tDiccionario* dicc, size_t cantMaxDicc, FunHash funcHashing)
{
    int i;
    
    dicc->tablaHash = malloc(cantMaxDicc * sizeof(tNodo*));
    if(dicc->tablaHash == NULL)
        return FALSO;
    
    for(i = 0; i < cantMaxDicc; i++)
    {
        dicc->tablaHash[i] = NULL;
    }
    
    dicc->funcHashing = funcHashing;
    dicc->tamMax = cantMaxDicc;
    dicc->ce = 0;

    return VERDADERO;
}

int poner_dic(tDiccionario* dicc, const void* data, size_t tamData, Cmp cmp, AccDupl procesarDupl)
{
    size_t index = dicc->funcHashing(data, dicc->tamMax) % dicc->tamMax;

    //si es lista vacia => no hay colision
    if(dicc->tablaHash[index] == NULL)
        dicc->ce++;

    // insercion al inicio de la lista(X)
    // insercion de forma ordenada
    tNodo** pl = &dicc->tablaHash[index];
    tNodo* nodo;
    
    // no se permitira duplicados
    // actualilzar en caso de duplicados
    while (*pl && cmp(data, (*pl)->data) < 0)
    {
        pl = &(*pl)->sig;
    }

    if(*pl && cmp(data, (*pl)->data) == 0)
    {
        if(procesarDupl)
            procesarDupl((*pl)->data, data);
        
        return DATA_DUPLICADO;
    }
    
    nodo = malloc(sizeof(tNodo));
    if(nodo == NULL)
        return SIN_MEMORIA;

    nodo->data = malloc(tamData);
    if(nodo->data == NULL)
    {
        free(nodo);
        return SIN_MEMORIA;
    }

    memcpy(nodo->data, data, tamData);
    nodo->tamData = tamData;

    nodo->sig = *pl;
    *pl = nodo;

    return INSERCION_EXITOSA;
}

void* obtener_dic(tDiccionario* dicc, void* data, size_t tamData, Cmp comp)
{
    size_t index = dicc->funcHashing(data, dicc->tamMax) % dicc->tamMax;
    
    tNodo** pl = &dicc->tablaHash[index];

    while (*pl && comp(data, (*pl)->data) < 0)
    {
        pl = &(*pl)->sig;
    }

    //devolver el ptr a data en lista (duda)
    //en lugar de una copia
    if(!*pl)
        return NULL;   // NULL
    
    //memcpy(data, (*pl)->data, MIN(tamData, (*pl)->tamData)); // comentarlo

    return (*pl)->data;   //(*pl)->data
}

int sacar_dic(tDiccionario* dicc, void* data, size_t tamData, Cmp comp)
{
    size_t index = dicc->funcHashing(data, dicc->tamMax) % dicc->tamMax;

    tNodo* nodo;
    tNodo** pl = &dicc->tablaHash[index];

    while (*pl && comp(data, (*pl)->data) < 0)
    {
        pl = &(*pl)->sig;
    }

    if(*pl == NULL)
    {
        return FALSO;
    }
    
    nodo = *pl;
    *pl = nodo->sig;
    memcpy(data, nodo->data, MIN(tamData, nodo->tamData));
    free(nodo->data);
    free(nodo);

    if(dicc->tablaHash[index] == NULL)
        dicc->ce--;

    return VERDADERO;
}

void recorrer_dic(tDiccionario* dicc, void* dataTransf, Accion funcAccion)
{
    tNodo** pl;
    for (size_t i = 0; i < dicc->tamMax; i++)
    {
        pl = &dicc->tablaHash[i];
        while(*pl)
        {
            funcAccion((*pl)->data, dataTransf);
            pl = &(*pl)->sig;
        }
    }
}

void vaciar_dic(tDiccionario* dicc, int tipoVaciar)
{
    tNodo** pl;
    tNodo* nodo;
    for (size_t i = 0; i < dicc->tamMax; i++)
    {
        pl = &dicc->tablaHash[i];
        while(*pl)
        {
            nodo = *pl;
            *pl = nodo->sig;

            free(nodo->data);
            free(nodo);
        }
    }
    
    if(tipoVaciar == COMPLETO_DICC)
        free(dicc->tablaHash);
}