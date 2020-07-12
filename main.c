#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "entrada.h"
#include "pecas.h"
#include "tab.h"
#include "jogada.h"
#include "flush.h"



int main(int *argc, char *argv[]) {
	//primeira e segunda dimensão de vetores e ints auxiliares
	int i;
	int j;
	//número de linhas e colunas do tabuleiro
	int linha = 1;
	int coluna = 1;
	//inicializa um ponteiro para os jogadores e um para as peças e o número de jogadores
	jogador *jogadores;
	int nJog;
	peca *pecas;
	//variável que guarda de quem é a vez de jogar
	int vez = 0;
	int jogadasT = 0;
	//aloca memória para as peças do jogo e as inicializa
	pecas = (peca *) malloc (sizeof(peca) * 108);
	inicializaPecas(pecas);
	//printa a interface inicial do jogo e recebe o número de jogadores
	system("clear || cls");
	printf("Bem-vindo ao Qwirkle! =)\n\nInsira o numero de jogadores (2 a 18): ");
	setbuf(stdin, NULL);
	scanf("%d", &nJog);
	//não permite que o usuário insira um número inválido de jogadores (menos que 2 ou mais que 18)
	while(nJog > 18 || nJog < 2) {
		printf("\nOh oh! Numero de jogadores invalido. Por favor, tente novamente inserindo numeros de 2 a 18.\n\n");
		setbuf(stdin, NULL);
		scanf("%d", &nJog);
	}
	//faz a alocação de memória pro ponteiro de jogadores e inicializa os jogadores com seus nomes, suas peças e pontuações iniciais (0)
	jogadores = (jogador *) malloc(sizeof(jogador) * nJog);
	configuraJogo (nJog, jogadores, pecas);
	
	//inicializa o tabuleiro como uma matriz de peças (que, por sua vez, são structs), com 5x5 posições abertas inicialmente
	peca **tabuleiro;
	tabuleiro = (peca **) malloc(sizeof(peca *)*108);
	
	for(i=0; i < 108; i++) {
		//aloca as colunas da matriz
		tabuleiro[i] = (peca *) malloc(sizeof(peca)*108);
		/*for (j=0; j < coluna; j++) {
			//inicializa as posições do tabuleiro com espaços
			tabuleiro[i][j].num=' ';
			tabuleiro[i][j].letra=' ';*/
		}
		tabuleiro[0][0].num = ' ';
		tabuleiro[0][0].letra = ' ';
	//}	
	//modo recebe o modo de jogo (cheat ou normal) e w é a flag que é levantada quando alguém ganhar o jogo (winner)
	char modo;
	printf("\nDeseja jogar no modo cheat? Digite S para sim ou N para nao. Em seguida, pressione Enter: ");
	while(jogadasT != 108) {
		setbuf(stdin, NULL);
		modo = getc(stdin);
		switch(modo) {
			case('S'):
			case('s'):
				system("clear || cls");
				printf("Divirta-se! =)\n\n");
				printf("Obs.: voce esta no cheat mode\n\n");
				break;
			case('N'):
			case('n'):
				system("clear || cls");
				getchar();
				while (jogadasT != 108) {
					jogada(tabuleiro, jogadores, pecas, vez, &linha, &coluna, &jogadasT);
					vez++;
					if(vez==nJog){
						vez=0;
					}
				}
				break;
			default:
				printf("\nOh oh! Opcao invalida. Tente novamente inserindo os caracteres S ou N.\n\n");
				break;
		}
	}
	free(jogadores);
	free(pecas);
}
