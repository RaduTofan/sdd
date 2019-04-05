#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;

//struct produs {
//	int cod;
//	char * denumire;
//	float pret;
//	float cantitate;
//
//};
//
//struct nodls { //nod lista;pentru definirea nodului unei lista
//	produs inf;
//	nodls *next;
//};
//
//nodls* inserare(nodls *cap, produs p)
//{
//	nodls* nou = (nodls*)malloc(sizeof(nodls));
//	
//	nou->inf.cod = p.cod;
//	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
//	strcpy(nou->inf.denumire, p.denumire);
//	nou->inf.pret = p.pret;
//	nou->inf.cantitate = p.cantitate;
//	nou->next = NULL;
//	if (cap == NULL)
//		cap = nou;
//	else
//	{
//		nodls*temp = cap;
//		while (temp->next != NULL)
//			temp = temp->next;
//		temp->next = nou;
//	}
//	return cap;
//}
//
//void traversare(nodls *cap) {
//	nodls*temp = cap;
//	while (temp != NULL) {
//		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.cantitate);
//		temp = temp->next;
//	}
//}
//
//void dezalocare(nodls* cap) {
//	nodls*temp = cap;
//	while (temp != NULL) {
//		nodls*temp2 = temp->next;
//		free(temp->inf.denumire);
//		free(temp);
//		temp = temp2;
//	}
//}
//
//void main()
//{
//	int n;
//	printf("Numarul de produse=");
//	scanf("%d", &n);
//
//	nodls*cap = NULL;
//	produs p;
//	char buffer[20];
//
//	for (int i = 0; i < n; i++)
//	{
//		printf("\nCod=");
//		scanf("%d", &p.cod);
//		printf("\nDenumire=");
//		scanf("%s", buffer);
//		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
//		strcpy(p.denumire, buffer);
//		printf("\nPret=");
//		scanf("%f", &p.pret);
//		printf("\nCantitate=");
//		scanf("%f", &p.cantitate);
//		cap = inserare(cap, p);
//
//	}
//	
//	traversare(cap);
//	dezalocare(cap);
//
//
//}

//--------------CAND INFORMATIA UTILA ESTE POINTER LA PRODUS (produs *inf) -------------//
//struct produs {
//	int cod;
//	char * denumire;
//	float pret;
//	float cantitate;
//
//};
//
//struct nodls { //pentru definirea nodului unei lista
//	produs *inf;
//	nodls *next;
//};
//
//nodls* inserare(nodls *cap, produs *p)
//{
//	nodls* nou = (nodls*)malloc(sizeof(nodls));
//	nou->inf = (produs*)malloc(sizeof(produs));
//	nou->inf->cod = p->cod;
//	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
//	strcpy(nou->inf->denumire, p->denumire);
//	nou->inf->pret = p->pret;
//	nou->inf->cantitate = p->cantitate;
//	nou->next = NULL;
//	if (cap == NULL)
//		cap = nou;
//	else
//	{
//		nodls*temp = cap;
//		while (temp->next != NULL)
//			temp = temp->next;
//		temp->next = nou;
//	}
//	return cap;
//}
//
//void traversare(nodls *cap) {
//	nodls*temp = cap;
//	while (temp != NULL) {
//		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", temp->inf->cod, temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
//		temp = temp->next;
//	}
//}
//
//void dezalocare(nodls* cap) {
//	nodls*temp = cap;
//	while (temp != NULL) {
//		nodls*temp2 = temp->next;
//		free(temp->inf->denumire);
//		free(temp->inf);
//		free(temp);
//		temp = temp2;
//	}
//}
//
//void main()
//{
//	int n;
//	printf("Numarul de produse=");
//	scanf("%d", &n);
//
//	nodls*cap = NULL;
//	produs *p=NULL;
//	char buffer[20];
//
//	for (int i = 0; i < n; i++)
//	{
//		p = (produs*)malloc(sizeof(produs));
//		printf("\nCod=");
//		scanf("%d", &p->cod);
//		
//		printf("\nDenumire=");
//		scanf("%s", buffer);
//		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
//		strcpy(p->denumire, buffer);
//		printf("\nPret=");
//		scanf("%f", &p->pret);
//		printf("\nCantitate=");
//		scanf("%f", &p->cantitate);
//		cap = inserare(cap, p);
//		free(p->denumire);
//		free(p);
//
//	}
//
//	traversare(cap);
//	dezalocare(cap);
//
//
//}

//LISTA DUBLA!!!!!!!!!

struct produs {
	int cod;
	char * denumire;
	float pret;
	float cantitate;

};

struct nodls { //pentru definirea nodului unei lista
	produs *inf;
	nodls *next;
	nodls* prev;
};

nodls* inserare(nodls *cap, produs *p)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = p->cod;
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;
	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
		cap = nou;
	else
	{
		nodls*temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
	}
	return cap;
}

void traversare(nodls *cap) {
	nodls*temp = cap;
	while (temp != NULL) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantiate=%5.2f", temp->inf->cod, temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
}

void dezalocare(nodls* cap) {
	nodls*temp = cap;
	while (temp != NULL) {
		nodls*temp2 = temp->next;
		free(temp->inf->denumire);
		free(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int n;
	printf("Numarul de produse=");
	scanf("%d", &n);

	nodls*cap = NULL;
	produs *p = NULL;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		printf("\nCod=");
		scanf("%d", &p->cod);

		printf("\nDenumire=");
		scanf("%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		printf("\nPret=");
		scanf("%f", &p->pret);
		printf("\nCantitate=");
		scanf("%f", &p->cantitate);
		cap = inserare(cap, p);
		free(p->denumire);
		free(p);

	}

	traversare(cap);
	dezalocare(cap);


}
