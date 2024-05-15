//
// Created by Alessio Frau on 14/05/2024.
//
#include "libreria_funzioni.h"


void somma_BonusMalus(IlGiocatore** giocatori){
    IlGiocatore* giocatoriTemp=*giocatori;

// Aggiungi al punteggio i bonus/malus
    while (giocatoriTemp!=NULL){
        for (int i = 0; i < NUMERO_TIPOLOGIA_OSTACOLI; ++i) {
            giocatoriTemp->CFUaccumulati+=giocatoriTemp->personaggio.BONUS_MALUS[i];
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
}


void effetti_cartePunto(int* i,CarteCFU** mazzoCfu, IlGiocatore** giocatoreTurno,CarteCFU** carta_giocatoreTurno,IlGiocatore** giocatori, CarteCFU** carteTurno_Scarti, CarteCFU** mazzoScarti, int numeroGiocatori,bool* inversionePunti_SCAMBIAP,bool *raddoppia_DOPPIOE){

    printf("\n[%s] ha giocato una carta con valore [%d] ed effetto [%s].\n",(*giocatoreTurno)->nomeutente,(*carta_giocatoreTurno)->valore,
           Switch_Case_effettoCarta((*carta_giocatoreTurno)->nomeEffetti));
    switch ((*carta_giocatoreTurno)->nomeEffetti) {
        case ANNULLA:
            *i=0;
            printf("Se son presenti carte con effetto, queste non verranno considerate!.\n");
            // Fai in modo che il ciclo della funzione precedente si concluda
            while ((*carta_giocatoreTurno)->prossimaCartaCFU != NULL) {
                (*carta_giocatoreTurno) = (*carta_giocatoreTurno)->prossimaCartaCFU;
            }
            break;
        case SCAMBIAC:
            effetto_SCAMBIAC(numeroGiocatori,giocatori,giocatoreTurno);
            break;
        case NESSUNO:
            printf("Non accadra' niente\n");
            break;
        case SCARTAP:
            effetto_SCARTAP(giocatoreTurno,mazzoScarti);
            break;
        case RUBA:
            effetto_RUBA(giocatoreTurno,giocatori);
            break;
        case SCAMBIADS:
            effetto_SCAMBIADS(giocatori,giocatoreTurno,carteTurno_Scarti,numeroGiocatori);
            break;
        case SCARTAE:
            effetto_SCARTAE(giocatori,giocatoreTurno,carteTurno_Scarti,numeroGiocatori,mazzoScarti);
            break;
        case SCARTAC:
            effetto_SCARTAC(giocatoreTurno,mazzoScarti);
            break;
        case SCAMBIAP:
            if(*inversionePunti_SCAMBIAP==false){
                printf("A fine turno il punteggio MASSIMO e quello MINIMO verranno invertiti!\n");
                *inversionePunti_SCAMBIAP=true;
            }else{
                *inversionePunti_SCAMBIAP=false;
                printf("E' gia' stata giocata una carta con effetto SCAMBIAP, a fine turno\nil punteggio MASSIMO e quello MINIMO non verranno piu' invertiti!\n");
            }
            break;
        case DOPPIOE:
            printf("Le carte ISTANTANEE con effetto AUMENTA e DIMINUISCI varranno il doppio, quindi rispettivamente +4 e -4 al posto di +2 e -2.\n");
            *raddoppia_DOPPIOE=true;
            break;
        case SBIRCIA:
            effetto_SBIRCIA(mazzoCfu,giocatoreTurno,mazzoScarti);
            break;
        default:
            printf("\nErrore nell'individuazione dell'effetto della carta\n");
            break;
    }


}


void sommaPunteggi_cartePunto(IlGiocatore** giocatori, CarteCFU** carteCfuPunto_scartate, int numeroGiocatori){
    IlGiocatore* giocatoriTemp=*giocatori;
    CarteCFU* carteTurno_temp=*carteCfuPunto_scartate;
    for (int i = 0; i < numeroGiocatori; ++i) {
        giocatoriTemp->CFUaccumulati+=carteTurno_temp->valore;     // Somma punteggio della carta ai punti del giocatore

        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        carteTurno_temp=carteTurno_temp->prossimaCartaCFU;
    }

}


void fase_carteIstantanee(CarteCFU** mazzoCFU,IlGiocatore** giocatori,CarteCFU** mazzoScarti, int* numeroGiocatori,const int punteggi_primaDelTurno[], bool raddoppia_DOPPIOE, CarteOSTACOLO** ostacoloTurno, CarteOSTACOLO** mazzoOstacoli){
    int partecipanti_faseIstantanea=0;
    CarteCFU* scarti_carteIstantanee=NULL;
    IlGiocatore* giocatoriTemp=*giocatori;
    int scelta[*numeroGiocatori];


    for (int i = 0; i < *numeroGiocatori; ++i){
        int* carte_Punto0_Istantanee1=NULL;

        if(verifica_carteIstantanee_mazzoGiocatore(&giocatoriTemp->carteCfu)){

            printf("\n[%s] scegli se partecipare alla fase delle carte Istantanee?\n"
                   "[0]->NO\n[1]->SI\n",giocatoriTemp->nomeutente);
            do {
                printf("Scelta: ");
                scanf("%d",&scelta[i]);
                if(scelta[i]!=0 && scelta[i]!=1){
                    printf("Il numero della scelta non e' ne 0(NO) ne 1(SI).\nRipeti!\n");
                }
            } while (scelta[i]!=0 && scelta[i]!=1);


            // Solo con scelta 1 verranno stampate le carte del mazzo
            if(scelta[i]==1){
                partecipanti_faseIstantanea++;

                // Riutilizzo l array soltanto nel caso in cui il giocatore scelga di giocare e sostituisco il 1 della scelta precedente con un numero corrispondende ad una carta istantanea della sua mano
                scelta[i] = selezioneCarta_daScartare(&giocatoriTemp, CARTA_ISTANTANEA);



                // Variabili per carta scartata
                char nome[DIM_CARATTERI];
                int valore;
                NomeEffetti nomeEffetti;

                eliminaCartaDalMazzo(&giocatoriTemp->carteCfu,nome,&valore,&nomeEffetti,scelta[i]);
                inserisciCfu_inCoda_nelMazzo(&scarti_carteIstantanee,nome,valore,nomeEffetti);
            }else{
                printf("[%s] non ha voluto giocare carte istantanee.\n",giocatoriTemp->nomeutente);
            }


        }else{
            printf("\n[%s] non hai carte istantanee o istantanee valide nella tua mano,\nnon potrai partecipare alla fase delle carte Istantanee.\n",giocatoriTemp->nomeutente);
            // Imposto la scelta a 0 in automatico, siccome appunto il giocatore non ha carte istantanee nella sua mano
            scelta[i]=0;
        }

        free(carte_Punto0_Istantanee1);               // Libera memoria
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;     // Scorri la lista giocatori
    }



    // Inserisci vincitori_o_perdenti

    vincitori_o_perdenti(mazzoCFU,giocatori,scelta,&scarti_carteIstantanee,numeroGiocatori,raddoppia_DOPPIOE,punteggi_primaDelTurno,partecipanti_faseIstantanea,ostacoloTurno,mazzoOstacoli,mazzoScarti);



    // Svuoto le carte istantanee giocate nella fase finale del gioco nel mazzo degli scarti
    riempi_daMazzo_aMazzo(mazzoScarti,&scarti_carteIstantanee);
}
