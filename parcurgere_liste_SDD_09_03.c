#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct student student;
typedef struct nod nod;

typedef struct student {
	unsigned int id;
	char* nume;
	float medie;

}student;

student initializareStudent(unsigned int id, char* nume, float medie) {
	student s;
	s.id = id;
	s.nume =(char*)malloc(sizeof(char)*(strlen(nume)+1));
	strcpy(s.nume, nume);
	s.medie = medie;
	return s;
}
typedef struct nod {
	student info;
	nod* next;
}nod;

//inserare -> la inceput si la final
//inseare la inceput 
nod* inserareInceput(nod* cap, student s) {   // unde inserez si ce inserez
	//creez nod
	//aloc memorie
	nod* nou = (nod*)malloc(sizeof(nod));
	//umplu nodul cu informatie
	//nou->info = s; //shallow copy
	nou->info = initializareStudent(s.id, s.nume, s.medie); //deep copy
	nou->next = NULL;
	if (cap == NULL) {
		cap = nou;
	}
	else {
		nod* aux = cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	return cap;
} 
//inseare la final 


 
//afisare -> 

//dezalocare -> 

void main() {

	 student s;
}