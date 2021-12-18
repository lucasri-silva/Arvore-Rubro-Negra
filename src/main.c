#include "inserirGerarData.h"
#include "tree.h"
#include "avl.h"
#include "redblack.h"

#include <time.h>

void searchBinaryAll(char *arqPesquisa, char *arqInsercao, TreeBinary *raizBinary, TreeBinary *auxBinary, RecordBinary rBinary) {
	clock_t start, end;
	double cpu_time_used;	
	
	start = clock();
	pesquisaBinaryAux(arqPesquisa, &raizBinary, &auxBinary, rBinary);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("\n\n-------ÁRVORE BINÁRIA COMUM-------");
	printf("\nELEMENTOS INSERIDOS: %s", arqInsercao);
	printf("\nNÚMERO DE ELEMENTOS PESQUISADOS: %s", arqPesquisa);
	printf("\nELEMENTOS ENCONTRADOS: %d", getNumElementoEncontradoBinary());
	printf("\nTEMPO DE PESQUISA: %lf segundos\n", cpu_time_used);
	zerarNumElementoEncontradoBinary();
	printf("\n\n\nPressione qualquer tecla para continuar ...");while(getchar() != '\n');
	system("clear||cls");
}

void searchAVLAll(char *arqPesquisa, char *arqInsercao, TreeAVL *raizAVL, TreeAVL *auxAVL, RecordAVL rAVL) {
	clock_t start, end;
	double cpu_time_used;	
	
	start = clock();
	pesquisaAVLAux(arqPesquisa, &raizAVL, &auxAVL, rAVL);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("\n\n-------ÁRVORE AVL-------");
	printf("\nELEMENTOS INSERIDOS: %s", arqInsercao);
	printf("\nNÚMERO DE ELEMENTOS PESQUISADOS: %s", arqPesquisa);
	printf("\nELEMENTOS ENCONTRADOS: %d", getNumElementoEncontradoAVL());
	printf("\nTEMPO DE PESQUISA: %lf segundos\n", cpu_time_used);
	zerarNumElementoEncontradoAVL();
	printf("\n\n\nPressione qualquer tecla para continuar ...");while(getchar() != '\n');
	system("clear||cls");
}


int main(){

	int opcao = 1;
	char *lstInsercao[3] = {"1K", "10K", "1000K"};
	char *lstPesquisa[3] = {"5K", "10K", "100K"};
	
	clock_t start, end;
	double cpu_time_used;
	
/*	TreeBinary *raizBinary = CreateTreeBinary();*/
/*	TreeBinary *auxBinary = CreateTreeBinary();*/
	RecordBinary rBinary;
	
/*	TreeAVL *raizAVL = CreateTreeAVL();*/
/*	TreeAVL *auxAVL = CreateTreeAVL();*/
	RecordAVL rAVL;
	
/*	TreeAVL *raizRN = CreateTreeRN();*/
/*	TreeAVL *auxAVL = CreateTreeAVL();*/
/*	int keyRN;*/
	
	while(opcao) {
		system("clear||cls");
		printf("1. Árvore Binaria Comum \n2. Árvore AVL \n3. Árvore Rubro-Negra \n4. Gerar novos dados para inserção/pesquisa \n5. Sair \n\nEscolha uma opção: ");
		scanf("%d", &opcao);
		
		switch (opcao)
		{
			case 1:
				for(int i=0; i < 3; i++) {
					TreeBinary *raizBinary = CreateTreeBinary();
					TreeBinary *auxBinary = CreateTreeBinary();
					system("clear||cls");
 					printf("-------ÁRVORE BINÁRIA COMUM-------");
					start = clock();
					insertBinaryAux(lstInsercao[i], &raizBinary, rBinary);
					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					printf("\nELEMENTOS INSERIDOS: %s", lstInsercao[i]);
					printf("\nTEMPO DE INSERÇÃO: %lf segundos\n", cpu_time_used);
					printf("\n\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
					system("clear||cls");
					
					for(int j=0; j < 3; j++)
						searchBinaryAll(lstPesquisa[j], lstInsercao[i], raizBinary, auxBinary, rBinary);
				}
				break;
			case 2:
				for(int i=0; i < 3; i++) {
					TreeAVL *raizAVL = CreateTreeAVL();
					TreeAVL *auxAVL = CreateTreeAVL();
					system("clear||cls");
 					printf("-------ÁRVORE AVL-------");
					start = clock();
					insertAVLAux(lstInsercao[i], &raizAVL, rAVL);
					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					printf("\nELEMENTOS INSERIDOS: %s", lstInsercao[i]);
					printf("\nTEMPO DE INSERÇÃO: %lf segundos\n", cpu_time_used);
					printf("\n\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
					system("clear||cls");
					
					for(int j=0; j < 3; j++)
						searchAVLAll(lstPesquisa[j], lstInsercao[i], raizAVL, auxAVL, rAVL);
				}
				break;
			case 3:
				for(int i=0; i < 3; i++) {
					TreeRN * raizRN = CreateTreeRN();
					//TreeRN * auxRN = CreateTreeRN();
					system("clear||cls");
 					printf("-------ÁRVORE RUBRO-NEGRA-------");
					start = clock();
					insertRNAux(lstInsercao[i], &raizRN, raizRN);
					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					printf("\nELEMENTOS INSERIDOS: %s", lstInsercao[i]);
					printf("\nTEMPO DE INSERÇÃO: %lf segundos\n", cpu_time_used);
					printf("\n\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
					system("clear||cls");
					
					//for(int j=0; j < 3; j++)
						//searchRNAll(lstPesquisa[j], lstInsercao[i], raizRN, auxRN, rRN);
				}
				break;
			case 4:
				gerarData();
				break;
			default:
				opcao = 0;
		}
	}
	return 0;
}
