#include "utilidades.h"

int menu(const char* listOpc, char* inputNombreArchivo)
{
    //desplegar menu con lista de opciones
    //guardar la opcion elegida
    //recibir la entrada de nombre del archivo
    //devuelve la opc elegida

    return 0;
}

void printDiccSignos(void* dataDicc, void* data)
{
    tSigno* signo = (tSigno*)dataDicc;
    int* total = (int*)data;
    if(dataDicc == NULL)
    {
        printf("|%-15s|%-6s|\n", "clave", "valor");
        return;
    }

    printf("|%-15s|%6d|\n", signo->keyNom, signo->valCant);
    *total = *total + signo->valCant;
}

void printDiccPalabras(void* dataDicc, void* data)
{
    tPalabra* palabra = (tPalabra*)dataDicc;
    int* total = (int*)data;
    if(dataDicc == NULL && data == NULL)
    {
        printf("|%-15s|%-6s|\n", "clave", "valor");
        return;
    }

    printf("|%-15s|%6d|\n", palabra->keyPal, palabra->valCant);
    *total = *total + palabra->valCant;
}

void printDiccPodio(void* dataDicc, void* data)
{
    tPodio* podio = (tPodio*)dataDicc;
    int* total = (int*)data;
    if(dataDicc == NULL && data == NULL)
    {
        printf("|%-15s|%-6s|\n", "clave", "valor");
        return;
    }

    if(1)
    {
        printf("|%-15s|%6d|\n", podio->keyPal, podio->valorRanking);
        *total = *total + 1;
    }
}

void printDiccPunto(void* dataDicc, void* data)
{
    tPunto* punto = (tPunto*)dataDicc;
    if(dataDicc == NULL && data == NULL)
    {
        printf("|%-6s|%-15s|\n", "clave", "valor");
        return;
    }

    printf("|%-6d|%-15d|\n", punto->keyCant, punto->valPosi);
}

void printDiccPodioFinal(void* dataDicc, void* data)
{
    tPodioFinal* pf = (tPodioFinal*)dataDicc;
    int* total = (int*)data;
    if(dataDicc == NULL && data == NULL)
    {
        printf("|%-15s|%-6s|\n", "clave", "valor");
        return;
    }

    if(1)
    {
        printf("|%-15s|%6d|\n", pf->podio.keyPal, pf->podio.valorRanking);
        *total = *total + 1;
    }
}
int cmpPodioFinal(const void* pf1, const void* pf2)
{
    tPodioFinal* pdf1 = (tPodioFinal*)pf1;
    tPodioFinal* pdf2 =(tPodioFinal*)pf2;

    return pdf1->key - pdf2->key;
}

int cmpPalabra(const void* pal1, const void* pal2)
{
    const tPalabra* p1 = (tPalabra*)pal1;
    const tPalabra* p2 = (tPalabra*)pal2;

    return strcmp(p1->keyPal, p2->keyPal);
}

int cmpSigno(const void* sig1, const void* sig2)
{
    const tSigno* s1 = (tSigno*)sig1;
    const tSigno* s2 = (tSigno*)sig2;

    return strcmp(s1->keyNom, s2->keyNom);
}

int cmpApariciones(const void* punto1, const void* punto2)
{
    const tPunto* p1 = (tPunto*)punto1;
    const tPunto* p2 = (tPunto*)punto2;

    return p1->keyCant - p2->keyCant;
}

void actPalabraRepetido(void* pal1, const void* pal2)
{
    tPalabra* p1 = (tPalabra*)pal1;
    const tPalabra* p2 = (tPalabra*)pal2;

    p1->valCant += p2->valCant;
}

void actSignoRepetido(void* sig1, const void* sig2)
{
    tSigno* s1 = (tSigno*)sig1;
    const tSigno* s2 = (tSigno*)sig2;

    s1->valCant += s2->valCant;
}