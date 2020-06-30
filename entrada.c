#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//recebe as configurações do jogo
int configuraJogo(jogador *jogador) {
	int nJog = 0;
	printf("Bem vindo ao Qwirkle! =)\n");
	printf("\nInsira o numero de jogadores (de 2 a 18): ");
	
	//recebe o número de jogadores e aloca o ponteiro para jogadores (cada jogador é uma struct "jogador")
	setbuf(stdin, NULL);
	
	//não permite que o usuário insira um número inválido de jogadores (menor que 2 ou maior que 18 (108 jogadores/6 peças))
	while (nJog < 2 || nJog > 18) {
		scanf("%d", &nJog);
		if (nJog < 2 || nJog > 18) printf("\nOh oh! Numero invalido. Tente novamente inserindo numeros de 2 a 18: ");
	}
	
	jogador = malloc(sizeof(jogador) * nJog); //alocação dos jogadores	
	
	int i = 1; //contador para o número de jogadores
	int j = 1; //contador auxiliar
	char auxC[40]; //char auxiliar para verificacoes do nome
	int auxI = 0; //int auxiliar

	//recebe o nome dos jogadores
	while (i <= nJog) {
		auxI = 0;
		while (!auxI) {
			printf("\nInsira o nome do jogador %d (ate 40 caracteres) e pressione Enter: ", i);
                	setbuf(stdin, NULL);
                	fgets(auxC, 50, stdin);

			if (strlen(auxC) > 40) {
				printf("\nEsse nome e grande demais. Tente novamente inserindo um nome de no maximo 40 caracteres.\n");
                        	while (getchar() != '\n');
				continue;
			}

			for (j = 1; j < i; j++) {
				if(strcmp(auxC, jogador[j].nome) == 0) {
					printf("\nOh oh! Esse nome ja foi inserido. Por favor, tente colocar outro nome.\n\n");
					break;
				}
			}
			if (j == i) {
				strcpy(jogador[i].nome, auxC);
				auxI = 1;
			}
		}	
		i++;
	}

	for (i = 0; i < nJog; i++) {
		jogador[i].pontos = 0;
	}
	return nJog;
}	

//inicializa as peças do jogo
void inicializaPecas(peca *pecas) {
	char aux = 'A';
	int posicao;
	int usados[107];
	int i = 0;
	int j = 0;
	int k = 0;
	srand(time(NULL));
	while(j<108) { //esse laço inicializa as peças
		k=0;
		posicao=rand()%108;//randomiza uma posição para a peça
		while(k<j){//checa se a posição ja esta ocupada
			if(usados[k]==posicao){
				posicao=rand()%108;//randomiza uma nova posição pois a anterior estava ocupada
				k=-1;//reseta k
			}
			k++;
		}
		usados[j]=posicao;//guarda a posição para não ser reutilizada
		pecas[posicao].num = '1'+i;
		pecas[posicao].letra = aux;
		i++;
		j++;
		if (i == 6){
			i=0;
			aux++;
			if (aux == 'G') aux = 'A';
		}
	}
}
