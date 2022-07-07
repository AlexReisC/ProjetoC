#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "carta.h"
#include "lista.h"
#include "pilha.h"

int main() {
	setlocale(LC_ALL, "Portuguese");
	//Criar m�o, mesa e baralho
	Lista *mao, *mesa;
	mao = NULL;
	mao = criarLista();
	mesa = NULL;
	mesa = criarLista();
	Pilha *baralho;
	baralho = NULL;
	baralho = criarPilha();
	
	//Criar cole��o do Jogador
	Lista **colecaoJogador;
	colecaoJogador = (Lista **)malloc(sizeof(Lista *)*6);
	int i;
	for(i=0 ; i<6 ; i++){
		colecaoJogador[i] = criarLista();
	}
	//Criar cole��o do Computador
	Lista **colecaoComputador;
	colecaoComputador = (Lista **)malloc(sizeof(Lista *)*6);
	for(i=0 ; i<6 ; i++){
		colecaoComputador[i] = criarLista();
	}
	
	struct carta c;

	printf(" ---------- PARADE ---------- \n");
	printf("| Feito por: Alex Reis |\n");
	
	//Criar Baralho e embaralhar
	int j;
	for(i = 0; i < 11; i++){
		for(j = 0; j < 6; j++){
			c.numero = i;
			c.naipe = 'A' + j;
			empilhar(baralho,c);
		}
	}
	for(i = 0; i < 66; i++){
		embaralhar(baralho);
	}
	
	//Adicionar 5 cartas a m�o
	for(i=0; i<5; i++){
		desempilhar(baralho,&c);
		inserirInicio(mao,c);
	}
	printf("\nMAO: ");
	imprimir(mao);
	
	//imprimir a Cole��o do Jogador
	printf("\n\nCole��o do Jogador ");
	for(i = 0; i < 6; i++){
		printf("\n%c -> ", 'A' + i);
		imprimir(colecaoJogador[i]);
		if(*colecaoJogador[i] == NULL){
			printf("Vazio");
		}
	}
	
	//Adicionar 6 cartas a mesa
	for(i=0; i<6; i++){
		desempilhar(baralho,&c);
		inserirInicio(mesa,c);
	}
	printf("\n\nMESA: ");
	printf("[NOVA CARTA] ");
	imprimir(mesa);
	printf("\n| %d Cartas no Baralho |\n", tamanho(baralho));
	
	//Fazer as jogadas
	int x;
	do{
		//Jogador joga uma carta
		do{
			printf("\nDigite a posi��o da carta que quer jogar (1 a 5): ");
			scanf("%d",&x);
			if(x >= 6 || x <= 0){
				printf("N�o existe carta nessa posi��o! P� amig�o joga direito.");
			}
		} while(x >= 6 || x <= 0);
	
		acessarIndice(mao,x,&c);
		removerQualquer(mao,c);
		inserirInicio(mesa,c);
		desempilhar(baralho,&c);
		inserirInicio(mao,c);	
	
		//Adicionar na Cole��o do Jogador
		acessarIndice(mesa,1,&c);
		adicionarColecao(mesa,c,colecaoJogador);
		printf("\nMESA: ");
		printf("[NOVA CARTA] ");
		imprimir(mesa);
		printf("\n| %d Cartas no Baralho |\n", tamanho(baralho));
		printf("\nMAO: ");
		imprimir(mao);
	
		//imprimir a Cole��o do Jogador
		printf("\n\nCole��o do Jogador ");
		for(i = 0; i < 6; i++){
			printf("\n%c -> ", 'A' + i);
			imprimir(colecaoJogador[i]);
			if(*colecaoJogador[i] == NULL){
				printf("Vazio");
			}
		}
	
		//Computador jogar uma carta
		desempilhar(baralho,&c);
		inserirInicio(mesa,c);

		//Adicionar na cole��o do Computador
		acessarIndice(mesa,1,&c);
		adicionarColecao(mesa,c,colecaoComputador);
		printf("\n\nMESA: ");
		printf("[NOVA CARTA] ");
		imprimir(mesa);
		printf("\n| %d Cartas no Baralho |\n", tamanho(baralho));
		
		//Jogador perdeu
		// Tem todas as cores na cole��o
		int contador = 0;
		for(i = 0; i < 6; i++){
			if(*colecaoJogador[i] != NULL){
				contador++; 
			}
		}
		if(contador == 6){
			printf("\n ----> VOC� PERDEU POIS TEM TODAS AS CORES NA SUA COLE��O! <---- ");
			break;
		}
		
	}while(tamanho(baralho) > 0 );
	
	//Jogador tem s� 4 cartas
	int contZero = 0;
	if(tamanho(baralho) == 0 && quantidade(mao) == 4){
		for(i = 1; i < 6; i++){
			acessarIndice(mao,i,&c);
			if(c.numero == 0){
				contZero++;
			}
		}
	}
	
	int a;
	switch(contZero){
		//Tem 1 ou nenhum zero na m�o
		case 0 || 1:
			for(i = 0; i < 2; i++){
				do{
					printf("\nDigite a posi��o da carta que quer jogar (1 a 5): ");
					scanf("%d",&a);
					if(a >= 6 || a <= -1){
						printf("N�o existe carta nessa posi��o! P� amig�o joga direito.");
					}
				}while(a >= 6 && a <= -1);
				
				acessarIndice(mao,a,&c);
				removerQualquer(mao,c);
				inserirInicio(mesa,c);
				desempilhar(baralho,&c);
				inserirInicio(mao,c);	
	
				acessarIndice(mesa,1,&c);
				adicionarColecao(mesa,c,colecaoJogador);
				printf("\nMESA: ");
				printf("[NOVA CARTA] ");
				imprimir(mesa);
				printf("\nMAO: ");
				imprimir(mao);
	
				printf("\n\nCole��o do Jogador ");
				for(i = 0; i < 6; i++){
					printf("\n%c -> ", 'A' + i);
					imprimir(colecaoJogador[i]);
					if(*colecaoJogador[i] == NULL){
						printf("Vazio");
					}
				}
			}
			//Somar pontos
			int cartasJ = 0;
			for(i = 0; i < 6; i++){
				if(quantidade(colecaoJogador[i]) <= quantidade(colecaoComputador[i])){
					cartasJ += somaValores(colecaoJogador[i]);
				} else{
					cartasJ += quantidade(colecaoJogador[i]);
				}
			}
			if(cartasJ == 0){
				printf("\n ----> VOC� VENCEU !!! <---- ");
			} else{
				printf("\n Voc� fez: -%d pontos", cartasJ);
			}
			break;
		case 2:
			//Tem 2 zeros na m�o
			for(i = 0; i < 6; i++){
				if(quantidade(colecaoJogador[i]) <= quantidade(colecaoComputador[i])){
					cartasJ += somaValores(colecaoJogador[i]);
				} else{
					cartasJ += quantidade(colecaoJogador[i]);
				}
			}
			if(cartasJ == 0){
				printf("\n ----> VOC� VENCEU PERFEITAMENTE!!! <---- ");
			} else{
				printf("\n Voc� fez: -%d pontos", cartasJ);
			}
			break;
	}
	
	return 0;
}
