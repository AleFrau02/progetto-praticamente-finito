//
// Created by Alessio Frau on 14/05/2024.
//
#include "libreria_funzioni.h"

int carteMancanti(CarteCFU** mazzoGiocatore){
    CarteCFU* mazzo=*mazzoGiocatore;
    int conta=0;

    while (mazzo!=NULL){
        conta++;
        mazzo=mazzo->prossimaCartaCFU;
    }

    return NUMERO_CARTE_INIZIALI-conta;
}

int stampaSceltaAzione(char nome[]){
    int scelta;
    printf("\n%s scegli cio che vuoi fare\n"
           "[0]Esci dalla partita\n"
           "[1]Gioca una carta CFU dalla tua mano\n"
           "[2]Controlla lo stato degli altri giocatori\n",nome);
    do {
        scanf("%d",&scelta);
        if(scelta!=0 && scelta!=1 && scelta!=2)printf("Il numero della tua scelta non corrisponde a un numero valido.\nRipeti!\n");
    } while (scelta!=0 && scelta!=1 && scelta!=2);

    return scelta;
}

void scelta1(IlGiocatore **giocatoreTurno, CarteCFU **carteTurno_Scarti, CarteCFU **mazzoScarti, CarteCFU **mazzoCFU) {

    // Verifica mazzo giocatore
    verificaMano_delGiocatore(mazzoScarti, mazzoCFU,&(*giocatoreTurno)->carteCfu);

    stampaGiocatore(*giocatoreTurno);

    // Selezione carta della mano del giocatore
    int nCartaSelezionata= selezioneCarta_daScartare(giocatoreTurno,CARTA_PUNTO);



    // Sposta puntatore nel mazzo del giocatore fino a che il puntatore non raggiunge la carta che il giocatore vuol giocare
    CarteCFU* carteGiocatore=(*giocatoreTurno)->carteCfu;
    CarteCFU *prevCarta = NULL;
    for (int i = 1; i < nCartaSelezionata; ++i) {
        prevCarta = carteGiocatore;
        carteGiocatore = carteGiocatore->prossimaCartaCFU;
    }

    // Prendi informazioni carta giocata
    char nome[DIM_CARATTERI];
    strcpy(nome, carteGiocatore->nome);
    int valore = carteGiocatore->valore;
    NomeEffetti nomeEffetti = carteGiocatore->nomeEffetti;

    // Elimina carta giocata
    if (prevCarta != NULL) {
        // Non è la prima carta
        prevCarta->prossimaCartaCFU = carteGiocatore->prossimaCartaCFU;
    } else {
        // La carta è la prima della lista
        (*giocatoreTurno)->carteCfu = carteGiocatore->prossimaCartaCFU;
    }
    printf("La carta [%s] e' stata giocata.\n\n", carteGiocatore->nome);
    free(carteGiocatore);  // Libera la memoria della carta giocata

    // Inserisci dati della carta nel mazzo degli scarti del turno
    inserisciCfu_inCoda_nelMazzo(carteTurno_Scarti, nome, valore, nomeEffetti);
}

void scelta2(IlGiocatore **giocatoreTurno, IlGiocatore **giocatori) {
    IlGiocatore *temp = *giocatori;
    printf("\n%s, ecco per te le carte degli altri giocatori: ", (*giocatoreTurno)->nomeutente);

    while (temp != NULL) {
        // Non stampa le carte del giocatore del turno
        if (temp == *giocatoreTurno) {
            temp = temp->GIOCATOREsuccessivo;
        } else {
            // Puntatori mazzi giocatori
            CarteCFU *tempCfu = temp->carteCfu;
            CarteOSTACOLO *tempOstacoli = temp->carteOstacolo;

            printf("\nLe carte di %s.\n", temp->nomeutente);
            // Stampa carte CFU
            printf("CFU:\n");
            while (tempCfu != NULL) {
                printf("Nome: %s | Effetto: %s | Valore: %d\n", tempCfu->nome,
                       Switch_Case_effettoCarta(tempCfu->nomeEffetti), tempCfu->valore);
                tempCfu = tempCfu->prossimaCartaCFU;
            }
            // Stampa carte Ostacoli
            printf("OSTACOLI:\n");
            if (tempOstacoli == NULL) {
                printf("Il giocatore non ha ostacoli\n");
            } else {
                while (tempOstacoli != NULL) {
                    printf("Nome: %s\n Descrizione: %s\n Tipo ostacolo: %s\n\n", tempOstacoli->nome,
                           tempOstacoli->descrizioneOSTACOLO, Switch_Case_tipoOstacoli(tempOstacoli->tipoOstacoli));
                    tempOstacoli = tempOstacoli->prossimaCartaOSTACOLO;
                }
            }
            temp = temp->GIOCATOREsuccessivo;
        }

    }

}
