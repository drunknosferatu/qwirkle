#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

//recebe as configurações do jogo, por meio da struct config
//config entrada(config dados) {

//}

//inicializa as peças do jogo
char **inicializaPecas(char *pecas[3]) {
	
	//aloca memória para as peças 
	for(int i = 0; i < 107; i++) {
		pecas[i] = (char *) malloc(sizeof(char)*3);
	}
	
	//inicializa as peças de fato
	char aux = 'A';	
	for(int i = 0; i < 107; i++) {
		for(int j = 0; j < 6; j++) {
			pecas[i][0] = aux;
			pecas[i][1] = '1' + j;
			pecas[i][2] = '\0';
		}
		aux++;
		if(aux == 'F') aux = 'A';
	}
	return pecas;
}
