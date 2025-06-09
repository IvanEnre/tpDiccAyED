#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char keyPal[16];   //claves: "guaymallen", "oreo", "pizza", "milanesa", ...
    int valCant;       //value:
}tPalabra;

typedef struct
{
    char keyNom[16];    //claves: "espacio", "sig-punt", ...
    int valCant;
}tSigno;

typedef struct
{
    char keyPal[16];    //claves: palabras
    int valorRanking;     //valor: 1-n
}tPodio;

typedef struct
{
    int keyCant;
    int valPosi;
}tPunto;

typedef struct
{
    int key;
    tPodio podio;
}tPodioFinal;

int menu(const char* listOpc, char* inputNombreArchivo);
void printDiccSignos(void* dataDicc, void* data);
void printDiccPalabras(void* dataDicc, void* data);
void printDiccPodio(void* dataDicc, void* data);
void printDiccPunto(void* dataDicc, void* data);
void printDiccPodioFinal(void* dataDicc, void* data);
int cmpPodioFinal(const void* pf1, const void* pf2);
int cmpPalabra(const void* pal1, const void* pal2);
int cmpSigno(const void* sig1, const void* sig2);
int cmpApariciones(const void* pal1, const void* pal2);
void actPalabraRepetido(void* pal1, const void* pal2);
void actSignoRepetido(void* pal1, const void* pal2);
#endif