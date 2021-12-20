#include <stdio.h>
#include <stdlib.h>

//ORDINAMENTO DI UNA LISTA

typedef struct node{
    int num;
    struct node *next;
} node;

typedef node *ptrNode;

ptrNode inserisciInTesta(ptrNode lista, int num);
void stampaLista(ptrNode lista);
ptrNode ordinaLista(ptrNode lista);
void ordinaListaRic(ptrNode lista, ptrNode prec, ptrNode *testa, int swap);

int main(int argc, const char * argv[]) {
    ptrNode lista = NULL;
    
    lista = inserisciInTesta(lista, 4);
    lista = inserisciInTesta(lista, 1);
    lista = inserisciInTesta(lista, 9);
    lista = inserisciInTesta(lista, 6);
    lista = inserisciInTesta(lista, 2);
    lista = inserisciInTesta(lista, 3);
    
    stampaLista(lista);
    //lista = ordinaLista(lista);
    ordinaListaRic(lista, NULL, &lista, 0);
    printf("\n");
    stampaLista(lista);
    return 0;
}

ptrNode inserisciInTesta(ptrNode lista, int num){
    ptrNode n;
    n = (ptrNode)malloc(sizeof(node));
    n->num = num;
    n->next = lista;
    return n;
}

void stampaLista(ptrNode lista){
    if (lista==NULL)
        return;
    printf("%d\n",lista->num);
    stampaLista(lista->next);
}

ptrNode ordinaLista(ptrNode lista){
    ptrNode testa = lista;
    ptrNode prec = NULL;
    ptrNode temp;
    int swap;
    
    if (lista == NULL || lista->next == NULL)
        return lista;
    
    do{
        swap = 0;
        lista = testa;
        prec = NULL;
        while(lista->next != NULL){
            if (lista->num > lista->next->num){
                temp = lista;
                lista = lista->next;
                temp->next = lista->next;
                lista->next = temp;
                swap = 1;
                if (prec == NULL)
                    testa = lista;
                else
                    prec->next = lista;
            }
            prec = lista;
            lista = lista->next;
        }
    }while (swap==1);
    return testa;
}

void ordinaListaRic(ptrNode lista, ptrNode prec, ptrNode *testa, int swap){
    ptrNode temp;
    if (lista==NULL || lista->next==NULL){
        if (swap==1)
            ordinaListaRic(*testa, NULL, testa, 0);
        else
            return;
    }
    
    else{
        if (lista->num > lista->next->num){
            temp = lista;
            lista = lista->next;
            temp->next = lista->next;
            lista->next = temp;
            if (prec == NULL)
                *testa = lista;
            else
                prec->next = lista;
            swap = 1;
        }
        ordinaListaRic(lista->next, lista, testa, swap);
    }
}
