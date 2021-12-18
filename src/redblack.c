#include "redblack.h"

#define RED 'R'
#define BLACK 'B'
#define BUFFER_SIZE 1024


//double atof(const char *str);

TreeRN * CreateTreeRN() {
	return NULL;
}

void rotacaoDireitaRN(TreeRN **raiz, TreeRN * y)
{
	TreeRN * aux;
	aux = y->esq;
	y->esq = aux->dir;
	
	if (aux->dir != NULL)
		aux->dir->pai = y;
	
	aux->pai = y->pai;
	if(y->pai == NULL)
		(*raiz) = aux;
	else if((y->pai->esq != NULL) && (aux->key == y->pai->esq->key))
		y->pai->esq = aux;
	else
		y->pai->dir = aux;
	aux->dir = y;
	y->pai = aux;
	
	return;
}

void rotacaoEsquerdaRN(TreeRN **raiz, TreeRN * x)
{
	TreeRN * aux;
	aux = x->dir;
	x->dir = aux->esq;
	
	if (aux->esq != NULL)
		aux->esq->pai = x;
	
	aux->pai = x->pai;
	if(x->pai == NULL)
		(*raiz) = aux;
	else if((x->pai->esq != NULL) && (x->key == x->pai->esq->key))
		x->pai->esq = aux;
	else
		x->pai->dir = aux;
	aux->esq = x;
	x->pai = aux;
	
	return;
}

void sentinelaRN(TreeRN **t, int key) {

	*t = (TreeRN*)malloc(sizeof(TreeRN));
	(*t)->pai = NULL;
	(*t)->dir = NULL;
	(*t)->dir = NULL;
	(*t)->key = key;
	(*t)->cor = BLACK;
}

int insertRNAux(char *nome, TreeRN **raiz, TreeRN *pai){
	FILE *fn;
	char buffer[30];
	char extensao[10];
	strcat(strcpy(extensao, nome), ".txt");		
	strcat(strcpy(buffer, "./data/insercao/"), extensao);
	fn = fopen(buffer, "r");
	const char *delimiter_characters = " ";
	char *last_token;
	int key;
	
	if( fn == NULL ){

		fprintf( stderr, "Arquivo de inserçao %s não encontrado! \n", nome );

	} else {

		while( fgets(buffer, BUFFER_SIZE, fn) != NULL ){
			
			last_token = strtok( buffer, delimiter_characters );
			while( last_token != NULL ) {
			
				key = atof(last_token);
				insertRN(raiz, raiz, pai, key);
				last_token = strtok( NULL, delimiter_characters );
				
			}
		}
		fclose( fn );
	}
    return 0;
}

void insertRN(TreeRN **raiz, TreeRN **t, TreeRN *pai, int key) {

	if(*t == NULL) {
	
		*t = (TreeRN*)malloc(sizeof(TreeRN));
		(*t)->esq = NULL;
		(*t)->dir = NULL;
		(*t)->pai = pai;
		(*t)->key = key;
		(*t)->cor = RED;
	
	} else {
	
		if(key < (*t)->key){insertRN(&(*raiz), &(*t)->esq, (*t), key);return;}
		if(key > (*t)->key){insertRN(&(*raiz), &(*t)->dir, (*t), key);return;}
	}
	
	consertaInsercaoRN(raiz, (*t));
}


void consertaInsercaoRN(TreeRN **raiz, TreeRN *novo)
{
	(*raiz)->cor = BLACK;
	TreeRN *pai = NULL;
	TreeRN *avo = NULL;
	
	if(novo->pai == NULL) {
		return;
	}
	
	if((novo->cor != BLACK) && (novo->pai->cor == RED))
	{

		pai = novo->pai;
		avo = novo->pai->pai;

		if (pai == avo->esq)
		{
			TreeRN *tio = avo->dir;

			if (tio != NULL && tio->cor == RED)
			{
				avo->cor = RED;
				pai->cor = BLACK;
				tio->cor = BLACK;
				consertaInsercaoRN(raiz, avo);
				return;
			}

			else
			{
				if (novo == pai->dir)
				{
					rotacaoEsquerdaRN(raiz, pai);
					novo = pai;
					pai = novo->pai;
				}

				rotacaoDireitaRN(raiz, avo);
				swapRN(pai, avo);
			}
		}

		else
		{
			TreeRN *tio = avo->esq;

			if ((tio != NULL) && (tio->cor == RED))
			{
				avo->cor = RED;
				pai->cor = BLACK;
				tio->cor = BLACK;
				consertaInsercaoRN(raiz, avo);
				return;
			}
			else
			{

				if (novo == pai->esq)
				{
					rotacaoDireitaRN(raiz, pai);
					novo = pai;
					pai = novo->pai;
				}

				rotacaoEsquerdaRN(raiz, avo);
				swapRN(pai, avo);
			}
		}
	}

	(*raiz)->cor = BLACK;
}

void swapRN(TreeRN * pai, TreeRN * avo) {

	if(pai->cor == RED && avo->cor == BLACK) {
		pai->cor = BLACK;
		avo->cor = RED;
	} else {
		pai->cor = RED;
		avo->cor = BLACK;
	}
		
}

void pesquisaRN(TreeRN ** raiz, TreeRN ** aux, int key)
{
	if(*raiz == NULL)
	{
		return;
	}

	if((*raiz)->key > key){ pesquisaRN(&(*raiz)->esq, aux, key); return;}
	if((*raiz)->key < key){ pesquisaRN(&(*raiz)->dir, aux, key); return;}
	
	printf("\nELEMENTO ENCONTRADO %f", (*raiz)->key); 
	//*aux = *raiz;
}

void inOrderRN(TreeRN *t) {

	if(!(t == NULL)) {
	
		inOrderRN(t->esq); 
		if(t->pai != NULL)
			printf("%f-%c-%f\t", t->key, t->cor, t->pai->key);
		else
			printf("%f-%c-%c\t", t->key, t->cor, 'A');
		inOrderRN(t->dir); 
	}
}

/*void destroy(TreeRN tree)*/
/*{*/
/*	if (tree == NULL)*/
/*		return;*/
/*	destroy(tree->esq);*/
/*	destroy(tree->dir);*/
/*	free(tree);*/
/*}*/
