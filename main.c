#include<stdio.h>
#include<stdlib.h>
int main(int *argc, char *argv[]){
	char ***tabuleiro;//matriz de strings utilizada como tabuleiro
	tabuleiro=(char***)malloc(sizeof(char**)*6);//a matriz vai ter inicialmente 6x6 strings abertas
	for(int i=0;i<6;i++){
		tabuleiro[i]=(char**)malloc(sizeof(char*)*6);//aloca as linhas da matriz
		for (int j=0;j<6;j++){
			tabuleiro[i][j]=(char*)malloc(sizeof(char)*3);//aloca as strings referente as peças (letra+numero+\0)
			tabuleiro[i][j][0]=' ';//preenche a matriz com espaços
			tabuleiro[i][j][1]=' ';
			tabuleiro[i][j][2]='\0';
		}
	}
}

