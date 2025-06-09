#include "funciones.h"
int solucion()
{
    //int cantPodio = PODIO;
    int opcion = 1;
    char nombreArchivo[26] = "archivo-4.txt";
    tDiccionario diccPalabras;  //{palabra: cantidad}, ...
    tDiccionario diccSignos;       //{puntuacion: cantidad}, {espacio: cantidad}
    tDiccionario diccPodio;     //{palabra: ranking}...
    tDiccionario diccPodioFinal;
    crear_dic(&diccPalabras, 10, hashingPalabra);
    crear_dic(&diccSignos, 2, hashingSigno);
    crear_dic(&diccPodio, 10, hashingPalabra);
    crear_dic(&diccPodioFinal, PODIO, hashingPodioFinal);
    while (opcion)
    {
        //opcion = menu(LISTA_OPCIONES, nombreArchivo);
        if(opcion == PROC_ARCHIVO && procesarArchivo(nombreArchivo, &diccPalabras, &diccSignos) == EXITO)
        {
            generarPodio(&diccPodio, &diccPalabras, PODIO);
            
            printf("Diccionario palabras.\n");
            generarInforme(&diccPalabras, printDiccPalabras);
            printf("\nDiccionario de signos.\n");
            generarInforme(&diccSignos, printDiccSignos);
            printf("\nDiccionario de ranking de ayuda.\n");
            generarInforme(&diccPodio, printDiccPodio);

            recorrer_dic(&diccPodio, &diccPodioFinal, clasificarPodioFinal);
            printf("\nDiccionario de ranking final.\n");
            generarInforme(&diccPodioFinal, printDiccPodioFinal);
        }
        opcion = 0;
    }

    vaciar_dic(&diccPalabras);
    vaciar_dic(&diccSignos);
    vaciar_dic(&diccPodio);
    vaciar_dic(&diccPodioFinal);
    return 0;
}

size_t hashingString(const char* s)
{
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;
    while(*s){
        hash_value = (hash_value + (*s - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
        s++;
    }
    return hash_value;
}

size_t hashingPodioFinal(const void* data, size_t capDicc)
{
    tPodioFinal* p = (tPodioFinal*)data;
    return p->key - 1;
}

size_t hashingRanking(const void* data, size_t capDicc)
{
    tPunto* punto = (tPunto*)data;
    return punto->keyCant - 1;
}

size_t hashingPalabra(const void* data, size_t capDicc)
{
    const tPalabra* palabra = (tPalabra*)data;
    return hashingString(palabra->keyPal);
}

size_t hashingSigno(const void* data, size_t capDicc)
{
    const tSigno* signo = (tSigno*)data;
    return hashingString(signo->keyNom);
}

void cargarSignos(tDiccionario* diccSignos, char** ptrStr)
{
    tSigno sEspacio = {"espacio", 1};
    tSigno sPuntuacion = {"sig-punt", 1};

    while (**ptrStr && !ES_LETRA(**ptrStr))
    {
        if(**ptrStr == ' ')
            poner_dic(diccSignos, &sEspacio, sizeof(tSigno), cmpSigno, actSignoRepetido);
        else
            poner_dic(diccSignos, &sPuntuacion, sizeof(tSigno), cmpSigno, actSignoRepetido);
        
        (*ptrStr)++;
    }
}

char* palabraLinea(char** lineaFrase, int* cantCaract)
{
    char* initPal;

    initPal = *lineaFrase;
    *cantCaract = 0;
    while(**lineaFrase && ES_LETRA(**lineaFrase))
    {
        **lineaFrase = A_MINUSCULA(**lineaFrase);
        (*cantCaract)++;
        (*lineaFrase)++;
    }
    
    return initPal;
}

void procesarLineaStr(char* ptrLinea, tDiccionario* diccPals, tDiccionario* diccSignos)
{
    char* ptrPalabraStr;
    int cantCaract;
    tPalabra palabra;

    while (*ptrLinea)
    {
        ptrPalabraStr = palabraLinea(&ptrLinea, &cantCaract);
        if(cantCaract)
        {
            strncpy(palabra.keyPal, ptrPalabraStr, cantCaract);
            palabra.keyPal[cantCaract] = '\0';
            palabra.valCant = 1;
            poner_dic(diccPals, &palabra, sizeof(tPalabra), cmpPalabra, actPalabraRepetido);
        }
        //esta funcion toma los digitos cómo
        //parte de un signo de puntuacion
        cargarSignos(diccSignos, &ptrLinea);

        //ptrLinea++;
    }
}

int procesarArchivo(const char* nombArchTxt, tDiccionario* diccPals, tDiccionario* diccSignos)
{
    /**
     * verificar que sea valido el nombre archivo
     * puede ser una funcion separada que valide
     * realizar la lectura del archivo txt
     * cargar los datos en los diccionarios
     */

    char lineaBuffer[MAX_BUFF];
    char* ptrSaltoLinea;
    FILE* pfTxt;

    pfTxt = fopen(nombArchTxt, "rt");
    if(pfTxt == NULL)
        return ERROR_APERTURA_ARCHIVO;
    
    while (fgets(lineaBuffer, MAX_BUFF, pfTxt))
    {
        ptrSaltoLinea = strchr(lineaBuffer, '\n');
        *ptrSaltoLinea = '\0';
        procesarLineaStr(lineaBuffer, diccPals, diccSignos);
    }

    fclose(pfTxt);

    return EXITO;
}

void copiarDatosEnDicc(void* dataDicc, void* data)
{
    tPalabra* palabra = (tPalabra*)dataDicc;
    tDiccionario* diccPunto = (tDiccionario*)data;
    tPunto punto;
    punto.keyCant = palabra->valCant;
    punto.valPosi = 1;
    poner_dic(diccPunto, &punto, sizeof(tPunto), cmpApariciones, NULL);
}

void clasificarPuntosRank(void* dataDicc, void* data)
{
    tPunto* punto = (tPunto*)dataDicc;
    int* rank = (int*)data;
    punto->valPosi = (*rank)++;
}

void generarDiccPodioPalabras(void* dataDicc, void* data)
{
    tPalabra* palabra = (tPalabra*)dataDicc;
    tDiccRank* dRank = (tDiccRank*)data;
    tPunto punto;
    tPunto* puntoFind;
    tPodio podio;

    //buscamos en que puesto ocupa la palabra
    //segun la cantidad
    punto.keyCant = palabra->valCant;
    puntoFind = obtener_dic(dRank->diccPunto, &punto, sizeof(tPunto), cmpApariciones);


    strcpy(podio.keyPal, palabra->keyPal);
    podio.valorRanking = puntoFind->valPosi;
    if(podio.valorRanking <= PODIO)
    {

        poner_dic(dRank->diccPodioPal, &podio, sizeof(tPodio), cmpPalabra, NULL);
    }
}

void generarPodio(tDiccionario* diccPodio, tDiccionario* diccPals, int cantPodio)
{
    /**
     * 1ero copia ordenada de diccionario palabras
     *    con sus cantidades
     *    cómo? produciendo colisiones
     * 2do iterar el nuevo diccionario e ir
     * guardando los datos en diccionario podio
     */
    tDiccionario diccPunto;
    tDiccRank diccRank;
    int rank;
    crear_dic(&diccPunto, 1, hashingRanking);
    
    recorrer_dic(diccPals, &diccPunto, copiarDatosEnDicc);
    rank = 1;
    recorrer_dic(&diccPunto, &rank, clasificarPuntosRank);

    printf("\ndicc puntos rank\n");
    recorrer_dic(&diccPunto, NULL, printDiccPunto);

    diccRank.rank = cantPodio;
    diccRank.diccPodioPal = diccPodio;
    diccRank.diccPunto = &diccPunto;
    recorrer_dic(diccPals, &diccRank, generarDiccPodioPalabras);
    vaciar_dic(&diccPunto);
}
void clasificarPodioFinal(void* dataPodio, void* diccPodioFinal)
{
    tPodio* p = (tPodio*)dataPodio;
    tDiccionario* dfp = (tDiccionario*)diccPodioFinal;
    tPodioFinal pf;
    tPodioFinal eliminar;
    pf.key = p->valorRanking;
    strcpy(pf.podio.keyPal, p->keyPal);
    pf.podio.valorRanking = p->valorRanking;

    int est = poner_dic(dfp, &pf, sizeof(tPodioFinal), cmpPodioFinal, NULL);
    if(est == DATA_DUPLICADO)
    {
        eliminar.key = pf.key + 1;
        if(eliminar.key > 5)
            eliminar.key--;
        sacar_dic(dfp, &eliminar, sizeof(tPodioFinal), cmpPodioFinal);
        pf.key++;
        if(pf.key > 5)
            pf.key--;
        poner_dic(dfp, &pf, sizeof(tPodioFinal), cmpPodioFinal, NULL);
    }
}

void generarInforme(tDiccionario* dicc, Accion printDiccionario)
{
    /**
     * usar la primitiva recorrer_dic
     * junto a la funcion printDiccionario
     */
    int total = 0;
    printDiccionario(NULL, NULL);
    recorrer_dic(dicc, &total, printDiccionario);
    printf("|%15s|%6d|\n", "Total", total);
}