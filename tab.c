#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

//imprime o tabuleiro com algumas manipulações para que fique minimamente simétrico
void imprimeTab(peca **tabuleiro,int linha, int coluna){
	int aux;
	printf("  ");
	//imprime os índices superiores das colunas
	for (aux=0;aux<coluna;aux++){
		if(aux>=10)printf("%d ",aux);
		else printf(" %d ",aux);
	}
	printf("\n");
	//imprime uma linha 
	for (int i=0;i<linha;i++){
		printf("  -");
		//imprime as divisórias de linhas
		for(aux=0;aux<coluna*3;aux++){
			printf("-");
		}
		printf("\n");
		if(i<10)printf(" ");
		//imprime o índice do lado esquerdo de cada linha
		printf("%d", i);			
		printf("|");
		//imprime as peças de cada posição, ou espaços, caso a posição não esteja ocupada
		for (int j=0;j<coluna;j++){
			printf("%c", tabuleiro[i][j].letra);
			printf("%c|",tabuleiro[i][j].num);
		}
		//imprime o índice do lado direito de cada linha
		printf("%d\n",i);
	}
	printf("  -");
	//divisória da linha
	for(aux=0;aux<coluna*3;aux++){
		printf("-");
	}
	printf("\n");
	printf("  ");
	//imprime os índices inferiores das colunas
	for (aux=0;aux<coluna;aux++){
		if(aux>=10) printf("%d ",aux);
		else printf(" %d ",aux);
	}
	printf("\n");
}

void realocaTab(peca **tabuleiro, int *linha, int *coluna, int chave) {
	//realoca um tabuleiro de dimensão MxN, sendo M o número de linhas e N o número de colunas
	int i;
	//a chave 1 é usada para o caso em que uma peça é colocada na primeira linha. nesse caso, é preciso que todas as peças sejam "puxadas" para baixo, no tabuleiro, se não o tabuleiro fica limitado superiormente.
	if(chave == 1) { 
		//acrescenta uma linha
		*linha += 1;
		//esse laço "puxa" todas as peças para a linha debaixo e limpa as posições da primeira linha, para que ela fique livre para novas jogadas.
		for(i = (*linha-1); i >= 0; i--) {
			for(int j = (*coluna-1); j >= 0; j--) {
				if(tabuleiro[i][j].letra != ' ') {
					//"puxa" todas as peças para baixo"
					tabuleiro[i+1][j].letra = tabuleiro[i][j].letra;
					tabuleiro[i+1][j].num = tabuleiro[i][j].num;
					//"limpa" as posições que as peças puxadas ocupavam
					tabuleiro[i][j].letra = ' ';
					tabuleiro[i][j].num = ' ';
					//atribui espaços às posições da última linha, para que as verificações do programa funcionem corretamente e o tabuleiro seja impresso corretamente
					tabuleiro[*linha-1][j].letra = ' ';
					tabuleiro[*linha-1][j].num = ' ';
				}
			}
		}
	}
	
	//a chave 2 é usada para o caso em que uma peça é colocada na última linha. Nesse caso, não é preciso "puxar" todas as peças para baixo, e sim apenas criar uma nova linha abaixo.
	if(chave == 2) {
		//cria uma nova linha abaixo
		*linha += 1;
		for(i = 0; i < *coluna; i++) {
			//atribui espaços às posições da linha criada, para verificações do programa e impressão correta.
			tabuleiro[*linha-1][i].letra = ' ';
			tabuleiro[*linha-1][i].num = ' ';
		}	
	}
	
	//a chave 3 é usada para o caso em que uma peça é colocada na primeira coluna. nesse caso, as peças devem ser "puxadas" para a direita, se não o tabuleiro fica limitado desse lado
	if(chave == 3) {
        	*coluna += 1;
		//esse laço "puxa" as peças para a direita e inicializa a última coluna com espaços
        	for(i = (*coluna-1); i >= 0; i--) {
                        for(int j = (*linha-1); j >= 0; j--) {
                                if(tabuleiro[j][i].letra != ' ') {
					//"puxa" as peças para a direita
                                        tabuleiro[j][i+1].letra = tabuleiro[j][i].letra;
                                        tabuleiro[j][i+1].num = tabuleiro[j][i].num;
					//"limpa" a posição das peças que foram "puxadas"
                                        tabuleiro[j][i].letra = ' ';
                                        tabuleiro[j][i].num = ' ';
					//inicializa a última coluna com espaços
					tabuleiro[j][*coluna-1].letra = ' ';
					tabuleiro[j][*coluna-1].num = ' ';
                                }
                        }
                }
	}

	//a chave 4 é usada quando o usuário insere uma peça na última coluna. Nesse caso, não há necessidade de puxar as peças para a direita, apenas de inserir uma nova coluna, que já será inserida na direita
	if(chave == 4) {
		//cria uma nova coluna
		*coluna += 1;
		//inicializa as posições da nova coluna com espaços
		for(i = 0; i < *linha; i++) {
			tabuleiro[i][*coluna-1].letra = ' ';
			tabuleiro[i][*coluna-1].num = ' ';
		}
	}
}
