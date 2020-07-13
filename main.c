#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "entrada.h"
#include "pecas.h"
#include "tab.h"
#include "jogada.h"



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
	if (pecas==NULL){
		printf("Falha interna. Reinicie o jogo\n");
	}
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
	if(jogadores==NULL){
		printf("Falha interna. Reinicie o jogo\n");
		exit(0);
	}
	configuraJogo (nJog, jogadores, pecas);
	
	//inicializa o tabuleiro como uma matriz de peças (que, por sua vez, são structs), com 5x5 posições abertas inicialmente
	peca **tabuleiro;
	tabuleiro = (peca **) malloc(sizeof(peca *)*108);
	if(tabuleiro==NULL){
		printf("Falha interna. Reinicie o programa\n");
		exit(0);
	}
	
	for(i=0; i < 108; i++) {
		//aloca as colunas da matriz
		tabuleiro[i] = (peca *) malloc(sizeof(peca)*108);
		if(tabuleiro[i]==NULL){
			printf("Falha interna reinicie o programa\n");
			exit(0);
		}
	}
		tabuleiro[0][0].num = ' ';
		tabuleiro[0][0].letra = ' ';
	//modo recebe o modo de jogo (cheat ou normal)
	char modo;
	printf("\nDeseja jogar no modo cheat? Digite S para sim ou N para nao. Em seguida, pressione Enter: ");
		setbuf(stdin, NULL);
		modo = getc(stdin);
		switch(modo) {
			case('S'):
			case('s'):
				system("clear || cls");
				printf("Divirta-se! =)\n\n");
				printf("Obs.: voce esta no cheat mode\n\n");
        	getchar();
				while (jogadasT != 108) {
          cheatMode(tabuleiro, jogadores, pecas, vez, &linha, &coluna, &jogadasT);
					vez++;
					if(vez==nJog){
						vez=0;
					}
				}
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
	char vencedor[42]="  ";
	char empate[42]="  ";
	int maiorPontos=0;
	for(i=0;i<nJog;i++){
		int z=strlen(jogadores[i].nome);
		jogadores[i].nome[z-1]='\0';
		printf("A pontuação do(a) jogador(a) %s foi:" "%d\n", jogadores[i].nome, jogadores[i].pontos);
		if(jogadores[i].pontos>maiorPontos){
			strcpy(vencedor,jogadores[i].nome);
			maiorPontos=jogadores[i].pontos;
		}
		else if(jogadores[i].pontos==maiorPontos&&vencedor!="  ")strcpy(empate,jogadores[i].nome);
	}
	printf("O(a) vencedor(a) foi %s\n", vencedor);
	if(empate[0]!=' ') printf("Houve empate entre %s e %s\n", empate, vencedor);
	free(jogadores);
	free(pecas);
	for(i=0;i<108;i++){
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}
