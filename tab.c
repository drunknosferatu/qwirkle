#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

void imprimeTab(peca **tabuleiro,int linha, int coluna){
	int aux;
	printf(" ");
	for (aux=0;aux<coluna;aux++){
		printf(" %d ",aux);
	}
	printf("\n");
	for (int i=0;i<linha;i++){
		printf(" -");
		for(aux=0;aux<coluna*3;aux++){
			printf("-");
		}
		printf("\n");
		printf("%d", i);			
		printf("|");
		for (int j=0;j<coluna;j++){
			printf("%c", tabuleiro[i][j].letra);
			printf("%c|",tabuleiro[i][j].num);
		}
		printf("%d\n",i);
	}
	printf(" -");
	for(aux=0;aux<coluna*3;aux++){
		printf("-");
	}
	printf("\n");
	printf(" ");
	for (aux=0;aux<coluna;aux++){
		printf(" %d ",aux);
	}
	printf("\n");
}

peca ** realocaTab(peca **tabuleiro, int *maxlinhas, int *maxcolunas) {
	*maxlinhas += 5;
	*maxcolunas += 5;
	//realoca um tabuleiro de dimensão MxN, sendo M o número de linhas e N o número de colunas
	tabuleiro = realloc(tabuleiro, (sizeof(peca) * ((*maxlinhas)*(*maxcolunas))));
	
	return tabuleiro;
}
