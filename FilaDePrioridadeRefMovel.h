#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
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


RefMovel *cria();
int insere(Pessoa *pessoa, RefMovel *fila);
int testaVazia(RefMovel *desc);
Pessoa * remover(RefMovel *desc);
int tamanhoFila(RefMovel *fila);
int buscaFrente(RefMovel *fila, Pessoa *pessoa);
int buscaCauda(RefMovel *fila, Pessoa *pessoa);
RefMovel *destroi(RefMovel *fila);
int reinicia(RefMovel *fila);
//fazer o inverte

