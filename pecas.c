#include"struct.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

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

void trocaPecas(peca *pecasJog, char letra,char num ,peca *pecas) {
	srand(time(NULL));
	for(int i=0; i<6; i++){
		if(pecasJog[i].num==num&&pecasJog[i].letra==letra){
			char auxLetra;
			char auxNum;
			int auxPosicao;
			for(auxPosicao=0;auxPosicao<108;auxPosicao++){
				if(pecas[auxPosicao].num==' '){
					break;
				}
			}
			int posicao=rand()%auxPosicao;
			auxNum=pecas[posicao].num;
			auxLetra=pecas[posicao].letra;
			pecas[posicao].num=num;
			pecas[posicao].letra=letra;
			for(int j=auxPosicao;j>0;j--){
				pecas[j].num=pecas[j-1].num;
				pecas[j].letra=pecas[j-1].letra;
			}
			pecas[0].letra=auxLetra;
			pecas[0].num=auxNum;
			pecasJog[i].letra=pecas[auxPosicao].letra;
			pecasJog[i].num=pecas[auxPosicao].num;
			pecas[auxPosicao].num=' ';
			pecas[auxPosicao].letra=' ';
			break;
		}
	}
}
