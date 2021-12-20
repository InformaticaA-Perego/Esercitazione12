/*
 Si vuole realizzare un programma C per la gestione dei campionati internazionali di calcio per nazioni.
Si vuole utilizzare una lista che contenga tutte le nazionali di calcio. Ogni elemento della lista rappresenta una squadra e comprende i seguenti campi: Nome nazione, ranking FIFA e continente di appartenenza (Europa, Nord America, Sud America, Africa, Oriente). Per agevolare la programmazione il continente è espresso come un ENUM.

Si consideri la lista già ordinata per ranking.

Definire le strutture dati necessarie (0,5 punti).
 
Scrivere una funzione che, data in ingresso la lista, restituisca una nuova lista contenente solamente le prime 20 squadre europee. La funzione segnala che c’è stato un errore se non è possibile trovare almeno 20 squadre. (2,5 punti).
 
Scrivere una funzione che, date in ingresso la lista delle squadre e un array di 5 float, calcola e restituisce il ranking medio dei vari continenti. I valori calcolati sono inseriti nell’array ricevuto come parametro in ingresso nel seguente ordine: Europa, Nord America, Sud America, Africa e Oriente. (3 punti)
 
Scrivere una funzione che, date in ingresso due squadre (come puntatori o come stringhe) ed i goal fatti dalle due squadre durante una partita, elimini dalla lista la squadra perdente. La funzione restituisce 1 se la rimozione è andata a buon fine. Restituisce 0 se non è possibile effettuare la rimozione, o perché nella lista non sono presenti entrambe le squadre o perché la partita è terminata in pareggio. (3 punti)

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum continente{
    europa,
    nord_america,
    sud_america,
    africa,
    oriente
} continente;

typedef struct nazione{
    char nome[30];
    int ranking;
    continente continente_appartenenza;
    struct nazione *next;
} nazione;
typedef nazione *ptrNazione;

ptrNazione listaEuropee(ptrNazione lista, ptrNazione listaEuropa, int *cont);
void calcolaMediaRanking(ptrNazione lista, float arrayMedie[], int arrayCont[]);
int eliminaSquadra(ptrNazione *lista, char *sq1, char *sq2, int goal1, int goal2);

void stampaLista(ptrNazione lista);
ptrNazione sortInsertRic(ptrNazione lista, int val, continente naz, char *nome);

int main(){
    ptrNazione lista = NULL;
    ptrNazione europee = NULL;
    int numEuropee = 0;
    float arrayMedie[5] = {0};
    int arrayCont[5] = {0};
    
    lista = sortInsertRic(lista, 1, europa, "Italia");
    lista = sortInsertRic(lista, 9, europa, "Francia");
    lista = sortInsertRic(lista, 6, europa, "Germania");
    lista = sortInsertRic(lista, 11, europa, "Olanda");
    lista = sortInsertRic(lista, 3, europa, "Grecia");
    lista = sortInsertRic(lista, 4, sud_america, "Brasile");
    lista = sortInsertRic(lista, 8, sud_america, "Argentina");
    lista = sortInsertRic(lista, 2, nord_america, "USA");
    lista = sortInsertRic(lista, 5, africa, "Nigeria");
    lista = sortInsertRic(lista, 7, oriente, "Cina");
    stampaLista(lista);
    
    printf("\nLISTA EUROPEE\n");
    europee = listaEuropee(lista, europee, &numEuropee);
    stampaLista(europee);
    
    calcolaMediaRanking(lista, arrayMedie, arrayCont);
    printf("\n");
    for (int i=0; i<5; i++)
        printf("%.2f ",arrayMedie[i]);
    
    printf("\n");
    if (eliminaSquadra(&lista, "Francia", "Italia", 0, 5)==1)
        stampaLista(lista);
    printf("\n");
    if (eliminaSquadra(&europee, "Italia", "Argentina", 3, 2)==1)
        stampaLista(europee);
    else
        printf("Errore!");
    stampaLista(europee);
    return 0;
}

ptrNazione listaEuropee(ptrNazione lista, ptrNazione listaEuropa, int *cont){
    if ((lista == NULL) || (*cont >=3)) //dovrebbero essere >=20
        return NULL;
    if (lista->continente_appartenenza == europa){
        listaEuropa = (ptrNazione)malloc(sizeof(nazione));
        listaEuropa->ranking = lista->ranking;
        listaEuropa->continente_appartenenza = lista->continente_appartenenza;
        strcpy(listaEuropa->nome,lista->nome);
        (*cont)++;
        listaEuropa->next = listaEuropee(lista->next, listaEuropa->next, cont);
    }
    else
        listaEuropa = listaEuropee(lista->next, listaEuropa, cont);
    return listaEuropa;
}

void calcolaMediaRanking(ptrNazione lista, float arrayMedie[], int arrayCont[]){
    if (lista==NULL)
    {
        for (int i=0; i<5; i++){
            if (arrayCont[i]==0)
                arrayMedie[i]=0;
            else
                arrayMedie[i] = arrayMedie[i]/arrayCont[i];
        }
        return;
    }
    arrayMedie[lista->continente_appartenenza] = arrayMedie[lista->continente_appartenenza] + lista->ranking;
    arrayCont[lista->continente_appartenenza]++;
    calcolaMediaRanking(lista->next, arrayMedie, arrayCont);
}

int eliminaSquadra(ptrNazione *lista, char *sq1, char *sq2, int goal1, int goal2){
    char daEliminare[30];
    char vincitore[30];
    ptrNazione testa = *lista;
    ptrNazione prec = NULL;
    
    if (goal1>goal2){
        strcpy(daEliminare,sq2);
        strcpy(vincitore, sq1);
    }
    else if (goal1<goal2){
        strcpy(daEliminare,sq1);
        strcpy(vincitore, sq2);
    }
    else
        return 0;
    
    while(*lista!=NULL && strcmp((*lista)->nome, vincitore) != 0)
        *lista = (*lista)->next;
    if (*lista == NULL){
        *lista = testa;
        return 0;
    }
    
    *lista = testa;
    while(*lista!=NULL && strcmp((*lista)->nome, daEliminare) != 0){
        prec = *lista;
        *lista = (*lista)->next;
    }
    if (*lista == NULL){
        *lista = testa;
        return 0;
    }
    
    if (prec == NULL){
        prec = *lista;
        *lista = (*lista)->next;
        free(prec);
    }
    else {
        prec->next = (*lista)->next;
        free(*lista);
        *lista = testa;
    }
    return 1;
}

void stampaLista(ptrNazione lista){
    if (lista == NULL)
        return;
    printf("%s %d %d\n",lista->nome,lista->continente_appartenenza, lista->ranking);
    stampaLista(lista->next);
}

ptrNazione sortInsertRic(ptrNazione lista, int val, continente naz, char *nome){
    ptrNazione n;
    
    if (lista != NULL && lista->ranking < val){
        lista->next = sortInsertRic(lista->next, val, naz, nome);
        return lista;
    } else {
        n = (ptrNazione) malloc(sizeof(nazione));
        n->ranking = val;
        n->continente_appartenenza = naz;
        strcpy (n->nome,nome);
        n->next = lista;
        return n;
    }
}
