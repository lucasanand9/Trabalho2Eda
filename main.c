#include "FilaDePrioridadeRefMovel.h"
// #include "Pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Pessoa* lerCSV(const char* nomeArquivo, int quantidade);

int main(int argc, char *argv[]){
    RefMovel *filaRM = cria();
    struct Pessoa p;
    int index = 1;
    while (index != 0){
        printf("NoFila %i\n", sizeof(NoFila));//remover
        printf("Pessoa %i\n", sizeof(struct Pessoa));//remover
        printf("RefMovel %i\n", sizeof(RefMovel));//remover

        printf("Digite uma opção: \n");
        printf("(1)Adicionar elemento na fila\n");
        printf("(2)Remover elemento na fila\n");
        printf("(3)Ver elemento da frente\n");
        printf("(4)Ver elemento da cauda\n");
        printf("(5)Ver o tamanho da fila\n");
        printf("(6)Reiniciar a fila\n");
        printf("(7)Destroi fila\n");
        printf("(8)Testar diferença\n");
        printf("(0)Sair\n");
        scanf("%i", &index);

        switch (index){
        case 1:
        long int interacao = 0;
        //arrumar essa leitura de pessoa
            printf("Digite o nome da pessoa:\n");
            scanf(" %[^\n]", p.nome);
            printf("Digite o curso:\n");
            scanf(" %[^\n]", p.curso);
            printf("Digite a matricula:\n");
            scanf(" %i", &(p.matricula));
            printf("Digite o ranking:\n");
            scanf(" %i", &(p.ranking));
            insere(&p, filaRM, &interacao);
            printf("Numero de interação: %li\n",interacao);
        break;

        case 2:
            struct Pessoa *pe = remover(filaRM);
            //ver o print que esta errado
            if(pe == NULL){
                printf("A Fila esta vazia!\n");
                continue;
            }
            printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", pe->nome,pe->curso, pe->matricula, pe->ranking);
        break;

        case 3:
            if(buscaFrente(filaRM, &p)){
                printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", p.nome,p.curso, p.matricula, p.ranking);    
            }else{
                printf("A Fila esta vazia!\n");
            }
        break;
        case 4: 
            if(buscaCauda(filaRM, &p)){
                printf("Nome: %s\nCurso: %s\nMatricula: %i\nRanking: %i\n", p.nome,p.curso, p.matricula, p.ranking);    
            }else{
                printf("A Fila esta vazia!\n");
            }
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

        case 8:
            printf("Testando as diferenças entre as filas!");
            
            int numDados[18] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
            // struct descF *filaPrioritaria = criar(sizeof(struct Pessoa));
            RefMovel *filaComRefMovel = cria();
            SemRefMovel *filaSemRefMovel = criaSemRef();

            for (int i = 0; i < 18; i++){//i<18
                long int numRepA = 0;
                long int numRepB = 0;
                struct Pessoa *p = lerCSV(argv[1],numDados[i]);
                for (int j = 0; j < numDados[i]; j++){
                    //printf("Nome: %s - Matricula: %i - Ranking: %i - Curso: %s\n", p[j].nome, p[j].matricula, p[j].ranking,p[j].curso);//remover
                    insere(&(p[j]),filaComRefMovel, &numRepA);//fila com refMovel
                    insereSemRef(&(p[j]), filaSemRefMovel,&numRepB);//fila sem refMovel
                }
                printf("Media com %i dados:\nCom refMovel: %ld\nSem refMovel: %d\n", numDados[i], numRepA, numRepB);
                reinicia(filaComRefMovel);
                reiniciaSemRefMovel(filaSemRefMovel);
            }
            
        break;

        case 0:
            filaRM = destroi(filaRM);
            free(filaRM);
            return 0;
        break;

        default:
        printf("Opção invalida\n");
            break;
        }
    }
}

//LEITURA ARQUIVO CSV
Pessoa* lerCSV(const char* nomeArquivo, int quantidade) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    int totalLinhas = 10000;
    if (quantidade > totalLinhas) {
        quantidade = totalLinhas;
    }

    int* linhasSelecionadas = malloc(quantidade * sizeof(int));
    if (!linhasSelecionadas) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return NULL;
    }

    // Inicializa gerador de números aleatórios
    srand(time(NULL));

    // Seleciona linhas aleatórias
    for (int i = 0; i < quantidade; i++) {
        linhasSelecionadas[i] = rand() % totalLinhas;
        for (int j = 0; j < i; j++) {
            if (linhasSelecionadas[i] == linhasSelecionadas[j]) {
                i--; // Evita duplicação
                break;
            }
        }
    }

    struct Pessoa* pessoas = malloc(quantidade * sizeof(struct Pessoa));
    if (!pessoas) {
        perror("Erro ao alocar memória");
        free(linhasSelecionadas);
        fclose(arquivo);
        return NULL;
    }

    char linha[256];
    int contador = 0;
    int linhaAtual = 0;

    // Lê o arquivo e armazena as linhas selecionadas
    while (fgets(linha, sizeof(linha), arquivo)) {
        for (int i = 0; i < quantidade; i++) {
            if (linhaAtual == linhasSelecionadas[i]) {
                struct Pessoa p;
                sscanf(linha, "%49[^,],%d,%d,%49[^\n]", p.nome, &p.matricula, &p.ranking, p.curso);
                pessoas[contador] = p;
                contador++;
                break;
            }
        }
        linhaAtual++;
    }

    fclose(arquivo);
    free(linhasSelecionadas);

    return pessoas;
}
