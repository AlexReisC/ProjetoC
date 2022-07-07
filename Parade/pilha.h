typedef struct pilha *Pilha;

Pilha *criarPilha();
int empilhar(Pilha *, struct carta);
int desempilhar(Pilha *, struct carta *);
void embaralhar(Pilha *);
int tamanho(Pilha *);
int imprimirPilha(Pilha *);
