//
// Created by Alessio Frau on 14/05/2024.
//
#include "libreria_funzioni.h"

void verificaMano_delGiocatore(CarteCFU** mazzoScarti,CarteCFU** mazzoCfu, CarteCFU** mazzoGiocatoreTurno){
    CarteCFU* temp=*mazzoGiocatoreTurno;
    int contaCarte_Istantanee=0;
    int contaCarte=0;

    // Conta carte Cfu e carte istantanee(tutte le carte Cfu con valore=0 tranne quelle di nome "Monitor")
    while (temp!=NULL){
        if(temp->valore==0 && strcmp(temp->nome,"Monitor")!=0){
            contaCarte_Istantanee++;
        }
        contaCarte++;
        temp=temp->prossimaCartaCFU;
    }

    // Se il numero delle carte nella mano del giocatore e' uguale al numero delle carte istantanee
    if(contaCarte==contaCarte_Istantanee){
        // Elimina mano
        riempi_daMazzo_aMazzo(mazzoScarti,mazzoGiocatoreTurno);
        do {
            // Se mazzo CFU vuoto
            if(*mazzoCfu==NULL){
                riempi_daMazzo_aMazzo(mazzoCfu,mazzoScarti);
                mescolaCarteCFU(mazzoCfu);
            }
            // Pesca dal mazzo delle carte Cfu
            pescaggioCartaCfu(mazzoCfu,mazzoGiocatoreTurno);
            // Fino a quando non avra' almeno una carta NON ISTANTANEA
        }while((*mazzoGiocatoreTurno)->valore==0 && strcmp((*mazzoGiocatoreTurno)->nome,"Monitor")!=0);
    }
}

int selezioneCarta_daScartare(IlGiocatore** giocatoreTurno,int Punto_o_Istantanea){
    CarteCFU *carteGiocatore = (*giocatoreTurno)->carteCfu;
    int nCartaSelezionata = 0;
    int nCarte = 0;

    int* carte_Punto0_Istantanee1=NULL;


    // Stampa carte nella mano del giocatore
    if(Punto_o_Istantanea==CARTA_PUNTO){
        printf("%s gioca una CARTA PUNTO tra le seguenti:\n", (*giocatoreTurno)->nomeutente);
    }else if(Punto_o_Istantanea==CARTA_ISTANTANEA){
        printf("%s gioca una CARTA ISTANTANEA tra le seguenti:\n", (*giocatoreTurno)->nomeutente);
    }else if(Punto_o_Istantanea==CARTA_ISTANTANEA_FINETURNO){
        printf("%s gioca una CARTA ISTANTANEA PER FINE TUNRO tra le seguenti:\n",(*giocatoreTurno)->nomeutente);
    }



    carte_Punto0_Istantanee1= stampaCarte_perScelta((*giocatoreTurno)->carteCfu,&nCarte);


    // Seleziona numero della posizione della carta da giocare

    printf("\nNumero carta: ");
    do {
        scanf("%d", &nCartaSelezionata);
        // Se la scelta e' per le carte istantanee(Punto_o_Istantanea==1) && la selezione in questione equivale a 2(ovvero carte istantanee con effetto DIROTTA o SALVA)
        if(Punto_o_Istantanea==1 && carte_Punto0_Istantanee1[nCartaSelezionata-1]==2){
            printf("E' probabile che tu abbia scelto una carta istantanea che si\npuo giocare soltanto a fine turno. Ripeti!\n");
        }

        // Se la scelta e' in un range differente da quello della lista precedentemente stampata o la selezione e' diversa da Punto_o_Istantanea
        if (nCartaSelezionata < 1 || nCartaSelezionata > nCarte || carte_Punto0_Istantanee1[nCartaSelezionata-1]  != Punto_o_Istantanea) {
            nCartaSelezionata = 0;
        }

        if (nCartaSelezionata < 1 || nCartaSelezionata > nCarte) {
            printf("La scelta non e' valida.\nRipeti!\n");
        }
    } while (nCartaSelezionata < 1 || nCartaSelezionata > nCarte);

    free(carte_Punto0_Istantanee1);      // Libera puntatore

    return nCartaSelezionata;
}

// Dopo aver stampato le carte del mazzo differenziandole tra carte PUNTO e ISTANTANEE, restituisce un puntatore con n elementi(numero delle carte
//  del mazzo mandato come parametro), dove ogni elemento varra o 0(carta punto) oppure 1(carta istantanea)
int* stampaCarte_perScelta(CarteCFU* mazzoGiocatore,int* numero_carteGiocatore){
    CarteCFU* carteGiocatore=mazzoGiocatore;
    int* carte_Punto0_Istantanee1=NULL;

    // Conta carte del mazzo
    while (carteGiocatore!=NULL){
        carteGiocatore=carteGiocatore->prossimaCartaCFU;
        (*numero_carteGiocatore)++;
    }
    carteGiocatore=mazzoGiocatore;   // Reset puntatore mazzo giocatore

    // Allocazione dinamica di un puntatore che salvera in base alla posizione della carta un valore(0 oppure 1, che indicheranno rispettivamente carta PUNTO o ISTANTANEA)
    carte_Punto0_Istantanee1=(int*) malloc((*numero_carteGiocatore) * sizeof(int));
    if(carte_Punto0_Istantanee1==NULL){
        printf("\nErrore allocazione dinamica");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (*numero_carteGiocatore); ++i){

        if((carteGiocatore->valore == 0 && strcmp(carteGiocatore->nome, "Monitor") != 0) && (carteGiocatore->nomeEffetti!=SALVA && carteGiocatore->nomeEffetti!=DIROTTA)){
            carte_Punto0_Istantanee1[i]=1;
        }else if(carteGiocatore->valore!=0 || (strcmp(carteGiocatore->nome, "Monitor") == 0) && carteGiocatore->valore==0){
            carte_Punto0_Istantanee1[i]=0;
        }else{
            carte_Punto0_Istantanee1[i]=2;
        }

        carteGiocatore=carteGiocatore->prossimaCartaCFU;
    }
    carteGiocatore=mazzoGiocatore; // Reset puntatore mazzo giocatore

    for (int i = 0; i < (*numero_carteGiocatore); ++i){
        printf(" [%d]-> Nome: %s | Nome effetto: %s | Valore: %d", i+1, carteGiocatore->nome, // Somma ++nCarte ad ogni stampa
               Switch_Case_effettoCarta(carteGiocatore->nomeEffetti), carteGiocatore->valore);

        if (carte_Punto0_Istantanee1[i]==1) {
            printf(" (CARTA ISTANTANEA)\n");
        } else if(carte_Punto0_Istantanee1[i]==0){
            printf(" (CARTA PUNTO)\n");
        }else{
            printf("(CARTA ISTANTANEA PER FINE TURNO)\n");
        }
        carteGiocatore = carteGiocatore->prossimaCartaCFU;
    }

    return carte_Punto0_Istantanee1;
}

