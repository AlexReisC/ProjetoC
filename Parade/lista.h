typedef struct lista *Lista;

Lista *criarLista();
int inserirInicio(Lista *, struct carta);
int removerQualquer(Lista *, struct carta);
int acessarIndice(Lista *, int, struct carta *);
int quantidade(Lista *);
int somaValores(Lista *);
int imprimir(Lista *);
int adicionarColecao(Lista *, struct carta , Lista **);

