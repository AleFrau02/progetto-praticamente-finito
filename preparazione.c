#include "libreria_funzioni.h"

/**PREPARAZIONE*/

//che include:
int numerogiocatori() {
    int numero;

    printf("Seleziona il numero di giocatori che parteciperanno a questa partita:");

    do {
        scanf(" %d", &numero);
        if (numero < 2 || numero > 4)printf("Il numero di giocatori selezionato non e' supportato.\nRipeti\n");
    } while (numero < 2 || numero > 4);

    return numero;
}

CarteCFU *leggiCfu() {
    CarteCFU *carteTesta = NULL;

    FILE *file = NULL;
    file = fopen("carte.txt", "r");
    if (file == NULL) {
        printf("Impossibile aprire il file delle carte");
        exit(EXIT_FAILURE);
    }

    bool continua = true;

    while (continua) {
        //variabili che verranno lette ad ogni lettura del file
        int numeroCarte=0;
        NomeEffetti nomeEffetti;
        int valore=0;
        char nome[DIM_CARATTERI];

        int a=fscanf(file,"%d %d %d %[^\n]",&numeroCarte,&nomeEffetti,&valore,nome);

        if(a==4){
            for (int i = 0; i < numeroCarte; ++i) {
                inserisciCfu_inCoda_nelMazzo(&carteTesta,nome,valore,nomeEffetti);
            }
        }else{
            continua = false;  //se fscanf non restituisce niente allora a varra' -1
        }
    }

    fclose(file);

    return carteTesta;
}

CarteOSTACOLO *leggiOSTACOLI() {
    CarteOSTACOLO *testa=NULL;

    FILE *file = NULL;
    file = fopen("ostacoli.txt", "r");
    if (file == NULL) {
        printf("Impossibile aprire il file degli ostacoli.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUMERO_TIPOLOGIA_OSTACOLI; ++i) {
        int countOstacoli_perTipo=0;                                  // Variabile per contenere i numeri del file che indicano la quantita di ostacoli per TIPO(studio,soppravvivenza,sociale,esami)
        fscanf(file, "%d\n", &countOstacoli_perTipo);   // Legge i numeri relattivi al totale degli ostacoli per TIPO

        int contaOstacoli=0;

        //quando contaOstacoli raggiungera' il numero degli ostacoli che viene letto nel file PRIMA dell'elenco di ogni tipologia di ostacoli
        while (contaOstacoli != countOstacoli_perTipo) {
            //variabili che verranno lette nel file
            char nome[DIM_CARATTERI];
            char descrizioneOSTACOLO[CARATTERIperDESCRIZIONE];
            TipoOstacoli tipoOstacoli=0;

            fscanf(file, "%32[^\n]\n", nome);
            fscanf(file, "%128[^\n]\n", descrizioneOSTACOLO);
            tipoOstacoli = i + 1;                                    // i+1 siccome nell'ENUM ho inizializzato i TIPI con valori 1,2,3,4 anziche' partire da 0

            inserisciOstaolo_inCoda_nelMazzo(&testa,nome,descrizioneOSTACOLO,tipoOstacoli);

            contaOstacoli++;
        }
    }

    fclose(file);

    return testa;
}

void leggiPERSONAGGI(Personaggio personaggi[]) {
    int i = 0;
    FILE *file = NULL;

    file = fopen("personaggi.txt", "r");
    if (file == NULL) {
        printf("Impossibile aprire il file dei personaggi.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %d %d %d %[^\n]",
                  &personaggi[i].BONUS_MALUS[0],
                  &personaggi[i].BONUS_MALUS[1],
                  &personaggi[i].BONUS_MALUS[2],
                  &personaggi[i].BONUS_MALUS[3],
                  personaggi[i].nome) == 5) {
        i++;  //finche c'e' questa sequenza di valori il fscanf dara 5
    }

    fclose(file);
}

void creaGiocatori(IlGiocatore** giocatori,Personaggio personaggi[],int numeroGiocatori){

    mischiaPersonaggi(personaggi,NUMERO_PERSONAGGI);

    for (int i = 0; i < numeroGiocatori; ++i) {
        char nome[DIM_CARATTERI];
        printf("\nSeleziona il nome del giocatore numero %d: ",i+1);
        scanf(" %31[^\n]s",nome);
        getchar();
        creaListaGiocatori(giocatori,nome,personaggi[i],0); // 0 siccome tutti i giocatori inizieranno con 0 punti
    }
}

void creaListaGiocatori(IlGiocatore** testa, char nome[], Personaggio personaggio, int CFUaccumulati) {
    // Crea un nuovo nodo (giocatore)
    IlGiocatore* nuovoGiocatore = (IlGiocatore*)malloc(sizeof(IlGiocatore));
    if (nuovoGiocatore == NULL) {
        printf("Errore di allocazione della memoria.\n");
        return;
    }

    // Inizializzazione del nuovo giocatore
    strcpy(nuovoGiocatore->nomeutente, nome);
    nuovoGiocatore->personaggio = personaggio;
    nuovoGiocatore->CFUaccumulati = CFUaccumulati;
    nuovoGiocatore->carteCfu = NULL;         // Imposta a NULL, sara' popolato in seguito
    nuovoGiocatore->carteOstacolo = NULL;    // Imposta a NULL, sara' popolato in seguito
    nuovoGiocatore->GIOCATOREsuccessivo = NULL;

    // Aggiungi il nuovo giocatore in coda alla lista
    if (*testa == NULL) {
        // Se la lista è vuota, il nuovo giocatore diventa la testa della lista
        *testa = nuovoGiocatore;
    } else {
        // Altrimenti, trova l'ultimo nodo della lista
        IlGiocatore* corrente = *testa;
        while (corrente->GIOCATOREsuccessivo != NULL) {
            corrente = corrente->GIOCATOREsuccessivo;
        }
        // Collega l'ultimo nodo al nuovo giocatore
        corrente->GIOCATOREsuccessivo = nuovoGiocatore;
    }
}




