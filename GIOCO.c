#include "libreria_funzioni.h"

/**GIOCO*/
void disegnoHappyLittleStudents() {
    FILE* file=NULL;
    file= fopen("savegame.sav","w");
    if(file==NULL){
        printf("Errore nella creazione del file savegame.sav");
        exit(EXIT_FAILURE);
    }
    fprintf(file,"+----------------------------------------------------------------------------+\n"
                 "| _   _                                     _       _   _     _     _        |\n"
                 "|| | | |   __ _   _ __    _ __    _   _    | |     (_) | |_  | |_  | |   ___ |\n"
                 "|| |_| |  / _` | | '_ \\  | '_ \\  | | | |   | |     | | | __| | __| | |  / _ \\|\n"
                 "||  _  | | (_| | | |_) | | |_) | | |_| |   | |___  | | | |_  | |_  | | |  __/|\n"
                 "||_| |_|  \\__,_| | .__/  | .__/   \\__, |   |_____| |_|  \\__|  \\__| |_|  \\___||\n"
                 "| ____    _      |_|     |_|_     |___/        _                             |\n"
                 "|/ ___|  | |_   _   _    __| |   ___   _ __   | |_   ___                     |\n"
                 "|\\___ \\  | __| | | | |  / _` |  / _ \\ | '_ \\  | __| / __|                    |\n"
                 "| ___) | | |_  | |_| | | (_| | |  __/ | | | | | |_  \\__ \\                    |\n"
                 "||____/   \\__|  \\__,_|  \\__,_|  \\___| |_| |_|  \\__| |___/                    |\n"
                 "+----------------------------------------------------------------------------+\n");
    fclose(file);
}

void stampaDatiGiocatori(IlGiocatore** giocatori,int numGiocatori) {
    IlGiocatore* temp=*giocatori;

    FILE* file=NULL;
    file= fopen("savegame.sav","a");
    if(file==NULL){
        printf("\nErrore nella creazione del file savegame.sav.");
        exit(EXIT_FAILURE);
    }

    fprintf(file,"\n\n=========================================== GIOCATORI - Num: %d =========================================================\n",
            numGiocatori);



    while(temp!=NULL){
        // OSTACOLI POSSEDUTI DAL GIOCATORE
        CarteCFU* carteCFU=NULL;
        CarteOSTACOLO* carteOSTACOLO=NULL;
        //dichiaro un puntatore carteCFU per ogni ciclo, quindi per ogni giocatore, cosi che posso resettare il puntatore delle carte CFU
        carteCFU=temp->carteCfu;
        carteOSTACOLO=temp->carteOstacolo;

        fprintf(file,"\nNome: %s\n"
                     "Studio: %d\n"
                     "Sopravvivenza: %d\n"
                     "Sociale:%d\n"
                     "Esame: %d\n", temp->nomeutente, temp->personaggio.BONUS_MALUS[0],
                temp->personaggio.BONUS_MALUS[1], temp->personaggio.BONUS_MALUS[2],
                temp->personaggio.BONUS_MALUS[3]);

        // RAFFIGURAZIONE CARTE CFU NELLA MANO DI OGNI GIOCATORE CON RISPETTIVO NOME, NOME EFFETTO E VALORE(PER CIASCUNA CARTA)
        while (carteCFU != NULL) {
            fprintf(file,"+--------------------+ ");
            carteCFU = carteCFU->prossimaCartaCFU;
        }

        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore
        fprintf(file,"\n");


        while (carteCFU != NULL) {
            fprintf(file,"| %d                  | ", carteCFU->valore);
            carteCFU = carteCFU->prossimaCartaCFU;
        }

        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore
        fprintf(file,"\n");


        //Inserisco i nomi di ogni carta
        while (carteCFU != NULL) {
            fprintf(file,"| %s", carteCFU->nome);

            int lunghezzaParola = strlen(carteCFU->nome);

            for (int j = 0; j < 19 - lunghezzaParola; ++j) {
                fprintf(file," ");
            }
            fprintf(file,"| ");

            carteCFU = carteCFU->prossimaCartaCFU;
        }


        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore
        fprintf(file,"\n");


//Inserisco i nomi degli effetti di ogni carta
        while (carteCFU != NULL) {
            char *nomeEffetto = Switch_Case_effettoCarta(carteCFU->nomeEffetti);

            fprintf(file,"| %s", nomeEffetto);

            int lunghezzaParola = strlen(nomeEffetto);

            for (int j = 0; j < 19 - lunghezzaParola; ++j) {
                fprintf(file," ");
            }
            fprintf(file,"| ");

            carteCFU = carteCFU->prossimaCartaCFU;
        }

        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore
        fprintf(file,"\n");

        while (carteCFU != NULL) {
            fprintf(file,"|                  %d | ", carteCFU->valore);
            carteCFU = carteCFU->prossimaCartaCFU;
        }

        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore
        fprintf(file,"\n");

        while (carteCFU != NULL) {
            fprintf(file,"+--------------------+ ");
            carteCFU = carteCFU->prossimaCartaCFU;
        }

        carteCFU=temp->carteCfu;  //reset puntatore carte cfu del giocatore

        // ELENCO CARTE OSTACOLO POSSEDUTE DAL GIOCATORE CON NOME, DESCRIZIONE E TIPOLOGIA(PER OGNI CARTA)
        fprintf(file,"\nOstacoli:\n");

        if(carteOSTACOLO==NULL)fprintf(file,"%s non ha nesuna carta Ostacolo\n\n",temp->nomeutente);

        while (carteOSTACOLO != NULL) {
            fprintf(file,"Nome: %s\n"
                         "Descrizione: %s\n"
                         "Tipologia: %s\n\n", carteOSTACOLO->nome, carteOSTACOLO->descrizioneOSTACOLO,
                    Switch_Case_tipoOstacoli(carteOSTACOLO->tipoOstacoli));
            carteOSTACOLO = carteOSTACOLO->prossimaCartaOSTACOLO;
        }
        carteOSTACOLO=temp->carteOstacolo;  //reset puntatore delle carte ostacolo

        temp=temp->GIOCATOREsuccessivo; //porto avanti il puntatore all elemento successivo della lista giocatori
    }
    fclose(file);
}

void sceltaAzione(IlGiocatore** giocatori,CarteCFU** mazzoCFU,bool* continua, CarteCFU** carteTurno_Scarti,int numeroTurno, CarteCFU** mazzoScarti){
    IlGiocatore* temp=*giocatori;
    bool Turno=true;
    while (Turno){
            // Carte mancanti per avere 5 carte nella mano
            int carteMancanti_perArrivare_a5= carteMancanti(&temp->carteCfu);

            for (int i = 0; i < carteMancanti_perArrivare_a5; ++i) {
                if(*mazzoCFU==NULL){
                    // Quando il mazzo delle carte da pescare finisce, questo diventera il precedente mazzo degli scarti dopo essere stato mescolato
                    riempi_daMazzo_aMazzo(mazzoCFU,mazzoScarti);
                    mescolaCarteCFU(mazzoCFU);
                }
                pescaggioCartaCfu(mazzoCFU,&temp->carteCfu);
            }


        int scelta=stampaSceltaAzione(temp->nomeutente);

        // Visualizza carte degli altri giocatori
        if(scelta==2){
            scelta2(&temp, giocatori);
            printf("\n%s, adesso\n[0]Esci dalla partita\n[1]Giochi una carta CFU ",temp->nomeutente);
            do {
                // Cambia valore della variabile "scelta" per l' azione successiva
                scelta = scanf("%d", &scelta);
            } while (scelta != 0 && scelta != 1);
        }

        if(scelta==0){
            // Conclude la partita
            printf("\nLa partita e' stata terminata. Il numero dei giocatori e' 0.\n");
            eliminaListaGiocatori(giocatori);
            Turno=false;
            *continua=false;
        }else if(scelta==1){
            // Gioca una carta
            scelta1(&temp,carteTurno_Scarti,mazzoScarti,mazzoCFU);
        }

        // Solo nel caso in cui la partita si concluda(scelta 0), il puntatore della lista non scorrera
        if(scelta==1 || scelta==2){
            if(temp->GIOCATOREsuccessivo==NULL){
                Turno=false;
            }else{
                temp=temp->GIOCATOREsuccessivo;
            }
        }

    }

}

void eliminaListaGiocatori(IlGiocatore** testa) {
    if (testa == NULL || *testa == NULL) {
        printf("La lista dei giocatori e' gia vuota");
        return; // Lista già vuota o puntatore non valido.
    }

    IlGiocatore* current = *testa;
    IlGiocatore* next;

    while (current != NULL) {
        next = current->GIOCATOREsuccessivo; // Salva il riferimento al giocatore successivo.

        // Elimina le liste di carte associate al giocatore corrente.
        eliminaMazzoCFU(&current->carteCfu);
        eliminaMazzoOstacoli(&current->carteOstacolo);

        free(current); // Libera la memoria allocata per il giocatore corrente.
        current = next; // Passa al prossimo giocatore.
    }

    *testa = NULL; // Assicurati che il puntatore alla testa della lista sia impostato su NULL dopo la pulizia.
}

void scopriCarte(CarteCFU* scartiTurno,IlGiocatore* giocatori){
    IlGiocatore* tempG=giocatori;
    CarteCFU* tempC=scartiTurno;
    printf("\nSCOPRIAMO LE CARTE GIOCATE!!\n");
    while (tempG!=NULL && tempC!=NULL){
        printf("%s ha scartato la carta->Nome: %s | Effetto: %s | Valore: %d\n",tempG->nomeutente,tempC->nome,Switch_Case_effettoCarta(tempC->nomeEffetti),tempC->valore);
        tempG=tempG->GIOCATOREsuccessivo;
        tempC=tempC->prossimaCartaCFU;
    }
    printf("\n\n\n");
}


void fasePunteggio(IlGiocatore** giocatori,CarteCFU** mazzoCfu, CarteCFU** carteTurno_Scarti, CarteCFU** mazzoScarti, CarteOSTACOLO** ostacoloTurno, int* numeroGiocatori, CarteOSTACOLO** mazzoOstacoli) {

    CarteCFU *carteTurno = *carteTurno_Scarti;
    IlGiocatore *giocatoriTemp = *giocatori;
    int punteggi_primaDelTurno[*numeroGiocatori];

    // Salva i punteggi dei giocatori prima dell'aggiunta dei nuovi punti
    for (int i = 0; i < *numeroGiocatori; ++i) {
        punteggi_primaDelTurno[i]=giocatoriTemp->CFUaccumulati;
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }

    somma_BonusMalus(giocatori);

    giocatoriTemp=*giocatori;    // Reset puntatore
    bool inversionePunti_SCAMBIAP=false;
    bool raddoppia_DOPPIOE=false;


    // Considera il valore delle carte punto scartate, dall piu alta di valore(9) alla piu bassa(0)
    for (int i = 9; i >= 0 ; --i){

        while (carteTurno != NULL && giocatoriTemp!=NULL) {

            if (carteTurno->valore == i) {

                // Azione in base all effetto della carta
                effetti_cartePunto(&i,mazzoCfu,&giocatoriTemp,&carteTurno,giocatori,carteTurno_Scarti,mazzoScarti,*numeroGiocatori,&inversionePunti_SCAMBIAP,&raddoppia_DOPPIOE);
            }
            // Queste due liste sono nello stesso ordine(Primo giocatore(di giocatoriTemp) ha giocato Prima carta(di carteTurno); Secondo giocatore ha giocato Seconda carta e cosi via..)
            giocatoriTemp = giocatoriTemp->GIOCATOREsuccessivo;
            carteTurno = carteTurno->prossimaCartaCFU;
        }
        // Reset cosi' che se continua e' ancora true
        giocatoriTemp = *giocatori;
        carteTurno = *carteTurno_Scarti;
    }

    /** Crea funzione che in base ad un NUMERO(da 1 a *numeroGiocatori) elimini il giocatore che sta in quella posizione nella lista dei giocatori(in base a chi viene eliminato a fine round).
     * Quindi nel caso in cui dovesse venir eliminato un giocatore, *numeroGiocatori diminuira e la rispettiva carta nella lista "carteTurno" dovra essere eliminata*/







    printf("\n\n");
    /** Questo sara da fare dopo la considerazione degli effetti delle carte*/
    if(inversionePunti_SCAMBIAP==false){
        // Somma punteggio delle carte giocate
        sommaPunteggi_cartePunto(giocatori,&carteTurno,*numeroGiocatori);

        // I punteggi verranno calcolati in maniera normale soltanto se nessuno giochera' una carta con effetto SCAMBIAP
        for (int i = 0; i < *numeroGiocatori; ++i) {
            printf("\n-[%s] ha fatto +[%d] punti",giocatoriTemp->nomeutente,(giocatoriTemp->CFUaccumulati-punteggi_primaDelTurno[i]));

            giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
            carteTurno=carteTurno->prossimaCartaCFU;
        }
    }else{
        /**potresti fare un ciclo e quindi cambiare inversionePunti_SCAMBIAP in un numero intero(cosi si fanno tot cicli di effetto_SCAMBIAP) nel caso in cui piu giocatori giochino
         * nello stesso turno una carta con effetto SCAMBIAP*/

        // Somma punteggio delle carte giocate
        sommaPunteggi_cartePunto(giocatori,&carteTurno,*numeroGiocatori);
        // Crea una funziona che aggiunga i punteggi in base alle carte punto giocate, cosi da sostituire la parte iniziare di
        // effetto_SCAMBIAC e utilizzare la stessa funzione per l effetto INVERTI delle carte istantanee

        effetto_SCAMBIAP(giocatori,*numeroGiocatori,punteggi_primaDelTurno);
    }
    printf("\n\n\n");
    fase_carteIstantanee(mazzoCfu,giocatori,mazzoScarti,numeroGiocatori,punteggi_primaDelTurno,raddoppia_DOPPIOE,ostacoloTurno,mazzoOstacoli);
}

void controlla_60_punti(IlGiocatore** giocatori, bool *continua){
    IlGiocatore* giocatoriTemp=*giocatori;

    while (giocatoriTemp!=NULL){
        if(giocatoriTemp->CFUaccumulati>=PUNTEGGIO_VINCITA){
            printf("\n[%s] ha vinto la partita\n",giocatoriTemp->nomeutente);
            (*continua)=false;
        }
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
}






























































