#include "tree.h"

#define BUFFER_SIZE 1024


double atof(const char *str);

int numElementoEncontradoBinary = 0;

int getNumElementoEncontradoBinary() {
	return numElementoEncontradoBinary;
}

void zerarNumElementoEncontradoBinary() {
	numElementoEncontradoBinary = 0;
}

TreeBinary* CreateTreeBinary(){
	return NULL;
}

double atof(const char *str);

int insertBinaryAux(char *nome, TreeBinary **raiz, RecordBinary r){
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
				insertBinary(raiz, r);
				last_token = strtok( NULL, delimiter_characters );
				
			}
		}
		fclose( fn );
	}
    return 0;
}

void insertBinary(TreeBinary **t, RecordBinary r){

	if(*t == NULL) {
	
		*t = (TreeBinary*)malloc(sizeof(TreeBinary));
		(*t)->esq = NULL; 
		(*t)->dir = NULL; 
		(*t)->reg = r; 
		
	} else {
	
		if(r.key < (*t)->reg.key){insertBinary(&(*t)->esq, r);}
		if(r.key > (*t)->reg.key){insertBinary(&(*t)->dir, r);}
		if(r.key == (*t)->reg.key){printf("\nelemento igual %f", (*t)->reg.key);}
		
	}

}

int pesquisaBinaryAux(char *nome, TreeBinary **raiz, TreeBinary **aux, RecordBinary r) {
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
				pesquisaBinary(raiz, aux, r);
				last_token = strtok( NULL, delimiter_characters );
			}
		}	
		fclose( fn );
	}
    return 0;
}

void pesquisaBinary(TreeBinary **t, TreeBinary **aux, RecordBinary r)
{
	if(*t == NULL)
		return;

	if((*t)->reg.key > r.key){ pesquisaBinary(&(*t)->esq, aux, r); return;}
	if((*t)->reg.key < r.key){ pesquisaBinary(&(*t)->dir, aux, r); return;}
	
	printf("\nELEMENTRO ENCONTRADO: %f", (*t)->reg.key);
	numElementoEncontradoBinary++;
	*aux = *t;
}

int isInTreeBinary(TreeBinary *t, RecordBinary r)
{
	if(t == NULL)
		return 0;

	return t->reg.key == r.key || isInTreeBinary(t->esq, r) || isInTreeBinary(t->dir, r);
}


void antecessorBinary(TreeBinary **t, TreeBinary *aux)
{ 
	if ((*t)->dir != NULL)
	{
		antecessorBinary(&(*t)->dir, aux);
		return;
	}
	aux->reg = (*t)->reg;
	aux = *t;
	*t = (*t)->esq;
	free(aux);
} 

void removeTreeBinary(TreeBinary **t, RecordBinary r){
	TreeBinary *aux;
  	
  	if (*t == NULL)
  	{ 
  		printf("[ERROR]: Record not found!!!\n");
    		return;
  	}

  	if (r.key < (*t)->reg.key){ removeTreeBinary(&(*t)->esq, r); return; }
  	if (r.key > (*t)->reg.key){ removeTreeBinary(&(*t)->dir, r); return; }

  	if ((*t)->dir == NULL)
  	{ 
  		aux = *t;  
  		*t = (*t)->esq;
	    	free(aux);
	    	return;
  	}

  	if ((*t)->esq != NULL){ antecessorBinary(&(*t)->esq, *t); return; }
  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
}
