#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeRN TreeRN;

struct TreeRN {
	float key;
	char cor;
	TreeRN *esq, *dir, *pai;
};

TreeRN * CreateTreeRN();

int insertRNAux(char *nome, TreeRN **raiz, TreeRN *pai);

void sentinelaRN(TreeRN **t, int key);
void swapRN(TreeRN * pai, TreeRN * avo);
void insertRN(TreeRN **raiz, TreeRN ** t, TreeRN * pai, int key);
void consertaInsercaoRN(TreeRN **raiz, TreeRN *novo);

void rotacaoDireitaRN(TreeRN **raiz, TreeRN * y);
void rotacaoEsquerdaRN(TreeRN **raiz, TreeRN * x);

void pesquisaRN(TreeRN ** raiz, TreeRN ** aux, int key);

void inOrderRN(TreeRN * raiz);

#endif
