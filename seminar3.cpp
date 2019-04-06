#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;
//LISTA DUBLA CIRCULARA

struct produs {
	int *cod;
	char * denumire;
	float pret;
	float cantitate;

};

struct nodls { //pentru definirea nodului unei lista
	produs *inf;
	nodls *next;
	nodls* prev;
};

nodls* inserare(nodls *cap, nodls**coada, produs *p)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = (int*)malloc(sizeof(int));

	*(nou->inf->cod) = *(p->cod);
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;
	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		*coada = nou;

	}
	else
	{
		nodls*temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}
	return cap;
}

void traversare(nodls *cap) {
	nodls*temp = cap;
	while (temp->next!=cap) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", *(temp->inf->cod), temp->inf->denumire, 
			temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
	printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", *(temp->inf->cod), temp->inf->denumire,
		temp->inf->pret, temp->inf->cantitate);
	
}

void traversare_inversa(nodls *coada) {
	nodls*temp = coada;
	while (temp->prev!=coada) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", *(temp->inf->cod), 
			temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
	printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", *(temp->inf->cod),
		temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
}

void dezalocare(nodls* cap) {
	nodls*temp = cap;
	while (temp->next!=cap) {
		nodls*temp2 = temp->next;
		free(temp->inf->denumire);
		free(temp->inf->cod);
		free(temp->inf);
		free(temp);
		temp = temp2;
	}
	nodls*temp2 = temp->next;
	free(temp->inf->denumire);
	free(temp->inf->cod);
	free(temp->inf);
	free(temp);
}

void conversie_lista_vector(nodls* cap,produs* *vect, int*nr) {
	nodls* temp = cap;
	while (temp->next != cap) {
		vect[*nr] = temp->inf;
		(*nr)++;
		nodls*temp2 = temp->next;
		free(temp);
		temp = temp2;

	}
	vect[*nr] = temp->inf;
	(*nr)++;
	free(temp);
}

//stergerea unui nod dupa denumirea lui
void sterge_nod_denumire(nodls **cap, nodls **coada, char* den)
{
	if (strcmp((*cap)->inf->denumire, den) == 0)//daca primul este nodul care
	//vrem sa il stergem
	{
		nodls* aux = *cap;
		*cap = (*cap)->next;
		(*coada)->next = *cap;
		(*cap)->prev = *coada;
		free(aux->inf->cod);
		free(aux->inf->denumire);
		free(aux->inf);
		free(aux);
		return; //ne scoate din functie
	}
	else
	{
		nodls*temp = *cap;
		while (temp->next != *cap)
		{
			if (strcmp(temp->inf->denumire, den) == 0){
				nodls*urmator = temp->next;
				nodls*anterior = temp->prev;
				anterior->next = urmator;
				urmator->prev = anterior;
				free(temp->inf->cod);
				free(temp->inf->denumire);
				free(temp->inf);
				free(temp);
				return;
			}
			else
			{
				temp=temp->next;
			}
		}
		if (strcmp(temp->inf->denumire, den) == 0) {
			nodls*urmator = temp->next;
			nodls*anterior = temp->prev;
			anterior->next = urmator;
			urmator->prev = anterior;
			free(temp->inf->cod);
			free(temp->inf->denumire);
			free(temp->inf);
			free(temp);
			return;
		}
	}
}


void main()
{
	int n;
	printf("Numarul de produse=");
	scanf("%d", &n);

	nodls*cap = NULL;
	nodls*coada = NULL;
	produs *p = NULL;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		p->cod = (int*)malloc(sizeof(int));
		printf("\nCod=");
		scanf("%d", p->cod);
		printf("\nDenumire=");
		scanf("%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		printf("\nPret=");
		scanf("%f", &p->pret);
		printf("\nCantitate=");
		scanf("%f", &p->cantitate);
		cap = inserare(cap, &coada,p);
		free(p->denumire);
		free(p->cod);
		free(p);

	}

	traversare(cap);
	traversare_inversa(coada);
	//dezalocare(cap);

	char denumire[20];
	printf("\nDenumire=");
	scanf("%s", denumire);
	sterge_nod_denumire(&cap, &coada, denumire);
	produs**vect = (produs**)malloc(n * sizeof(produs*));
	int nr = 0;
	conversie_lista_vector(cap,vect,&nr);
	for(int i=0;i<nr;i++)
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", *(vect[i]->cod),vect[i]->denumire,vect[i]->pret,
			vect[i]->cantitate);
	for (int i = 0; i < nr; i++) {
		free(vect[i]->cod);
		free(vect[i]->denumire);
		free(vect[i]);
	}
	free(vect);

}
