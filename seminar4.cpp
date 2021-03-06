#include "pch.h"
#include <iostream>

//STIVA

struct carte {
	int cod;
	char * titlu;
	float pret;

};

struct nodStiva {
	carte inf;
	nodStiva *next;

};

struct nodld {	//lista dubla
	carte inf;
	nodld *next;
	nodld *prev;
};

void push(nodStiva **varf, carte c) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = c.cod;
	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);
	nou->inf.pret = c.pret;
	nou->next = NULL;
	if (*varf == NULL) {
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		*varf = nou;
	}

}

int pop(nodStiva** varf, carte *val) {
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).cod = (*varf)->inf.cod;
		(*val).titlu = (char*)malloc((strlen((*varf)->inf.titlu) + 1) * sizeof(char));
		strcpy((*val).titlu, (*varf)->inf.titlu);
		(*val).pret = (*varf)->inf.pret;
		nodStiva*aux = *varf;
		*varf = (*varf)->next;
		free(aux->inf.titlu);
		free(aux);
		return 0;
	}
}

void inserareLista(nodld **cap, carte c ) {      //2 stelute pt ca e void
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->inf.cod = c.cod;
	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);
	nou->inf.pret = c.pret;
	nou->next = NULL;
	nou->prev = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodld *temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
	}
}

void traversareStiva(nodStiva *varf) {
	nodStiva *temp = varf;
	while (temp)
	{
		printf("\nCod=%d, Titlu=%s, Pret=%5.2f", temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void dezalocareLista(nodld *cap) {
	nodld *temp = cap;
	while (temp)
	{
		nodld *temp2 = temp->next;
		free(temp->inf.titlu);
		free(temp);
		temp = temp2;
	}
}

void traversareLista(nodld *cap) {
	nodld *temp = cap;
	while (temp)
	{
		printf("\nCod=%d, Titlu=%s, Pret=%5.2f", temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void conversieStivaLista(nodStiva **varf, nodld**cap) {
	carte val;
	while (pop(varf, &val) == 0)
		inserareLista(cap, val);


}

void conversieStivaVector(nodStiva **varf, carte *vect, int*nr)
{
	carte val;
	while (pop(varf, &val) == 0) {
		vect[*nr] = val;
		(*nr)++;
	}
}

void main() {
	int n;
	printf("Nr. carti=");
	scanf("%d", &n);
	
	nodStiva *varf = NULL;
	carte c;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod=");
		scanf("%d", &c.cod);
		printf("\nTitlu=");
		//gets(buffer);
		//fgets(buffer, 20, stdin);
		//cin.getline(buffer, 20, '.');
		scanf(" %[^\n]s", buffer);       //trebuie sa alegem una dintre aceste metode de citire, scanf cel mai bn. ATENTIE trebuie lasat spatiu intr " si %;
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		printf("\nPret=");
		scanf("%f", &c.pret);
		push(&varf, c);

	}

	traversareStiva(varf);

	//carte c1;
	//pop(&varf, &c1);
	//printf("\nCartea extrasa are codul %d, titlul %s, pretul %5.2f", c1.cod, c1.titlu, c1.pret);

	//while (pop(&varf, &c1) == 0)
	//{
	//	printf("\nAm sters %d", c1.cod);
	//}

	printf("\nVector---------------------------\n");

	//carte* vect = (carte*)malloc(n * sizeof(carte));
	//int nr = 0;
	//conversieStivaVector(&varf, vect, &nr);
	//for (int i = 0; i < nr; i++)
	//	printf("\nCod=%d, Titlu=%s, Pret=%5.2f", vect[i].cod, vect[i].titlu, vect[i].pret);
	//for (int i = 0; i < nr; i++)
	//	free(vect[i].titlu);
	//free(vect);

	nodld *cap = NULL;
	conversieStivaLista(&varf, &cap);
	traversareLista(cap);
	dezalocareLista(cap);


}








