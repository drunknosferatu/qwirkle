#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tab.h"
#include "flush.h"


//verifica se o jogador pode ou não fazer a jogada que deseja
int verificaJogada(peca **tabuleiro, peca pecaJog, int linhaJog, int colunaJog) {
	//não pode ter duas peças iguais na mesma linha ou coluna sequencial de peças. Nesse sentido, a linha e a coluna de peças aonde o jogador deseja inserir sua peça são conferidas para que isso não ocorra
	//nesse ponto, a coluna de peças acima da posição é conferida para ver se uma peça igual já não foi inserida na mesma. Caso tenha sido, a jogada é inválida e a função retorna 0 (falso).
	int i = linhaJog - 1;
	while(tabuleiro[i][colunaJog].letra != ' ') {
		if((tabuleiro[i][colunaJog].letra == pecaJog.letra) && (tabuleiro[i][colunaJog].num == pecaJog.num)) return 0;
		i--;
	}	
	printf("passei");

	//o mesmo procedimento é repetido para coluna abaixo, a linha à esquerda e a linha à direita
	i = linhaJog + 1;
	while(tabuleiro[i][colunaJog].letra != ' ') {
        	if((tabuleiro[i][colunaJog].letra == pecaJog.letra) && (tabuleiro[i][colunaJog].num == pecaJog.num)) return 0;
                i++;
        }
	
	i = colunaJog - 1;
        while(tabuleiro[linhaJog][i].letra != ' ') {
                if((tabuleiro[linhaJog][i].letra == pecaJog.letra) && (tabuleiro[linhaJog][i].num == pecaJog.num)) return 0;
                i--;
        }

	i = colunaJog + 1;
        while(tabuleiro[linhaJog][i].letra != ' ') {
                if((tabuleiro[linhaJog][i].letra == pecaJog.letra) && (tabuleiro[linhaJog][i].num == pecaJog.num)) return 0;
                i++;
        }

	//existem quatro posições que PODEM invalidar uma jogada. São elas: a de cima, de baixo, da esquerda e da direita. Esse contador acumula quantas dessas posições batem com a posições permitem a jogada. Se as quatro permitirem, a jogada é válida
	int cont = 0;

	//se a letra for igual a espaço, quer dizer que a posição está vazia. Logo, não há nenhuma restrição e essa posição está de acordo com a jogada. Portanto, o contador é incrementado
	if(tabuleiro[linhaJog][colunaJog-1].letra == ' ') cont++;
	//caso não seja espaço, a posição está ocupada. Portanto, para a jogada ser possível, OU a letra, OU o número da peça da jogada deve ser igual à da peca que já está posicionada. Se for, a peça da jogada está de acordo com a peça ao lado e o contador é incrementado
	else {
		if((tabuleiro[linhaJog][colunaJog-1].letra == pecaJog.letra) || (tabuleiro[linhaJog][colunaJog-1].num == pecaJog.num))
			cont++;
		else return 0;
	}

	//o procedimento é repetido para as quatro posições anteriormente mencionadas
	if(tabuleiro[linhaJog-1][colunaJog].letra == ' ') cont++;
	else {
		if((tabuleiro[linhaJog-1][colunaJog].letra == pecaJog.letra) || (tabuleiro[linhaJog-1][colunaJog].num == pecaJog.num))
                        cont++;
		else return 0;
	}

	if(tabuleiro[linhaJog][colunaJog+1].letra == ' ') cont++;
	else {
		if((tabuleiro[linhaJog][colunaJog+1].letra == pecaJog.letra) || (tabuleiro[linhaJog][colunaJog+1].num == pecaJog.num))
                        cont++;
		else return 0;
	}

	if(tabuleiro[linhaJog+1][colunaJog].letra == ' ') cont++;
	else {
		if((tabuleiro[linhaJog+1][colunaJog].letra == pecaJog.letra) || (tabuleiro[linhaJog+1][colunaJog].num == pecaJog.num))
                        cont++;
		else return 0;
	}

	//se o contador for igual a 4, a peça está de acordo com as 4 posições que a circundam e a jogada é válida. Logo, a função retorna 1 (verdadeiro). Caso contrário, a jogada é inválida e a função retorna 0.
	if(cont == 4) return 1;
	else return 0;
}
void jogada(peca **tabuleiro,jogador *jogadores, peca *pecas, int vez) {
	printf("\nVez do(a) %s\n", jogadores[vez].nome);
	printf("Peças disponiveis: ");
	
	int i;
	for(i = 0; i < 6; i++) printf("%c%c ", jogadores[vez].pecasJog[i].letra, jogadores[vez].pecasJog[i].num);

	printf("\n\nComandos disponiveis:\n-Para jogar, digite jogar -peca- -linha- -coluna- (exemplo: jogar E5 0 0) e em seguida pressione Enter;\n");
	printf("-Para trocar uma peca, digite trocar -peca- (exemplo: trocar E5) e em seguida pressione Enter;\n");
	printf("-Para passar sua vez, digite passar e em seguida pressione Enter.\n\n");
	printf("O que deseja fazer?\n\n");

  flush_in();

	char entrada[30];
	fgets(entrada, 30, stdin);
	char movimento[30];
	int aux;
  int j=0;
  while(entrada[j]!=' ')j++;
  aux=j;
  movimento[j--]='\0';
  while(j>=0) {
	  movimento[j]=entrada[j];
	  j--;
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
        int linha = entrada[j++]-'0';
        while(entrada[j]==' ')j++;
        int coluna = entrada[j]-'0';
		if(verificaJogada(tabuleiro,jogadores[vez].pecasJog[k],linha,coluna)){
			tabuleiro[linha][coluna].letra=movimento[0];
			tabuleiro[linha][coluna].num=movimento[1];
		}else{
			printf("Oh Oh, Entrada inválida\n");
		}
		break;
        } 
      } 
  }
  imprimeTab(tabuleiro,1,1);
}/*
    printf ("Movimento invalido.\n");
        
  } else {
     if (strcmp(movimento, "trocar")==0){
       movimento = strtok(NULL, " ");
       trocaPecas(jogadores[vez].pecasJog, movimento[0], movimento[1], pecas);
    }
      
      if (strcmp (movimento, "passar")==0){
  
    }
  }

}*/


