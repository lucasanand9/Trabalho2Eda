#ifndef FilaDePrioridadeRefMovel
#define FilaDePrioridadeRefMovel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Pessoa.h"

typedef struct NoFila {
    struct Pessoa pessoa;
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
int insere( struct Pessoa *pessoa, RefMovel *fila, long *cont);
int testaVazia(RefMovel *desc);
struct Pessoa * remover(RefMovel *desc);
int tamanhoFila(RefMovel *fila);
int buscaFrente(RefMovel *fila,struct Pessoa *pessoa);
int buscaCauda(RefMovel *fila,struct Pessoa *pessoa);
RefMovel *destroi(RefMovel *fila);
int reinicia(RefMovel *fila);
//fazer o inverte

#endif