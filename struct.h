//struct que consiste nas peças do jogo (cada uma possui um número de 1 a 6 e uma letra de A a F)
typedef struct{
        char num;
        char letra;
} peca;

typedef struct {
	char nome[40];
	peca *pecasJog;
	int pontos;
} jogador;
