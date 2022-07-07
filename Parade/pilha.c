#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carta.h"
#include "pilha.h"

struct pilha{
	struct carta dados;
	struct pilha *prox;
};

Pilha *criarPilha(){
	Pilha *pi = (Pilha *)malloc(sizeof(Pilha));
	if(pi != NULL){
		*pi = NULL;
	}
	return pi;
}

int empilhar(Pilha *pi, struct carta novosdados){
	if(pi == NULL){
		return 0;
	}
	struct pilha *nova = (struct pilha *)malloc(sizeof(struct pilha));
	if(nova != NULL){
		nova->dados = novosdados;
		nova->prox = *pi;
		*pi = nova;
	}
	return 1;
}

int desempilhar(Pilha *pi, struct carta *apagar){
	if(pi == NULL || *pi == NULL){
		return 0;
	} else{
		struct pilha *aux = *pi;
		*pi = aux->prox;
		*apagar = aux->dados;
		free(aux);
		return 1;
	}
}

void embaralhar(Pilha *pi){
	if(pi == NULL || *pi == NULL){
		exit(1);
	} else{
		int cont = 0, n;
		struct pilha *aux = *pi;
		struct pilha *aux2 = *pi, *ant;
		n = rand() % 66;
		while(aux != NULL && cont != n){
			aux = aux->prox;
			cont++;
		}
		*pi = aux2->prox;
		aux2->prox = aux->prox;
		aux->prox = aux2;
	}
}

int tamanho(Pilha *pi){
	if(pi == NULL ||  *pi == NULL){
		return 0;
	} else{
		struct pilha *aux = *pi;
		int tam = 0;
		while(aux != NULL){
			tam++;
			aux = aux->prox;
		}
		return tam;
	}
}

int imprimirPilha(Pilha *pi){
	if(pi == NULL || *pi == NULL){
		return 0;
	} else{
		struct pilha *aux = *pi;
		while(aux != NULL){
			printf("[%c %d] ", aux->dados.naipe, aux->dados.numero);
			aux = aux->prox;
		}
		return 1;
	}
}
