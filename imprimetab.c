#include<stdio.h>
#include "peca.h"	
void imprimetab(peca **tabuleiro,int linha, int coluna){
	int aux;
	printf(" ");
	for (aux=0;aux<coluna;aux++){
		printf("  %d ",aux);
	}
	printf("\n");
	for (int i=0;i<linha;i++){
		printf(" ");
		for(aux=0;aux<coluna*4;aux++){
			printf("-");
		}
		printf("\n");
		printf("%d", i);
		for (int j=0;j<coluna;j++){
			printf("|%c", tabuleiro[i][j].letra);
			printf("%c|",tabuleiro[i][j].num);
		}
		printf("%d\n",i);
	}
	printf(" ");
	for(aux=0;aux<coluna*4;aux++){
		printf("-");
	}
	printf("\n");
	printf(" ");
	for (aux=0;aux<coluna;aux++){
		printf("  %d ",aux);
	}
	printf("\n");
}
