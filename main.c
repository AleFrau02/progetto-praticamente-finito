//Nome: Alessio Frau (a.frau66@studenti.unica.it)
//Matricola: 60/61/66487
//Tipologia progetto:MEDIO


#include "libreria_funzioni.h"


int main(void){
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));
    //dichiarazione delle variabili
    int numerodeigiocatori=0;
    Personaggio personaggi[NUMERO_PERSONAGGI];
    CarteOSTACOLO *OSTACOLI=NULL;
    CarteCFU *CFU=NULL;
    IlGiocatore *giocatori = NULL;

    PREPARAZIONE_gioco(&giocatori,personaggi,&CFU,&OSTACOLI,&numerodeigiocatori);

    GIOCO(&giocatori,&CFU,&OSTACOLI,&numerodeigiocatori);

    return 0;
}



void PREPARAZIONE_gioco(IlGiocatore** giocatori, Personaggio personaggi[], CarteCFU** CFU, CarteOSTACOLO** OSTACOLI, int* numerodeigiocatori){
    // Lettura dei file
    *CFU=leggiCfu();
    *OSTACOLI=leggiOSTACOLI();
    leggiPERSONAGGI(personaggi);
// Numero e creazione dei giocatori
    *numerodeigiocatori = numerogiocatori();
    creaGiocatori(giocatori,personaggi,*numerodeigiocatori);
    // Mischiaggio mazzi
    mescolaCarteCFU(CFU);
    mescolaCarteOSTACOLO(OSTACOLI);
// Distribuzione 5 carte per giocatore
    IlGiocatore* temp=*giocatori;
    while (temp!=NULL){
        for (int i = 0; i < NUMERO_CARTE_INIZIALI; ++i) {
            pescaggioCartaCfu(CFU,&temp->carteCfu);
        }
        temp=temp->GIOCATOREsuccessivo;
    }
}





void GIOCO(IlGiocatore** giocatori, CarteCFU** CFU, CarteOSTACOLO** OSTACOLI,int* numeroGiocatori){
    CarteOSTACOLO* ostacoloTurno=NULL;
    CarteCFU* carteTurno_Scarti=NULL;
    CarteCFU* mazzoScarti=NULL;
    int numero_Turno=0;


    // TURNO
    bool continua=true;
    while (continua) {
        pescaggioCartaOstacolo(OSTACOLI,&ostacoloTurno);
        printf("\n\nTurno numero %d\n\n",++numero_Turno);
        printf("OSTACOLO PESCATO IN QUESTO TURNO:\n");

        disegnoHappyLittleStudents();
        stampaDatiGiocatori(giocatori, *numeroGiocatori);
        stampaOstacoli(ostacoloTurno);
        sceltaAzione(giocatori,CFU,&continua,&carteTurno_Scarti,numero_Turno,&mazzoScarti);

        // Nel caso in cui la scelta fosse 0, continua(che gestisce anche il ciclo) diventera false
        if(continua){
            scopriCarte(carteTurno_Scarti, *giocatori);

            fasePunteggio(giocatori, CFU, &carteTurno_Scarti, &mazzoScarti, &ostacoloTurno, numeroGiocatori,OSTACOLI);

            // Finisce la partita con la fine delle carte Ostacolo
            if (*OSTACOLI == NULL) {
                continua = false;
                printf("\nGli ostacoli sono finiti, la partita e' finita.\n");
            }

            if(*numeroGiocatori==1){
                printf("\n[%s] e' l'unico giocatore rimasto, ha vinto!",(*giocatori)->nomeutente);
                continua=false;
            }
            // A fine di ogni turno riempi il mazzo degli scarti con le carte giocate(scartate) durante il turno
            riempi_daMazzo_aMazzo(&mazzoScarti, &carteTurno_Scarti);

            controlla_60_punti(giocatori,&continua);

            if(continua==false){
                // Elimina tutte le liste
                stampaGiocatori(*giocatori);
                eliminaMazzoCFU(CFU);
                eliminaMazzoCFU(&mazzoScarti);
                eliminaMazzoCFU(&carteTurno_Scarti);
                eliminaMazzoOstacoli(OSTACOLI);
            }
        }
    }
}






