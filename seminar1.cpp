#include "pch.h"
#include <iostream>
#include <stdio.h>

using namespace std;

struct produs {
	int cod; //daca punem * la cod, facem 1 alocare in plus si o dezalocare in plus si la citire/afisare scriem p[i]->cod in loc de p[i].cod;
	char* denumire;
	float pret;
	float cantitate;
};


void citireVector(produs *p, int n) {

	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod= ");
		scanf("%d", &p[i].cod);
		printf("\nDenumire= ");
		scanf("%s", buffer);
		p[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p[i].denumire, buffer); //mare atentie, aici sunt cele mai multe erori
		printf("\nPret= ");
		scanf("%f", &p[i].pret);
		printf("\nCanitate= ");
		scanf("%f", &p[i].cantitate);

	}
}

void afisareVector(produs *p, int n) {
	for (int i = 0; i < n; i++)
		printf("\nCod=%d, Denumire: %s, Pret=%5.2f, Cantitate=%5.2f", p[i].cod, p[i].denumire, p[i].pret, p[i].cantitate);
}

void dezalocareVector(produs *p, int n) {
	for (int i = 0; i < n; i++)
		free(p[i].denumire); //pt malloc - folosim free, pt new - delete;
	free(p);
}

void citire4Vectori(int *cod, char**den, float *pret, float*cant, int n) {
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod= ");
		scanf("%d", &cod[i]);
		printf("\nDenumire= ");
		scanf("%s", buffer);
		den[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(den[i], buffer); //mare atentie, aici sunt cele mai multe erori
		printf("\nPret= ");
		scanf("%f", &pret[i]);
		printf("\nCanitate= ");
		scanf("%f", &cant[i]);

	}
}
void afisare4Vectori(int *cod, char**den, float *pret, float*cant, int n) {
	for (int i = 0; i < n; i++)
		printf("\nCod=%d, Denumire: %s, Pret=%5.2f, Cantitate=%5.2f", cod[i], den[i], pret[i], cant[i]);
}

void dezalocare4Vectori(int *cod, char**den, float *pret, float*cant, int n) {
	free(cod);
	for (int i = 0; i < n; i++)
		free(den[i]);
	free(den);
	free(pret);
	free(cant);
}
void main()
{
	int n;
	printf("Nr. prodyse= ");
	scanf("%d", &n);

	//produs* vp = (produs*)malloc(n * sizeof(produs));
	//citireVector(vp, n);
	//afisareVector(vp, n);
	//dezalocareVector(vp, n);

	int *coduri = (int*)malloc(n * sizeof(int));
	char **denumiri = (char**)malloc(n * sizeof(char*));
	float *preturi = (float*)malloc(n * sizeof(float));
	float *cantitati = (float*)malloc(n * sizeof(float));
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, n);


}

