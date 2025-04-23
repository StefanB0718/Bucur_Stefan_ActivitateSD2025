#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;
struct Comanda {
	unsigned int id;
	char* dataLansare;
	char* dataLivrare;
	char* numeClient;
	float valoareComanda;
};

struct Nod {
	Comanda info;
	Nod* next;
	Nod* prev;
};
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
void InserareLista(ListaDubla* lista, Comanda c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;
	if (lista->prim == NULL) {
		lista->prim = lista->ultim = nou;
	}
	else {
		nou->next = lista->prim;
		lista->prim->prev = nou;
		lista->prim = nou;
	}
}

void Afisare(ListaDubla lista) {
	if (lista.prim) {
		while (lista.prim) {
			printf("%u, %s, %s, %s, %.2f \n", lista.prim->info.id, lista.prim->info.dataLansare, lista.prim->info.dataLivrare, lista.prim->info.numeClient, lista.prim->info.valoareComanda);
			lista.prim = lista.prim->next;
		}
	}
	else {
		printf("Lista este goala");
	}
}

void Dezalocare(ListaDubla lista) {
	while (lista.prim) {
		Nod* temp = lista.prim;
		lista.prim = lista.prim->next;
		free(temp->info.dataLansare);
		free(temp->info.dataLivrare);
		free(temp->info.numeClient);
		free(temp);
	}
}

float ValMedie(ListaDubla lista) {
	float suma = 0;
	int contor = 0;
	while (lista.prim) {
		suma += lista.prim->info.valoareComanda;
		contor++;
		lista.prim = lista.prim->next;
	}
	return suma / contor;
}

int ContorClient(ListaDubla lista, char* numeClient) {
	int contor = 0;
	while (lista.prim) {
		if (strcmp(numeClient, lista.prim->info.numeClient) == 0) {
			contor++;
		}
		lista.prim = lista.prim->next;
	}
	return contor;
}

void main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	Comanda c;
	char Linie[100];
	char Sep[] = ",";
	char* token;

	FILE* f = fopen("Text.txt", "r");
	while (fgets(Linie, 100, f)) {
		token = strtok(Linie, Sep);
		c.id = atoi(token);
		token = strtok(NULL, Sep);
		c.dataLansare = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(c.dataLansare, token);
		token = strtok(NULL, Sep);
		c.dataLivrare = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(c.dataLivrare, token);
		token = strtok(NULL, Sep);
		c.numeClient = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(c.numeClient, token);
		token = strtok(NULL, Sep);
		c.valoareComanda = atof(token);

		InserareLista(&lista, c);
	}
	Afisare(lista);

	printf("%.2f\n", ValMedie(lista));
	printf("%d\n", ContorClient(lista, " Avram Iulian"));
}