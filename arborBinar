#include "pch.h"
#include <iostream>

struct comanda {
	int id;
	char*den_client;
	int nr_produse;
	char**produse_comandate;
	char*data_livrare;
};

struct nodarb {
	comanda inf;
	nodarb*stanga;
	nodarb*dreapta;
};



nodarb*inserareArb(nodarb* rad, comanda c) {
	if (rad) {
		if (rad->inf.id > c.id)
		{
			rad->stanga = inserareArb(rad->stanga, c);
		}
		else
		{
			rad->dreapta = inserareArb(rad->dreapta, c);
		}
		return rad;
	}
	else
	{
		nodarb*nou = (nodarb*)malloc(sizeof(nodarb));
		nou->inf.id = c.id;
		nou->inf.den_client = (char*)malloc(sizeof(char)*strlen(c.den_client) + 1);
		strcpy(nou->inf.den_client, c.den_client);
		nou->inf.nr_produse = c.nr_produse;
		nou->inf.produse_comandate = (char**)malloc(sizeof(char*)*c.nr_produse);
		for (int i = 0; i < c.nr_produse; i++)
		{
			nou->inf.produse_comandate[i] = (char*)malloc(sizeof(char)*strlen(c.produse_comandate[i])+1);
			strcpy(nou->inf.produse_comandate[i], c.produse_comandate[i]);
		}
		nou->inf.data_livrare= (char*)malloc(sizeof(char)*strlen(c.data_livrare) + 1);
		strcpy(nou->inf.data_livrare, c.data_livrare);
		nou->dreapta = NULL;
		nou->stanga = NULL;
		return nou;
	}
}

void inordine(nodarb*rad) {
	if (rad) {
		inordine(rad->stanga);
		printf("\nID: %d, Den Client: %s, Nr Produse: %d", rad->inf.id, rad->inf.den_client, rad->inf.nr_produse);
		for (int i = 0; i < rad->inf.nr_produse; i++)
		{
			printf(".\nProdusul %d are denumirea %s", i, rad->inf.produse_comandate[i]);
		}
		printf(".\nData livrarii: %s", rad->inf.data_livrare);
		inordine(rad->dreapta);
	}
}

void dezalocare(nodarb*rad) {
	if (rad) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->inf.den_client);
		for (int i = 0; i < rad->inf.nr_produse; i++)
			free(rad->inf.produse_comandate[i]);
		free(rad->inf.data_livrare);
		free(rad);
	}
}

void verificare(nodarb*rad, int*vect, int*dimVec, const char data[100])
{
	if (rad) {
		if (strcmp(rad->inf.data_livrare, data) == 0) {
			vect[*dimVec] = rad->inf.id;
			(*dimVec)++;
		}
		verificare(rad->stanga, vect, dimVec, data);
		verificare(rad->dreapta, vect, dimVec, data);
	}
}

int*vectDeId(nodarb*rad, int*vect,int*dimVec, const char data[100])
{
	verificare(rad, vect, dimVec, data);
	return vect;
}

int nodFrunza(nodarb*rad, int *nrNod, const char client[100]) {
	if (rad) {
		if (rad->dreapta == NULL && rad->stanga == NULL && strcmp(rad->inf.den_client,client)==0) {
			(*nrNod)++;
		}
		
		nodFrunza(rad->stanga, nrNod, client);
		nodFrunza(rad->dreapta, nrNod, client);

	}
	return *nrNod;
}

void main()
{
	int nr;
	comanda c;
	nodarb*rad=NULL;
	FILE *f = fopen("arbore.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &c.id);
		char buf[100];
		fscanf(f, "%s", &buf);
		c.den_client = (char*)malloc(sizeof(char)*strlen(buf) + 1);
		strcpy(c.den_client, buf);
		fscanf(f, "%d", &c.nr_produse);
		c.produse_comandate = (char**)malloc(sizeof(char*)*c.nr_produse);
		for (int j = 0; j < c.nr_produse; j++)
		{
			fscanf(f, "%s", &buf);
			c.produse_comandate[j] = (char*)malloc(sizeof(char)*strlen(buf) + 1);
			strcpy(c.produse_comandate[j], buf);
			
		}
		fscanf(f, "%s", &buf);
		c.data_livrare = (char*)malloc(sizeof(char)*strlen(buf) + 1);
		strcpy(c.data_livrare, buf);
		rad = inserareArb(rad, c);

	}
	fclose(f);
	inordine(rad);
	printf("\nYEEET!\n");
	int dimvec = 0;
	int*vect = (int*)malloc(sizeof(int)*nr);
	char data[20] = "25/04/2019";
	vect = vectDeId(rad, vect, &dimvec, data);
	if (dimvec > 0) {
		printf("Pe data de %s au fost efectuate livrari cu id-urile:",data);
		for (int i = 0; i < dimvec; i++)
		{
			printf("\t%d", vect[i]);
		}
	}
	else {
		printf("Nu au fost gasite livrari pentru data de %s",data);
	}
	printf("\n===========Functie frunza:===========\n");
	int nrNoduriFrunza=0;
	nrNoduriFrunza = nodFrunza(rad, &nrNoduriFrunza, "Vasilescu");
	printf("%d", nrNoduriFrunza);



	dezalocare(rad);

}
