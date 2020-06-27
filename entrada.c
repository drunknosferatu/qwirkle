#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

//recebe as configurações do jogo, por meio da struct config
//config entrada(config dados) {

//}

//inicializa as peças do jogo
char **inicializaPecas(char *pecas[3]) {
	
	//aloca memória para as peças 
	for(int i = 0; i < 108; i++) {
		pecas[i] = (char *) malloc(sizeof(char)*3);
	}
	
	//inicializa as peças de fato
	char aux = 'A';	
	int i = 0;
	int j = 0;
	while (i<108){
		pecas[i][0] = aux;
		pecas[i][1] = '1' + j;
		pecas[i][2] = '\0';
		i++;
		j++;
		if (j == 6){
			j=0;
			aux++;
			if (aux == 'G') aux = 'A';
		}
	}
	return pecas;
}
