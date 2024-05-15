#include "libreria_funzioni.h"

/** PESCA UNA CARTA DAL MAZZO E LO AGGIUNGE IN TESTA NEL MAZZO RICEVENTE, LA PRIMA CFU E LA SECONDA OSTACOLI */
void pescaggioCartaCfu(CarteCFU** mazzoCfu, CarteCFU** mazzoRicevente) {
    if (*mazzoCfu == NULL) {
        printf("Il mazzo CFU e' vuoto, non ci sono carte da pescare.\n");
        return;  // Non ci sono carte da pescare
    }

    // Ottieni i dettagli della carta da pescare
    char nome[DIM_CARATTERI];
    strcpy(nome, (*mazzoCfu)->nome);
    int valore = (*mazzoCfu)->valore;
    NomeEffetti nomeEffetti = (*mazzoCfu)->nomeEffetti;

    // Rimuovi la carta dalla testa del mazzo CFU
    eliminaCfu_inTesta(mazzoCfu);

    // Inserisci la carta pescata in coda al mazzo del giocatore
    inserisciCfu_inTesta_nelMazzo(mazzoRicevente, nome, valore, nomeEffetti);
}
void pescaggioCartaOstacolo(CarteOSTACOLO** mazzoOstacoli, CarteOSTACOLO** mazzoRicevente){
    if (*mazzoOstacoli == NULL) {
        printf("Il mazzo Ostacoli è vuoto, non ci sono carte da pescare.\n");
        exit(EXIT_FAILURE);  // Non ci sono carte da pescare
    }

    // Ottieni i dettagli della carta da pescare
    char nome[DIM_CARATTERI];
    strcpy(nome, (*mazzoOstacoli)->nome);
    char descrizione[CARATTERIperDESCRIZIONE];
    strcpy(descrizione,(*mazzoOstacoli)->descrizioneOSTACOLO);
    TipoOstacoli tipoOstacoli=(*mazzoOstacoli)->tipoOstacoli;

    // Rimuovi la carta dalla testa del mazzo Ostacoli
    eliminaOstacolo_inTesta(mazzoOstacoli);

    // Inserisci la carta pescata in coda al mazzo
    inserisciOstaolo_inCoda_nelMazzo(mazzoRicevente, nome, descrizione,tipoOstacoli);
}


/** INSERISCI UN NUOVO NODO CON I DATI MANDATI COME PARAMETRO, LA PRIMA NELLA CODA DEL MAZZO E LA SECONDA IN TESTA */
void inserisciCfu_inCoda_nelMazzo(CarteCFU** mazzo, char nome[], int valore, NomeEffetti nomeEffetti) {
    // Creazione della nuova carta
    CarteCFU* nuovaCarta = (CarteCFU*)malloc(sizeof(CarteCFU));
    if (nuovaCarta == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della nuova carta
    strcpy(nuovaCarta->nome, nome);
    nuovaCarta->valore = valore;
    nuovaCarta->nomeEffetti = nomeEffetti;
    nuovaCarta->prossimaCartaCFU = NULL;  // Nessuna carta successiva per ora

    if (*mazzo == NULL) {
        // Se il mazzo è vuoto, la nuova carta diventa la testa
        *mazzo = nuovaCarta;
    } else {
        // Altrimenti, navigare fino all'ultimo nodo del mazzo
        CarteCFU* current = *mazzo;
        while (current->prossimaCartaCFU != NULL) {
            current = current->prossimaCartaCFU;
        }
        // Inserire la nuova carta in coda
        current->prossimaCartaCFU = nuovaCarta;
    }
}
void inserisciCfu_inTesta_nelMazzo(CarteCFU** mazzo, char nome[], int valore, NomeEffetti nomeEffetti) {
    // Creazione della nuova carta
    CarteCFU* nuovaCarta = (CarteCFU*)malloc(sizeof(CarteCFU));
    if (nuovaCarta == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della nuova carta
    strcpy(nuovaCarta->nome, nome);
    nuovaCarta->valore = valore;
    nuovaCarta->nomeEffetti = nomeEffetti;
    nuovaCarta->prossimaCartaCFU = *mazzo;  // La nuova carta punta alla vecchia testa

    // Aggiorna la testa del mazzo alla nuova carta
    *mazzo = nuovaCarta;
}
// STESSA COSA DELLE PRECEDNTI MA CON OSTACOLI
void inserisciOstaolo_inCoda_nelMazzo(CarteOSTACOLO** mazzo,char nome[], char descrizioneOSTACOLO[],TipoOstacoli tipoOstacoli){
// Creazione della nuova carta ostacolo
    CarteOSTACOLO* nuovoOstacolo = (CarteOSTACOLO*)malloc(sizeof(CarteOSTACOLO));
    if (nuovoOstacolo == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della nuova carta ostacolo
    strcpy(nuovoOstacolo->nome, nome);
    strcpy(nuovoOstacolo->descrizioneOSTACOLO, descrizioneOSTACOLO);
    nuovoOstacolo->tipoOstacoli = tipoOstacoli;
    nuovoOstacolo->prossimaCartaOSTACOLO = NULL;

    if (*mazzo == NULL) {
        // Se il mazzo è vuoto, il nuovo ostacolo diventa la testa
        *mazzo = nuovoOstacolo;
    } else {
        // Altrimenti, navigare fino all'ultimo nodo del mazzo
        CarteOSTACOLO* current = *mazzo;
        while (current->prossimaCartaOSTACOLO != NULL) {
            current = current->prossimaCartaOSTACOLO;
        }
        // Inserire il nuovo ostacolo in coda
        current->prossimaCartaOSTACOLO = nuovoOstacolo;
    }
}
void inserisciOstacolo_inTesta_nelMazzo(CarteOSTACOLO** mazzo, char nome[], char descrizioneOSTACOLO[], TipoOstacoli tipoOstacoli) {
    // Creazione della nuova carta ostacolo
    CarteOSTACOLO* nuovoOstacolo = (CarteOSTACOLO*)malloc(sizeof(CarteOSTACOLO));
    if (nuovoOstacolo == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della nuova carta ostacolo
    strcpy(nuovoOstacolo->nome, nome);
    strcpy(nuovoOstacolo->descrizioneOSTACOLO, descrizioneOSTACOLO);
    nuovoOstacolo->tipoOstacoli = tipoOstacoli;
    nuovoOstacolo->prossimaCartaOSTACOLO = *mazzo;  // La nuova carta punta alla vecchia testa

    // Aggiorna la testa del mazzo alla nuova carta
    *mazzo = nuovoOstacolo;
}


/** ELIMINA L'ELEMENTO IN CODA E IN TESTA */
void eliminaCfu_inCoda(CarteCFU** mazzo) {
    if (*mazzo == NULL) {
        // Il mazzo è vuoto, non c'è nulla da eliminare
        return;
    }

    if ((*mazzo)->prossimaCartaCFU == NULL) {
        // Solo un elemento nel mazzo
        free(*mazzo);
        *mazzo = NULL;
        return;
    }

    // Trovare il penultimo elemento
    CarteCFU* current = *mazzo;
    while (current->prossimaCartaCFU->prossimaCartaCFU != NULL) {
        current = current->prossimaCartaCFU;
    }

    // Eliminare l'ultimo elemento
    free(current->prossimaCartaCFU);
    current->prossimaCartaCFU = NULL;
}
void eliminaCfu_inTesta(CarteCFU** mazzo) {
    if (*mazzo == NULL) {
        // Il mazzo è vuoto, non c'è nulla da eliminare
        return;
    }

    // Memorizza il secondo nodo
    CarteCFU* temp = (*mazzo)->prossimaCartaCFU;

    // Libera la memoria dell'elemento in testa
    free(*mazzo);

    // Imposta il nuovo inizio del mazzo
    *mazzo = temp;
}
// STESSA COSA DELLE PRECEDNTI MA CON OSTACOLI
void eliminaOstacolo_inCoda(CarteOSTACOLO** mazzo) {
    if (*mazzo == NULL) {
        // Il mazzo è vuoto, non c'è nulla da eliminare
        return;
    }

    if ((*mazzo)->prossimaCartaOSTACOLO == NULL) {
        // Solo un elemento nel mazzo
        free(*mazzo);
        *mazzo = NULL;
        return;
    }

    // Trovare il penultimo elemento
    CarteOSTACOLO* current = *mazzo;
    while (current->prossimaCartaOSTACOLO->prossimaCartaOSTACOLO != NULL) {
        current = current->prossimaCartaOSTACOLO;
    }

    // Eliminare l'ultimo elemento
    free(current->prossimaCartaOSTACOLO);
    current->prossimaCartaOSTACOLO = NULL;
}
void eliminaOstacolo_inTesta(CarteOSTACOLO** mazzo) {
    if (*mazzo == NULL) {
        // Il mazzo è vuoto, non c'è nulla da eliminare
        return;
    }

    // Memorizza il secondo nodo
    CarteOSTACOLO* temp = (*mazzo)->prossimaCartaOSTACOLO;

    // Libera la memoria dell'elemento in testa
    free(*mazzo);

    // Imposta il nuovo inizio del mazzo
    *mazzo = temp;
}


/** MISCHIANO GLI ELEMENTI DELLA LISTA IN ORDINE CASUALE, LA PRIMA PER CFU E LA SECONDA OSTACOLI */
void mescolaCarteCFU(CarteCFU** mazzo) {
    // Conta il numero di carte nel mazzo
    int contaCarte = 0;
    CarteCFU* current = *mazzo;
    while (current != NULL) {
        contaCarte++;
        current = current->prossimaCartaCFU;
    }

    if (contaCarte > 1) {
        // Trasferisci le carte in un array
        CarteCFU** array = malloc(contaCarte * sizeof(CarteCFU*));
        current = *mazzo;
        for (int i = 0; i < contaCarte; i++) {
            array[i] = current;
            current = current->prossimaCartaCFU;
        }

        // Mescola l'array
        for (int i = 0; i < contaCarte - 1; i++) {
            int j = i + (rand() % (contaCarte - i)) ;
            CarteCFU* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }

        // Ricostruisci il mazzo dalla versione mescolata dell'array
        *mazzo = array[0];
        current = *mazzo;
        for (int i = 1; i < contaCarte; i++) {
            current->prossimaCartaCFU = array[i];
            current = current->prossimaCartaCFU;
        }
        current->prossimaCartaCFU = NULL;

        free(array);
    }
}
void mescolaCarteOSTACOLO(CarteOSTACOLO** mazzo) {
    // Conta il numero di ostacoli nel mazzo
    int contaCarte = 0;
    CarteOSTACOLO* current = *mazzo;
    while (current != NULL) {
        contaCarte++;
        current = current->prossimaCartaOSTACOLO;
    }

    if (contaCarte > 1) {
        // Trasferisci gli ostacoli in un array
        CarteOSTACOLO** array = malloc(contaCarte * sizeof(CarteOSTACOLO*));
        current = *mazzo;
        for (int i = 0; i < contaCarte; i++) {
            array[i] = current;
            current = current->prossimaCartaOSTACOLO;
        }

        // Mescola l'array
        for (int i = 0; i < contaCarte - 1; i++) {
            int j=i + (rand() % (contaCarte - i));
            CarteOSTACOLO* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }

        // Ricostruisci il mazzo dalla versione mescolata dell'array
        *mazzo = array[0];
        current = *mazzo;
        for (int i = 1; i < contaCarte; i++) {
            current->prossimaCartaOSTACOLO = array[i];
            current = current->prossimaCartaOSTACOLO;
        }
        current->prossimaCartaOSTACOLO = NULL;

        free(array);
    }
}


/** MISCHIANO GLI ELEMENTI DELLA LISTA IN ORDINE CASUALE, LA PRIMA PER CFU E LA SECONDA OSTACOLI */
void eliminaMazzoCFU(CarteCFU** mazzo) {
    CarteCFU* current = *mazzo;
    CarteCFU* next;

    while (current != NULL) {
        next = current->prossimaCartaCFU;  // Salva il riferimento alla prossima carta
        free(current);                     // Libera la memoria della carta corrente
        current = next;                    // Passa alla prossima carta
    }

    *mazzo = NULL;  // Assicurati che il puntatore al mazzo sia impostato su NULL dopo la pulizia
}
void eliminaMazzoOstacoli(CarteOSTACOLO** mazzo) {
    CarteOSTACOLO* current = *mazzo;
    CarteOSTACOLO* next;

    while (current != NULL) {
        next = current->prossimaCartaOSTACOLO;  // Salva il riferimento alla prossima carta
        free(current);                          // Libera la memoria della carta corrente
        current = next;                         // Passa alla prossima carta
    }

    *mazzo = NULL;  // Assicurati che il puntatore al mazzo sia impostato su NULL dopo la pulizia
}



//servira' per eliminare la carta che viene scartata da un giocatore in un turno
void eliminaCartaDalMazzo(CarteCFU** mazzo, char* nome, int* valore, NomeEffetti* nomeEffetti,const int posizione) {
    if (mazzo == NULL || *mazzo == NULL || posizione < 1) {
        return; // Controlla se il mazzo è vuoto o la posizione non è valida
    }

    CarteCFU* current = *mazzo;
    CarteCFU* prev = NULL;
    int currentIndex = 1;  // Inizia dalla testa, che è considerata posizione 1

    // Trova la carta alla posizione specificata
    while (current != NULL && currentIndex < posizione) {
        prev = current;
        current = current->prossimaCartaCFU;
        currentIndex++;
    }

    // Controlla se la posizione specificata è valida
    if (current == NULL) {
        return; // La posizione specificata è oltre la lunghezza del mazzo
    }

    // Salva i dati della carta nei parametri passati
    strncpy(nome, current->nome, DIM_CARATTERI);  // Usa strncpy per copiare il nome con sicurezza
    *valore = current->valore;                    // Copia il valore
    *nomeEffetti = current->nomeEffetti;          // Copia l'effetto

    // Rimuovi la carta dal mazzo
    if (prev == NULL) {
        // La carta da eliminare è la prima nella lista
        *mazzo = current->prossimaCartaCFU;
    } else {
        // La carta da eliminare è nel mezzo o alla fine del mazzo
        prev->prossimaCartaCFU = current->prossimaCartaCFU;
    }

    // Libera la memoria occupata dalla carta
    free(current);
}

/** STAMPANO I MAZZI DAL PUNTATORE CHE SI MANDA COME PARAMETRO FINO ALLA FINE DELLA LISTA */
void stampaMazzo(CarteCFU* mazzo) {
    if (mazzo == NULL) {
        printf("Il mazzo è vuoto.\n");
        return;
    }

    CarteCFU* current = mazzo;
    while (current != NULL) {
        printf("Carta: %s\n", current->nome);
        printf("Valore: %d\n", current->valore);
        printf("Effetto: %s\n\n", Switch_Case_effettoCarta(current->nomeEffetti));

        current = current->prossimaCartaCFU;
    }
}
void stampaOstacoli(CarteOSTACOLO* mazzo) {
    if (mazzo == NULL) {
        printf("Il mazzo di ostacoli è vuoto.\n");
        return;
    }

    CarteOSTACOLO* current = mazzo;
    while (current != NULL) {
        printf("Nome Ostacolo: %s\n", current->nome);
        printf("Descrizione: %s\n", current->descrizioneOSTACOLO);
        printf("Tipo di Ostacolo: %s\n\n", Switch_Case_tipoOstacoli(current->tipoOstacoli));

        current = current->prossimaCartaOSTACOLO;
    }
}
void stampaGiocatori(const IlGiocatore* testa) {
    if (testa == NULL) {
        printf("Non ci sono giocatori nella lista.\n");
        return;
    }

    const IlGiocatore* corrente = testa;
    while (corrente != NULL) {
        printf("Nome utente: %s\n", corrente->nomeutente);
        printf("Personaggio: %s\n", corrente->personaggio.nome);  // Assumendo che Personaggio abbia un campo 'nome'
        printf("CFU Accumulati: %d\n", corrente->CFUaccumulati);

        stampaMazzo(corrente->carteCfu);
        printf("---------------------\n");
        corrente = corrente->GIOCATOREsuccessivo;
    }
}


/** MISCHIA L'ARRAY DEI PERSONAGGI */
void mischiaPersonaggi(Personaggio personaggi[], int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);  // Genera un indice casuale tra 0 e i

            // Scambia personaggi[i] con personaggi[j] usando una variabile temporanea di tipo Personaggio
            Personaggio temp = personaggi[i];
            personaggi[i] = personaggi[j];
            personaggi[j] = temp;
        }
    }
}


/** RESTITUISCONO LA "SCRITTA" ALLA QUALE SI RIFERISCONO GLI ENUM DEL PROGRAMMA */
char *Switch_Case_effettoCarta(int numero) {
    char *nomeEffetto = NULL;
    switch (numero) {
        case NESSUNO:
            nomeEffetto = "NESSUNO";
            break;
        case SCARTAP:
            nomeEffetto = "SCARTAP";
            break;
        case RUBA:
            nomeEffetto = "RUBA";
            break;
        case SCAMBIADS:
            nomeEffetto = "SCAMBIADS";
            break;
        case SCARTAE:
            nomeEffetto = "SCARTAE";
            break;
        case SCARTAC:
            nomeEffetto = "SCARTAC";
            break;
        case SCAMBIAP:
            nomeEffetto = "SCAMBIAP";
            break;
        case DOPPIOE:
            nomeEffetto = "DOPPIOE";
            break;
        case SBIRCIA:
            nomeEffetto = "SBIRCIA";
            break;
        case SCAMBIAC:
            nomeEffetto = "SCAMBIAC";
            break;
        case ANNULLA:
            nomeEffetto = "ANNULLA";
            break;
        case AUMENTA:
            nomeEffetto = "AUMENTA";
            break;
        case DIMINUISCI:
            nomeEffetto = "DIMINUISCI";
            break;
        case INVERTI:
            nomeEffetto = "INVERTI";
            break;
        case SALVA:
            nomeEffetto = "SALVA";
            break;
        case DIROTTA:
            nomeEffetto = "DIROTTA";
            break;
        default:
            printf("Errore in Switch_Case_effettoCarta.\n");
            exit(EXIT_FAILURE);
    }
    return nomeEffetto;
}
char *Switch_Case_tipoOstacoli(int numero) {
    char *nome;
    switch (numero) {
        case STUDIO:
            nome = "Studio";
            break;
        case SOPRAVVIVENZA:
            nome = "Sopravvivenza";
            break;
        case SOCIALE:
            nome = "Sociale";
            break;
        case ESAME:
            nome = "Esame";
            break;
        default:
            printf("Errore in Switch_Case_tipoOstacoli.\n");
            break;
    }
    return nome;
}

/** Scambia due mazzi */
void scambiaMazzi(CarteCFU **mazzo1, CarteCFU **mazzo2) {
    CarteCFU *temp = *mazzo1;
    *mazzo1 = *mazzo2;
    *mazzo2 = temp;
}


void trasferisciOstacoloInCoda(CarteOSTACOLO** mazzoRicevente, CarteOSTACOLO** cartaOstacolo) {
    if (cartaOstacolo == NULL || *cartaOstacolo == NULL) {
        printf("Nessun ostacolo da trasferire.\n");
        return;
    }

    // Creazione della nuova carta ostacolo
    CarteOSTACOLO* nuovoOstacolo = (CarteOSTACOLO*)malloc(sizeof(CarteOSTACOLO));
    if (nuovoOstacolo == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Copia dei dati da cartaOstacolo a nuovoOstacolo
    strcpy(nuovoOstacolo->nome, (*cartaOstacolo)->nome);
    strcpy(nuovoOstacolo->descrizioneOSTACOLO, (*cartaOstacolo)->descrizioneOSTACOLO);
    nuovoOstacolo->tipoOstacoli = (*cartaOstacolo)->tipoOstacoli;
    nuovoOstacolo->prossimaCartaOSTACOLO = NULL;

    // Inserimento del nuovo ostacolo in coda al mazzoRicevente
    if (*mazzoRicevente == NULL) {
        *mazzoRicevente = nuovoOstacolo; // Se il mazzoRicevente è vuoto, nuovoOstacolo diventa la testa
    } else {
        CarteOSTACOLO* current = *mazzoRicevente;
        while (current->prossimaCartaOSTACOLO != NULL) {
            current = current->prossimaCartaOSTACOLO;
        }
        current->prossimaCartaOSTACOLO = nuovoOstacolo; // Inserimento in coda
    }

    // Liberazione della memoria occupata dall'ostacolo in cartaOstacolo e impostazione a NULL
    free(*cartaOstacolo);
    *cartaOstacolo = NULL;
}

void trasferisciTutteLeCarteCFU(CarteCFU **destinazione, CarteCFU *sorgente) {
    CarteCFU *current = sorgente;
    while (current != NULL) {
        CarteCFU *next = current->prossimaCartaCFU; // Salviamo il riferimento al prossimo
        current->prossimaCartaCFU = NULL; // Isoliamo l'elemento corrente
        if (*destinazione == NULL) {
            *destinazione = current; // Se il mazzo è vuoto, diventa la testa
        } else {
            CarteCFU *temp = *destinazione;
            while (temp->prossimaCartaCFU != NULL) {
                temp = temp->prossimaCartaCFU; // Trova l'ultimo elemento
            }
            temp->prossimaCartaCFU = current; // Aggiungi in coda
        }
        current = next; // Passa al prossimo elemento
    }
}
void trasferisciTuttiGliOstacoli(CarteOSTACOLO **destinazione, CarteOSTACOLO *sorgente) {
    CarteOSTACOLO *current = sorgente;
    while (current != NULL) {
        CarteOSTACOLO *next = current->prossimaCartaOSTACOLO;
        current->prossimaCartaOSTACOLO = NULL;
        if (*destinazione == NULL) {
            *destinazione = current;
        } else {
            CarteOSTACOLO *temp = *destinazione;
            while (temp->prossimaCartaOSTACOLO != NULL) {
                temp = temp->prossimaCartaOSTACOLO;
            }
            temp->prossimaCartaOSTACOLO = current;
        }
        current = next;
    }
}
void eliminaGiocatore(IlGiocatore **giocatori, IlGiocatore *giocatoreDaEliminare, CarteCFU **mazzoCfu, CarteOSTACOLO **mazzoOstacoli) {
    if (giocatori == NULL || *giocatori == NULL || giocatoreDaEliminare == NULL) {
        printf("Parametri non validi.\n");
        return;
    }

    IlGiocatore *current = *giocatori;
    IlGiocatore *prev = NULL;

    // Trova il giocatore nella lista e mantieni il riferimento al precedente
    while (current != NULL && current != giocatoreDaEliminare) {
        prev = current;
        current = current->GIOCATOREsuccessivo;
    }

    if (current == NULL) {
        printf("Giocatore non trovato nella lista.\n");
        return;
    }

    // Trasferisci le carte CFU e OSTACOLO ai mazzi principali
    trasferisciTutteLeCarteCFU(mazzoCfu, current->carteCfu);
    trasferisciTuttiGliOstacoli(mazzoOstacoli, current->carteOstacolo);

    // Rimuovi il giocatore dalla lista
    if (prev == NULL) {
        *giocatori = current->GIOCATOREsuccessivo;  // Il giocatore è la testa della lista
    } else {
        prev->GIOCATOREsuccessivo = current->GIOCATOREsuccessivo;
    }

    // Libera la memoria allocata per il giocatore
    free(current);
}


/** VERIFICA LA PRESENZA DI CARTE ISTANTANEE NEL MAZZO */
bool verifica_carteIstantanee_mazzoGiocatore(CarteCFU** mazzoGiocatore){
    CarteCFU* temp=*mazzoGiocatore;
    int conta_carteIstantanee=0;

    while (temp!=NULL){
        if((temp->valore==0 && strcmp(temp->nome,"Monitor")!=0) && (temp->nomeEffetti!=SALVA && temp->nomeEffetti!=DIROTTA)){
            conta_carteIstantanee++;
        }
        temp=temp->prossimaCartaCFU;
    }
    // Almeno una carta istantanea nel mazzo per true
    if(conta_carteIstantanee>=1){
        return true;
    }else{
        return false;
    }
}

/** VERIFICA LA PRESENZA DI CARTE CFU PUNTO NEL MAZZO */
bool verifica_cartePunto_mazzoGiocatore(CarteCFU** mazzoGiocatore){
    CarteCFU* temp=*mazzoGiocatore;
    int conta_cartePunto=0;

    while (temp!=NULL){
        if(temp->valore!=0 ||(temp->valore==0 && strcmp(temp->nome,"Monitor")==0)){
            conta_cartePunto++;
        }
        temp=temp->prossimaCartaCFU;
    }
    // Almeno una carta istantanea nel mazzo per true
    if(conta_cartePunto>=1){
        return true;
    }else{
        return false;
    }
}

/** VERIFICA LA PRESENZA DI CARTE ISTANTANEE CON EFFETTO SALVA O DIROTTA NEL MAZZO */
bool verifica_SALVA_DIROTTA(CarteCFU** mazzoGiocatore){
    CarteCFU* mazzoTemp=*mazzoGiocatore;

    // Alla prima carta del mazzo con effetto SALVA o DIROTTA ritornera true
    while(mazzoTemp!=NULL){
        if(mazzoTemp->nomeEffetti==SALVA || mazzoTemp->nomeEffetti==DIROTTA){
            return true;
        }
        mazzoTemp=mazzoTemp->prossimaCartaCFU;
    }


    return false;
}

/** RIEMPIE PER INTERO DA UN MAZZO ALL ALTRO, NE SVUOTA UNO E RIEMPIE L ALTRO(ANCHE SE NON VUOTO) */
void riempi_daMazzo_aMazzo(CarteCFU** mazzoRicevente, CarteCFU** mazzoPescato){
    while (*mazzoPescato!=NULL){
        pescaggioCartaCfu(mazzoPescato, mazzoRicevente);
    }
}


void trasferisciCarta(CarteCFU **mazzoRicevente, CarteCFU **mazzoDonante, int posizione) {
    if (mazzoDonante == NULL || *mazzoDonante == NULL || posizione < 1) {
        printf("Mazzo donante vuoto o posizione non valida.\n");
        return;
    }

    CarteCFU *current = *mazzoDonante;
    CarteCFU *prev = NULL;
    int currentPosition = 1;

    // Trova la carta da trasferire
    while (current != NULL && currentPosition < posizione) {
        prev = current;
        current = current->prossimaCartaCFU;
        currentPosition++;
    }

    if (current == NULL) {
        printf("Posizione oltre il limite del mazzo donante.\n");
        return;
    }

    // Rimuovi la carta dal mazzo donante
    if (prev == NULL) {
        *mazzoDonante = current->prossimaCartaCFU;  // Rimuovi la testa
    } else {
        prev->prossimaCartaCFU = current->prossimaCartaCFU;  // Rimuovi da posizione intermedia
    }

    // Inserisci la carta nel mazzo ricevente in coda
    current->prossimaCartaCFU = NULL;  // Isolare la carta estratta
    if (*mazzoRicevente == NULL) {
        *mazzoRicevente = current;  // Il mazzo ricevente è vuoto, la carta diventa la nuova testa
    } else {
        CarteCFU *tail = *mazzoRicevente;
        while (tail->prossimaCartaCFU != NULL) {
            tail = tail->prossimaCartaCFU;  // Trova l'ultimo elemento
        }
        tail->prossimaCartaCFU = current;  // Aggiungi la carta in coda
    }
}

void invertiPosizione_carteMazzo(CarteCFU** mazzo, int posizione1, int posizione2) {
    if (mazzo == NULL || *mazzo == NULL || posizione1 < 1 || posizione2 < 1 || posizione1 == posizione2) {
        return; // Controlla se il mazzo è vuoto o le posizioni non sono valide o sono uguali
    }

    CarteCFU* carta1 = NULL;
    CarteCFU* carta2 = NULL;
    CarteCFU* prev1 = NULL;
    CarteCFU* prev2 = NULL;
    CarteCFU* current = *mazzo;
    int currentIndex = 1;

    // Trova le due carte e i loro nodi precedenti
    while (current != NULL && (carta1 == NULL || carta2 == NULL)) {
        if (currentIndex == posizione1) {
            carta1 = current;
            prev1 = (currentIndex == 1) ? NULL : prev1;
        } else if (currentIndex == posizione2) {
            carta2 = current;
            prev2 = (currentIndex == 1) ? NULL : prev2;
        }
        if (carta1 == NULL || carta2 == NULL) {
            prev1 = (currentIndex == posizione1) ? prev1 : current;
            prev2 = (currentIndex == posizione2) ? prev2 : current;
        }
        current = current->prossimaCartaCFU;
        currentIndex++;
    }

    // Se una delle due carte non è stata trovata, termina la funzione
    if (carta1 == NULL || carta2 == NULL) {
        return;
    }

    // Scambia i nodi
    if (prev1) prev1->prossimaCartaCFU = carta2;
    if (prev2) prev2->prossimaCartaCFU = carta1;

    // Scambia i puntatori delle carte successive
    CarteCFU* temp = carta1->prossimaCartaCFU;
    carta1->prossimaCartaCFU = carta2->prossimaCartaCFU;
    carta2->prossimaCartaCFU = temp;

    // Aggiusta la testa del mazzo se necessario
    if (posizione1 == 1) *mazzo = carta2;
    if (posizione2 == 1) *mazzo = carta1;
}

void stampaVincenti_Turno(int numeroVincenti, IlGiocatore** giocatori, const int perdenti0_vincitori1[]){
    IlGiocatore* giocatoriTemp=*giocatori;
    int conta=0;


    if (numeroVincenti==1){
        printf("\nIl VINCENTE del turno e' ");
    }else{
        printf("\nI VINCENTI del turno sono ");
    }


    // Stampa il nome del/dei giocatore/i
    while (giocatoriTemp!=NULL){
        if(perdenti0_vincitori1[conta]==VINCENTI){
            printf("[%s]",giocatoriTemp->nomeutente);

            if(conta<numeroVincenti){
                if((conta+1)==numeroVincenti){
                    printf(" e ");
                }else{
                    printf(", ");
                }
            }
        }

        conta++;
        giocatoriTemp=giocatoriTemp->GIOCATOREsuccessivo;
    }
    printf("\n\n");
}

void invertiMinMax(int array[], int dimensine) {
    if (dimensine < 2) return;  // Se l'array ha meno di due elementi, non fare nulla

    int minIndice = 0;  // Indice iniziale dell'elemento più piccolo
    int maxIndice = 0;  // Indice iniziale dell'elemento più grande

    // Trova gli indici dell'elemento minimo e massimo
    for (int i = 1; i < dimensine; i++) {
        if (array[i] < array[minIndice]) {
            minIndice = i;
        }
        if (array[i] > array[maxIndice]) {
            maxIndice = i;
        }
    }

    // Scambia gli elementi in minIndex e maxIndex
    int temp = array[minIndice];
    array[minIndice] = array[maxIndice];
    array[maxIndice] = temp;
}

void stampaCarteOstacolo(const CarteOSTACOLO *carta) {
    if(carta==NULL){
        printf("Nessuna carta ostacolo\n");
    }
    while (carta != NULL) {
        printf("Nome: %s\t", carta->nome);
        printf("Descrizione: %s\t", carta->descrizioneOSTACOLO);
        printf("Tipo: %s\t", Switch_Case_tipoOstacoli(carta->tipoOstacoli));  // Supponendo che TipoOstacoli sia stampabile come int
        carta = carta->prossimaCartaOSTACOLO;
        printf("\n");
    }
}

void stampaCarteCFU(const CarteCFU *carta) {
    while (carta != NULL) {
        printf("Nome: %s\t", carta->nome);
        printf("Valore: %d\t", carta->valore);
        printf("Effetto: %s\t", Switch_Case_effettoCarta(carta->nomeEffetti));  // Supponendo che NomeEffetti sia stampabile come int
        carta = carta->prossimaCartaCFU;
        printf("\n");
    }
}

void stampaGiocatore(const IlGiocatore *giocatore) {
    printf("Giocatore: %s\n", giocatore->nomeutente);
    printf("Personaggio: %s\n", giocatore->personaggio.nome);
    printf("BONUS/MALUS: [");
    for (int i = 0; i < NUMERO_TIPOLOGIA_OSTACOLI; i++) {
        printf("%d", giocatore->personaggio.BONUS_MALUS[i]);
        if (i < NUMERO_TIPOLOGIA_OSTACOLI - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("CFU Accumulati: %d\n", giocatore->CFUaccumulati);

    // Stampa delle carte CFU
    printf("Carte CFU:\n");
    stampaCarteCFU(giocatore->carteCfu);

    // Stampa delle carte ostacolo
    printf("Carte Ostacolo:\n");
    stampaCarteOstacolo(giocatore->carteOstacolo);
}















