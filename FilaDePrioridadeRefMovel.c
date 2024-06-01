#include "FilaDePrioridadeRefMovel.h"

RefMovel *cria(){
    RefMovel *desc = (RefMovel*) malloc(sizeof(RefMovel));
    if(desc != NULL) {
        desc->cauda = NULL;
        desc->frente = NULL;
        desc->referencial = NULL;
	    desc->tam= 0;
    }
    return desc;
}

int insere(Pessoa *pessoa, RefMovel *fila){
    printf("entrando na insere\n");//remover
    NoFila *visita = NULL;
    NoFila *novoNo;
    if((novoNo = (NoFila*) malloc(sizeof(NoFila))) != NULL){
        printf("primeiro if\n");//remover
        memcpy(&(novoNo->pessoa), pessoa, sizeof(Pessoa));
    
        if(testaVazia(fila)){
            printf("vazia\n");//remover

            novoNo->maior = novoNo->menor = NULL;
            fila->frente = fila->cauda = fila->referencial = novoNo;
        }else{
            //insere na cauda
            if (novoNo->pessoa.ranking < fila->cauda->pessoa.ranking){
            printf("insere na cauda\n");//remover

            novoNo->maior = fila->cauda;
            novoNo->menor = NULL;
            fila->cauda->menor = novoNo;
            fila->cauda = novoNo;
            fila->referencial = novoNo;
            }else if(novoNo->pessoa.ranking > fila->frente->pessoa.ranking){//insere na cabeça
                printf("insere na cabeca\n");//remover
                novoNo->maior = NULL;
                novoNo->menor = fila->frente;
                fila->frente->maior = novoNo;
                fila->frente = novoNo;
                fila->referencial = novoNo;
            }else if(novoNo->pessoa.ranking < fila->referencial->pessoa.ranking && novoNo->pessoa.ranking > fila->cauda->pessoa.ranking){//insere entre a cauda e o referencial
                printf("entre cauda e ref|calcula D1/D2");//remover
                
                int D1 = (int) fabs((double)fila->cauda->pessoa.ranking - (double)novoNo->pessoa.ranking);
                int D2 = (int) fabs((double)fila->referencial->pessoa.ranking - (double)novoNo->pessoa.ranking);
                if(D1<=D2){//cauda para o referencial
                    printf("cauda->ref\n");//remover
                    visita = fila->cauda;
                    while (visita != fila->referencial && (visita->pessoa.ranking <= novoNo->pessoa.ranking)){
                        visita = visita->maior;
                    }

                    if(visita->pessoa.ranking > novoNo->pessoa.ranking){
                        printf("inserindo cauda->ref\n");//remover
                        novoNo->maior = visita;
                        novoNo->menor = visita->menor;
                        visita->menor->maior = novoNo;
                        visita->menor = novoNo;
                        fila->referencial = novoNo;
                    }
                }else{//referencial para a cauda
                    printf("ref->cauda\n");//remover
                    visita = fila->referencial;
                    while ((visita != NULL) && (visita->pessoa.ranking >= novoNo->pessoa.ranking)){
                        visita= visita->menor;
                    }
                    if(visita->pessoa.ranking < novoNo->pessoa.ranking){
                        printf("inserindo ref->cauda\n");//remover

                        novoNo->menor = visita;
                        novoNo->maior = visita->maior;
                        visita->maior->menor = novoNo;
                        visita->maior = novoNo;
                        fila->referencial = novoNo;
                    }
                }//insere entre a cabeça e o referencial
                }else if((novoNo->pessoa.ranking >= fila->referencial->pessoa.ranking) && (novoNo->pessoa.ranking < fila->frente->pessoa.ranking)){
                        printf("insere entre a cabeça e o referencial\n");//remover
                    int D1 = (int) fabs((double)fila->frente->pessoa.ranking - (double)novoNo->pessoa.ranking);
                    int D2 = (int) fabs((double)fila->referencial->pessoa.ranking - (double)novoNo->pessoa.ranking);
                    if(D1<=D2){//frente da fila para o referencial
                        printf("cab->ref\n");//remover

                        visita = fila->frente;
                        while ((visita != fila->referencial) && visita->pessoa.ranking >= novoNo->pessoa.ranking){
                            visita = visita->menor;
                        }
                        if(visita->pessoa.ranking < novoNo->pessoa.ranking){
                            printf("frente da fila para o referencia\n");//remover
                            visita->maior->menor = novoNo;
                            novoNo->maior = visita->maior;
                            novoNo->menor = visita;
                            visita->maior = novoNo;
                            fila->referencial = novoNo;
                        }
                    }
                    if(D1>=D2){//referencia para a frente da fila
                        printf("ref->cab\n");//remover

                        visita = fila->referencial;
                        while ((visita != fila->frente) && (visita->pessoa.ranking <= novoNo->pessoa.ranking)){
                            visita = visita->maior;
                        }
                        if(visita->pessoa.ranking > novoNo->pessoa.ranking){
                            printf("referencia para a frente da fila\n");//remover
                            visita->menor->maior = novoNo;
                            novoNo->menor = visita->menor;
                            visita->menor = novoNo;
                            novoNo->maior = visita;
                            fila->referencial = novoNo;
                        }
                    }

                }        
            }
            fila->tam += 1;
            return 1;
    }
    return 0;
}

int testaVazia(RefMovel *desc){
    return (desc->frente == NULL) && (desc ->cauda == NULL);
}

Pessoa * remover(RefMovel *desc){
    NoFila *aux = desc->cauda;
    if(testaVazia(desc)){
        Pessoa *p = NULL;
        return p;
    }
    Pessoa *temp;
    memcpy(temp, &(desc->frente->pessoa), sizeof(Pessoa));  
    if(aux == desc->frente){
        free(desc->frente);
        desc->frente = desc->cauda = desc->referencial = NULL;
    }else{
        desc->frente = desc->frente->menor;
        free(desc->frente->maior);
        desc->frente->maior = NULL;
    }
    desc->tam -= 1;
    return temp;
}

int tamanhoFila(RefMovel *fila){
    return fila->tam;
}

int buscaCauda(RefMovel *fila, Pessoa *pessoa){
    if(testaVazia(fila)){
        return 0;
    }
    *pessoa = fila->cauda->pessoa;
    return 1;
}

int buscaFrente(RefMovel *fila, Pessoa *pessoa){
    if(testaVazia(fila)){
        return 0;
    }
    *pessoa = fila->frente->pessoa;
    return 1;
}

int reinicia(RefMovel *fila){
    if(testaVazia(fila)){
        return 0;
    }
    NoFila *atual = fila->frente;
    while (atual != NULL){
        atual = atual->menor;
        free(fila->frente);
        fila->frente = atual;
    }
    fila->cauda = fila->frente=fila->referencial = NULL;
    fila->tam = 0;
    return 1;
}

RefMovel *destroi(RefMovel *fila){
    reinicia(fila);
    free(fila);
    return NULL;
}

//fazer o inverte




