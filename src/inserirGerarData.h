#ifndef INSERIRGERARDATA_H
#define INSERIRGERARDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gerarData();
int gerarDataPesquisa(int quantidade, char *nome);
int gerarDataInsercao(int quantidade, char *nome);
void shuffle(float *arr, size_t n);

#endif
