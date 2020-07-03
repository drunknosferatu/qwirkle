#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

void jogada(jogador *jogadores, peca *pecas, int vez) {
	printf("\nVez do(a) %s\n", jogadores[vez].nome);
	printf("Peças disponiveis: ");
	for(int i = 0; i < 6; i++) printf("%c%c ", jogadores[vez].pecasJog[i].letra, jogadores[vez].pecasJog[i].num);
	printf("\n");
}
