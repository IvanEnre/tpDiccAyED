/**
 * 
 * 
 */
#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <stdlib.h>
#include <string.h>

#define FALSO 0
#define VERDADERO 1
#define DATA_DUPLICADO -10
#define SIN_MEMORIA -20
#define INSERCION_EXITOSA 0
#define COMPLETO_DICC 1
#define MIN(X, Y) (X) < (Y) ? (X) : (Y)

typedef size_t (*FunHash)(const void* data, size_t capDicc);
typedef int (*Cmp)(const void* d1, const void* d2);
typedef void (*Accion)(void* d1, void* d2);
typedef void (*AccDupl)(void* d1, const void* d2);

typedef struct sNodo
{
    void* data;
    size_t tamData;
    struct sNodo* sig;
}tNodo;

//typedef tNodo* tLista;
//comentario de prueba para los efectos en github desde
//desde la maquina local
typedef struct sBucket
{
    //tLista lista[N], un vector que apunta
    //a distintas listas
    tNodo** tablaHash; //vector que apunta a distintas listas
    FunHash funcHashing;
    size_t ce;
    size_t tamMax; 
}tBucket;

typedef tBucket tDiccionario;

int crear_dic(tDiccionario* dicc, size_t cantMaxDicc, FunHash funcHashing);
int poner_dic(tDiccionario* dicc, const void* data, size_t tamData, Cmp cmp, AccDupl procesarDupl);
int sacar_dic(tDiccionario* dicc, void* data, size_t tamData, Cmp comp);
void* obtener_dic(tDiccionario* dicc, void* data, size_t tamData, Cmp comp);
void recorrer_dic(tDiccionario* dicc, void* dataTransf, Accion funcAccion);
void vaciar_dic(tDiccionario* dicc, int tipoVaciar);

#endif

