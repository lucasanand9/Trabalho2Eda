#include "FilaDePrioridadeRefMovel.h"
// #include "Pessoa.h"

/********************COM REFERENCIAL********************/

//CRIA COM REF
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

//INSERE COM REF
int insere(Pessoa *pessoa, RefMovel *fila, long *cont){
    long mediaInt = 1;
    if(cont == NULL){
        printf("Insira um contador valido!");
        return 0;
    }
    // printf("entrando na insere\n");//remover
    NoFila *visita = NULL;
    NoFila *novoNo;
    if((novoNo = (NoFila*) malloc(sizeof(NoFila))) != NULL){
        // printf("primeiro if\n");//remover
        memcpy(&(novoNo->pessoa), pessoa, sizeof(struct Pessoa));
    
        if(testaVazia(fila)){
            // printf("vazia\n");//remover

            novoNo->maior = novoNo->menor = NULL;
            fila->frente = fila->cauda = fila->referencial = novoNo;
        }else{
            //insere na cauda
            if (novoNo->pessoa.ranking < fila->cauda->pessoa.ranking){
            // printf("insere na cauda\n");//remover
            novoNo->maior = fila->cauda;
            novoNo->menor = NULL;
            fila->cauda->menor = novoNo;
            fila->cauda = novoNo;
            fila->referencial = novoNo;
            }else if(novoNo->pessoa.ranking > fila->frente->pessoa.ranking){//insere na cabeça
                // printf("insere na cabeca\n");//remover
                novoNo->maior = NULL;
                novoNo->menor = fila->frente;
                fila->frente->maior = novoNo;
                fila->frente = novoNo;
                fila->referencial = novoNo;
            }else if(novoNo->pessoa.ranking < fila->referencial->pessoa.ranking && novoNo->pessoa.ranking > fila->cauda->pessoa.ranking){//insere entre a cauda e o referencial
                // printf("entre cauda e ref|calcula D1/D2");//remover
                
                int D1 = (int) fabs((double)fila->cauda->pessoa.ranking - (double)novoNo->pessoa.ranking);
                int D2 = (int) fabs((double)fila->referencial->pessoa.ranking - (double)novoNo->pessoa.ranking);
                if(D1<=D2){//cauda para o referencial
                    // printf("cauda->ref\n");//remover
                    visita = fila->cauda;
                    while (visita != fila->referencial && (visita->pessoa.ranking <= novoNo->pessoa.ranking)){
                        visita = visita->maior;
                        mediaInt++;
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
                    // printf("ref->cauda\n");//remover
                    visita = fila->referencial;
                    while ((visita != NULL) && (visita->pessoa.ranking >= novoNo->pessoa.ranking)){
                        visita= visita->menor;
                        mediaInt++;
                    }
                    if(visita->pessoa.ranking < novoNo->pessoa.ranking){
                        // printf("inserindo ref->cauda\n");//remover

                        novoNo->menor = visita;
                        novoNo->maior = visita->maior;
                        visita->maior->menor = novoNo;
                        visita->maior = novoNo;
                        fila->referencial = novoNo;
                    }
                }//insere entre a cabeça e o referencial
                }else if((novoNo->pessoa.ranking >= fila->referencial->pessoa.ranking) && (novoNo->pessoa.ranking < fila->frente->pessoa.ranking)){
                        // printf("insere entre a cabeça e o referencial\n");//remover
                    int D1 = (int) fabs((double)fila->frente->pessoa.ranking - (double)novoNo->pessoa.ranking);
                    int D2 = (int) fabs((double)fila->referencial->pessoa.ranking - (double)novoNo->pessoa.ranking);
                    if(D1<=D2){//frente da fila para o referencial
                        // printf("cab->ref\n");//remover

                        visita = fila->frente;
                        while ((visita != fila->referencial) && visita->pessoa.ranking >= novoNo->pessoa.ranking){
                            visita = visita->menor;
                            mediaInt++;
                        }
                        if(visita->pessoa.ranking < novoNo->pessoa.ranking){
                            // printf("frente da fila para o referencia\n");//remover
                            visita->maior->menor = novoNo;
                            novoNo->maior = visita->maior;
                            novoNo->menor = visita;
                            visita->maior = novoNo;
                            fila->referencial = novoNo;
                        }
                    }
                    if(D1>=D2){//referencia para a frente da fila
                        // printf("ref->cab\n");//remover

                        visita = fila->referencial;
                        while ((visita != fila->frente) && (visita->pessoa.ranking <= novoNo->pessoa.ranking)){
                            visita = visita->maior;
                            mediaInt++;
                        }
                        if(visita->pessoa.ranking > novoNo->pessoa.ranking){
                            // printf("referencia para a frente da fila\n");//remover
                            visita->menor->maior = novoNo;
                            novoNo->menor = visita->menor;
                            visita->menor = novoNo;
                            novoNo->maior = visita;
                            fila->referencial = novoNo;
                        }
                    }

                }        
            }
            (*cont) += mediaInt;
            fila->tam += 1;
            return 1;
    }
    return 0;
}

//TESTA VAZIA COM REF
int testaVazia(RefMovel *desc){
    return (desc->frente == NULL) && (desc ->cauda == NULL);
}

//REMOVE COM REF
struct Pessoa *remover(RefMovel *desc){
    NoFila *aux = desc->cauda;
    if(testaVazia(desc)){
        struct Pessoa *p = NULL;
        return p;
    }
   struct Pessoa *temp = ( struct Pessoa*) malloc(sizeof(struct Pessoa));
    memcpy(temp, &(desc->frente->pessoa), sizeof(struct Pessoa));  
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

//TAMANHO COM REF
int tamanhoFila(RefMovel *fila){
    return fila->tam;
}

//BUSCA CAUDA COM REF
int buscaCauda(RefMovel *fila, struct Pessoa *pessoa){
    if(testaVazia(fila)){
        return 0;
    }
    *pessoa = fila->cauda->pessoa;
    return 1;
}

//BUSCA FRENTE COM REF
int buscaFrente(RefMovel *fila, struct Pessoa *pessoa){
    if(testaVazia(fila)){
        return 0;
    }
    *pessoa = fila->frente->pessoa;
    return 1;
}

//REINICIA COM REF
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

//DESTROI COM REF
RefMovel *destroi(RefMovel *fila){
    reinicia(fila);
    free(fila);
    return NULL;
}

/********************SEM REFERENCIAL********************/

//CRIA SEM REF
SemRefMovel *criaSemRef(){
    SemRefMovel *desc = (SemRefMovel*) malloc(sizeof(SemRefMovel));
    if(desc != NULL) {
        desc->cauda = NULL;
        desc->frente = NULL;
	    desc->tam= 0;
    }
    return desc;
}

//INSERE SEM REF
int insereSemRef(Pessoa *pessoa, SemRefMovel *desc, long *cont){
    long mediaInt = 1;
    if(cont == NULL){
        printf("Insira um contador valido!");
        return 0;
    }
    NoFila *visita = NULL;
    NoFila *novoNo;
    if((novoNo = (NoFila*) malloc(sizeof(NoFila))) != NULL){
        memcpy(&(novoNo->pessoa), pessoa, sizeof(struct Pessoa));
    
        if(testaVaziaSemRef(desc)){
            novoNo->maior = novoNo->menor = NULL;
            desc->frente = desc->cauda = novoNo;
        }else{
            if (novoNo->pessoa.ranking < desc->cauda->pessoa.ranking){//insere na cauda
            novoNo->maior = desc->cauda;
            novoNo->menor = NULL;
            desc->cauda->menor = novoNo;
            desc->cauda = novoNo;
            }else if(novoNo->pessoa.ranking > desc->frente->pessoa.ranking){//insere na frente
                novoNo->maior = NULL;
                novoNo->menor = desc->frente;
                desc->frente->maior = novoNo;
                desc->frente = novoNo;
            }else if((novoNo->pessoa.ranking > desc->cauda->pessoa.ranking) && (novoNo->pessoa.ranking < desc->frente->pessoa.ranking)){
                visita = desc->frente;
                while (visita->menor != NULL && (visita->pessoa.ranking >= novoNo->pessoa.ranking)){
                    visita = visita->menor;
                    mediaInt++;
                }
                if(visita->pessoa.ranking<novoNo->pessoa.ranking){
                    novoNo->menor = visita;
                    novoNo->maior = visita->maior;
                    visita->maior->menor = novoNo;
                    visita->maior = novoNo;
                }   
                
            }
            
        }
        (*cont) += mediaInt;
        desc->tam += 1;
        return 1;
    }
    return 0;
}


//TESTA VAZIA SEM REF
int testaVaziaSemRef(SemRefMovel *desc){
    return (desc->frente == NULL) && (desc->cauda == NULL);
}

//REMOVE SEM REF
Pessoa *removeSemRef(SemRefMovel *desc){
    NoFila *aux = desc->cauda;
    if(testaVaziaSemRef(desc)){
        struct Pessoa *p = NULL;
        return p;
    }
   struct Pessoa *temp = ( struct Pessoa*) malloc(sizeof(struct Pessoa));
    memcpy(temp, &(desc->frente->pessoa), sizeof(struct Pessoa));  
    if(aux == desc->frente){
        free(desc->frente);
        desc->frente = desc->cauda = NULL;
    }else{
        desc->frente = desc->frente->menor;
        free(desc->frente->maior);
        desc->frente->maior = NULL;
    }
    desc->tam -= 1;
    return temp;
}

//TAMANHO SEM REF
int tamanhoFilaSemRef(SemRefMovel *desc){
    return desc->tam;
}

//BUSCA FRENTE SEM REF
Pessoa *buscaFrenteSemRef(SemRefMovel *desc){
    if(testaVaziaSemRef(desc)){
        return 0;
    }
    Pessoa *p = &(desc->frente->pessoa);
    return p;
}

//BUSCA CAUDA SEM REF
Pessoa *buscaCaudaSemRef(SemRefMovel *desc){
    if(testaVaziaSemRef(desc)){
        return 0;
    }
    Pessoa *p = &(desc->cauda->pessoa);
    return p;
}

//REINICIA SEM REF
int reiniciaSemRefMovel(SemRefMovel *desc){
    if(testaVaziaSemRef(desc)){
        return 0;
    }
    NoFila *atual = desc->frente;
    while (atual != NULL){
        atual = atual->menor;
        free(desc->frente);
        desc->frente = atual;
    }
    desc->cauda = desc->frente= NULL;
    desc->tam = 0;
    return 1;
}

//DESTROI SEM REF
SemRefMovel *destroiSemRefMovel(SemRefMovel *desc){
    reiniciaSemRefMovel(desc);
    free(desc);
    return NULL;
}




