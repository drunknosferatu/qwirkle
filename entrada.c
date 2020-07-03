#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

//recebe as configurações do jogo
void configuraJogo(int nJog, jogador *jogadores, peca *pecas) {
	int i = 0; //contador para o número de jogadores
	int j; //contador auxiliar
	char auxC[42]; //char auxiliar para verificacoes do nome
	int auxI = 0; //int auxiliar

	//recebe o nome dos jogadores
	while (i < nJog) {
		auxI = 0;
		while (!auxI) {
			printf("\nInsira o nome do jogador %d (ate 40 caracteres) e pressione Enter: ", i+1);
                	setbuf(stdin, NULL);
                	fgets(auxC, 50, stdin);
					

			if (strlen(auxC) > 42) {
				printf("\nEsse nome e grande demais. Tente novamente inserindo um nome de no maximo 40 caracteres.\n");
                        	while (getchar() != '\n');
				continue;
			}

			for (j = 0; j < i; j++) {
				if(strcmp(auxC, jogadores[j].nome) == 0) {
					printf("\nOh oh! Esse nome ja foi inserido. Por favor, tente colocar outro nome.\n\n");
					break;
				}
			}
			if (j == i) {
				strcpy(jogadores[i].nome, auxC);
				auxI = 1;
			}
		}	
		i++;
	}
	
	auxI = 0;
	for(i = 0; i < nJog; i++) {
		jogadores[i].pontos = 0;
		for(j = 0; j < 6; j++) {
			jogadores[i].pecasJog[j].num = pecas[107-auxI].num;
			jogadores[i].pecasJog[j].letra = pecas[107-auxI].letra;
			pecas[107-auxI].num = ' ';
			pecas[107-auxI].letra = ' ';
			auxI++;
		}
	}
}
