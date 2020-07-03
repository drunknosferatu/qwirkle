//struct que consiste nas peças do jogo (cada uma possui um número de 1 a 6 e uma letra de A a F)
typedef struct{
        char num;
        char letra;
} peca;

typedef struct {
	char nome[42];
	peca pecasJog[6];
	int pontos;
} jogador;

void trocaPecas(peca *pecasJog,char num, char letra, peca *pecas);
