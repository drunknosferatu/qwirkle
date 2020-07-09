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
	//número de linhas e colunas do tabuleiro, em tempo real
	int linha = 1;
	int coluna = 1;
	//limite máximo de linhas e colunas antes de ser dado um realloc
	int maxlinhas = 5;
	int maxcolunas = 5;
	//inicializa um ponteiro para os jogadores e um para as peças e o número de jogadores
	jogador *jogadores;
	int nJog;
	peca *pecas;
	//variável que guarda de quem é a vez de jogar
	int vez = 0;
	
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
	tabuleiro = (peca **) malloc(sizeof(peca *) * maxlinhas);
	
	for(i=0; i < maxlinhas; i++) {
		//aloca as colunas da matriz
		tabuleiro[i] = (peca *) malloc(sizeof(peca) * maxcolunas);
		for (j=0; j < maxcolunas; j++) {
			//inicializa as posições do tabuleiro com espaços
			tabuleiro[i][j].num=' ';
			tabuleiro[i][j].letra=' ';
		}
	}	
	
	//modo recebe o modo de jogo (cheat ou normal) e w é a flag que é levantada quando alguém ganhar o jogo (winner)
	char modo;
	int w = 0;
	printf("\nDeseja jogar no modo cheat? Digite S para sim ou N para nao. Em seguida, pressione Enter: ");

	while(!w) {
		setbuf(stdin, NULL);
		modo = getc(stdin);
		switch(modo) {
			case('S'):
			case('s'):
				system("clear || cls");
				printf("Divirta-se! =)\n\n");
				printf("Obs.: voce esta no cheat mode\n\n");
				w = 1;
				break;
			case('N'):
			case('n'):
				system("clear || cls");
				imprimeTab(tabuleiro, linha, coluna);
				char movimento[30];
				char entrada[30];
				while(1){
					printf("\nVez do(a) %s\n", jogadores[vez].nome);
					printf("Peças disponiveis: ");
					int i;
					for(i = 0; i < 6; i++) printf("%c%c ", jogadores[vez].pecasJog[i].letra, jogadores[vez].pecasJog[i].num);
					printf("\n\nComandos disponiveis:\n-Para jogar, digite jogar -peca- -linha- -coluna- (exemplo: jogar E5 0 0) e em seguida pressione Enter;\n");
					printf("-Para trocar uma peca, digite trocar -peca- (exemplo: trocar E5) e em seguida pressione Enter;\n");
					printf("-Para passar sua vez, digite passar e em seguida pressione Enter.\n\n");
					printf("O que deseja fazer?\n\n");
					flush_in();
					fgets(entrada, 30, stdin);
					//printf("%s",entrada);
					int aux;
					int j=0;
					while(entrada[j]){
						if(entrada[j]==' ') break;
						j++;
					}
					aux=j;
					if(j!=strlen(entrada)){
						movimento[j--]='\0';
						while(j>=0) {
							movimento[j]=entrada[j];
							j--;
						}
					}else{
						strcpy(movimento,entrada);
						movimento[j-1]='\0';
					}
					i=0;
					int cont = 0;
					if (!strcmp(movimento, "jogar")||!strcmp(movimento,"j")){
						j=aux;
						while(entrada[j]==' ')j++;
						int i=0;
						while(entrada[j]!=' '){
						movimento[i++]=entrada[j++];
						}
						movimento[i]='\0';
						if (movimento[0] >= 'a'&&movimento[0] <= 'f') {
							movimento[0] -= 'a';
							movimento[0] += 'A';
						}
						for (int k = 0; k < 6; k++){
							if (movimento[0]==jogadores[vez].pecasJog[k].letra && movimento[1]==jogadores[vez].pecasJog[k].num){
								while(entrada[j]==' ')j++;
								int linhaJog = entrada[j++]-'0';
								while(entrada[j]==' ')j++;
								int colunaJog = entrada[j]-'0';
								if(cont&&verificaJogada(tabuleiro,jogadores[vez].pecasJog[k],linhaJog,colunaJog)){
									tabuleiro[linhaJog][colunaJog].letra=movimento[0];
									tabuleiro[linhaJog][colunaJog].num=movimento[1];
									cont++;
								}else if(!cont){
									tabuleiro[linhaJog][colunaJog].letra=movimento[0];
									tabuleiro[linhaJog][colunaJog].num=movimento[1];
									cont++;
								}else{
									printf("Oh Oh, Entrada inválida\n");
								}
								break;
							}
						}
					}else if(!strcmp(movimento,"trocar")||!strcmp(movimento,"t")){
						j=aux;
						while(entrada[j]==' ')j++;
						int i=0;
						while(entrada[j]!=' '){
							movimento[i++]=entrada[j++];
						}
						movimento[i]='\0';
						if (movimento[0] >= 'a'&&movimento[0] <= 'f') {
							movimento[0] -= 'a';
							movimento[0] += 'A';
						}
						aux=trocaPecas(jogadores[vez].pecasJog,movimento[0],movimento[1],pecas);
						if(!aux){
							printf("Oh Oh, você não tem essa peça\n");
						}
					}else if(!strcmp(movimento,"passar")||!strcmp(movimento,"p")){
							break;
					}else{
						printf("Oh Oh entrada inválida");
					}
				}
				vez++;
				while (!w) {
					jogada(tabuleiro ,jogadores, pecas, vez);
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
