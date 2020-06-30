#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "entrada.h"
#include "tab.h"

int main(int *argc, char *argv[]) {
	int i; //primeira dimensão de vetores e int auxiliar
	int j; //segunda dimensão de vetores e int auxiliar
	jogador *jogador;
	int nJog;
	nJog = configuraJogo(jogador);
	peca *pecas;
	pecas = malloc (sizeof(peca) * 108); //alocando espaço para peças
	peca **tabuleiro; //matriz de structs utilizada como tabuleiro
	tabuleiro = (peca **) malloc(sizeof(peca *) * 6);//a matriz vai ter inicialmente 6x6 structs abertas
	
	for(i=0; i<6; i++) {
		tabuleiro[i] = (peca *) malloc(sizeof(peca) * 6); //aloca as colunas da matriz
		for (j=0; j<6; j++) {
			//inicializa as posições do tabuleiro com espaços
			tabuleiro[i][j].num=' ';
			tabuleiro[i][j].letra=' ';
		}
	}	
	
	imprimeTab(tabuleiro,6,6); //imprime o tabuleiro inicial
	inicializaPecas(pecas); //inicializa as peças do jogo
}
