#ifndef AVL_H 
#define AVL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct RecordAVL RecordAVL;
typedef struct TreeAVL TreeAVL;

struct RecordAVL {
	float key;
};

struct TreeAVL {
	RecordAVL reg;
	TreeAVL *esq, *dir;
	int weight;
};

int getNumElementoEncontradoAVL();
void zerarNumElementoEncontradoAVL();

TreeAVL* CreateTreeAVL();

void insertAVL(TreeAVL **t, RecordAVL r);
int insertAVLAux(char *nome, TreeAVL **raiz, RecordAVL r);

void pesquisaAVL(TreeAVL **t, TreeAVL **aux, RecordAVL r);
int pesquisaAVLAux(char *nome, TreeAVL **raiz, TreeAVL **aux, RecordAVL r);
int isInTreeAVL(TreeAVL *t, RecordAVL r);

void removeTreeAVL(TreeAVL **t, TreeAVL **f, RecordAVL r);
void antecessorAVL(TreeAVL **t, TreeAVL *aux);
void rebalanceTreeAVL(TreeAVL **t);

void centralAVL(TreeAVL *t);

int getWeightAVL(TreeAVL **t);
int getMaxWeightAVL(int left, int right);

void rotacaoSimplesDireitaAVL(TreeAVL **t);
void rotacaoSimplesEsquerdaAVL(TreeAVL **t);
void rotacaoDuplaDireitaAVL(TreeAVL **t);
void rotacaoDuplaEsquerdaAVL(TreeAVL **t);


#endif
