#include "pch.h"
#include <iostream>


struct cotaIntretinere {
	char*adresa;
	int nr_apart;
	int nr_pers;
	int anul;
	int luna;
	float valoare;
};

struct nodls {
	cotaIntretinere info;
	nodls*next;
};

struct hashT {
	nodls**vect;
	int size;
};

int functieHash(hashT tabela, int cheie) {
	return cheie % tabela.size;
}


int inserare(hashT tabela, cotaIntretinere c) {
	int pozitie;
	if (tabela.vect != NULL) {
		pozitie = functieHash(tabela, c.nr_apart);
		nodls*nou = (nodls*)malloc(sizeof(nodls));
		nou->info.nr_apart = c.nr_apart;
		nou->info.adresa= (char*)malloc(sizeof(char)*(strlen(c.adresa)+1));
		strcpy(nou->info.adresa, c.adresa);
		
		nou->info.nr_pers = c.nr_pers;
		nou->info.anul = c.anul;
		nou->info.luna = c.luna;
		nou->info.valoare = c.valoare;
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
		{
			tabela.vect[pozitie] = nou;
		}
		else
		{
			nodls*temp = tabela.vect[pozitie];
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversare(hashT tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				nodls*temp = tabela.vect[i];
				printf("\nPentru pozitia %d:", i);
				while (temp)
				{
					printf("\nAdresa: %s, Nr apart: %d, Nr Persoane/apart: %d, Anul: %d, Luna: %d, Valoarea intretinerii: %f", temp->info.adresa,
						temp->info.nr_apart, temp->info.nr_pers, temp->info.anul, temp->info.luna, temp->info.valoare);
					temp = temp->next;
				}
			}
		}
	}
}

float valTot(hashT tabela, int nr_apart, int an, const char* adresa) {
	float suma = 0;
	for (int i = 0; i < tabela.size; i++)
	{
		nodls*temp = tabela.vect[i];
		while (temp) {
			if (temp->info.nr_apart == nr_apart && temp->info.anul == an && strcmp(temp->info.adresa, adresa) == 0) {
				suma += temp->info.valoare;
			}
			temp = temp->next;
		}
	}
	return suma;
}

int nrCote(hashT tabela, float prag) {
	int numar=0;
	if (tabela.vect!=NULL) {
		for (int i = 0; i < tabela.size; i++)
		{
			nodls*temp = tabela.vect[i];
			while (temp) {
				if (temp->info.valoare > prag) {
					numar++;
				}
				temp = temp->next;
			}
		}

	}
	return numar;
}

void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				nodls*temp = tabela.vect[i];
				while (temp) {
					nodls*temp2 = temp->next;
					free(temp->info.adresa);
					free(temp);
					temp = temp2;
				}
				
			}
		}
		free(tabela.vect);
	}
}

void main() {
	hashT tabela;
	cotaIntretinere c;
	tabela.size = 101;
	int nr;
	tabela.vect = (nodls**)malloc(sizeof(nodls)*tabela.size);
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = NULL;
	}
	FILE*f = fopen("cote.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		char buf[100];
		fscanf(f, "%s", &buf);
		c.adresa = (char*)malloc(sizeof(char)*strlen(buf) + 1);
		strcpy(c.adresa, buf);
		fscanf(f, "%d", &c.nr_apart);
		fscanf(f, "%d", &c.nr_pers);
		fscanf(f, "%d", &c.anul);
		fscanf(f, "%d", &c.luna);
		fscanf(f, "%f", &c.valoare);
		inserare(tabela, c);

	}
	fclose(f);
	traversare(tabela);
	float suma = valTot(tabela, 101, 2019, "Piata_Romana_10");
	printf("\n\n\%f", suma);
	float prag = 160;
	int nrdeCote = nrCote(tabela, prag);
	printf("\n\n\n\n%d", nrdeCote);

	dezalocare(tabela);
}
