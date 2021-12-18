#include "avl.h"

#define BUFFER_SIZE 1024

double atof(const char *str);

int numElementoEncontradoAVL = 0;

int getNumElementoEncontradoAVL() {
	return numElementoEncontradoAVL;
}

void zerarNumElementoEncontradoAVL() {
	numElementoEncontradoAVL = 0;
}

TreeAVL* CreateTreeAVL(){
	return NULL;
}

void insertAVL(TreeAVL **t, RecordAVL r){

  if(*t == NULL){
    *t = (TreeAVL*)malloc(sizeof(TreeAVL));
    (*t)->esq    = NULL; 
    (*t)->dir    = NULL; 
    (*t)->weight = 0;
    (*t)->reg    = r; 

  } else {
    
    if(r.key < (*t)->reg.key){
      insertAVL(&(*t)->esq, r);
      if ((getWeightAVL(&(*t)->esq) - getWeightAVL(&(*t)->dir)) == 2){
      	if(r.key < (*t)->esq->reg.key)
      		rotacaoSimplesDireitaAVL(t);
      	else
      		rotacaoDuplaDireitaAVL(t);
      }
    }
    
    if(r.key > (*t)->reg.key){
      insertAVL(&(*t)->dir, r);
      if ((getWeightAVL(&(*t)->dir) - getWeightAVL(&(*t)->esq)) == 2){
      	if(r.key > (*t)->dir->reg.key)
      		rotacaoSimplesEsquerdaAVL(t);
      	else
      		rotacaoDuplaEsquerdaAVL(t);
      }
    }
  
  }

  (*t)->weight = getMaxWeightAVL(getWeightAVL(&(*t)->esq), getWeightAVL(&(*t)->dir)) + 1;
}

int insertAVLAux(char *nome, TreeAVL **raiz, RecordAVL r){
	FILE *fn;
	char buffer[30];
	char extensao[10];
	strcat(strcpy(extensao, nome), ".txt");		
	strcat(strcpy(buffer, "./data/insercao/"), extensao);
	fn = fopen(buffer, "r");
	const char *delimiter_characters = " ";
	char *last_token;
	
	if( fn == NULL ){

		fprintf( stderr, "Arquivo de inserçao %s não encontrado! \n", nome );

	} else {

		while( fgets(buffer, BUFFER_SIZE, fn) != NULL ){
			
			last_token = strtok( buffer, delimiter_characters );
			while( last_token != NULL ) {
			
				r.key = atof(last_token);
				insertAVL(raiz, r);
				last_token = strtok( NULL, delimiter_characters );
				
			}
		}
		fclose( fn );
	}
    return 0;
}


void pesquisaAVL(TreeAVL **t, TreeAVL **aux, RecordAVL r){

	if(*t == NULL){
		return;
	}

	if((*t)->reg.key > r.key){ pesquisaAVL(&(*t)->esq, aux, r); return;}
	if((*t)->reg.key < r.key){ pesquisaAVL(&(*t)->dir, aux, r); return;}
	
	printf("\nELEMENTRO ENCONTRADO: %f", (*t)->reg.key);
	numElementoEncontradoAVL++;
	*aux = *t;
}

int pesquisaAVLAux(char *nome, TreeAVL **raiz, TreeAVL **aux, RecordAVL r) {
	FILE *fn;
	char buffer[30];
	char extensao[10];
	strcat(strcpy(extensao, nome), ".txt");		
	strcat(strcpy(buffer, "./data/pesquisa/"), extensao);
	fn = fopen(buffer, "r");
	const char *delimiter_characters = " ";
	char *last_token;
	
	if( fn == NULL ){

		fprintf( stderr, "Arquivo de pesquisa %s não encontrado\n", nome );

	} else {

		while( fgets(buffer, BUFFER_SIZE, fn) != NULL ){
			
			last_token = strtok( buffer, delimiter_characters );
			while( last_token != NULL ) {
			
				r.key = atof(last_token);
				pesquisaAVL(raiz, aux, r);
				last_token = strtok( NULL, delimiter_characters );
			}
		}	
		fclose( fn );
	}
    return 0;
}

int isInTreeAVL(TreeAVL *t, RecordAVL r){
  
  if(t == NULL){ 
    return 0;
  }
  
  return t->reg.key == r.key || isInTreeAVL(t->esq, r) || isInTreeAVL(t->dir, r);
}


void antecessorAVL(TreeAVL **t, TreeAVL *aux){ 

	if ((*t)->dir != NULL){ 
		antecessorAVL(&(*t)->dir, aux);
		return;
  	}
  	
  	aux->reg = (*t)->reg;
  	aux = *t; 
  	*t = (*t)->esq;
  	free(aux);
} 

void rebalanceTreeAVL(TreeAVL **t){
	int balance;
  	int left = 0;
  	int right = 0;

	balance = getWeightAVL(&(*t)->esq) - getWeightAVL(&(*t)->dir);
	if((*t)->esq)
		left = getWeightAVL(&(*t)->esq->esq) - getWeightAVL(&(*t)->esq->dir);
	if((*t)->dir)
		right = getWeightAVL(&(*t)->dir->esq) - getWeightAVL(&(*t)->dir->dir);

	printf("Item:%f, peso:%d, peso esq:%d, peso dir:%d\n", (*t)->reg.key, balance, left, right);

	if(balance == 2 && left >= 0)
		rotacaoSimplesDireitaAVL(t);
	if(balance == 2 && left < 0)
		rotacaoDuplaDireitaAVL(t);

	if(balance == -2 && right <= 0)
		rotacaoSimplesEsquerdaAVL(t);
	if(balance == -2 && right > 0)
		rotacaoDuplaEsquerdaAVL(t); 	

}

void removeTreeAVL(TreeAVL **t, TreeAVL **f, RecordAVL r){
	TreeAVL *aux;
  	
  	if (*t == NULL){ 
  		printf("[ERROR]: Record not found!!!\n");
    	return;
  	}

  	if (r.key < (*t)->reg.key){ removeTreeAVL(&(*t)->esq, t, r); return;}
  	if (r.key > (*t)->reg.key){ removeTreeAVL(&(*t)->dir, t, r); return;}

  	if ((*t)->dir == NULL){ 
  		aux = *t;  
  		*t = (*t)->esq;
	    	free(aux);
	    	rebalanceTreeAVL(f);
	    	return;
  	}

  	if ((*t)->esq != NULL){ 
  		antecessorAVL(&(*t)->esq, *t);
  		rebalanceTreeAVL(f);
  		rebalanceTreeAVL(t);
  		return;
  	}

  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
  	rebalanceTreeAVL(f);
  	rebalanceTreeAVL(t); 	
  	
}

int getWeightAVL(TreeAVL **t){
	if(*t == NULL)
		return -1;
	return (*t)->weight;
}

int getMaxWeightAVL(int left, int right){
	if(left > right)
		return left;
	return right;
}

void rotacaoSimplesDireitaAVL(TreeAVL **t){
	TreeAVL *aux;
	aux = (*t)->esq;
	(*t)->esq = aux->dir;
	aux->dir = (*t);
	(*t)->weight = getMaxWeightAVL(getWeightAVL(&(*t)->esq), getWeightAVL(&(*t)->dir)) + 1;
	aux->weight  = getMaxWeightAVL(getWeightAVL(&aux->esq), (*t)->weight) + 1;
	(*t) = aux;
}

void rotacaoSimplesEsquerdaAVL(TreeAVL **t){
	TreeAVL *aux;
	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	(*t)->weight = getMaxWeightAVL(getWeightAVL(&(*t)->esq), getWeightAVL(&(*t)->dir)) + 1;
	aux->weight  = getMaxWeightAVL(getWeightAVL(&aux->esq), (*t)->weight) + 1;
	(*t) = aux;
}

void rotacaoDuplaDireitaAVL(TreeAVL **t){
	rotacaoSimplesEsquerdaAVL(&(*t)->esq);
	rotacaoSimplesDireitaAVL(t);
}

void rotacaoDuplaEsquerdaAVL(TreeAVL **t){
	rotacaoSimplesDireitaAVL(&(*t)->dir);
	rotacaoSimplesEsquerdaAVL(t);
}
