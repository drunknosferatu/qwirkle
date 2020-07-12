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

void realocaTab(peca **tabuleiro, int *linha, int *coluna, int chave) {
	//realoca um tabuleiro de dimensão MxN, sendo M o número de linhas e N o número de colunas
	int i;
	if(chave == 1) { 
		*linha += 2;
		/*tabuleiro = realloc(tabuleiro, sizeof(peca *)*(*linha));	
		//tabuleiro[(*linha)-2] = (peca *) malloc(sizeof(peca)*(*coluna));
		//tabuleiro[(*linha)-1] = (peca *) malloc(sizeof(peca)*(*coluna));
		for(i = 0; i < *coluna; i++) {
			tabuleiro[i] = realloc(tabuleiro[i], sizeof(peca)*(*linha));
		}*/
		for(i = (*linha-1); i >= 0; i--) {
			for(int j = (*coluna-1); j >= 0; j--) {
				if(tabuleiro[i][j].letra != ' ') {
					tabuleiro[i+1][j].letra = tabuleiro[i][j].letra;
					tabuleiro[i+1][j].num = tabuleiro[i][j].num;
					tabuleiro[i][j].letra = ' ';
					tabuleiro[i][j].num = ' ';
					tabuleiro[*linha-1][j].letra = ' ';
					tabuleiro[*linha-1][j].num = ' ';
				}
			}
		}
	}
	
	if(chave == 2) {
		*linha += 1;
		for(i = 0; i < *coluna; i++) {
			//tabuleiro[*linha-2][i].letra = ' ';
			//tabuleiro[*linha-2][i].num = ' ';
			tabuleiro[*linha-1][i].letra = ' ';
			tabuleiro[*linha-1][i].num = ' ';
		}	
	}

	if(chave == 3) {
        	*coluna += 2;
		/*for(i = 0; i < *linha; i++) {
                        tabuleiro = realloc(tabuleiro, sizeof(peca *)*(*linha));
                }
                tabuleiro[(*coluna)-2] = (peca *) malloc(sizeof(peca)*(*linha));
		tabuleiro[(*coluna)-1] = (peca *) malloc(sizeof(peca)*(*linha));*/
        	for(i = (*coluna-1); i >= 0; i--) {
                        for(int j = (*linha-1); j >= 0; j--) {
                                if(tabuleiro[j][i].letra != ' ') {
                                        tabuleiro[j][i+1].letra = tabuleiro[j][i].letra;
                                        tabuleiro[j][i+1].num = tabuleiro[j][i].num;
                                        tabuleiro[j][i].letra = ' ';
                                        tabuleiro[j][i].num = ' ';
					tabuleiro[j][*coluna-1].letra = ' ';
					tabuleiro[j][*coluna-1].num = ' ';
                                }
                        }
                }
	}

	if(chave == 4) {
		*coluna += 1;
		for(i = 0; i < *linha; i++) {
			tabuleiro[i][*coluna-1].letra = ' ';
			tabuleiro[i][*coluna-1].num = ' ';
		}
	}
}
