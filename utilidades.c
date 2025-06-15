/**
 * 
 * 
 */
#include "utilidades.h"

void mensajeEstado(int estado, const char *inputNombreArchivo)
{
    if(estado == EXITO)
    {
        printf("\nArchivo procesado correctamente.\n");
        printf("Listo para mostrar los datos.\n\n");
    }
    if(estado == ERROR_APERTURA_ARCHIVO)
    {
        puts("\nERROR -- ARCHIVO NO ENCONTRADO");
        printf("\tArchivo: %s\n", inputNombreArchivo);
        
        puts("Verificar nombre de archivo y/o directorio del mismo.\n");
    }
}

void inArchivo(char *inputNombreArchivo)
{
    int priVez = 1;
    char* ptrStr;
    do
    {
        if (!priVez)
        {
            puts("(X)-ERROR -- TIPO ARCHIVO NO VALIDO");
            puts("REINGRESE NOMBRE( termina en.txt):");
        }
        puts("\nIngrese el nombre del archivo:");
        printf("-> ");
        fgets(inputNombreArchivo, TAM_NOM_ARCH, stdin);
        printf("\npresione enter para continuar ->");
        clean_stdin();
        priVez = 0;
    }while(strstr(inputNombreArchivo, ".txt") == NULL);
    ptrStr = strchr(inputNombreArchivo, '\n');
    *ptrStr = '\0';
}

int menu(const char *opcValidas, char *inputNombreArchivo)
{
    // desplegar menu con lista de opciones
    // guardar la opcion elegida
    // recibir la entrada de nombre del archivo
    // devuelve la opc elegida
    char opc;
    int priVez = 1;
    do
    {
        if(!priVez)
        {
            printf("\n%s", "ERROR - Opcion Incorrecta\n\n");
            //printf("\e[1;1H\e[2J");
        }
        
        //puts("Ingresar opcion(I-P-D-S):");
        printf(MENU_MSJ);
        printf("-> ");
        
        scanf("%c", &opc);
        clean_stdin();
        opc = A_MAYUSCULA(opc);
        priVez = 0;
    } while (strchr(opcValidas, opc) == NULL);

    return opc;
}

void printDiccSignos(void *dataDicc, void *data)
{
    tSigno *signo = (tSigno *)dataDicc;
    tGrupoRank* gr = (tGrupoRank*)data;
    if (dataDicc == NULL)
    {
        printf("+-------------------------+------+\n");
        printf("|%-*s|%-6s|\n", TAM_PALABRA, "clave", "valor");
        printf("+-------------------------+------+\n");
        return;
    }

    printf("|%-*s|%6d|\n", TAM_PALABRA, signo->keyNom, signo->valCant);
    //printf("+---------------+------+\n");
    gr->item++;
}

void printDiccPalabras(void *dataDicc, void *data)
{
    tPalabra *palabra = (tPalabra *)dataDicc;
    tGrupoRank* gr = (tGrupoRank*)data;
    if (dataDicc == NULL)
    {
        printf("+-------------------------+------+\n");
        printf("|%-*s|%-6s|\n", TAM_PALABRA, "clave", "valor");
        printf("+-------------------------+------+\n");
        return;
    }

    printf("|%-*s|%6d|\n", TAM_PALABRA, palabra->keyPal, palabra->valCant);
    //printf("+---------------+------+\n");
    //*total = *total + palabra->valCant;
    gr->item++;
}

void printDiccPodio(void* rank, void* clasificar)
{
    tRank* rActual = (tRank*)rank;
    tRank* rAnterior;
    tGrupoRank* gr = (tGrupoRank*)clasificar;

    if (rActual == NULL)
    {
        printf("+-------------------------+------+\n");
        printf("|%-*s|%-6s|\n", TAM_PALABRA, "clave", "valor");
        printf("+-------------------------+------+\n");
        return;
    }

    rAnterior = gr->dataPrev;
    if(gr->item > 0 && rActual->valPal.valCant != rAnterior->valPal.valCant)
        gr->pos = gr->item + 1;
    
    //printf("|%-15s|%6d|\n", r->valPal.keyPal, r->valPal.valCant);
    if(gr->item < gr->limite)
        printf("|%-*s|%6d|\n", TAM_PALABRA, rActual->valPal.keyPal, gr->pos);
    //printf("+---------------+------+\n");
    gr->item++;
    gr->dataPrev = rActual; //paso la data al siguiente;
}

void printDiccPunto(void *dataDicc, void *data)
{
    tPunto *punto = (tPunto *)dataDicc;
    if (dataDicc == NULL)
    {
        printf("+------+---------------+\n");
        printf("|%-6s|%-*s|\n", "clave", TAM_PALABRA, "valor");
        printf("+------+---------------+\n");
        return;
    }

    printf("|%-6d|%-6d|\n", punto->keyCant, punto->valPosi);
    //printf("+------+---------------+\n\n");
}

int cmpPalabra(const void *pal1, const void *pal2)
{
    const tPalabra *p1 = (tPalabra *)pal1;
    const tPalabra *p2 = (tPalabra *)pal2;

    return strcmp(p1->keyPal, p2->keyPal);
}

int cmpSigno(const void *sig1, const void *sig2)
{
    const tSigno *s1 = (tSigno *)sig1;
    const tSigno *s2 = (tSigno *)sig2;

    return strcmp(s1->keyNom, s2->keyNom);
}

int cmpPunto(const void* punto1, const void* punto2)
{
    const tPunto *p1 = (tPunto *)punto1;
    const tPunto *p2 = (tPunto *)punto2;

    return p1->keyCant - p2->keyCant;    
}
int cmpRank(const void* rank1, const void* rank2)
{
    const tRank *r1 = (tRank*)rank1;
    const tRank *r2 = (tRank*)rank2;

    return r1->key - r2->key;
}

int cmpApariciones(const void *punto1, const void *punto2)
{
    const tPunto *p1 = (tPunto *)punto1;
    const tPunto *p2 = (tPunto *)punto2;

    return p1->keyCant - p2->keyCant;
}

void actPalabraRepetido(void *pal1, const void *pal2)
{
    tPalabra *p1 = (tPalabra *)pal1;
    const tPalabra *p2 = (tPalabra *)pal2;

    p1->valCant += p2->valCant;
}

void actSignoRepetido(void *sig1, const void *sig2)
{
    tSigno *s1 = (tSigno *)sig1;
    const tSigno *s2 = (tSigno *)sig2;

    s1->valCant += s2->valCant;
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
