// ConsoleApplication63.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

//SCHIMBAM PENTRU VECTOR, PUNEM APEL

using namespace std;
struct Apel {
	int prioritate;
	char*solicitant;

};
struct heap {
	Apel*vect;
	int nrElem;
};


void filtrare(heap h, int index) //index - pozitia de unde incepe filtrarea Radacina =i, Stanga=2*i+1,Dreapta=2*i+2;
{
	int indexMax = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS<h.nrElem && h.vect[indexS].prioritate>h.vect[indexMax].prioritate) //doar schimbam indexul, daca gasim 1 mai mare;
		indexMax = indexS;

	if (indexD<h.nrElem && h.vect[indexD].prioritate>h.vect[indexMax].prioritate)
		indexMax = indexD;

	if (index != indexMax) //interschimbarea efectiva
	{
		Apel aux = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = aux;

		filtrare(h, indexMax);
	}

}

void inserare(heap *h, int elem)//daca ceva se modifica la parametri, bagam 1 steluta
{
	Apel *vect1 = (Apel*)malloc(((*h).nrElem + 1) * sizeof(Apel));//alocam vect elem 
	for (int i = 0; i < (*h).nrElem; i++)
		vect1[i] = (*h).vect[i];
	vect1[(*h).nrElem] = elem;
	(*h).nrElem++;//crestem numarul de elemente
	free((*h).vect);
	(*h).vect = vect1;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i++)
		filtrare(*h, i);

}

void extragere(heap *h, int *elem)//* pt ca am un element mai putin
{
	Apel *vect1 = (Apel*)malloc(((*h).nrElem - 1) * sizeof(Apel));

	int aux = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = aux;
	//l-am dus pe ultimul element
	*elem = (*h).vect[(*h).nrElem - 1];

	for (int i = 0; i < (*h).nrElem - 1; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem--;
	free((*h).vect);
	(*h).vect = vect1;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i++)
		filtrare(*h, i);
}

void afisare(heap h)
{
	printf("\nElemente heap: ");
	for (int i = 0; i < h.nrElem; i++)
		printf("%d ", h.vect[i]);

}

void main()
{
	heap h;
	printf("Nr. Elemente: ");
	scanf("%d", &h.nrElem);
	h.vect = (int*)malloc(h.nrElem * sizeof(int));
	for (int i = 0; i < h.nrElem; i++)
	{
		printf("\nElement %d: ", i + 1);
		scanf("%d", &h.vect[i]);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisare(h);
	inserare(&h, 50);
	//afisare(h);

	//int elem;
	//extragere(&h, &elem);
	//printf("\nElemente extras:", elem);
	//afisare(h);

//	int *vectSortat = (int*)malloc(h.nrElem * sizeof(int));
//	int n = h.nrElem;
//	for (int i = 0; i < n; i++)
//	{
//		extragere(&h, &elem);
//		vectSortat[i] = elem;
//	}
//	printf("\nVector sortat: ");
//	for (int i = 0; i < n; i++)
//		printf("%d ", vectSortat[i]);
//	free(h.vect);
//	free(vectSortat);



}
