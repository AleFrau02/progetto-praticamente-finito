//
// Created by Alessio Frau on 10/05/2024.
//
#include "libreria_funzioni.h"



void effetto_SCAMBIAC(int numeroGiocatori, IlGiocatore** giocatori, IlGiocatore** giocatoreTurno) {
    if (numeroGiocatori > 2) {
        IlGiocatore* temp = *giocatori;
        IlGiocatore* giocatore1 = NULL;
        IlGiocatore* giocatore2 = NULL;
        int sceltaGiocatore1 = 0;
        int sceltaGiocatore2 = 0;

        if (numeroGiocatori == 3) {
            // Caso di esattamente tre giocatori
            printf("\nI suoi due avversari si scambieranno il mazzo\n");
            while (temp != NULL) {
                if (temp != *giocatoreTurno) {
                    if (giocatore1 == NULL) {
                        giocatore1 = temp;
                    } else {
                        giocatore2 = temp;
                        // Fai in modo che il ciclo si concluda
                        while (temp->GIOCATOREsuccessivo!=NULL)temp=temp->GIOCATOREsuccessivo;
                    }
                }
                temp = temp->GIOCATOREsuccessivo;
            }
        } else {
            // Caso di più di tre giocatori
            int conta = 1;
            printf("\nSeleziona i due giocatori che vuoi si scambino le mani (escludendo il giocatore di turno)\n");
            while (temp != NULL) {
                if (temp != *giocatoreTurno) {
                    printf("[%d] -> Nome: %s\n", conta++, temp->nomeutente);
                }
                temp = temp->GIOCATOREsuccessivo;
            }

            do {
                printf("\nGiocatore 1: ");
                scanf("%d", &sceltaGiocatore1);
                printf("\nGiocatore 2: ");
                scanf("%d", &sceltaGiocatore2);
                if (((sceltaGiocatore1 < 1) || (sceltaGiocatore2 < 1)) || ((sceltaGiocatore1 > (numeroGiocatori - 1)) || (sceltaGiocatore2 > (numeroGiocatori - 1))) || (sceltaGiocatore1 == sceltaGiocatore2)) {
                    printf("\nErrore nelle scelte. Riprova!\n");
                }
            } while (((sceltaGiocatore1 < 1) || (sceltaGiocatore2 < 1)) || ((sceltaGiocatore1 > (numeroGiocatori - 1)) || (sceltaGiocatore2 > (numeroGiocatori - 1))) || (sceltaGiocatore1 == sceltaGiocatore2));

            temp = *giocatori;
            conta = 1;
            while (temp != NULL) {
                if (temp != *giocatoreTurno) {
                    if (sceltaGiocatore1 == conta) {
                        giocatore1 = temp;
                    } else if (sceltaGiocatore2 == conta) {
                        giocatore2 = temp;
                    }
                    conta++;
                }
                temp = temp->GIOCATOREsuccessivo;
            }
        }

        // Effettua lo scambio dei mazzi
        if (giocatore1 && giocatore2) {    // Usare && con due puntatori, dara' VERO se e solo se i puntatori sono entrambi NON NULL
            scambiaMazzi(&giocatore1->carteCfu, &giocatore2->carteCfu);
            printf("\nScambio effettuato tra %s e %s.\n", giocatore1->nomeutente, giocatore2->nomeutente);
        } else {
            printf("\nErrore: Non è stato possibile identificare correttamente i giocatori per lo scambio.\n");
        }
    } else {
        printf("\nGiocatori avversari non sufficienti per effettuare lo scambio\n");
    }
}
void effetto_SCARTAP(IlGiocatore** giocatoreTurno,CarteCFU** mazzoScarti){
    int contaCarte_Mano=0;
    int contaCarte_CfuPunto=0;
    CarteCFU* mazzoGiocatore=(*giocatoreTurno)->carteCfu;

    while (mazzoGiocatore!=NULL){
        if((mazzoGiocatore->valore!=0 && strcmp(mazzoGiocatore->nome,"Monitor")!=0) || (mazzoGiocatore->valore==0 && strcmp(mazzoGiocatore->nome,"Monitor")==0)){
            contaCarte_CfuPunto++;
        }
        contaCarte_Mano++;
        mazzoGiocatore=mazzoGiocatore->prossimaCartaCFU;
    }

    if(contaCarte_CfuPunto==0)printf("\n[%s] non hai carte sufficienti per applicare l'effetto della tua carta.\n",(*giocatoreTurno)->nomeutente);
    else{
        int nCartaSelezionata= selezioneCarta_daScartare(giocatoreTurno,CARTA_PUNTO);

        CarteCFU* carteGiocatore=(*giocatoreTurno)->carteCfu;
        CarteCFU *prevCarta = NULL;
        for (int i = 1; i < nCartaSelezionata; ++i) {
            prevCarta = carteGiocatore;
            carteGiocatore = carteGiocatore->prossimaCartaCFU;
        }

        // Somma valore della carta scartata ai punti del giocatore, grazie all effetto SCARTAP
        printf("Grazie alla carta con effetto SCARTAP, avrai +[%d] punti CFU\n",carteGiocatore->valore);
        (*giocatoreTurno)->CFUaccumulati+=carteGiocatore->valore;

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

        // Inserisci dati della carta nel mazzo degli scarti
        inserisciCfu_inCoda_nelMazzo(mazzoScarti, nome, valore, nomeEffetti);
    }
}
void effetto_RUBA(IlGiocatore** giocatoreTurno,IlGiocatore** giocatori){
    IlGiocatore* temp=*giocatori;
    int contaCarte=0;
    int scelta=0;
    printf("\nScegli una delle seguenti carte dei tuoi avversari.\n");

    while (temp!=NULL){
        if(temp!=*giocatoreTurno){
            // Solo se il giocatore e' diverso dal giocatore della carta
            CarteCFU* carteGiocatore=temp->carteCfu;
            printf("Carte CFU di %s:\n",temp->nomeutente);
            // Scorro le carte CFU nella mano del giocatore
            while (carteGiocatore!=NULL){
                printf("[%d]-> Nome: %s | Effetto: %s | Valore: %d\n",++contaCarte,carteGiocatore->nome,
                       Switch_Case_effettoCarta(carteGiocatore->nomeEffetti),carteGiocatore->valore);
                carteGiocatore=carteGiocatore->prossimaCartaCFU;
            }
        }
        temp=temp->GIOCATOREsuccessivo;
    }
    temp=*giocatori;  // Reset puntatore della lista dei giocatori

    do {
        scanf("%d",&scelta);
        if(scelta<1 && scelta>contaCarte){
            printf("Il numero della carta non e' valido\nRipeti.\n");
        }
    } while (scelta<1 && scelta>contaCarte);

    // Variabili per carta scelta
    char nome[DIM_CARATTERI];
    int valore;
    NomeEffetti nomeEffetti;

    // Ricerco la carta selezionata
    while (temp!=NULL){
        if(temp!=*giocatoreTurno){
            eliminaCartaDalMazzo(&temp->carteCfu,nome,&valore,&nomeEffetti,contaCarte);
        }
        temp=temp->GIOCATOREsuccessivo;
    }

    // Inserimento carta nel mazzo del giocatore della carta
    inserisciCfu_inTesta_nelMazzo(&(*giocatoreTurno)->carteCfu,nome,valore,nomeEffetti);
}
void effetto_SCAMBIADS(IlGiocatore** giocatori, IlGiocatore** giocatoreTurno, CarteCFU** carteTurno, int numeroGiocatori){
    // Variabili
    CarteCFU* temp_carteTurno=*carteTurno;
    IlGiocatore* temp_giocatori=*giocatori;
    int conta=0,contaCarte_senzaEffetto=0,nCarta_giocatoreTurno=0,scelta=0;
    bool validita_selezioneCarte[numeroGiocatori];


    while(temp_carteTurno!=NULL){
        if(temp_carteTurno->nomeEffetti==NESSUNO){
            contaCarte_senzaEffetto++;
        }
        temp_carteTurno=temp_carteTurno->prossimaCartaCFU;
    }
    temp_carteTurno=*carteTurno;    // Reset del puntatore

// Verifica validita effetto
    if(contaCarte_senzaEffetto==0){
        printf("\n[%s], l'effetto SCAMBIADS della tua carta non e' applicabile, i tuoi avversari non hanno scartato carte prive di effetti",(*giocatoreTurno)->nomeutente);
    } else{
        printf("\nScegli una carta(SENZA EFFETTO) con la quale vuoi fare lo scambio:");

        // Stampa carte scartate dai giocatori durante il turno
        for (int i = 0; i < numeroGiocatori; ++i){
            printf("\n[%d]-> Nome: %s | Effetto: %s | Valore: %d  ",++conta,temp_carteTurno->nome,Switch_Case_effettoCarta(temp_carteTurno->nomeEffetti),temp_carteTurno->valore);

            if(temp_giocatori!=*giocatoreTurno){

                // Solo se il giocatore(corrispondente alla carta) e' diverso dal giocatore del turno
                if(temp_carteTurno->nomeEffetti==NESSUNO){
                    // Se senza effetto
                    printf("(CARTA SENZA EFFETTO)");
                    validita_selezioneCarte[i]=true;
                }else{
                    // Altrimenti
                    printf("(CARTA CON EFFETTO)");
                    validita_selezioneCarte[i]=false;
                }

            }else{
                // Solo se il giocatore(corrispondente alla carta) e' il giocatore del turno
                printf("(LA TUA CARTA)");
                nCarta_giocatoreTurno=conta;
                validita_selezioneCarte[i]=false;
            }
            temp_carteTurno=temp_carteTurno->prossimaCartaCFU;
            temp_giocatori=temp_giocatori->GIOCATOREsuccessivo;
        }
        temp_carteTurno=*carteTurno;
        temp_giocatori=*giocatori;

        // Scelta della carta con la quale fare lo scambio
        do {
            printf("\nNumero carta:");
            scanf(" %d",&scelta);
            if(validita_selezioneCarte[scelta-1]!=true){
                printf("\nE' probabile che tu abbia selezinato LA TUA CARTA oppure una CARTA CON EFFETTO.\nRipeti\n");
            }
        } while (validita_selezioneCarte[scelta-1]!=true);

        // Scambia posizione carte nel mazzo delle carte scartate dai giocatori nel turno(ricordo che "carteTurno" e "giocatori" sono nello stesso ordine(LISTE PARALLELE)).
        invertiPosizione_carteMazzo(carteTurno,nCarta_giocatoreTurno,scelta);
    }
}
void effetto_SCARTAE(IlGiocatore** giocatori, IlGiocatore** giocatoreTurno, CarteCFU** carteTurno, int numeroGiocatori, CarteCFU** mazzoScarti){
// Variabili
    int conta=0,contaCarte_conEffetto=0,scelta=0;
    bool validita_selezioneCarte[numeroGiocatori];

    CarteCFU* carte_giocatoreTurno=(*giocatoreTurno)->carteCfu;

    // Conta le carte nella mano del giocatore che abbiano effetto
    while (carte_giocatoreTurno!=NULL){
        if(carte_giocatoreTurno->nomeEffetti!=NESSUNO && (carte_giocatoreTurno->valore!=0 || strcmp(carte_giocatoreTurno->nome,"Monitor")==0)){
            contaCarte_conEffetto++;
        }
        carte_giocatoreTurno=carte_giocatoreTurno->prossimaCartaCFU;
    }
    carte_giocatoreTurno=(*giocatoreTurno)->carteCfu;

    if(contaCarte_conEffetto==0){
        printf("\n[%s] non hai carte con effetto nella tua mano.",(*giocatoreTurno)->nomeutente);
    }else{
        printf("Scarta una carta CFU punto con effetto e aggiungi\nil suo punteggio a quello del turno:");

        // Stampa carte della mano del giocatore indicando quali CARTE PUNTO CON EFFETTO e quali NO
        while (carte_giocatoreTurno!=NULL){
            printf("\n[%d]-> Nome: %s | Effetto: %s | Valore: %d  ",++conta,carte_giocatoreTurno->nome,
                   Switch_Case_effettoCarta(carte_giocatoreTurno->nomeEffetti),carte_giocatoreTurno->valore);
            if(carte_giocatoreTurno->nomeEffetti!=NESSUNO && (carte_giocatoreTurno->valore!=0 || strcmp(carte_giocatoreTurno->nome,"Monitor")==0)){
                printf("(CARTA PUNTO CON EFFETTO)");
                validita_selezioneCarte[conta-1]=true;
            }else{
                printf("(CARTA NON VALIDA)");
                validita_selezioneCarte[conta-1]=false;
            }
            carte_giocatoreTurno=carte_giocatoreTurno->prossimaCartaCFU;
        }

        // Selezione carta
        do{
            printf("\nNumero carta: ");
            scanf("%d",&scelta);
            if(validita_selezioneCarte[scelta-1]!=true){
                printf("\nE' probabile che tu abbia selezinato una carta NON VALIDA.\nRipeti\n");
            }
        } while (validita_selezioneCarte[scelta-1]!=true);

        // Variabili per salvare carta
        char nome[DIM_CARATTERI];
        NomeEffetti nomeEffetti;
        int valore;

        eliminaCartaDalMazzo(&(*giocatoreTurno)->carteCfu,nome,&valore,&nomeEffetti,scelta);

        inserisciCfu_inTesta_nelMazzo(mazzoScarti,nome,valore,nomeEffetti);

        // Aggiungi il valore della nuova carta scartata al punteggio del giocatore
        (*giocatoreTurno)->CFUaccumulati+=valore;
    }
}
void effetto_SCARTAC(IlGiocatore** giocatoreTurno,CarteCFU** mazzoScarti){
    // Se il mazzo del giocatore e' vuoto
    if((*giocatoreTurno)->carteCfu==NULL){
        printf("\nIl mazzo di [%s] e' vuoto, non puo essere scartata nessuna carta.",(*giocatoreTurno)->nomeutente);
        return;
    }

    int nCarta_daScartare=3,conta=0,numero_carteDaScartare=0,conta_carteGiocatore=0;
    CarteCFU* carteGiocatore=(*giocatoreTurno)->carteCfu;

// Conta carte presenti nella mano del giocatore
    while (carteGiocatore!=NULL){
        carteGiocatore=carteGiocatore->prossimaCartaCFU;
        conta_carteGiocatore++;
    }
    carteGiocatore=(*giocatoreTurno)->carteCfu;

    // Nel caso in cui le carte fossero piu di 3, limito la scelta a 3 secondo la regola dell effetto SCARTAE
    if(conta_carteGiocatore>=3){
        numero_carteDaScartare=3;
    }else{
        numero_carteDaScartare=conta_carteGiocatore;
    }

    if(numero_carteDaScartare>1){
        printf("\n[%s] seleziona quante carte desideri scartare(fino a %d carte) dalla tua mano,\n magari carte che non ritieni vantaggiose da tenere. Questo e' il tuo mazzo:  ",(*giocatoreTurno)->nomeutente,numero_carteDaScartare);

        // Stampa carte
        while (carteGiocatore!=NULL){
            printf("\n[%d]-> Nome: %s | Effetto: %s | Valore: %d",++conta,carteGiocatore->nome, Switch_Case_effettoCarta(carteGiocatore->nomeEffetti),carteGiocatore->valore);
            carteGiocatore=carteGiocatore->prossimaCartaCFU;
        }
        carteGiocatore=(*giocatoreTurno)->carteCfu;

// Offri la possibilita' di scelta della quantita di carte da scartare solo se il numero di carte nella mano del giocatore e' >=2
        do {
            printf("\nQuante carte? \nRisposta(numero tra 1 e %d): ",numero_carteDaScartare);
            scanf(" %d",&nCarta_daScartare);
            if(nCarta_daScartare<1 || nCarta_daScartare>numero_carteDaScartare){
                printf("\nIl numero selezionato non e' valido, ricorda che puoi scegliere fino a %d carte da scartare.\nRipeti",numero_carteDaScartare);
            }
        } while (nCarta_daScartare<1 || nCarta_daScartare>numero_carteDaScartare);

        printf("\nPerfetto, adesso seleziona [%d] carte.",nCarta_daScartare);

    }else{
        printf("\nHai solo una carta,verra' scartata soltanto la carta [%s]",carteGiocatore->nome);
    }


// Stampa delle carte nella mano del giocatore


    // Array dove terro' le scelte del giocatore, delle carte da SCARTARE


    if(numero_carteDaScartare!=1){
        // Nel caso in cui il giocatore ha avuto la possibilita di scegliere quante carte poter scartare, e quindi possiede piu' di una carta nella mano
        for (int i = 0; i < nCarta_daScartare; ++i) {
            int scelta=0;
            CarteCFU* temp=(*giocatoreTurno)->carteCfu;
             conta=0;
             bool confermaElimina=true;

            //stampa mazzo
            while (temp!=NULL){
                printf("\n[%d]-> Nome: %s | Effetto: %s | Valore: %d",++conta,temp->nome, Switch_Case_effettoCarta(temp->nomeEffetti),temp->valore);
                temp=temp->prossimaCartaCFU;
            }

            printf("\nCarta numero %d da eliminare: ", i + 1);
            scanf(" %d", &scelta);

                // Se una nuova scelta risulta uguale a una scelta precedente || la scelta non e' nel range del numero delle carte presenti nella mano del giocatore
                if ((scelta < 1 || scelta > conta)) {
                    confermaElimina=false;
                    i--;
                    printf("\nHai inserito un numero non valido.\nRipeti quest'ultima scelta");
                }
                if(confermaElimina==true){
                    char nome[DIM_CARATTERI];
                    int valore;
                    NomeEffetti nomeEffetti;

                    eliminaCartaDalMazzo(&(*giocatoreTurno)->carteCfu,nome,&valore,&nomeEffetti,scelta);

                    inserisciCfu_inTesta_nelMazzo(mazzoScarti,nome,valore,nomeEffetti);
                }



        }
    }else{
        // Nel caso in cui il giocatore avesse una carta da poter scartare e quindi la scelta della carta da poter scartare non puo essere effettuata,
        // pongo il valore del primo elemento dell array a 1(che corrisponde alla posizione dell unica carta nella mano del giocatore)
        int scelta=0;
        char nome[DIM_CARATTERI];
        int valore;
        NomeEffetti nomeEffetti;

        eliminaCartaDalMazzo(&(*giocatoreTurno)->carteCfu,nome,&valore,&nomeEffetti,scelta);

        inserisciCfu_inTesta_nelMazzo(mazzoScarti,nome,valore,nomeEffetti);

    }
}
void effetto_SCAMBIAP(IlGiocatore** giocatori, int numeroGiocatori, const int punteggi_primaDelTurno[]){
    int punteggiNelTurno[numeroGiocatori];
    IlGiocatore* giocatoriTemp=*giocatori;

    printf("\nIl punteggio MASSIMO e il punteggio MINIMO sono stati invertiti, quindi:");




    for (int i = 0; i < numeroGiocatori; ++i) {
        punteggiNelTurno[i]=giocatoriTemp->CFUaccumulati-punteggi_primaDelTurno[i];   // Calcolo il punteggio fatto alla fine del turno per ogni giocatore
        giocatoriTemp->CFUaccumulati=punteggi_primaDelTurno[i];                       // Imposto il punteggio di ogni giocatore, al punteggio del turno precedente
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    giocatoriTemp=*giocatori; // Reset puntatore

// Funzione che inverte il minimo e il massimo di un array, che in questo caso e' un array che contiene i punteggi in ordine fatti nell ultimo turno dai giocatori
    invertiMinMax(punteggiNelTurno,numeroGiocatori);

    for (int i = 0; i < numeroGiocatori; ++i) {
        giocatoriTemp->CFUaccumulati+=punteggiNelTurno[i];   // Imposto nuovamente i punteggi di questo tunro ma con il punteggio MASSIMO e quello MINIMO invertiti
        printf("\n-[%s] ha fatto +[%d] punti",giocatoriTemp->nomeutente,(giocatoriTemp->CFUaccumulati-punteggi_primaDelTurno[i]));
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
}
void effetto_SBIRCIA(CarteCFU** mazzoCfu,IlGiocatore** giocatoreTurno, CarteCFU** mazzoScarti){
    CarteCFU* temp_mazzoCfu=*mazzoCfu;
    CarteCFU* mazzoGiocatore=(*giocatoreTurno)->carteCfu;
    int nCarte_daSbirciare=2;
    int conta=0;
    int scelta=0;

    // Se il mazzo di pescaggio delle carte cfu ha solo una carta
    if(temp_mazzoCfu->prossimaCartaCFU==NULL){
        riempi_daMazzo_aMazzo(mazzoCfu,mazzoScarti);
        mescolaCarteCFU(mazzoCfu);
    }

    printf("\nSeleziona quale delle due carte in cima al mazzo CFU di pescaggio, vuoi pescare:");

    // Stampa prime due carte del mazzo di pescaggio
    for (int i = 0; i < nCarte_daSbirciare; ++i) {
        printf("\n[%d]-> Nome: %s | Effetto: %s | Valore: %d",++conta,temp_mazzoCfu->nome, Switch_Case_effettoCarta(temp_mazzoCfu->nomeEffetti),temp_mazzoCfu->valore);
        temp_mazzoCfu=temp_mazzoCfu->prossimaCartaCFU;
    }
    temp_mazzoCfu=*mazzoCfu;   // Reset puntatore

    // Scelta carta tra la prima e la seconda
    do{
        printf("\nNumero carta: ");
        scanf("%d",&scelta);
        if(scelta!=1 && scelta!=2){
            printf("La tua scelta e' errata, non e' ne 1 ne 2.\nRipeti!\n");
        }
    } while (scelta!=1 && scelta!=2);

    // Variabili per i dati della carta
    char nome[DIM_CARATTERI];
    int valore;
    NomeEffetti nomeEffetti;

    eliminaCartaDalMazzo(mazzoCfu,nome,&valore,&nomeEffetti,scelta);

    inserisciCfu_inTesta_nelMazzo(&(*giocatoreTurno)->carteCfu,nome,valore,nomeEffetti);
}



