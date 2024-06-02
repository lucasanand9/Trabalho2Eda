#ifndef FilaDePrioridade
#define FilaDePrioridade
#define LIVRE 0
#define OCUPADA 1
#define FRACASSO 0
#define SUCESSO 1
#define FALSO 0
#define VERDADEIRO 1
#define NAO 0
#define SIM 1
#define MAIOR 1
#define IGUAL 0
#define MENOR -1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Pessoa.h"

struct noFila{ 
	struct Pessoa dados;
	struct noFila *atras;
    struct noFila *defronte;
};

struct descF{ 	
	struct noFila *frente;
	struct noFila *cauda;
    int tamInfo;
};


//======================APLICACAO=====================


//======================FILA=====================
struct descF * criar(int tamInfo);
int inserir(struct Pessoa *novo,struct descF *p, long *cont);
int tamanhoDaFila(struct descF *p);
int reiniciar(struct descF *p);
struct descF * destroir(struct descF *p);
int buscaNaCauda(struct Pessoa *reg, struct descF *p);
int buscaNaFrente(struct Pessoa *reg, struct descF *p);
int remove_(struct Pessoa *reg, struct descF *p);
int testeVazia(struct descF *p);
int inverte(struct descF *p);

#endif