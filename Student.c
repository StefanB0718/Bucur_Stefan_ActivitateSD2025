#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct student student;
typedef struct nod nod;
typedef struct ListaDubla ListaDubla;

typedef struct student {
	unsigned int id;//%u
	char* nume;//%s
	float medie;//%.2f
}student;

student initializareStudent(unsigned int id, char* nume, float medie) {
	student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.medie = medie;
	return s;
}

typedef struct nod {
	student info;
	nod* next;
}nod;
nod* inserare(nod* cap, student s) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializareStudent(s.id, s.nume, s.medie);
	nou->next = NULL;
	if (cap == NULL) {
		cap = nou;
		nou->next = cap;
	}
	else {
		nod* aux = cap;
		while (aux->next!=cap) {
			aux = aux->next;
		}
		aux->next = nou;
		nou->next = cap;
		
		//cap=nou
	}
	return cap;
}
void afisare(nod* cap) {
	nod* aux = cap;
	while (aux->next!=cap) {
		printf("Studentul: %u, %s, %.2f \n", aux->info.id, aux->info.nume, aux->info.medie);
		aux = aux->next;
	}
	printf("Studentul: %u, %s, %.2f \n", aux->info.id, aux->info.nume, aux->info.medie);
}

void dezalocare(nod* cap) {
	nod* aux = cap;
	while (aux->next != cap) {
		free(aux->info.nume);
		nod* temp = aux->next;
		free(aux);
		aux = temp;
	}
	free(aux->info.nume);
	free(aux);
}

void main() {


	//initializare lista
	nod* cap = NULL;
	student s;

	//pt citire din fisier 
	char linieBuffer[128];
	char* token;
	char delimitator[] = ",";//\n

	//fisierul
	FILE* f = fopen("studenti.txt", "r");

	//citire
	if (f) {
		while (fgets(linieBuffer, sizeof(linieBuffer), f)) {//linieBuffer="111,Andrei Popescu,9.8"
			//pt int
			token = strtok(linieBuffer, delimitator);//token="111"
			s.id = atoi(token);//s.id=111

			//pt char*
			token = strtok(NULL, delimitator);//token="Andrei Popescu"
			s.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(s.nume, token);//s.nume="Andrei Popescu"

			//pt float
			token = strtok(NULL, delimitator);//token="9.8"
			s.medie = atof(token);

			cap = inserare(cap, s);

			free(s.nume);
		}
	}
	fclose(f);

	afisare(cap);




}