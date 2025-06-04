#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "diccionario.h"
#define PROC_ARCHIVO 1
#define SALIR 0
#define PODIO 5
#define LISTA_OPCIONES "listar opciones"

void printDiccEsp(void* dataDicc, void* data);
void printDiccPalabras(void* dataDicc, void* data);
void printDiccPodio(void* dataDicc, void* data);

int menu(const char* listOpc, char* inputNombreArchivo);
int procesarArchivo(const char* nombArchTxt, tDiccionario* diccPals, tDiccionario* diccEsp);
void generarPodio(tDiccionario* diccPodio, tDiccionario* diccPals, int cantPodio);
void generarInforme(tDiccionario* dicc, Accion printDiccionario);
int solucion();

#endif