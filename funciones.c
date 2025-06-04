#include "funciones.h"

int solucion()
{
    int cantPodio = PODIO;
    int opcion;
    char nombreArchivo[26];
    tDiccionario diccPalabras;  //{palabra: cantidad}, ...
    tDiccionario diccEsp;       //{puntuacion: cantidad}, {espacio: cantidad}
    tDiccionario diccPodio;     //{palabra: ranking}...

    while (opcion)
    {
        opcion = menu(LISTA_OPCIONES, nombreArchivo);
        if(opcion == PROC_ARCHIVO && procesarArchivo(nombreArchivo, &diccPalabras, &diccEsp))
        {
            generarPodio(&diccPodio, &diccPalabras, cantPodio);
            generarInforme(&diccEsp, printDiccEsp);
            generarInforme(&diccPalabras, printDiccEsp);
            generarInforme(&diccPodio, printDiccPodio);
        }

    }
    
}

void printDiccEsp(void* dataDicc, void* data)
{

}

void printDiccPalabras(void* dataDicc, void* data)
{

}

void printDiccPodio(void* dataDicc, void* data)
{

}

int menu(const char* listOpc, char* inputNombreArchivo)
{
    //desplegar menu con lista de opciones
    //guardar la opcion elegida
    //recibir la entrada de nombre del archivo
    //devuelve la opc elegida
}

int procesarArchivo(const char* nombArchTxt, tDiccionario* diccPals, tDiccionario* diccEsp)
{
    /**
     * verificar que sea valido el nombre archivo
     * puede ser una funcion separada que valide
     * realizar la lectura del archivo txt
     * cargar los datos en los diccionarios
     */
}

void generarPodio(tDiccionario* diccPodio, tDiccionario* diccPals, int cantPodio)
{
    /**
     * (¯_(ツ)_/¯ )
     */
}

void generarInforme(tDiccionario* dicc, Accion printDiccionario)
{
    /**
     * usar la primitiva recorrer_dic
     * junto a la funcion printDiccionario
     */
}