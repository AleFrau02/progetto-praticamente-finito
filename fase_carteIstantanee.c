//
// Created by Alessio Frau on 14/05/2024.
//
#include "libreria_funzioni.h"

void vincitori_o_perdenti(CarteCFU** mazzoCFU,IlGiocatore** giocatori, const int scelte[],CarteCFU** scarti_carteIstantanee,int* numeroGiocatori,bool raddoppia_DOPPIOE,
                          const int puntaggi_primaDelTurno[],int partecipanti_faseIstantanea, CarteOSTACOLO** ostacolo_Turno, CarteOSTACOLO** mazzoOstacoli,CarteCFU** mazzoScarti){
    IlGiocatore* giocatoriTemp=*giocatori;
    CarteCFU* carteistantanee=*scarti_carteIstantanee;



    printf("\n\nCONTEGGIO DEI PUNTI E EVENTUALI ROUND FINALI\n\n");

    // Solo se i giocatori sono piu di 1



    if (partecipanti_faseIstantanea>0) {


        for (int i = 0; i < (*numeroGiocatori); ++i) {
            // Se scelta[i]=0 vuol dire che prima il giocatore in questione non aveva carte istantanee oppure ha scelto di non giocare
            if (scelte[i] != 0) {


                effetti_carteIstantanee(giocatori,raddoppia_DOPPIOE,&carteistantanee,&giocatoriTemp,puntaggi_primaDelTurno,*numeroGiocatori);


                // Mando avanti il mazzo delle carte istantanee che sono state scartate soltanto quando giunge il giocatore che l ha giocata
                carteistantanee = carteistantanee->prossimaCartaCFU;
            }
            printf("\n\n");
            giocatoriTemp = giocatoriTemp->GIOCATOREsuccessivo;
        }


    }else{
        printf("\nNessuno ha voluto o potuto partecipare alla fase 'istantanea' del turno.\nSi va dritti al conteggio dei punti");
    }






    // Calcolo punteggio
    calcoloPunteggio(giocatori,numeroGiocatori,puntaggi_primaDelTurno,mazzoCFU,ostacolo_Turno,mazzoOstacoli,mazzoScarti);



}

void calcoloPunteggio(IlGiocatore** giocatori, int* numeroGiocatori,const int puntaggi_primaDelTurno[], CarteCFU** mazzoCFU, CarteOSTACOLO** ostacolo_Turno, CarteOSTACOLO** mazzoOstacoli, CarteCFU** mazzoScarti){
    int punteggi[*numeroGiocatori];
    IlGiocatore* giocatoriTemp=*giocatori;
    int maxPunteggio=0;
    int minPunteggio;
    // Array con numero degli elementi uguali al numero dei giocari. In ogni elemento mettero un numero che avra' un significato(0 se ha il punteggio piu basso; 1 se e' il piu alto; 2 ne il piu basso ne il piu alto)
    int perdenti0_vincitori1[*numeroGiocatori];
    int contaVincitori=0,contaPerdenti=0;

    // Calcolo punteggio fatto da ogni giocatore nel turno
    for (int i = 0; i < (*numeroGiocatori); ++i){
        punteggi[i]=(giocatoriTemp->CFUaccumulati - puntaggi_primaDelTurno[i]);
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    giocatoriTemp=*giocatori;

    // Imposto il punteggio minimo al punteggio fatto dal primo giocatore nel turno
    minPunteggio=punteggi[0];

    // Individuo punteggio massimo e minimo tra i giocatori
    for (int i = 0; i < (*numeroGiocatori); ++i){
        if(punteggi[i]>maxPunteggio){
            maxPunteggio=punteggi[i];
        }
        if(punteggi[i]<minPunteggio){
            minPunteggio=punteggi[i];
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    giocatoriTemp=*giocatori;


    // Riempio l'array in base al punteggio e conto quanti perdenti e vincenti ci sono
    for (int i = 0; i < (*numeroGiocatori); ++i){

        if (maxPunteggio==punteggi[i]){
            perdenti0_vincitori1[i]=VINCENTI;
            contaVincitori++;
        }else if( minPunteggio==punteggi[i]){
            //
            perdenti0_vincitori1[i]=PERDENTI;
            contaPerdenti++;
        }else{
            perdenti0_vincitori1[i]=NE_VINCENTI_NE_PERDENTI;
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;

    }
    giocatoriTemp=*giocatori;

    // Se tutti i giocatori fanno lo stesso punteggio nel turno, e quindi il punteggi minimo=massimo, la carta ostacolo finira in fondo al mazzo
    if(contaVincitori==(*numeroGiocatori) && minPunteggio==maxPunteggio){
        printf("\nTutti quanto hanno fatto il medesimo punteggio, tutti quanti sono vincitori(del turno)\n");
        trasferisciOstacoloInCoda(mazzoOstacoli,ostacolo_Turno);
    }


    if(contaPerdenti==1){
        for (int i = 0; i < (*numeroGiocatori); ++i){
            if(perdenti0_vincitori1[i]==PERDENTI){
                fase_delPerdente(giocatori,&giocatoriTemp,mazzoOstacoli,ostacolo_Turno,mazzoCFU,numeroGiocatori);
            }

            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }
        giocatoriTemp=*giocatori;
    }else{
        // Nel caso in cui i perdenti fossero piu di 1
        // C'e' la fase dell ulteriore turno tra i perdenti
        // Individuare uno o piu vincitori, quest ultimo nel caso in cui maxPunteggio sia appunto stato fatto da piu giocatori

        turnoAggiuntivo(numeroGiocatori,giocatori,mazzoCFU,ostacolo_Turno,mazzoOstacoli,perdenti0_vincitori1,contaPerdenti,contaVincitori,mazzoScarti);

        // Do l ostacolo al giocare perdente che e' stato individuato
        for (int i = 0; i < (*numeroGiocatori); ++i) {
            if(perdenti0_vincitori1[i]==PERDENTI){
                fase_delPerdente(giocatori,&giocatoriTemp,mazzoOstacoli,ostacolo_Turno,mazzoCFU,numeroGiocatori);
            }
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }
        giocatoriTemp=*giocatori;

    }


    // Funzione che toglie il punteggio fatto durante il turno, ai non vincitori, quindi a PERDENTI e NE_VINCENTI_NE_PERDENTI nell array perdenti0_vincitori1
    eliminaPunteggio_aiNonVincitori(giocatori,perdenti0_vincitori1,punteggi);


}


void turnoAggiuntivo(int* numeroGiocatori, IlGiocatore** giocatori, CarteCFU** mazzoCfu, CarteOSTACOLO** ostacoloTurno, CarteOSTACOLO** mazzoOstacoli, int perdenti0_vincitori1[],
                     int contaPerdenti, int contaVincenti, CarteCFU** mazzoScarti){
    IlGiocatore* giocatoriTemp=*giocatori;
    CarteCFU* mazzoScarti_turnoAggiuntivo=NULL;
    bool Turno=true;
    int perdentiSenzaCarte[*numeroGiocatori];
    int nGiocatori_senzaCarte=0;

    stampaVincenti_Turno(contaVincenti,giocatori, perdenti0_vincitori1);


//
    while (Turno){
        // Verifico tra i perdenti se qualcuno ha il mazzo privo di carte punto, nel caso in cui fosse cosi il Turno finisce
        for (int i = 0; i < (*numeroGiocatori); ++i){
            if(perdenti0_vincitori1[i]==PERDENTI){
                if(verifica_cartePunto_mazzoGiocatore(&giocatoriTemp->carteCfu)==false){
                    Turno=false;
                    perdentiSenzaCarte[i]=SENZA_CARTE;
                    nGiocatori_senzaCarte++;
                }
            }else{
                perdentiSenzaCarte[i]=CON_CARTE_O_NONPERDENTI;
            }
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }
        giocatoriTemp=*giocatori;

        // Se tutti i giocatori perdenti non hanno carte CFU PUNTO da poter giocare, allora l ostacolo finira in fondo al mazzo degli ostacoli
        if(nGiocatori_senzaCarte==contaPerdenti){
            printf("\nNessuno dei giocatori perdenti ha carte Punto da poter giocare, nessuno\n"
                   "sara' il reale perdente, l'Ostacolo andra in fondo al mazzo.\n");
            trasferisciOstacoloInCoda(mazzoOstacoli,ostacoloTurno);
            // Se i giocatori perdenti sono piu' di 2 e i giocatori senza carte sono 2
        }else if(nGiocatori_senzaCarte==(contaPerdenti-1) && contaPerdenti>2){
            // Non e' stato specificato questo caso, quindi lo gestisco come il precedente, "Due dei tre giocatori" in questo gioco siccome i giocatori massimi sono 4
            printf("\nDue dei tre giocatori perdenti non hanno carte Punto da poter\n"
                   "giocare, l'Ostacolo andra' in fondo al mazzo");
            trasferisciOstacoloInCoda(mazzoOstacoli,ostacoloTurno);
        }else if(nGiocatori_senzaCarte==1){
            // Altrimenti il giocatore perdente senza carte cfu punto da poter giocare sara' soltanto 1 e quindi ricevera lui la carta ostacolo
            for (int i = 0; i < (*numeroGiocatori); ++i) {
                if(perdentiSenzaCarte[i]==SENZA_CARTE){
                    fase_delPerdente(giocatori,&giocatoriTemp,mazzoOstacoli,ostacoloTurno,mazzoCfu,numeroGiocatori);
                }
                giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
            }
            giocatoriTemp=*giocatori; // reset

        }

        if(Turno){
            for (int i = 0; i < (*numeroGiocatori); ++i) {
                if(perdenti0_vincitori1[i]==PERDENTI){
                    int scelta= selezioneCarta_daScartare(&giocatoriTemp,CARTA_PUNTO);
                    trasferisciCarta(&mazzoScarti_turnoAggiuntivo,&giocatoriTemp->carteCfu,scelta);
                    // Inserisci verificaPunteggio_turnoAggiuntivo


                }
                giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
            }
            giocatoriTemp=*giocatori;
            verificaPunteggio_turnoAggiuntivo(giocatori,&contaPerdenti,perdenti0_vincitori1,&mazzoScarti_turnoAggiuntivo);
        }

        // Metto le carte scartate nel mazzo degli scarti
        riempi_daMazzo_aMazzo(mazzoScarti,&mazzoScarti_turnoAggiuntivo);

    }


}


void verificaPunteggio_turnoAggiuntivo(IlGiocatore** giocatori, int *numeroPerdenti, int perdenti0_vincitori1[],CarteCFU** mazzoScarti_turnoAggiuntivo){
    IlGiocatore* giocatoriTemp=*giocatori;
    CarteCFU* mazzoScarti_temp=*mazzoScarti_turnoAggiuntivo;


    int valoreMAX=0;
    int valoreMIN=mazzoScarti_temp->valore;  // Imposta il valore minimo alla prima carta giocata

    int valoriMAX_giocati=0;
    int valoriMIN_giocati=0;

    // Individuo valore MASSIMO e MINIMO che sono stati giocati
    for (int i = 10; i >= 0; --i) {

        while (mazzoScarti_temp!=NULL){
            if(mazzoScarti_temp->valore==i){
                if(mazzoScarti_temp->valore>valoreMAX){
                    valoreMAX=mazzoScarti_temp->valore;
                }
                if(mazzoScarti_temp->valore<valoreMIN){
                    valoreMIN=mazzoScarti_temp->valore;
                }
            }
            mazzoScarti_temp=mazzoScarti_temp->prossimaCartaCFU;
        }
        mazzoScarti_temp=*mazzoScarti_turnoAggiuntivo;   // Reset
    }


    // Individuo quante volte il valore MASSIMO e MINIMO che sono stati giocati, quante volte sono stati giocati(per individuare eventuali pareggi)
    for (int i = valoreMAX; i >= valoreMIN ; --i) {

        while (mazzoScarti_temp!=NULL){
            if(mazzoScarti_temp->valore==valoreMAX){
                valoriMAX_giocati++;
            }
            if(mazzoScarti_temp->valore==valoreMIN){
                valoriMIN_giocati++;
            }

            mazzoScarti_temp=mazzoScarti_temp->prossimaCartaCFU;
        }
        mazzoScarti_temp=*mazzoScarti_turnoAggiuntivo;
    }


    int indice=0;

    if(valoriMIN_giocati==1){
        // Se e' e' stata giocata una sola volta la carta col valore minore, allora ci sara un solo perdente
        while (mazzoScarti_temp!=NULL){
            // Individuazione vincenti turno aggiuntivo
            if(mazzoScarti_temp->valore!=valoreMIN && perdenti0_vincitori1[indice]!=VINCENTI){
                // I perdenti che non hanno perso il turno aggiuntivo, diventano NE_VINCENTI_NE_PERDENTI
                perdenti0_vincitori1[indice]=NE_VINCENTI_NE_PERDENTI;
                (*numeroPerdenti)--;           // Diminuisco di conseguenza il numero dei perdenti
            }else if(perdenti0_vincitori1[indice]!=VINCENTI){
                printf("\n[%s] riceverai la carta ostacolo",giocatoriTemp->nomeutente);
            }
            indice++;
            mazzoScarti_temp=mazzoScarti_temp->prossimaCartaCFU;
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }

    }else if(valoriMIN_giocati>1 && valoriMIN_giocati<*numeroPerdenti){
        // Se il valore minimo e' stato giocato piu di una volta ma meno del numero dei giocatori che stanno giocando il turno aggiuntivo
        // Chi ha fatto il punteggio massimo sara' NE_VINCENTI_NE_PERDENTI, gli altri rifaranno il turno
        while (mazzoScarti_temp!=NULL){
            // Individuazione vincenti turno aggiuntivo
            if(mazzoScarti_temp->valore==valoreMAX && perdenti0_vincitori1[indice]!=VINCENTI){
                printf("\n[%s] sei salvo, gli altri giocatori continueranno con un altro turno",giocatoriTemp->nomeutente);
                // I perdenti che non hanno perso il turno aggiuntivo, diventano NE_VINCENTI_NE_PERDENTI
                perdenti0_vincitori1[indice]=NE_VINCENTI_NE_PERDENTI;
                (*numeroPerdenti)--;           // Diminuisco di conseguenza il numero dei perdenti
            }
            indice++;
            mazzoScarti_temp=mazzoScarti_temp->prossimaCartaCFU;
            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
        }
    }else if((*numeroPerdenti)==valoriMIN_giocati && valoriMAX_giocati==(*numeroPerdenti)){
        printf("\n Tutti i giocatori hanno fatto il medesimo punto, si svolgera' un altro turno");
    }

}







void eliminaPunteggio_aiNonVincitori(IlGiocatore** giocatori, const int perdenti0_vincitori1[], const int punteggiTurno[]){
    IlGiocatore* giocatoriTemp=*giocatori;
    int indice=0;

    // Tolgo i punteggi fatti durante il turno ai giocatori che non risultano VINCENTI
    while (giocatoriTemp!=NULL){
        if(perdenti0_vincitori1[indice]==PERDENTI || perdenti0_vincitori1[indice]==NE_VINCENTI_NE_PERDENTI){
            giocatoriTemp->CFUaccumulati-=punteggiTurno[indice];
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }

}







void fase_delPerdente(IlGiocatore** giocatori, IlGiocatore** giocatorePerdente,CarteOSTACOLO** mazzoOstacoli, CarteOSTACOLO** ostacoloTurno, CarteCFU** mazzoCfu, int* numeroGiocatori){
    IlGiocatore* giocatoriTemp=*giocatori;
    CarteCFU* carte_giocatorePerdente=(*giocatorePerdente)->carteCfu;
    CarteCFU* cartaScartata_nellaPerdita=NULL;
    int conta=0, sceltaGiocatore;

    // Se ha carte con effetto SALVA o DIROTTA nella mano
    if (verifica_SALVA_DIROTTA(&(*giocatorePerdente)->carteCfu)){
        printf("\n[%s] hai perso ma avrai la possibilita di giocare una carta \nistantanea che abbia effetto SALVA o DIROTTA.",(*giocatorePerdente)->nomeutente);
        int scelta= selezioneCarta_daScartare(giocatorePerdente,CARTA_ISTANTANEA_FINETURNO);
        trasferisciCarta(&cartaScartata_nellaPerdita,&(*giocatorePerdente)->carteCfu,scelta);

        // In base alla carta scelta tra SALVA e DIROTTA
        if(cartaScartata_nellaPerdita->nomeEffetti==SALVA){
            printf("\nTi sei salvato, la carta ostacolo finira in fondo al mazzo");
            trasferisciOstacoloInCoda(mazzoOstacoli,ostacoloTurno);
        }else{
            printf("\nHai giocato una carta con effetto DIROTTA, scegli un giocatore \nal quale dirottare la carta ostacolo:");

            // Stampa dei giocatori
            while (giocatoriTemp!=NULL){
                if(giocatoriTemp!=(*giocatorePerdente)){
                    printf("\n[%d]-> Nome: %s",++conta,giocatoriTemp->nomeutente);
                }
                giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
            }
            giocatoriTemp=*giocatori;

            // Selezione scelta
            printf("\nSelezione: ");
            do {
                scanf("%d",&scelta);
                if(scelta<1 || scelta>conta){
                    printf("Il numero selezionato non e' valido.\nRipeti!\n");
                }
            } while (scelta<1 || scelta>conta);


            //Sposto puntatore fino a quando non raggiungo il giocatore scelto in base a "scelta"
            for (int i = 0; i < scelta; ++i) {
                giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
            }

            // Inserisco giocatoriTemp nella funzione per il giocatore perdente
            inserisci_Ostacolo(&giocatoriTemp,ostacoloTurno,mazzoCfu,giocatori,numeroGiocatori,mazzoOstacoli);

        }

// Oppure se non ha carte con effetto SALVA o DIROTTA nella mano
    }else{
        printf("\n[%s] non hai carte che possono salvarti, hai preso un ostacolo",(*giocatorePerdente)->nomeutente);
        // inserisci_ostacolo
        inserisci_Ostacolo(giocatorePerdente,ostacoloTurno,mazzoCfu,giocatori,numeroGiocatori,mazzoOstacoli);
    }



}


void inserisci_Ostacolo(IlGiocatore** giocatoreSfortunato_o_Perdente, CarteOSTACOLO** ostacoloTurno,CarteCFU** mazzoCfu, IlGiocatore** giocatori, int* numeroGiocatori, CarteOSTACOLO** mazzoOstacoli){
    // Contera il numero degli ostacoli non di tipo ESAME
    int contaOstacoli=0;

    if((*ostacoloTurno)==NULL){
        printf("Errore in inserisci_Ostacolo");
        exit(EXIT_FAILURE);
    }
    // Aggiungo ostacolo
    (*giocatoreSfortunato_o_Perdente)->personaggio.BONUS_MALUS[(*ostacoloTurno)->tipoOstacoli]+=1;
    trasferisciOstacoloInCoda(&(*giocatoreSfortunato_o_Perdente)->carteOstacolo,&(*ostacoloTurno));

    for (int i = 0; i < NUMERO_TIPOLOGIA_OSTACOLI; ++i) {
        // Se son presenti tre ostacoli di una stessa categoria
        if((*giocatoreSfortunato_o_Perdente)->personaggio.BONUS_MALUS[i]==3){
            printf("\n[%s] e' stato eliminato",(*giocatoreSfortunato_o_Perdente)->nomeutente);
            //ELIMINA GIOCATORE
            eliminaGiocatore(giocatori,*giocatoreSfortunato_o_Perdente,mazzoCfu,mazzoOstacoli);
            (*numeroGiocatori)--;
            return;
        }
        // Conto tutti gli ostacoli che non sono di tipo ESAME
        if(i!=ESAME){
            contaOstacoli+=(*giocatoreSfortunato_o_Perdente)->personaggio.BONUS_MALUS[i];
        }
    }

    // Se almeno un ostacolo di tipo ESAME e almeno due ostacoli di tipo differente da ESAME oppure almeno 3 ostacoli di tipo differente da ESAME
    if(((*giocatoreSfortunato_o_Perdente)->personaggio.BONUS_MALUS[ESAME]>=1 && contaOstacoli>=2) || contaOstacoli>=3){
        printf("\n[%s] e' stato eliminato",(*giocatoreSfortunato_o_Perdente)->nomeutente);
        // ELIMINA GIOCATORE
        eliminaGiocatore(giocatori,*giocatoreSfortunato_o_Perdente,mazzoCfu,mazzoOstacoli);
        (*numeroGiocatori)--;
    }

}
