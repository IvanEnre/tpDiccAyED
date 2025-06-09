#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "utilidades.h"
#include "diccionario.h"

#define PROC_ARCHIVO 1
#define SALIR 0
#define PODIO 5
#define ERROR_APERTURA_ARCHIVO -10
#define EXITO 0
#define MAX_BUFF 100
#define LISTA_OPCIONES "listar opciones"
#define A_MINUSCULA(X) (X)>='A' && (X)<='Z'? (X) + 32 : (X)
#define ES_LETRA(X) (((X)>='A' && (X)<='Z') || ((X)>='a' && (X)<='z'))

typedef struct
{
    tDiccionario* diccPunto;
    tDiccionario* diccPodioPal;
    int rank;
}tDiccRank;

size_t hashingString(const char* s);
size_t hashingPalabra(const void* data, size_t capDicc);
size_t hashingSigno(const void* data, size_t capDicc);
size_t hashingPodioFinal(const void* data, size_t capDicc);
size_t hashingRanking(const void* data, size_t capDicc);

void cargarSignos(tDiccionario* diccSignos, char** ptrStr);
char* palabraLinea(char** lineaFrase, int* cantCaract);

void copiarDatosEnDicc(void* dataDicc, void* data);
void clasificarPuntosRank(void* dataDicc, void* data);
void generarDiccPodioPalabras(void* dataDicc, void* data);
void clasificarPodioFinal(void* dataPodio, void* diccPodioFinal);
int procesarArchivo(const char* nombArchTxt, tDiccionario* diccPals, tDiccionario* diccSignos);
void generarPodio(tDiccionario* diccPodio, tDiccionario* diccPals, int cantPodio);
void generarInforme(tDiccionario* dicc, Accion printDiccionario);
int solucion();

#endif