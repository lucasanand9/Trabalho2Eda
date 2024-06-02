#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "Pessoa.h"

typedef struct Pessoa{
    int matricula;
    int ranking;
    char nome[50];
    char curso[50];
}Pessoa;

typedef struct NoFila {
    Pessoa pessoa;
    struct NoFila *maior;
    struct NoFila *menor;
} NoFila;

typedef struct {
    int tam;
    NoFila *frente;
    NoFila *cauda;
    NoFila *referencial;
}RefMovel;

typedef struct {
    int tam;
    NoFila *frente;
    NoFila *cauda;
}SemRefMovel;

//Fila com referencial movel
RefMovel *cria();
int insere( struct Pessoa *pessoa, RefMovel *fila, long *cont);
int testaVazia(RefMovel *desc);
struct Pessoa * remover(RefMovel *desc);
int tamanhoFila(RefMovel *fila);
int buscaFrente(RefMovel *fila,struct Pessoa *pessoa);
int buscaCauda(RefMovel *fila,struct Pessoa *pessoa);
RefMovel *destroi(RefMovel *fila);
int reinicia(RefMovel *fila);

//Fila sem referencial movel
SemRefMovel *criaSemRef();
int insereSemRef(Pessoa *pessoa, SemRefMovel *desc, long *cont);
int testaVaziaSemRef(SemRefMovel *desc);
Pessoa *removeSemRef(SemRefMovel *desc);
int tamanhoFilaSemRef(SemRefMovel *desc);
Pessoa *buscaFrenteSemRef(SemRefMovel *desc);
Pessoa *buscaCaudaSemRef(SemRefMovel *desc);
SemRefMovel *destroiSemRefMovel(SemRefMovel *desc);
int reiniciaSemRefMovel(SemRefMovel *desc);
