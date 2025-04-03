#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>


typedef struct Comanda Comanda;

struct Comanda {
	unsigned int id;
	char* dataLansare;
	char* dataLivrare;
	char* nume;
	float suma;
};

Comanda creareComanda(unsigned int id, char* dataLansare, char* dataLivrare, char* nume, float suma) {
	Comanda c;
	c.id = id;
	c.dataLansare = (char*)malloc(sizeof(char) * strlen(dataLansare) + 1);
	strcpy(c.dataLansare, dataLansare);
	c.dataLivrare = (char*)malloc(sizeof(char) * strlen(dataLivrare) + 1);
	strcpy(c.dataLivrare, dataLivrare);
	c.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.suma = suma;

	return c;

}
typedef struct hashTable hashTable;
typedef struct nod nod;
struct nod {
	Comanda info;
	nod* next;
};

struct hashTable {
	int dim;
	nod** vector;
};


int functieHash(hashTable tabela, unsigned int id) {
	return id % tabela.dim;
}

int functieHash1(hashTable tabela, const char* dataLansare) {
	return  strlen(dataLansare) % tabela.dim;//nr de caractere din sir %10
}

int functieHash2(hashTable tabela, const char* dataLansare) {
	return  dataLansare[0] % tabela.dim;//nr de caractere din sir %10
}

int inserareHash(hashTable tabela, Comanda c) {
	int poz = 0;
	if (tabela.vector) {
		poz = functieHash2(tabela, c.dataLansare);
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareComanda(c.id, c.dataLansare, c.dataLivrare, c.nume, c.suma);
		nou->next = NULL;
		if (tabela.vector[poz] == NULL) {
			tabela.vector[poz] = nou;
		}
		else {//coliziune
			nod* aux = tabela.vector[poz];
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = nou;
		}
	}

	return poz;
}

void afisare(hashTable tabela) {
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			printf("Pozitia: %d\n", i);
			nod* aux = tabela.vector[i];
			while (aux) {
				printf("Comanda: %u, %s, %s, %s, %.2f \n", aux->info.id, aux->info.dataLansare, aux->info.dataLivrare, aux->info.nume, aux->info.suma);
				aux = aux->next;
			}
		}
	}
}

void dezalocare(hashTable tabela) {
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			nod* aux = tabela.vector[i];
			while (aux) {
				free(aux->info.dataLansare);
				free(aux->info.dataLivrare);
				free(aux->info.nume);
				nod* temp = aux->next;
				free(aux);
				aux = temp;

			}
		}
		free(tabela.vector);

	}
}


int numarComenziLaDataLivrare(hashTable tabela, const char* dataLivrareCautata) {
	int contor = 0;
	if (tabela.vector) {
		for (int i = 0; i < tabela.dim; i++) {
			nod* aux = tabela.vector[i];
			while (aux) {
				if (strcmp(aux->info.dataLivrare, dataLivrareCautata) == 0) {
					contor++;
				}

				aux = aux->next;;
			}
		}

	}

	return contor;
}

void main() {
	int dim = 3;
	Comanda* vector = (Comanda*)malloc(sizeof(Comanda) * dim);
	Comanda c1 = creareComanda(122, "13.03.2025", "25.03.2025", "Ana", 178.98);
	Comanda c2 = creareComanda(222, "27.03.2025", "07.03.2025", "Dan", 123.99);
	Comanda c3 = creareComanda(478, "03.03.2025", "15.03.2025", "Andrei", 328.99);
	Comanda c4 = creareComanda(475, "17.03.2025", "09.03.2025", "Maria", 1478.88);
	Comanda c5 = creareComanda(982, "31.03.2025", "25.03.2025", "Popescu", 11489.99);
	Comanda c6 = creareComanda(985, "23.03.2025", "15.03.2025", "Ionesccu", 787);
	vector[0] = c1;
	vector[1] = c2;
	vector[2] = c3;

	for (int i = 0; i < dim; i++) {
		printf("Comanda cu ID: %u, %s\n", vector[i].id, vector[i].nume);
	}
	Comanda* pointerC1 = &c1;
	int dim1 = 3;
	Comanda** vector1 = (Comanda**)malloc(sizeof(Comanda*) * dim1);
	vector1[0] = pointerC1;
	vector1[1] = &c2;
	vector1[2] = &c3;
	for (int i = 0; i < dim; i++) {
		printf("Comanda cu ID: %u, %s\n", (*vector1[i]).id, vector1[i]->nume);
	}


	//initializare hash table
	hashTable tabela;
	tabela.dim = 10;
	tabela.vector = (nod**)malloc(sizeof(nod*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vector[i] = NULL;
	}

	inserareHash(tabela, c1);
	inserareHash(tabela, c2);
	inserareHash(tabela, c3);
	inserareHash(tabela, c4);
	inserareHash(tabela, c5);
	inserareHash(tabela, c6);


	afisare(tabela);

	int nr = numarComenziLaDataLivrare(tabela, "25.03.2025");
	printf("\n%d\n", nr);

}
