#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tab.h"
#include "pecas.h"

//verifica se o jogador pode ou não fazer a jogada que deseja
int verificaJogada(peca **tabuleiro, peca pecaJog, int linhaJog, int colunaJog, int linha, int coluna, int *pontos) {
	int i;
	//existem quatro posições que PODEM invalidar uma jogada. São elas: a de cima, de baixo, da esquerda e da direita. Esse contador acumula quantas dessas posições batem com a posições permitem a jogada. Se as quatro permitirem, a jogada é válida
	int cont = 0;
	//se as quatro posições ao redor estiverem vazias, a pessoa não pode colocar a peça no lugar desejado (exceto na primeira jogada, que não usa essa função). Portanto, a variável vazia guarda quantas casas estão vazias ao redor da posição desejada.
	int vazia = 0;	
	//se a letra for igual a espaço, quer dizer que a posição está vazia. Logo, não há nenhuma restrição e essa posição está de acordo com a jogada. Portanto, o contador é incrementado
	if(colunaJog) {
		if(tabuleiro[linhaJog][colunaJog-1].letra == ' ') {
			cont++;
			vazia++;
		//caso não seja espaço, a posição está ocupada. Portanto, para a jogada ser possível, OU a letra, OU o número da peça da jogada deve ser igual à da peca que já está posicionada. Se for, a peça da jogada está de acordo com a peça ao lado e o contador é incrementado
		} else {
			if((tabuleiro[linhaJog][colunaJog-1].letra == pecaJog.letra) || (tabuleiro[linhaJog][colunaJog-1].num == pecaJog.num))
				cont++;
			else return 0;
		}
	} else {
		cont++;
		vazia++;
	}
	//o procedimento é repetido para as quatro posições anteriormente mencionadas
	if(linhaJog) {
		if(tabuleiro[linhaJog-1][colunaJog].letra == ' ') {
		       	cont++;
			vazia++;
		} else {
			if((tabuleiro[linhaJog-1][colunaJog].letra == pecaJog.letra) || (tabuleiro[linhaJog-1][colunaJog].num == pecaJog.num))
                        	cont++;
			else return 0;
		}
	} else {
		cont++;
		vazia++;
	}

	if(colunaJog != (coluna-1)) {
		if(tabuleiro[linhaJog][colunaJog+1].letra == ' ') {
		       	cont++;
			vazia++;
		} else {
			if((tabuleiro[linhaJog][colunaJog+1].letra == pecaJog.letra) || (tabuleiro[linhaJog][colunaJog+1].num == pecaJog.num))
                        	cont++;
			else return 0;
		}
	} else {
		cont++;
		vazia++;
	}

	if(linhaJog != (linha-1)) {
		if(tabuleiro[linhaJog+1][colunaJog].letra == ' ') {
			cont++;
			vazia++;
		} else {
			if((tabuleiro[linhaJog+1][colunaJog].letra == pecaJog.letra) || (tabuleiro[linhaJog+1][colunaJog].num == pecaJog.num))
                        	cont++;
			else return 0;
		}
	} else {
		cont++;
		vazia++;
	}

	//não pode ter duas peças iguais na mesma linha ou coluna sequencial de peças. Nesse sentido, a linha e a coluna de peças aonde o jogador deseja inserir sua peça são conferidas para que isso não ocorra
	//nesse ponto, a coluna de peças acima da posição é conferida para ver se uma peça igual já não foi inserida na mesma. Caso tenha sido, a jogada é inválida e a função retorna 0 (falso).
	if(linhaJog) {
		i = linhaJog - 1;
		while((tabuleiro[i][colunaJog].letra != ' ') && (i >= 0)) {
			if((tabuleiro[i][colunaJog].letra == pecaJog.letra) && (tabuleiro[i][colunaJog].num == pecaJog.num)) return 0;
			*pontos++;
			i--;
		}
	}	
	//o mesmo procedimento é repetido para coluna abaixo, a linha à esquerda e a linha à direita
	i = linhaJog + 1;
	while((tabuleiro[i][colunaJog].letra != ' ') && (i < linha)) {
        	if((tabuleiro[i][colunaJog].letra == pecaJog.letra) && (tabuleiro[i][colunaJog].num == pecaJog.num)) return 0;
                *pontos++;
		i++;
        }
	
	if(colunaJog) {
		i = colunaJog - 1;
        	while((tabuleiro[linhaJog][i].letra != ' ') && (i >= 0)) {
                	if((tabuleiro[linhaJog][i].letra == pecaJog.letra) && (tabuleiro[linhaJog][i].num == pecaJog.num)) return 0;
                	*pontos++;
			i--;
        	}
	}

	i = colunaJog + 1;
        while((tabuleiro[linhaJog][i].letra != ' ') && (i < coluna)) {
                if((tabuleiro[linhaJog][i].letra == pecaJog.letra) && (tabuleiro[linhaJog][i].num == pecaJog.num)) return 0;
                *pontos++;
		i++;
        }


	//se o contador for igual a 4, a peça está de acordo com as 4 posições que a circundam e a jogada é válida. Logo, a função retorna 1 (verdadeiro). Caso contrário, a jogada é inválida e a função retorna 0. Além disso, as quatro posições ao redor da peça não podem ser vazias, se não a peça estaria sendo inserida numa posição isolada de todas as demais
	if(cont == 4 && vazia != 4) {
		
		return 1;
	}
	return 0;
}

void posJogada(peca* pecasJog, peca* pecas){
	int i=0;
	while(i<6){
		if (pecasJog[i].letra==' '){
			int j=0;
			while(j<108){
				if(pecas[j].letra==' ')break;
				j++;
			}
			pecasJog[i].letra=pecas[j-1].letra;
			pecasJog[i].num=pecas[j-1].num;
			pecas[j-1].num=' ';
			pecas[j-1].letra=' ';
		}
	i++;
	}
}



void jogada(peca **tabuleiro,jogador *jogadores, peca *pecas, int vez, int *linha, int *coluna, int *jogadasT) {
	int jogadasTotais = *jogadasT; 
	char movimento[30];
	char entrada[30];
	int guardaLinha;
	int guardaColuna;
	char loc;
	int flag = 0;
	int jogada = 1;
	int auxPontos = 0;
	while(1){
		printf("Jogada: %d\n\n\n", jogada);
		printf("Jogadas totais: %d\n\n\n", jogadasTotais);
		imprimeTab(tabuleiro, *linha, *coluna);
		printf("\nVez do(a) %s\n", jogadores[vez].nome);
		printf("Peças disponiveis: ");
		int i;
		for(i = 0; i < 6; i++){
			if(jogadores[vez].pecasJog[i].letra!=' ')printf("%c%c ", jogadores[vez].pecasJog[i].letra, jogadores[vez].pecasJog[i].num);
		}
		printf("\n\nQuantidade de pontos: %d\n\n", jogadores[vez].pontos);
		printf("\n\nComandos disponiveis:\n-Para jogar, digite jogar -peca- -linha- -coluna- (exemplo: jogar E5 0 0) e em seguida pressione Enter;\n");
		printf("-Para trocar uma peca, digite trocar -peca- (exemplo: trocar E5) e em seguida pressione Enter;\n");
		printf("-Para passar sua vez, digite passar e em seguida pressione Enter.\n\n");
		printf("O que deseja fazer?\n\n");
		setbuf(stdin,NULL);
		fgets(entrada, 30, stdin);
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
			int k;
			int linhaJog;
			int colunaJog;
			flag = 0;
			for (k = 0; k < 6; k++){
				if (movimento[0]==jogadores[vez].pecasJog[k].letra && movimento[1]==jogadores[vez].pecasJog[k].num){
					while(entrada[j]==' ')j++;
					linhaJog = entrada[j++]-'0';
					while(entrada[j]==' ')j++;
					colunaJog = entrada[j]-'0';
					if(colunaJog<0||colunaJog>=*coluna||linhaJog<0||linhaJog>=*linha){
						printf("Oh Oh! Essa posição nao existe.\n");
						break;
					}
					if(jogadasTotais && verificaJogada(tabuleiro,jogadores[vez].pecasJog[k],linhaJog,colunaJog, *linha, *coluna, &auxPontos)){
						if(jogada == 3) {
							if(loc = 'C') {
								if(colunaJog == guardaColuna) {
									tabuleiro[linhaJog][colunaJog].letra=movimento[0];
									tabuleiro[linhaJog][colunaJog].num=movimento[1];
									jogadores[vez].pecasJog[k].letra=' ';
									jogadores[vez].pecasJog[k].num=' ';
									jogadasTotais++;
									jogadores[vez].pontos += auxPontos;
									auxPontos = 0;
									system("clear || cls");
									flag = 1;
									break;
								} else {
									printf("Oh oh! Jogada invalida. Voce so pode jogar na coluna que jogou nas ultimas jogadas!\n\n");
									break;
								}
							}
							if(loc = 'L') {
								if(linhaJog == guardaLinha) {
									tabuleiro[linhaJog][colunaJog].letra=movimento[0];
									tabuleiro[linhaJog][colunaJog].num=movimento[1];
									jogadores[vez].pecasJog[k].letra=' ';
									jogadores[vez].pecasJog[k].num=' ';
									jogadasTotais++;
									jogadores[vez].pontos += auxPontos;
									auxPontos = 0;
									system("clear || cls");
									flag = 1;
									break;
								} else {
									printf("Oh oh! Jogada invalida. Voce so pode jogar na linha que jogou nas ultimas jogadas!\n\n");
									break;
								}
							}
						}
						if(jogada == 2) {
							if(guardaLinha == linhaJog) {
								loc = 'L';
								tabuleiro[linhaJog][colunaJog].letra=movimento[0];
								tabuleiro[linhaJog][colunaJog].num=movimento[1];
								jogadores[vez].pecasJog[k].letra=' ';
								jogadores[vez].pecasJog[k].num=' ';
								jogadasTotais++;
								jogadores[vez].pontos += auxPontos;
								auxPontos = 0;
								system("clear || cls");
								jogada++;
								flag = 1;
								break;
							}
							if(guardaColuna == colunaJog) {
								loc = 'C';
								tabuleiro[linhaJog][colunaJog].letra=movimento[0];
								tabuleiro[linhaJog][colunaJog].num=movimento[1];
								jogadores[vez].pecasJog[k].letra=' ';
								jogadores[vez].pecasJog[k].num=' ';
								jogadasTotais++;
								jogadores[vez].pontos += auxPontos;
								auxPontos = 0;
								system("clear || cls");
								jogada++;
								flag = 1;
								break;
							}
							printf("Oh oh! Jogada invalida. Voce so pode jogar na linha ou coluna que jogou na ultima jogada!");
							break;
						}
						if(jogada == 1) {
							tabuleiro[linhaJog][colunaJog].letra=movimento[0];
							tabuleiro[linhaJog][colunaJog].num=movimento[1];
							jogadores[vez].pecasJog[k].letra=' ';
							jogadores[vez].pecasJog[k].num=' ';
							jogadasTotais++;
							jogadores[vez].pontos += auxPontos;
							auxPontos = 0;
							system("clear || cls");
							guardaLinha = linhaJog;
							guardaColuna = colunaJog;
							jogada++;
							flag = 1;
							break;
						}
					}else if(!jogadasTotais){
								tabuleiro[linhaJog][colunaJog].letra=movimento[0];
								tabuleiro[linhaJog][colunaJog].num=movimento[1];
								jogadores[vez].pecasJog[k].letra=' ';
								jogadores[vez].pecasJog[k].num=' ';
								jogada++;
								jogadasTotais++;
								jogadores[vez].pontos++;
								system("clear || cls");
								flag = 1;
								break;
					}else{
						system("clear || cls");
						printf("Oh Oh! Jogada invalida.\n");
						break;
					}
				}
			}
			if(flag) {
				if(colunaJog == 0) {
					realocaTab(tabuleiro, linha, coluna, 3);
					guardaColuna++;
				}
				if(colunaJog == (*coluna-1) && (*coluna > 1)) {
					realocaTab(tabuleiro, linha, coluna, 4);
				}
				if(linhaJog == 0) {
					realocaTab(tabuleiro, linha, coluna, 1);
					guardaLinha++;
				}
				if(linhaJog == (*linha-1) && (*linha > 1)) {
					realocaTab(tabuleiro, linha, coluna, 2);
				}
				system("clear || cls");
			}
			if(k==6) printf("Oh Oh! Voce nao tem essa peça.\n");
			if(jogadasTotais==108) {
				*jogadasT = jogadasTotais;
				break;
			}
		}else if((!strcmp(movimento,"trocar")||!strcmp(movimento,"t"))&&jogada==1){
			j=aux;
			int flagValido=0;
			while(entrada[j+1]){
				while(entrada[j]==' ')j++;
				int i=0;
				while(entrada[j]!=' '&&entrada[j+1])movimento[i++]=entrada[j++];
				movimento[i]='\0';
				if (movimento[0] >= 'a'&&movimento[0] <= 'f') {
					movimento[0] -= 'a';
					movimento[0] += 'A';
				}
				aux=trocaPecas(jogadores[vez].pecasJog,movimento[0],movimento[1],pecas);
				if(!aux){
					system("clear || cls");
					printf("Oh Oh! Voce nao tem a peça %c%c. As demais serao trocadas, caso validas.\n",movimento[0], movimento[1]);
				}else flagValido=1;
			}
			if(flagValido){
				system("clear || cls");
				printf("Troca efetuada das peças validas!\n");
				break;
			}
		}else if(!strcmp(movimento,"passar")||!strcmp(movimento,"p")){
			*jogadasT = jogadasTotais;
			system("clear || cls");
			posJogada(jogadores[vez].pecasJog,pecas);
			break;
		}else{
			system("clear || cls");
			printf("Oh Oh! Entrada invalida.");
		}
	}
}
