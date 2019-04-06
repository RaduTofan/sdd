#include "pch.h"
#include <iostream>

using namespace std;
//lista simpla de liste simple

struct student
{
	int varsta;
	char* nume;
	float medie;

};

struct nodls {    //nodls- nod lista secundara
	student inf;
	nodls *next;


};

struct nodlp     //nodlp- nod lista principala
{
	nodls* info;
	nodlp* next;

};

void inserareLS(nodls **cap, student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodls *temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;

	}

}
void inserareLP(nodlp **capLP, nodls *capLS)
{
	nodlp* nou = (nodlp*)malloc(sizeof(nodlp));
	nou->info = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
		*capLP = nou;
	else
	{
		nodlp *temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;

	}
}

void traversareLS(nodls *cap) {
	nodls *temp = cap;
	while (temp)
	{
		printf("\nVarsta=%d, Nume=%s, Medie=%5.2f", temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;

	}
}

void traversareLP(nodlp *cap) {
	nodlp *temp = cap;
	while (temp) {
		printf("\nSublista\n");
		traversareLS(temp->info);
		temp = temp->next;

	}
}



void dezalocareLS(nodls *cap)
{
	nodls *temp = cap;
	while (temp) {
		nodls *temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;

	}
}

void dezalocareLP(nodlp *cap)
{
	nodlp *temp = cap;
	while (temp) {
		nodlp *temp2 = temp->next;
		dezalocareLS(temp->info);
		temp = temp2;

	}
}

void main()
{

	int n;
	printf("Nr studenti=");
	scanf("%d", &n);

	nodlp *capLP = NULL;
	nodls *capLSpar = NULL;
	nodls *capLSimpar = NULL;
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nVarsta=");
		scanf("%d", &s.varsta);
		printf("\nNume=");
		scanf(" %[^\n]s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);
		if (s.varsta % 2 == 0)
			inserareLS(&capLSpar, s);
		else
			inserareLS(&capLSimpar, s);
		
	}
	inserareLP(&capLP, capLSpar);
	inserareLP(&capLP, capLSimpar);
	traversareLP(capLP);
	dezalocareLP(capLP);
	
}