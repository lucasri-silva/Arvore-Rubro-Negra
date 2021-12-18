#include "inserirGerarData.h"

void shuffle(float *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          float t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

int gerarDataPesquisa(int quantidade, char *nome) {
	FILE *fn;
	char buffer[50];
	strcat(strcpy(buffer, "./data/pesquisa/"), nome);	
	fn=fopen(buffer, "w");
	float arr[quantidade];

	srand(time(NULL));

	for (int i = 0; i < quantidade; i++) {
		arr[i] = (float)1 + (float)rand() / (float)RAND_MAX / (float)10;
	}
	
	
	for (int i = 0; i < quantidade; i++) {
		fprintf(fn,"%f\n", arr[i]);
	}

	fclose(fn);
	
	return 0;
}

int gerarDataInsercao(int quantidade, char *nome)
{
	FILE *fn;
	char buffer[50];
	strcat(strcpy(buffer, "./data/insercao/"), nome);	
	fn=fopen(buffer, "w");
	float arr[quantidade];
	
	for (int i=0; i < quantidade; i++)
		arr[i] = 1 + (i / (float)quantidade);
		
	shuffle(arr, quantidade);
	
	for (int i = 0; i < quantidade; i++)
		fprintf(fn,"%f\n", arr[i]);

	fclose(fn);
	
	return 0;
}

int gerarData() {

	gerarDataInsercao(1000, "1K.txt");
	gerarDataInsercao(10000, "10K.txt");
	gerarDataInsercao(1000000, "1000K.txt");
	printf("\nBase de dados para inserção de 1.000, 10.000 e 1.000.000 entradas foram criadas!");

	gerarDataPesquisa(5000, "5K.txt");
	gerarDataPesquisa(10000, "10K.txt");
	gerarDataPesquisa(100000, "100K.txt");
	printf("\nBase de dados para pesquisa de 5.000, 10.000 e 100.000 entradas foram criadas!");
   
   	printf("\n\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
	
	return 0;   
}
 
