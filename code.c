#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 10
#define M 10
#define TEM_BOMBA -1
#define POS_INVALIDA -2
#define VERDADEIRO 1
#define FALSO 0

// estrutura criada para conter informações sobre cada posição do campo
struct Campo {
	int qnt_bombas; // indica a quantidade de bombas vizinhas; apenas para campos sem bombas
	int bomba; // indica com TEM_BOMBA para indicar que tem uma bomba na posição; apenas para campos com bombas
	int saiu; // indica com VERDADEIRO ou FALSO se o jogador já escolheu aquela posição ou não
};

typedef struct Campo Campo;

// imprime o campo minado no formato adequado
void print_campo(Campo campo_minado[12][12]) {
	int i, j;

	printf("    0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9\n");
	printf("  -----------------------------------------\n");

	for (i = 1; i < 11; i++) {
		printf("%d | ", i-1);
		for (j = 1; j < 11; j++) {
			if (campo_minado[i][j].bomba == TEM_BOMBA) printf("* | ");
			else printf("%d | ", campo_minado[i][j].qnt_bombas);
		}
		printf("\n");
		printf("  -----------------------------------------\n");
	}

	printf("\n");
}

// cria um vetor com posições aleatórias para preencher o campo com bombas nessas posições
void preencher_bombas(Campo campo_minado[12][12]) {
	int posicoes[30] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int i, alea, contagem = 0, saiu;

	srand(time(NULL)); // randomiza novos números toda vez que o programa roda

	while(contagem < 30) {
		alea = rand() % (N*M);
		saiu = FALSO;
		
		// confere se a posição aleatorizada já saiu ou não, garantindo que sempre tenham 30 bombas no mapa
		for (i = 0; i < 30; i++) {
			if(posicoes[i] == alea) {
				saiu = VERDADEIRO;
				break;
			}
		}
		
		// se a posição não saiu ainda, coloca no vetor
		if(!saiu) {
			posicoes[contagem] = alea;
			contagem++;
		}
	}

	// insere no campo as bombas
	// int(posicoes[i]/M) + 1 e posicoes[i]%M + 1 encontra o índice correspondente da matriz
	// soma + 1 pois as bordas não fazem parte do jogo
	for (i = 0; i < 30; i++) {
		campo_minado[((int)posicoes[i]/M) + 1][posicoes[i]%M + 1].bomba = TEM_BOMBA;
	}
}

// prepara o campo minado antes do jogador começar a jogar
void inciar_campo(Campo campo_minado[12][12]) {
	int i, j, soma;

	// marca que ainda nenhuma posição foi escolhida pelo jogador
	// percorre de 1 a < 11 pois as bordas não fazem parte do jogo
	for (i = 1; i < 11; i++)
		for (j = 1; j < 11; j++)
			campo_minado[i][j].saiu = FALSO;

	// marca as bordas da matriz como inválidas, já que não fazem parte do campo minado
	for (i = 0; i < 12; i++)
		for (j = 0; j < 12; j++)
			if (i == 0 || j == 0 || i == 11 || j == 11)
				campo_minado[i][j].qnt_bombas = POS_INVALIDA;

	preencher_bombas(campo_minado);

	// percorre a matriz somando a quantidade de bombas vizinhas e marcando no campo
	for (i = 1; i < 11; i++) {
		for (j = 1; j < 11; j++) {
			soma = 0;
			if (campo_minado[i-1][j].qnt_bombas != POS_INVALIDA && campo_minado[i-1][j].bomba == TEM_BOMBA) 
				soma++;
			if (campo_minado[i+1][j].qnt_bombas != POS_INVALIDA && campo_minado[i+1][j].bomba == TEM_BOMBA) 
				soma++;
			if (campo_minado[i][j-1].qnt_bombas != POS_INVALIDA && campo_minado[i][j-1].bomba == TEM_BOMBA) 
				soma++;
			if (campo_minado[i][j+1].qnt_bombas != POS_INVALIDA && campo_minado[i][j+1].bomba == TEM_BOMBA) 
				soma++;

			campo_minado[i][j].qnt_bombas = soma;
		}
	}
}

int main() {
	// criamos uma matriz [12][12] para facilitar a checagem de vizinhos; as bordas não fazem parte do jogo
	Campo campo_minado[12][12];
	int i, j, count = 0;

	inciar_campo(campo_minado);
	print_campo(campo_minado);

	return 0;
}