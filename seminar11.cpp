#include "pch.h"
#include <iostream>
#include <stdio.h>

//ARBORE BINAR DE CAUTARE
using namespace std;


struct student
{
int cod;
char *nume;
float medie;
};

struct nodarb
{
student inf; //informatia utila
nodarb *left, *right; //
};


nodarb* creare(student s, nodarb *st, nodarb* dr)
{
nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
nou->inf.cod = s.cod;
nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
strcpy(nou->inf.nume, s.nume);
nou->inf.medie = s.medie;
nou->left = st;
nou->right = dr;
return nou;
}

//functia de inserare
nodarb *inserare(student s, nodarb *rad)
{
nodarb*aux = rad; //ne vom folosi de acest aux pt a explora radacina
if (rad == NULL)
{
aux = creare(s, NULL, NULL);
return aux;
}
else
{
while (true) {
if (s.cod < aux->inf.cod)
{
if (aux->left != NULL)
aux = aux->left;
else
{
aux->left = creare(s, NULL, NULL);
return rad;
}
}
else
{
if (s.cod > aux->inf.cod)
if (aux->right != NULL)
aux = aux->right;
else
{
aux->right = creare(s, NULL, NULL);
return rad;
}
else
{
return rad;
}
}
}
}

}

//traversare in preordine
void preordine(nodarb *rad)
{
if (rad != NULL)
{
printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
preordine(rad->left);
preordine(rad->right);
}
}

void inordine(nodarb *rad)
{
if (rad != NULL)
{

inordine(rad->left);
printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
inordine(rad->right);
}
}

void postordine(nodarb *rad)
{
if (rad != NULL)
{

postordine(rad->left);
postordine(rad->right);
printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);

}
}

//dezalocare
void dezalocare(nodarb*rad)
{
if (rad != NULL)
{
nodarb *st = rad->left;
nodarb *dr = rad->right;
free(rad->inf.nume);
free(rad);
dezalocare(st);
dezalocare(dr);
}
}

int maxim(int a, int b)
{
int max = a;
if (max < b)
max = b;
return max;
}

int nrNiveluri(nodarb *rad)
{
if (rad != NULL)
return 1 + maxim(nrNiveluri(rad->left), nrNiveluri(rad->right));
else
return 0;

}

nodarb* cautare(nodarb * rad, int cheie)
{
if (rad != NULL)
{
if (rad->inf.cod == cheie)
return rad;
else
if (cheie < rad->inf.cod)
return cautare(rad->left, cheie);
else
return cautare(rad->right, cheie);
}
}

void conversieArboreVector(nodarb *rad, student *vect, int *nr) {
if (rad != NULL)
{
vect[*nr] = rad->inf;
(*nr)++;
conversieArboreVector(rad->left, vect, nr);
conversieArboreVector(rad->right, vect, nr);
}
}
void main()
{
int nr;
printf("Nr. studenti=");
scanf("%d", &nr);

nodarb *rad = NULL;
student s;
char buffer[20];

for (int i = 0; i < nr; i++)
{
printf("\nCod=");
scanf("%d", &s.cod);
printf("\nNume=");
scanf("%s", buffer);
s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
strcpy(s.nume, buffer);
printf("\nMedie=");
scanf("%f", &s.medie);

rad = inserare(s, rad);

}
inordine(rad);

printf("\nInaltimea este %d", nrNiveluri(rad));

nodarb *nodCautat = cautare(rad, 3);
if (nodCautat != NULL)
printf("\nStudent cu codul 3 se cheama %s", nodCautat->inf.nume);

printf("\n======================\n");

student *vect = (student*)malloc(nr * sizeof(student));
int k = 0;
conversieArboreVector(rad, vect, &k);
for (int i = 0; i < k; i++)
printf("\nCod=%d, Nume=%s, Medie=%5.2f", vect[i].cod, vect[i].nume, vect[i].medie);
free(vect);


dezalocare(rad);

}










