#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "lista.h"

struct lista{
	struct carta dados;
	struct lista *prox;
};

Lista *criarLista(){
	Lista *li = (Lista *)malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

int inserirInicio(Lista *li, struct carta novosDados){
	if(li == NULL){
		return 0;
	}
	struct lista *nova =(struct lista *)malloc(sizeof(struct lista));
	if(nova !=  NULL){
		nova->dados = novosDados;
		nova->prox = *li;
		*li = nova;
	}
	return 1;
}

int removerQualquer(Lista *li, struct carta dados){
	if(li == NULL || *li == NULL){
		return 0;
	} else{
		struct lista *aux = *li, *ant;
		if(aux->dados.naipe == dados.naipe && aux->dados.numero == dados.numero){
			*li = aux->prox;
			free(aux);
			return 1;
		} else{
			while(aux != NULL){
				if(aux->dados.naipe == dados.naipe && aux->dados.numero == dados.numero){
					ant->prox = aux->prox;
					free(aux);
					return 1;
				} else{
					ant = aux;
					aux = aux->prox;
				}
			}
			if(aux == NULL){
				printf("Carta não existe!");
				return 0;
			}
		}
	}
}

int acessarIndice(Lista *li, int x, struct carta *c){
	if(li == NULL || *li == NULL){
		return 0;
	} else if(x < 0){
		return 0;
	} else{
		struct lista *aux = *li;
		int cont = 1;
		while(aux != NULL && x != cont){
			aux = aux->prox;
			cont++;
		}
		if(aux == NULL){
			return 0;
		} else{
			*c = aux->dados;
		}
		return 1;
	}
}

int quantidade(Lista *li){
	if(li == NULL){
		return 0;
	}
	struct lista *aux = *li;
	int qtd = 0;
	while(aux != NULL){
		qtd++;
		aux = aux->prox;
	}
	return qtd;
}

int somaValores(Lista *li){
	if(li == NULL || *li == NULL){
		return 0;
	} else{
		struct lista *aux = *li;
		int soma = 0;
		while(aux != NULL){
			soma = soma + aux->dados.numero;
			aux = aux->prox;
		}
		return soma;
	}
}

int imprimir(Lista *li){
	if(li == NULL || *li == NULL){
		return 0;
	}
	else{
		struct lista *aux = *li;
		while(aux != NULL){
			printf("[%c %d] ", aux->dados.naipe, aux->dados.numero);
			aux = aux->prox;
		}
		return 1;
	}                  
}

int adicionarColecao(Lista *li, struct carta c, Lista **colecao){
	if(li == NULL || *li == NULL){
		return 0;
	} else if(colecao == NULL){
		return 0;
	} else{
		struct lista *aux = *li, *ant;
		int i;
		int numero;
		numero = c.numero;
		char cor; 
		cor = c.naipe;
		
		for(i = 0; i < numero+1; i++){
			ant = aux;
			aux = aux->prox;
			if(aux == NULL){
				break;
				return 1;
			}
		}
		
		while(aux != NULL){
			if(aux->dados.numero <= numero){
				for(i = 0; i < 6; i++){
					if(aux->dados.naipe == 'A' + i){
						inserirInicio(colecao[i],aux->dados);
					}
				}
				ant->prox = aux->prox;
				aux->prox = NULL;
				aux = ant->prox;
			} else if(aux->dados.naipe == cor){
				for(i = 0; i < 6; i++){
					if(aux->dados.naipe == 'A' + i){
						inserirInicio(colecao[i],aux->dados);
					}
				}
				ant->prox = aux->prox;
				aux->prox = NULL;
				aux = ant->prox;
			} else {
				ant = aux;
				aux = aux->prox;
			}
		}
		if(aux == NULL){
			return 1;
		}
		return 1;
	}
}

