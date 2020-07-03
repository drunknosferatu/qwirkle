#include"struct.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void trocaPecas(peca *pecasJog, char letra,char num ,peca *pecas){
	srand(time(NULL));
	for(int i=0; i<6; i++){
		printf("hm");
		if(pecasJog[i].num==num&&pecasJog[i].letra==letra){
			char auxLetra;
			char auxNum;
			int auxPosicao;
			printf("hm");
			for(auxPosicao=0;auxPosicao<108;auxPosicao++){
				if(pecas[auxPosicao].num==' '){
					break;
				}
			}
			printf("%d",auxPosicao);
			int posicao=rand()%auxPosicao;
			auxNum=pecas[posicao].num;
			auxLetra=pecas[posicao].letra;
			pecas[posicao].num=num;
			pecas[posicao].letra=letra;
			for(int j=auxPosicao;j>0;j--){
				pecas[j].num=pecas[j-1].num;
				pecas[j],letra=pecas[j-1].letra;
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








