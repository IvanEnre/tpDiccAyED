#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "utilidades.h" //.h -> .c
#include "diccionario.h" //.h -> .c

#define OPC_VALIDAS "IPDS"
#define INPUT_NOM_ARCHIVO 'I'
#define INF_DATOS 'D'
#define PROC_ARCHIVO 'P'
#define SALIR 'S'

#define PODIO 5

typedef struct
{
    tDiccionario* diccPuntosMax;
    tDiccionario* diccPodioPals;
    int podio;
}tGrupoDicc;

size_t hashingString(const char* s);

size_t hashingPalabra(const void* data, size_t capDicc);
size_t hashingSigno(const void* data, size_t capDicc);
size_t hashingRank(const void* rank, size_t capDicc);
size_t hashingPunto(const void* punto, size_t capDicc);

void cargarSignos(tDiccionario* diccSignos, char** ptrStr);
char* palabraLinea(char** lineaFrase, int* cantCaract);

int procesarArchivo(const char* nombArchTxt, tDiccionario* diccPals, tDiccionario* diccSignos);

void guardarPalsRankEnDiccPodio(void* palabra, void* grupDicc);
void obtenerPuntoMax(void* punto, void* puntoMax);
void copiarApariEnDiccPuntos(void* palabra, void* diccApar);
void generarPodio(tDiccionario* diccPodio, tDiccionario* diccPals, int cantPodio);
void generarInforme(tDiccionario* dicc, Accion printDiccionario);
int solucion();

#endif