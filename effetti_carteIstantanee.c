//
// Created by Alessio Frau on 12/05/2024.
//
#include "libreria_funzioni.h"

void effetti_carteIstantanee(IlGiocatore** giocatori, bool raddoppia_DOPPIOE, CarteCFU** cartaIstantanea_giocatore, IlGiocatore** giocatore_delTurno, const int punteggi_primaDelTurno[], int numeroGiocatori){
    printf("\n[%s] ha giocata una carta istantanea con effetto [%s]",(*giocatore_delTurno)->nomeutente,Switch_Case_effettoCarta((*cartaIstantanea_giocatore)->nomeEffetti));
    switch ((*cartaIstantanea_giocatore)->nomeEffetti) {
        case AUMENTA:
            effetto_AUMENTA(raddoppia_DOPPIOE,*giocatori,*giocatore_delTurno);
            break;
        case DIMINUISCI:
            effetto_DIMINUISCI(raddoppia_DOPPIOE,*giocatori,*giocatore_delTurno);
            break;
        case INVERTI:
            // E' essenzialmente la stessa cosa dello SCAMBIAP
            effetto_SCAMBIAP(giocatori,numeroGiocatori,punteggi_primaDelTurno);
            break;
        default:
            printf("\nErrore in effetti_carteIstantanee, non e' arrivata nessuna carta istantanea");
    }




}



void effetto_AUMENTA(bool raddoppia_DOPPIOE,IlGiocatore* giocatori, IlGiocatore* giocatore_delTurno){
    int aumento;
    int conta=0;
    int scelta;
    IlGiocatore* giocatoriTemp=giocatori;

    if(raddoppia_DOPPIOE==true){
        aumento=4;
    }else{
        aumento=2;
    }
    printf("\n[%s] scegli un giocatore al quale vuoi aumentare di %d il punteggio:\n",giocatore_delTurno->nomeutente,aumento);

    while (giocatoriTemp!=NULL){
        // Stampa i giocatori tranne il giocatore che ha giocato la carta in questione
        if(giocatoriTemp!=giocatore_delTurno){
            printf("[%d]-> %s\n",++conta,giocatoriTemp->nomeutente);
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    giocatoriTemp=giocatori;

    // Scela da 1 a conta
    do {
        printf("Numero scelta: ");
        scanf("%d",&scelta);
        if (scelta<1 || scelta>conta){
            printf("La tua scelta non e' valida.\nRipeti!\n");
        }
} while (scelta<1 || scelta>conta);

    for (int i = 1; i <= scelta; ++i) {
        if (i!=scelta){
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }else{
            // Sommo l aumento al giocatore selezionato
            giocatoriTemp->CFUaccumulati+=aumento;
        }
    }
}


void effetto_DIMINUISCI(bool raddoppia_DOPPIOE,IlGiocatore* giocatori, IlGiocatore* giocatore_delTurno){
    int aumento;
    int conta=0;
    int scelta;
    IlGiocatore* giocatoriTemp=giocatori;

    if(raddoppia_DOPPIOE==true){
        aumento=4;
    }else{
        aumento=2;
    }
    printf("\n[%s] scegli un giocatore al quale vuoi diminuire di %d il punteggio:\n",giocatore_delTurno->nomeutente,aumento);

    while (giocatoriTemp!=NULL){
        // Stampa i giocatori tranne il giocatore che ha giocato la carta in questione
        if(giocatoriTemp!=giocatore_delTurno){
            printf("[%d]-> %s\n",++conta,giocatoriTemp->nomeutente);
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    giocatoriTemp=giocatori;

    // Scela da 1 a conta
    do {
        printf("Numero scelta: ");
        scanf("%d",&scelta);
        if (scelta<1 || scelta>conta){
            printf("La tua scelta non e' valida.\nRipeti!\n");
        }
    } while (scelta<1 || scelta>conta);

    for (int i = 1; i <= scelta; ++i) {
        if (i!=scelta){
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }else{
            // Sommo l aumento al giocatore selezionato
            giocatoriTemp->CFUaccumulati-=aumento;
        }
    }
}

