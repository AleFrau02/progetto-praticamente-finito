//
// Created by Alessio Frau on 10/05/2024.
//

#ifndef UNTITLED60_LIBRERIA_FUNZIONI_H
#define UNTITLED60_LIBRERIA_FUNZIONI_H

#include "intestazione.h"


void pescaggioCartaCfu(CarteCFU** mazzoCfu,CarteCFU** mazzoRicevente);
void pescaggioCartaOstacolo(CarteOSTACOLO** mazzoOstacoli, CarteOSTACOLO** mazzoRicevente);

void inserisciCfu_inCoda_nelMazzo(CarteCFU** mazzo, char nome[DIM_CARATTERI], int valore, NomeEffetti nomeEffetti);
void inserisciOstaolo_inCoda_nelMazzo(CarteOSTACOLO** mazzo,char nome[DIM_CARATTERI], char descrizioneOSTACOLO[CARATTERIperDESCRIZIONE],TipoOstacoli tipoOstacoli);
void inserisciCfu_inTesta_nelMazzo(CarteCFU** mazzo, char nome[DIM_CARATTERI], int valore, NomeEffetti nomeEffetti);
void inserisciOstacolo_inTesta_nelMazzo(CarteOSTACOLO** mazzo, char nome[DIM_CARATTERI], char descrizioneOSTACOLO[CARATTERIperDESCRIZIONE], TipoOstacoli tipoOstacoli);

void eliminaCfu_inCoda(CarteCFU** mazzo);
void eliminaOstacolo_inCoda(CarteOSTACOLO** mazzo);
void eliminaCfu_inTesta(CarteCFU** mazzo);
void eliminaOstacolo_inTesta(CarteOSTACOLO** mazzo);

void mescolaCarteCFU(CarteCFU** mazzo);
void mescolaCarteOSTACOLO(CarteOSTACOLO** mazzo);

void stampaMazzo(CarteCFU* mazzo);
void stampaOstacoli(CarteOSTACOLO* mazzo);

void eliminaCartaDalMazzo(CarteCFU** mazzo, char* nome, int* valore, NomeEffetti* nomeEffetti, int posizione);

void eliminaMazzoCFU(CarteCFU** mazzo);
void eliminaMazzoOstacoli(CarteOSTACOLO** mazzo);

char *Switch_Case_effettoCarta(int numero);
char *Switch_Case_tipoOstacoli(int numero);
void mischiaPersonaggi(Personaggio personaggi[NUMERO_PERSONAGGI], int n);
void stampaGiocatori(const IlGiocatore* testa);



void trasferisciOstacoloInCoda(CarteOSTACOLO** mazzoRicevente, CarteOSTACOLO** cartaOstacolo);
void trasferisciTutteLeCarteCFU(CarteCFU **destinazione, CarteCFU *sorgente);
void trasferisciTuttiGliOstacoli(CarteOSTACOLO **destinazione, CarteOSTACOLO *sorgente);
void eliminaGiocatore(IlGiocatore **giocatori, IlGiocatore *giocatoreDaEliminare, CarteCFU **mazzoCfu, CarteOSTACOLO **mazzoOstacoli);

void stampaVincenti_Turno(int numeroVincenti, IlGiocatore** giocatori,const int perdenti0_vincitori1[]);

/**PREPARAZIONE*/
void PREPARAZIONE_gioco(IlGiocatore** giocatori, Personaggio personaggi[], CarteCFU** CFU, CarteOSTACOLO** OSTACOLI, int* numerodeigiocatori);
//che include:
int numerogiocatori();
CarteCFU *leggiCfu();
CarteOSTACOLO *leggiOSTACOLI();
void leggiPERSONAGGI(Personaggio personaggi[NUMERO_PERSONAGGI]);
void creaGiocatori(IlGiocatore** giocatori,Personaggio personaggi[NUMERO_PERSONAGGI],int numeroGiocatori);
void creaListaGiocatori(IlGiocatore** testa, char nome[DIM_CARATTERI], Personaggio personaggio, int CFUaccumulati);



/**GIOCO*/
void GIOCO(IlGiocatore** giocatori, CarteCFU** CFU, CarteOSTACOLO** OSTACOLI,int* numeroGiocatori);
//che include:
void disegnoHappyLittleStudents();
void stampaDatiGiocatori(IlGiocatore** giocatori,int numGiocatori);
void sceltaAzione(IlGiocatore** giocatori,CarteCFU** mazzoCFU,bool* continua, CarteCFU** carteTurno_Scarti,int numeroTurno, CarteCFU** mazzoScarti);
int stampaSceltaAzione(char nome[]);
void eliminaListaGiocatori(IlGiocatore** testa);
void scelta1(IlGiocatore** giocatoreTurno, CarteCFU** carteTurno_Scarti, CarteCFU** mazzoScarti, CarteCFU** mazzoCFU);
int selezioneCarta_daScartare(IlGiocatore** giocatoreTurno,int Punto_o_Istantanea);
void scelta2(IlGiocatore** giocatoreTurno, IlGiocatore** giocatori);
void riempi_daMazzo_aMazzo(CarteCFU** mazzoRicevente, CarteCFU** mazzoPescato);
void verificaMano_delGiocatore(CarteCFU** mazzoScarti,CarteCFU** mazzoCfu, CarteCFU** mazzoGiocatoreTurno);
void scopriCarte(CarteCFU* scartiTurno,IlGiocatore* giocatori);
void fasePunteggio(IlGiocatore** giocatori,CarteCFU** mazzoCfu, CarteCFU** carteTurno_Scarti, CarteCFU** mazzoScarti, CarteOSTACOLO** ostacoloTurno,int* numeroGiocatori, CarteOSTACOLO** mazzoOstacoli);
void somma_BonusMalus(IlGiocatore** giocatori);
void ordinamentoDecrescente_perValore(CarteCFU** mazzoDaRiordinare);
void scambiaMazzi(CarteCFU **mazzo1, CarteCFU **mazzo2);



void vincitori_o_perdenti(CarteCFU** mazzoCFU,IlGiocatore** giocatori, const int scelte[],CarteCFU** scarti_carteIstantanee,int* numeroGiocatori,bool raddoppia_DOPPIOE,const int puntaggi_primaDelTurno[],int partecipanti_faseIstantanea, CarteOSTACOLO** ostacolo_Turno, CarteOSTACOLO** mazzoOstacoli,CarteCFU** mazzoScarti);
void calcoloPunteggio(IlGiocatore** giocatori, int* numeroGiocatori,const int puntaggi_primaDelTurno[], CarteCFU** mazzoCFU, CarteOSTACOLO** ostacolo_Turno, CarteOSTACOLO** mazzoOstacoli, CarteCFU** mazzoScarti);
void turnoAggiuntivo(int* numeroGiocatori, IlGiocatore** giocatori, CarteCFU** mazzoCfu, CarteOSTACOLO** ostacoloTurno, CarteOSTACOLO** mazzoOstacoli, int perdenti0_vincitori1[], int contaPerdenti, int contaVincenti, CarteCFU** mazzoScarti);
void verificaPunteggio_turnoAggiuntivo(IlGiocatore** giocatori, int *numeroPerdenti, int perdenti0_vincitori1[],CarteCFU** mazzoScarti_turnoAggiuntivo);
void fase_delPerdente(IlGiocatore** giocatori, IlGiocatore** giocatorePerdente,CarteOSTACOLO** mazzoOstacoli, CarteOSTACOLO** ostacoloTurno, CarteCFU** mazzoCfu, int* numeroGiocatori);
void inserisci_Ostacolo(IlGiocatore** giocatoreSfortunato_o_Perdente, CarteOSTACOLO** ostacoloTurno,CarteCFU** mazzoCfu, IlGiocatore** giocatori, int* numeroGiocatori, CarteOSTACOLO** mazzoOstacoli);
void eliminaPunteggio_aiNonVincitori(IlGiocatore** giocatori, const int perdenti0_vincitori1[], const int punteggiTurno[]);


int carteMancanti(CarteCFU** mazzoGiocatore);
void controlla_60_punti(IlGiocatore** giocatori, bool *continua);



void effetti_cartePunto(int* i,CarteCFU** mazzoCfu,IlGiocatore** giocatoreTurno,CarteCFU** carta_giocatoreTurno,IlGiocatore** giocatori, CarteCFU** carteTurno_Scarti, CarteCFU** mazzoScarti, int numeroGiocatori,bool* inversionePunti_SCAMBIAP,bool *raddoppia_DOPPIOE);
/** EFFETTI CARTE PUNTO*/
void effetto_SCAMBIAC(int numeroGiocatori, IlGiocatore** giocatori, IlGiocatore** giocatoreTurno);
void effetto_SCARTAP(IlGiocatore** giocatoreTurno,CarteCFU** mazzoScarti);
void effetto_RUBA(IlGiocatore** giocatoreTurno,IlGiocatore** giocatori);
void effetto_SCAMBIADS(IlGiocatore** giocatori, IlGiocatore** giocatoreTurno, CarteCFU** carteTurno, int numeroGiocatori);
void effetto_SCARTAE(IlGiocatore** giocatori, IlGiocatore** giocatoreTurno, CarteCFU** carteTurno, int numeroGiocatori, CarteCFU** mazzoScarti);
void effetto_SCARTAC(IlGiocatore** giocatoreTurno,CarteCFU** mazzoScarti);
void effetto_SCAMBIAP(IlGiocatore** giocatori, int numeroGiocatori, const int punteggi_primaDelTurno[]);
void effetto_SBIRCIA(CarteCFU** mazzoCfu,IlGiocatore** giocatoreTurno, CarteCFU** mazzoScarti);


void effetti_carteIstantanee(IlGiocatore** giocatori, bool raddoppia_DOPPIOE, CarteCFU** cartaIstantanea_giocatore, IlGiocatore** giocatore_delTurno, const int punteggi_primaDelTurno[], int numeroGiocatori);
/**EFFETTI CARTE ISTANTANEE*/
void effetto_AUMENTA(bool raddoppia_DOPPIOE,IlGiocatore* giocatori, IlGiocatore* giocatore_delTurno);
void effetto_DIMINUISCI(bool raddoppia_DOPPIOE,IlGiocatore* giocatori, IlGiocatore* giocatore_delTurno);



void invertiPosizione_carteMazzo(CarteCFU** mazzo, int posizione1, int posizione2);
void invertiMinMax(int array[], int dimensine);
bool verifica_carteIstantanee_mazzoGiocatore(CarteCFU** mazzoGiocatore);
bool verifica_cartePunto_mazzoGiocatore(CarteCFU** mazzoGiocatore);
int* stampaCarte_perScelta(CarteCFU* mazzoGiocatore,int* numero_carteGiocatore);





void fase_carteIstantanee(CarteCFU** mazzoCFU,IlGiocatore** giocatori,CarteCFU** mazzoScarti, int* numeroGiocatori,const int punteggi_primaDelTurno[], bool raddoppia_DOPPIOE, CarteOSTACOLO** ostacoloTurno, CarteOSTACOLO** mazzoOstacoli);

void sommaPunteggi_cartePunto(IlGiocatore** giocatori, CarteCFU** carteCfuPunto_scartate, int numeroGiocatori);

bool verifica_SALVA_DIROTTA(CarteCFU** mazzoGiocatore);


void trasferisciCarta(CarteCFU **mazzoRicevente, CarteCFU **mazzoDonante, int posizione);









void stampaGiocatore(const IlGiocatore *giocatore);
void stampaCarteCFU(const CarteCFU *carta);
void stampaCarteOstacolo(const CarteOSTACOLO *carta);



#endif //UNTITLED60_LIBRERIA_FUNZIONI_H
