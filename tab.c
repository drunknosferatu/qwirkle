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

peca ** realocaTab(peca **tabuleiro, int *maxlinhas, int *maxcolunas, int chave) {
	
	if(!chave) *maxlinhas += 5;
	if(chave) *maxcolunas += 5;
	//realoca um tabuleiro de dimensão MxN, sendo M o número de linhas e N o número de colunas
	tabuleiro = realloc(tabuleiro, (sizeof(peca) * ((*maxlinhas)*(*maxcolunas))));
	
	return tabuleiro;
}

peca ** atualizaTab(peca **tabuleiro, int linhaJog, int colunaJog, int *linha, int *coluna, int *maxlinhas, int *maxcolunas) {
	
	if((linhaJog == *linha) || (linhaJog == 0)) {
		*linha += 2;
		if(*linha == *maxlinhas) realocaTab(tabuleiro, maxlinhas, maxcolunas, 0);
		for(int i = (*linha - 2); i >= 0; i--) {
			for(int j = *coluna; j >= 0; j--) {
				if(tabuleiro[i][j].letra != ' ') {
					tabuleiro[i+1][j].letra = tabuleiro[i][j].letra;
					tabuleiro[i+1][j].num = tabuleiro[i][j].num;
					tabuleiro[i][j].letra = ' ';
					tabuleiro[i][j].num = ' ';
				}
			}
		}
	}

	if(colunaJog == *linha || colunaJog == 0) {
        	*coluna += 2;
		if(*coluna == *maxcolunas) realocaTab(tabuleiro, maxlinhas, maxcolunas, 1);
                for(int i = (*coluna - 2); i >= 0; i--) {
                        for(int j = *linha; j >= 0; j--) {
                                if(tabuleiro[j][i].letra != ' ') {
                                        tabuleiro[j][i+1].letra = tabuleiro[j][i].letra;
                                        tabuleiro[j][i+1].num = tabuleiro[j][i].num;
                                        tabuleiro[j][i].letra = ' ';
                                        tabuleiro[j][i].num = ' ';
                                }
                        }
                }
        }


}
