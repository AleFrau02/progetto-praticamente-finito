#ifndef UNTITLED60_INTESTAZIONE_H
#define UNTITLED60_INTESTAZIONE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>


#define DIM_CARATTERI 32
#define CARATTERIperDESCRIZIONE 128
#define NUMERO_CARTE_OSTACOLO 28
#define NUMERO_TIPOLOGIA_OSTACOLI 4
#define NUMERO_PERSONAGGI 4
#define NUMERO_CARTE_INIZIALI 5
#define SPAZI 23
#define CARTA_ISTANTANEA_FINETURNO 2
#define CARTA_ISTANTANEA 1
#define CARTA_PUNTO 0
#define PUNTEGGIO_VINCITA 60
#define SENZA_CARTE 0
#define CON_CARTE_O_NONPERDENTI 1
#define VINCENTI 1
#define PERDENTI 0
#define NE_VINCENTI_NE_PERDENTI 2


typedef enum {
    NESSUNO,
    SCARTAP,
    RUBA,
    SCAMBIADS,
    SCARTAE,
    SCARTAC,
    SCAMBIAP,
    DOPPIOE,
    SBIRCIA,
    SCAMBIAC,
    ANNULLA,
    AUMENTA,
    DIMINUISCI,
    INVERTI,
    SALVA,
    DIROTTA
} NomeEffetti; //nomi degli effetti


typedef enum {
    STUDIO, SOPRAVVIVENZA, SOCIALE, ESAME
} TipoOstacoli;


typedef struct CarteCFU {
    char nome[DIM_CARATTERI];
    int valore;
    NomeEffetti nomeEffetti;
    struct CarteCFU *prossimaCartaCFU;
} CarteCFU;


typedef struct CarteOSTACOLO {
    char nome[DIM_CARATTERI];
    char descrizioneOSTACOLO[CARATTERIperDESCRIZIONE];
    TipoOstacoli tipoOstacoli;
    struct CarteOSTACOLO *prossimaCartaOSTACOLO;
} CarteOSTACOLO;


typedef struct {
    char nome[DIM_CARATTERI];
    int BONUS_MALUS[NUMERO_TIPOLOGIA_OSTACOLI];
} Personaggio;


typedef struct IlGiocatore {
    char nomeutente[DIM_CARATTERI];
    Personaggio personaggio;
    int CFUaccumulati;
    CarteCFU *carteCfu;
    CarteOSTACOLO *carteOstacolo;
    struct IlGiocatore *GIOCATOREsuccessivo;
} IlGiocatore;




#endif //UNTITLED60_INTESTAZIONE_H
