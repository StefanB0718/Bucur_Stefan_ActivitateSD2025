#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraCarte {
	int id; //%d
	int nrPagini; //%d
	float pret; //%.2f
	char* titlu; // %s
	char* autor;// %s
	unsigned char cod; //%c
};
typedef struct StructuraCarte Carte;

void afisareCarte(Carte carte) {
	printf("ID:%d\n", carte.id);
	printf("Nr. pagini:%d\n", carte.nrPagini);
	printf("Pret:%.2f\n", carte.pret);
	printf("Titlul cartii:%s\n", carte.titlu);
	printf("Autorul cartii:%s\n", carte.autor);
	printf("Codul cartii:%c\n\n", carte.cod);
}

void afisareVectorCarti(Carte* carti, int nrCarti) {
	for (int i=0; i < nrCarti; i++) {
		afisareCarte(carti[i]); 
	}
}

void adaugaCarteInVector(Carte** carti, int* nrCarti, Carte carteNoua) {
	Carte* aux = (Carte*)malloc(sizeof(Carte)*((*nrCarti)+1));
	for (int i = 0; i < *nrCarti; i++) {
		aux[i] = (*carti)[i];
	}
	aux[(*nrCarti)] = carteNoua; //shallow copy
	free(*carti);
	(*carti) = aux;
	(*nrCarti)++;
	
}

Carte citireCarteFisier(FILE* file) {
	Carte c;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);
	c.id = atoi(strtok(buffer, sep));
	c.nrPagini = atoi(strtok(NULL, sep));
	c.pret = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy(c.titlu, aux);
	aux = strtok(NULL, sep);
	c.autor = (char*)malloc(strlen(aux) + 1);
	strcpy(c.autor, aux);
	c.cod = strtok(NULL, sep)[0];
	return c;
}

Carte* citireVectorCartiFisier(const char* numeFisier, int* nrCartiCitite) {
	FILE* file = fopen(numeFisier, "r");
	Carte* carti = NULL;
	(*nrCartiCitite) = 0;
	while (!feof(file)) {
		adaugaCarteInVector(&carti, nrCartiCitite, citireCarteFisier(file));
	}
	fclose(file);
	return carti;

	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorCarti(Carte** vector, int* nrCarti) {
	for (int i = 0; i < *nrCarti; i++) {
		if ((*vector)[i].autor != NULL) {
			free((*vector)[i].autor);
		}
		if ((*vector)[i].titlu != NULL) {
			free((*vector)[i].titlu);
		}
	}
	free(*vector);
	(*vector) = NULL;
	(*nrCarti) = 0;
}

int main() {
	int nrCarti = 0;
	Carte* carti = citireVectorCartiFisier("carti.txt", &nrCarti);
	afisareVectorCarti(carti, nrCarti);
	dezalocareVectorCarti(&carti, &nrCarti);


	return 0;
}