#include "FilaDePrioridadeRefMovel.h"
#include <stdio.h>
#include<stdlib.h>

int main(){
    RefMovel *filaRM = cria();
    Pessoa p;
    int index = 1;
    while (index != 0){
        printf("NoFila %i\n", sizeof(NoFila));//remover
        printf("Pessoa %i\n", sizeof(Pessoa));//remover
        printf("RefMovel %i\n", sizeof(RefMovel));//remover


        printf("Digite uma opção: \n");
        printf("(1)Adicionar elemento na fila\n");
        printf("(2)Remover elemento na fila\n");
        printf("(3)Ver elemento da frente\n");
        printf("(4)Ver elemento da cauda\n");
        printf("(5)Ver o tamanho da fila\n");
        printf("(6)Reiniciar a fila\n");
        printf("(7)Destroi fila\n");
        printf("(0)Sair\n");
        scanf("%i", &index);

        switch (index){
        case 1:
        //arrumar essa leitura de pessoa
            printf("Digite o nome da pessoa:\n");
            scanf(" %[^\n]", p.nome);
            printf("Digite o curso:\n");
            scanf(" %[^\n]", p.curso);
            printf("Digite a matricula:\n");
            scanf(" %i", &(p.matricula));
            printf("Digite o ranking:\n");
            scanf(" %i", &(p.ranking));
            insere(&p, filaRM);
        break;

        case 2:
            Pessoa *pe = remover(filaRM);
            //ver o print que esta errado
            printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", pe->nome,pe->curso, pe->matricula, pe->ranking);
        break;

        case 3:
            buscaFrente(filaRM, &p);
            printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", p.nome,p.curso, p.matricula, p.ranking);
        break;

        case 4: 
            buscaCauda(filaRM, &p);
            printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", *p.nome,*p.curso, p.matricula, p.ranking);    
        break;

        case 5:
	    printf("Tamanho: %i\n", tamanhoFila(filaRM));
        break;

        case 6:
            reinicia(filaRM);
        break;
        
        case 7:
            filaRM = destroi(filaRM);
        break;

        case 0:
            return 0;
        break;

        default:
        printf("Opção invalida\n");
            break;
        }
    }
}
