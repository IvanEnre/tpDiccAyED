/**
 * 
 * 
 */
#include "funciones.h"

int solucion()
{
    int opcion;
    int estado;
    char nombreArchivo[TAM_NOM_ARCH];
    tDiccionario diccPalabras; //{palabra: cantidad}, ...
    tDiccionario diccSignos;   //{puntuacion: cantidad}, {espacio: cantidad}
    tDiccionario diccPodio;    //{palabra: ranking}...

    crear_dic(&diccPalabras, 10, hashingPalabra);
    crear_dic(&diccSignos, 2, hashingSigno);
    crear_dic(&diccPodio, PODIO, hashingRank);

    estado = SIN_PROCESAR_ARCHIVO;
    do
    {
        opcion = menu(OPC_VALIDAS, nombreArchivo);

        switch (opcion)
        {
        case INPUT_NOM_ARCHIVO:
            inArchivo(nombreArchivo);
            printf("\n##Archivo a procesar: %s\n\n", nombreArchivo);;
            break;
        case PROC_ARCHIVO:
            estado = procesarArchivo(nombreArchivo, &diccPalabras, &diccSignos);
            if(estado == EXITO)
            {
                vaciar_dic(&diccPodio, 0);
                generarPodio(&diccPalabras, &diccPodio, PODIO);
            }
            mensajeEstado(estado, nombreArchivo);
            break;
        case INF_DATOS:
            printf("\n---------DATOS A INFORMAR---------\n\n");
            //printf("\'%s\'\n", nombreArchivo);
            if (estado != EXITO)
            {
                printf("...\n\n");
                break;
            }
            printf("--Diccionario palabras.\n");
            generarInforme(&diccPalabras, printDiccPalabras);
            printf("\n--Diccionario de signos.\n");
            generarInforme(&diccSignos, printDiccSignos);
            printf("\n--Diccionario de podios.\n");
            generarInforme(&diccPodio, printDiccPodio);
            printf("-->\'%s\'\n", nombreArchivo);
            printf("\n\n");
            break;
        case SALIR:
            break;
        }

    } while (opcion != SALIR);

    vaciar_dic(&diccPalabras, COMPLETO_DICC);
    vaciar_dic(&diccSignos, COMPLETO_DICC);
    vaciar_dic(&diccPodio, COMPLETO_DICC);
    return 0;
}

size_t hashingString(const char *s)
{
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;
    while (*s)
    {
        hash_value = (hash_value + (*s - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
        s++;
    }
    return hash_value;
}

size_t hashingPunto(const void *punto, size_t capDicc)
{
    tPunto *p = (tPunto *)punto;
    return p->keyCant - 1;
}

size_t hashingRank(const void *rank, size_t capDicc)
{
    tRank *r = (tRank *)rank;
    return r->key - 1;
}

size_t hashingPalabra(const void *data, size_t capDicc)
{
    const tPalabra *palabra = (tPalabra *)data;
    return hashingString(palabra->keyPal);
}

size_t hashingSigno(const void *data, size_t capDicc)
{
    const tSigno *signo = (tSigno *)data;
    return hashingString(signo->keyNom);
}

void cargarSignos(tDiccionario *diccSignos, char **ptrStr)
{
    tSigno sEspacio = {"espacio", 1};
    tSigno sPuntuacion = {"sig-punt", 1};

    while (**ptrStr && !ES_LETRA(**ptrStr))
    {
        if (**ptrStr == ' ')
            poner_dic(diccSignos, &sEspacio, sizeof(tSigno), cmpSigno, actSignoRepetido);
        else
            poner_dic(diccSignos, &sPuntuacion, sizeof(tSigno), cmpSigno, actSignoRepetido);

        (*ptrStr)++;
    }
}

char *palabraLinea(char **lineaFrase, int *cantCaract)
{
    char *initPal;

    initPal = *lineaFrase;
    *cantCaract = 0;
    while (**lineaFrase && ES_LETRA(**lineaFrase))
    {
        **lineaFrase = A_MINUSCULA(**lineaFrase);
        (*cantCaract)++;
        (*lineaFrase)++;
    }

    return initPal;
}

void procesarLineaStr(char *ptrLinea, tDiccionario *diccPals, tDiccionario *diccSignos)
{
    char *ptrPalabraStr;
    int cantCaract;
    tPalabra palabra;

    while (*ptrLinea)
    {
        ptrPalabraStr = palabraLinea(&ptrLinea, &cantCaract);
        if (cantCaract)
        {
            strncpy(palabra.keyPal, ptrPalabraStr, cantCaract);
            palabra.keyPal[cantCaract] = '\0';
            palabra.valCant = 1;
            poner_dic(diccPals, &palabra, sizeof(tPalabra), cmpPalabra, actPalabraRepetido);
        }
        // esta funcion toma los digitos cómo
        // parte de un signo de puntuacion
        cargarSignos(diccSignos, &ptrLinea);

        // ptrLinea++;
    }
}

int procesarArchivo(const char *nombArchTxt, tDiccionario *diccPals, tDiccionario *diccSignos)
{
    /**
     * realizar la lectura del archivo txt
     * cargar los datos en los diccionarios
     */

    char lineaBuffer[MAX_BUFF];
    char *ptrSaltoLinea;
    FILE *pfTxt;
    
    pfTxt = fopen(nombArchTxt, "rt");
    if (pfTxt == NULL)
        return ERROR_APERTURA_ARCHIVO;

    vaciar_dic(diccPals, 0);
    vaciar_dic(diccSignos, 0);
    
    while (fgets(lineaBuffer, MAX_BUFF, pfTxt))
    {
        ptrSaltoLinea = strchr(lineaBuffer, '\n');
        *ptrSaltoLinea = '\0';
        procesarLineaStr(lineaBuffer, diccPals, diccSignos);
    }

    fclose(pfTxt);

    return EXITO;
}

void generarInforme(tDiccionario *dicc, Accion printDiccionario)
{
    /**
     * usar la primitiva recorrer_dic
     * junto a la funcion printDiccionario
     */
    tGrupoRank clasificar;

    clasificar.item = 0;
    clasificar.pos = 1;
    clasificar.dataPrev = NULL;
    clasificar.limite = PODIO;
    printDiccionario(NULL, NULL);
    recorrer_dic(dicc, &clasificar, printDiccionario);


    printf("+-------------------------+------+\n");
    printf("|%*s|%6d|\n", TAM_PALABRA, "Total", clasificar.item);
    printf("+-------------------------+------+\n");
}

void generarPodio(tDiccionario *diccPals, tDiccionario *diccPodioPals, int podio)
{
    int i;
    tPunto punto;
    tGrupoDicc grupDicc;
    tDiccionario diccPuntos;    //{cantApar: 0}
    tDiccionario diccPuntoMaxs; //{cantApar: pos}, pos = 1, 2, ..., N

    crear_dic(&diccPuntos, podio, hashingPunto);
    crear_dic(&diccPuntoMaxs, podio, hashingPunto);

    recorrer_dic(diccPals, &diccPuntos, copiarApariEnDiccPuntos);

    for (i = 0; i < podio; i++)
    {
        punto.keyCant = 0;
        recorrer_dic(&diccPuntos, &punto, obtenerPuntoMax);
        sacar_dic(&diccPuntos, &punto, sizeof(tPunto), cmpPunto);

        punto.valPosi = i + 1;
        poner_dic(&diccPuntoMaxs, &punto, sizeof(tPunto), cmpPunto, NULL);
    }
    i = 0;

    // printf("\ndicc con los puntos segun clasificacion\n");
    // recorrer_dic(&diccPuntoMaxs, &i, printDiccPunto);
    vaciar_dic(&diccPuntos, COMPLETO_DICC);

    grupDicc.diccPuntosMax = &diccPuntoMaxs;
    grupDicc.diccPodioPals = diccPodioPals;
    grupDicc.podio = podio;

    recorrer_dic(diccPals, &grupDicc, guardarPalsRankEnDiccPodio);
    vaciar_dic(&diccPuntoMaxs, COMPLETO_DICC);
}

void copiarApariEnDiccPuntos(void *palabra, void *diccPunto)
{
    tPalabra *pal = (tPalabra *)palabra;
    tPunto punto;

    punto.keyCant = pal->valCant;
    punto.valPosi = 0;

    poner_dic(diccPunto, &punto, sizeof(tPunto), cmpPunto, NULL);
}

void obtenerPuntoMax(void *punto, void *puntoMax)
{
    tPunto *p = (tPunto *)punto;
    tPunto *pmax = (tPunto *)puntoMax;

    if (p->keyCant > pmax->keyCant)
        pmax->keyCant = p->keyCant;
}

void guardarPalsRankEnDiccPodio(void *palabra, void *grupDicc)
{
    tPalabra *pal = (tPalabra *)palabra;
    tGrupoDicc *coleccDicc = (tGrupoDicc *)grupDicc;
    tPunto punto;
    tPunto *puntoEncontrado;
    tRank rank;

    // buscamos en que posicion(clasificacion)
    // de la palabra
    punto.keyCant = pal->valCant;
    puntoEncontrado = obtener_dic(coleccDicc->diccPuntosMax, &punto, sizeof(tPunto), cmpPunto);

    if (!puntoEncontrado)
        return;
    // contruir el ranking con la palabra
    rank.key = puntoEncontrado->valPosi;
    strcpy(rank.valPal.keyPal, pal->keyPal);
    rank.valPal.valCant = puntoEncontrado->valPosi % coleccDicc->podio;
    if (rank.valPal.valCant == 0)
        rank.valPal.valCant = coleccDicc->podio;

    puntoEncontrado->valPosi += coleccDicc->podio;

    poner_dic(coleccDicc->diccPodioPals, &rank, sizeof(tRank), cmpRank, NULL);
}
