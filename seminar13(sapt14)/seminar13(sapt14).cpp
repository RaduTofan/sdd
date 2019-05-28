#include "pch.h"
#include <iostream>
#include <stdio.h>

using namespace std;

//======================GRAFURI======================
//pentru DF folosim stiva
//1.
//2.vom avea si un vect care reprez vecinii si daca sunt vizitati(initial tot vect e 0)
//3.
//
//BF se fol coada

struct nodStiva
{
	int inf;
	nodStiva *next;

};

struct nodCoada
{
	int inf;
	nodCoada *next;
};

//inserarea in stiva
void push(nodStiva **varf, int val) //** pt ca il returnam prin parametru
{
	nodStiva *nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}

}


//facem void pt ca dupa nu o bagam in while, la stiva normala puneam functia int pt ca o foloseam in while
void pop(nodStiva **varf, int *val)
{
	if (*varf == NULL)
	{
		return;
	}
	else
	{
		*val = (*varf)->inf; //copiez informatia utila din nodul varf
		nodStiva *aux = *varf;
		*varf = (*varf)->next;	//il mut pe varf pe urmator
		free(aux);
	}
}

void put(nodCoada **prim, nodCoada ** ultim, int val)
{
	nodCoada *nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{//lam legat pe nodul nou la finalul structurii si am actualizat nodul ca fiind chiar asta
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

//extragerea din coada
void get(nodCoada **prim, nodCoada **ultim, int*val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		//acelasi lucru ca la stiva(copy+paste)
		*val = (*prim)->inf; //copiez informatia utila din nodul varf
		nodCoada *aux = *prim;
		*prim = (*prim)->next;	//il mut pe varf pe urmator
		free(aux);
	}
	if (*prim == NULL)
		*ultim = NULL;

}

void main()
{
	int nr;
	FILE *f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nr);
	//clic drept resource files: add utility, text file;
	int **mat = (int**)malloc(nr * sizeof(int*));
	for (int i = 0; i < nr; i++)
		mat[i] = (int*)malloc(nr * sizeof(int));
	//facem initial matricea 0 si dupa decidem daca avem legaturi
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nr; j++)
			mat[i][j] = 0;
	//citim numarul de arce;
	int nrArce;
	fscanf(f, "%d", &nrArce);
	int ii, jj;//doua variabile pt a le folosi pt a decide care este nodul sursa si nodul destinatie pt fiecare arc
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &ii);//nodul sursa
		fscanf(f, "%d", &jj);//nodul destinatie
		mat[ii][jj] = 1;
		mat[jj][ii] = 1; //am marcat ca graful meu este neorientat =>matricea este 

	}

	fclose(f);

	int *vizitat = (int*)malloc(nr * sizeof(int));
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	int nod;
	printf("\nParcurgere in adancime de la nodul: ");
	scanf("%d", &nod);

	nodStiva *varf = NULL;

	push(&varf, nod);
	vizitat[nod] = 1;
	while (varf != NULL)
	{
		//extragerea din stiva
		pop(&varf, &nod);
		printf("%d-", nod);
		for(int k=0;k<nr;k++)
			if (mat[nod][k] == 1 && vizitat[k] == 0) //daca am vecinii de la un nod catre
				//celelalte noduri din matrice si daca acei vecini nu au mai fost parcursi ii punem pe stiva si ii marcam ca vizitati
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}

	//PARCURGEREA IN LATIME!!:
	//resetam vectorul cu vecini
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	
	printf("\nParcurgere in latime de la nodul: ");
	scanf("%d", &nod);

	nodCoada *prim = NULL, *ultim = NULL;

	put(&prim, &ultim,nod);
	vizitat[nod] = 1;
	while (prim != NULL)
	{
		//extragerea din stiva
		get(&prim, &ultim,&nod);
		printf("%d-", nod);
		for (int k = 0; k < nr; k++)
			if (mat[nod][k] == 1 && vizitat[k] == 0) //daca am vecinii de la un nod catre
				//celelalte noduri din matrice si daca acei vecini nu au mai fost parcursi ii punem pe stiva si ii marcam ca vizitati
			{
				put(&prim,&ultim, k);
				vizitat[k] = 1;
			}
	}

}