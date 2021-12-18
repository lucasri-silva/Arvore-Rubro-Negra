#ifndef TREE_H 
#define TREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct RecordBinary RecordBinary;
typedef struct TreeBinary TreeBinary;

struct RecordBinary{
	float key;
};

struct TreeBinary{
	RecordBinary reg;
	TreeBinary *esq, *dir;
};

int getNumElementoEncontradoBinary();
void zerarNumElementoEncontradoBinary();

TreeBinary* CreateTreeBinary();

int insertBinaryAux(char *nome, TreeBinary **raiz, RecordBinary r);
void insertBinary(TreeBinary **t, RecordBinary r);

void pesquisaBinary(TreeBinary **t, TreeBinary **aux, RecordBinary r);
int pesquisaBinaryAux(char *nome, TreeBinary **raiz, TreeBinary **aux, RecordBinary r);

int isInTreeBinary(TreeBinary *t, RecordBinary r);
void removeTreeBinary(TreeBinary **t, RecordBinary r);
void antecessorBinary(TreeBinary **t, TreeBinary *aux);

#endif
