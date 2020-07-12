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

	//esse laço inicializa as peças
	while(j<108) {
		k=0;
		//randomiza uma posição para a peça
		posicao=rand()%108;
		//esse laço confere se a posição randomizada já está ocupada
		while(k<j){
			//confere se a posição sorteada já está sendo utilizada
			if(usados[k]==posicao){
				//caso esteja, uma nova posição é randomizada para a peça e o k é reinicializado
				posicao=rand()%108;
				k=-1;
			}
			k++;
		}
		//computa a nova posição nas posições já usadas
		usados[j]=posicao;
		//atribui letra e número à peça
		pecas[posicao].num = '1'+i;
		pecas[posicao].letra = aux;
		i++;
		j++;
		//faz com que as letras variem apenas entre 'A' e 'F' e que os números variem entre '1' e '6'
		if (i == 6){
			i=0;
			aux++;
			if (aux == 'G') aux = 'A';
		}
	}
}

//troca peças do jogador
int trocaPecas(peca *pecasJog, char letra,char num ,peca *pecas) {
	srand(time(NULL));
	for(int i=0; i<6; i++){
		//confere se a peça na mão do jogador corresponde à peça que ele pediu para trocar
		if(pecasJog[i].num==num&&pecasJog[i].letra==letra){
			char auxLetra;
			char auxNum;
			int auxPosicao;
			//percorre o vetor de peças, até a primeira posição em branco ("última peça do saco")
			for(auxPosicao=0;auxPosicao<108;auxPosicao++){
				if(pecas[auxPosicao].num==' '){
					break;
				}
			}
			//sorteia uma nova posição pra peça que estava na mão do jogador, porque deve existir a possibilidade de ele pegar sua própria peça (joga no saco e pega sua própria peça). isso acontece se a posição sorteada for a última do vetor
			int posicao=rand()%auxPosicao;
			//como a posição sorteada já estava ocupada, variáveis auxiliares recebem sua letra e número para ela não ser perdida
			auxNum=pecas[posicao].num;
			auxLetra=pecas[posicao].letra;
			//a posição sorteada recebe a peça que estava na mão do jogador
			pecas[posicao].num=num;
			pecas[posicao].letra=letra;
			//"puxa" todas as peças para trás no vetor de peças (seus índices são aumentados em uma unidade)
			for(int j=auxPosicao;j>0;j--){
				pecas[j].num=pecas[j-1].num;
				pecas[j].letra=pecas[j-1].letra;
			}
			//a peça que ocupava a posição na qual a peça do jogador foi inserida, se torna a primeira do vetor de peças
			pecas[0].letra=auxLetra;
			pecas[0].num=auxNum;
			//o jogador recebe a última peça do saco
			pecasJog[i].letra=pecas[auxPosicao].letra;
			pecasJog[i].num=pecas[auxPosicao].num;
			//a peça que o jogador recebeu é "zerada"
			pecas[auxPosicao].num=' ';
			pecas[auxPosicao].letra=' ';
			return 1;
		}
	}
	//se a função retornar 0, significa que o usuário pediu para trocar uma peça que não está na sua mão.
	return 0;
}
