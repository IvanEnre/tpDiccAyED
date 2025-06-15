#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A_MINUSCULA(X) (X)>='A' && (X)<='Z'? (X) + 32 : (X)
#define A_MAYUSCULA(X) (X)>='a' && (X)<='z'? (X) - 32 : (X)
#define ES_LETRA(X) (((X)>='A' && (X)<='Z') || ((X)>='a' && (X)<='z'))
#define MAX_BUFF 100
#define TAM_NOM_ARCH 15
#define TAM_PALABRA 25
#define SIN_PROCESAR_ARCHIVO -15
#define ERROR_APERTURA_ARCHIVO -10
#define EXITO 0

#define MENU_MSJ    "     MENU PROCESADOR DE TEXTO\n"      \
                    "----------------------------------\n"  \
                    "  I - Ingresar Archivo de texto\n"       \
                    "  P - Procesar Archivo\n"                \
                    "  D - Informar Datos\n"                  \
                    "  S - Salir\n"


typedef struct
{
    char keyPal[TAM_PALABRA];   //claves: "guaymallen", "oreo", "pizza", "milanesa", ...
    int valCant;       //value:
}tPalabra;

typedef struct
{
    char keyNom[TAM_PALABRA];    //claves: "espacio", "sig-punt", ...
    int valCant;
}tSigno;

typedef struct
{
    int keyCant;
    int valPosi;
}tPunto;

typedef struct
{
    int key;
    tPalabra valPal;
}tRank;

typedef struct
{
    int item;
    int pos;
    int limite;
    void* dataPrev;
}tGrupoRank;

void clean_stdin(void);
void mensajeEstado(int estado, const char *inputNombreArchivo);
void inArchivo(char *inputNombreArchivo);
int menu(const char* listOpc, char* inputNombreArchivo);
void printDiccSignos(void* dataDicc, void* data);
void printDiccPalabras(void* dataDicc, void* data);
void printDiccPodio(void* dataDicc, void* data);
void printDiccPunto(void* dataDicc, void* data);

int cmpPalabra(const void* pal1, const void* pal2);
int cmpSigno(const void* sig1, const void* sig2);
int cmpApariciones(const void* pal1, const void* pal2);
int cmpPunto(const void* punto1, const void* punto2);
int cmpRank(const void* rank1, const void* rank2);

void actPalabraRepetido(void* pal1, const void* pal2);
void actSignoRepetido(void* pal1, const void* pal2);
#endif
