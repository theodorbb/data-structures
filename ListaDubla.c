#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Avion Avion;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Avion
{
	char* denumire;
	int capacitate;
};

struct Nod
{
	Avion info;
	Nod* prev;
	Nod* next;

};


struct ListaDubla
{
	Nod* prim;
	Nod* ultim;
};

Avion initAvion(char* denumire, int capacitate)
{
	Avion a;
	a.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(a.denumire, denumire);

	a.capacitate = capacitate;
	return a;
}

void inserareLaInceput(Avion a, ListaDubla* lista)
{
	Nod* n;
	n = (Nod*)malloc(sizeof(Nod) * 1);

	n->prev = NULL;
	n->info = a;
	n->next = lista->prim;

	if (lista->prim != NULL)
	{
		lista->prim->prev = n;
		lista->prim = n;
	}
	else {
		lista->prim = lista->ultim = n;
	}

}


void inserareLaSfarsit(Avion a, ListaDubla* lista)
{
	Nod* n = (Nod*)malloc(sizeof(Nod));
	n->info = a;
	n->next = NULL;
	n->prev = lista->ultim;

	if (lista->ultim != NULL)
	{
		lista->ultim->next = n;
		lista->ultim = n;
	}
	else
	{
		lista->ultim = lista->prim = n;
	}
}

void afisAvion(Avion a)
{
	printf("\n %s %d", a.denumire, a.capacitate);
}

//afisare lista de la stanga la dreapta
void afisareLista(ListaDubla lista)
{
	while (lista.prim != NULL)
	{
		afisAvion(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

//lista circulara
void afisareListaCirculara(ListaDubla lista)
{
	Nod* aux = lista.prim; //sau lista.ultim->
	do {
		afisAvion(aux->info);
		aux = aux->next;
	} while (aux != lista.prim);

}

//dezalocare de la dreapta la stanga
void stergereLista(ListaDubla* lista)
{
	Nod* aux = lista->ultim;
	while (aux != NULL)
	{
		free(aux->info.denumire);
		aux = aux->prev;

		//ne deplasam in stanga, dar sa nu ajungem pe null
		if (aux != NULL)
			free(aux->next);
	}
	free(lista->prim); //dezalocam si ultimul nod din lista
	lista->prim = NULL;
	lista->ultim = NULL;
	printf("\nS-a dezalocat complet");
}

//functie de conversie
void conversie(ListaDubla lista, int* pozVect, Avion** vectAvioane)
{
	Nod* aux = lista.prim;
	while (aux)
	{
		(*vectAvioane)[*pozVect] = initAvion(aux->info.denumire, aux->info.capacitate);
		(*pozVect)++;
		aux = aux->next;
	}
}


int main()
{
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initAvion("Boeing", 500), &lista);
	inserareLaInceput(initAvion("Boeing 1", 530), &lista);
	inserareLaInceput(initAvion("Boeing 2", 400), &lista);

	inserareLaSfarsit(initAvion("TAROM1", 120), &lista);
	inserareLaSfarsit(initAvion("TAROM2", 190), &lista);
	inserareLaSfarsit(initAvion("TAROM3", 150), &lista);

	afisareLista(lista);


	//lista circulara
	//lista.prim->prev = lista.ultim;
	//lista.ultim->next = lista.prim;
	//printf("\nAfisare lista circulara\n");
	//afisareListaCirculara(lista);


	int nrAvioane = 6;
	Avion* vectAvioane = (Avion*)malloc(sizeof(Avion) * nrAvioane);


	int pozVect = 0;
	conversie(lista, &pozVect, &vectAvioane);

	printf("\nAfisare vector\n");
	for (int i = 0; i < pozVect; i++)
	{
		afisAvion(vectAvioane[i]);
		free(vectAvioane[i].denumire);
	}
	free(vectAvioane);

	//! atentie: daca vreau sa dezaloc lista dubla e diferita de lista circulara
	//dezalocare
	stergereLista(&lista);

	return 0;
}
