#include<stdio.h>
#include<malloc.h>

struct Laptop {
	int id; //%d
	int HDD; //%d
	char* producator ; //%s
	float pret ; //%.2f
	char model ; //%c
};
struct Laptop initializare(int id, int HDD, const char* producator, float pret, char model) {
	struct Laptop l;
	l.id = 1;
	l.HDD = HDD;
	l.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(l.producator, strlen(producator) + 1, producator);
	l.pret = pret;
	l.model = model;
	return l;
}

void afisare(struct Laptop l) {
	if (l.producator != NULL) {
		printf("%d Laptopul produs de catre %s, modelul %c, are %d GB si costa %.2f lei. \n", l.id, l.producator, 
			l.model, l.HDD, l.pret);
	}
}

void afisareVector(struct Laptop* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Laptop* copiazaPrimeleNElemente(struct Laptop* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Laptop *vectorNou=NULL;
	vectorNou = (struct Laptop*)malloc(sizeof(struct Laptop) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator) + 1);
		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
	}
	return vectorNou;
}

void dezalocare(struct Laptop** vector, int* nrElemente) {
	for (int i = 0; i < (*nrElemente); i++) {
		if ((*vector)[i].producator != NULL) {
			free((*vector)[i].producator);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaLaptopuriScumpe(struct Laptop* vector, char nrElemente, float pretMinim, struct Laptop** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret >= pretMinim) {
			(*dimensiune)++;
		}
	}
	if ((*vectorNou) != NULL) {
		free(*vectorNou);
	}
	*vectorNou = (struct Laptop*)malloc(sizeof(struct Laptop) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret >= pretMinim) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
			k++;
		}
	}
}

struct Laptop getPrimulLaptopByProducator(struct Laptop* vector, int nrElemente, const char* producator) {
	struct Laptop l;
	l.producator = NULL;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].producator, producator) == 0) {
			l = vector[i];
			l.producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s(l.producator, strlen(vector[i].producator)+1, vector[i].producator);
			return l;
		}
	}
	return l;
}
	


int main() {
	struct Laptop* laptop = NULL;
	int nrLaptop = 3;
	laptop = (struct Laptop*)malloc(sizeof(struct Laptop) * nrLaptop);
	laptop[0] = initializare(1, 500, "Asus", 2000.99, 'M');
	laptop[1] = initializare(2, 1000, "MSI", 3000.99, 'S');
	laptop[2] = initializare(3, 250, "Lenovo",1500.89, 'B');

	afisareVector(laptop, nrLaptop);

	struct Laptop* primeleLaptopuri = NULL;
	int nrPrimeleLaptopuri = 2;
	primeleLaptopuri = copiazaPrimeleNElemente(laptop, nrLaptop, nrPrimeleLaptopuri);
	printf("\n\nPrimele laptopuri:\n");
	afisareVector(primeleLaptopuri, nrPrimeleLaptopuri);
	dezalocare(&primeleLaptopuri, &nrPrimeleLaptopuri);
	afisareVector(primeleLaptopuri, nrPrimeleLaptopuri);

	//copiaza Laptopuri scumpe
	struct Laptop* laptopuriScumpe = NULL;
	int nrLaptopuriScumpe = 0;
	copiazaLaptopuriScumpe(laptop, nrLaptop, 2000.99, &laptopuriScumpe, &nrLaptopuriScumpe);
	printf("\n\nLaptopuri Scumpe: \n");
	afisareVector(laptopuriScumpe, nrLaptopuriScumpe);
	dezalocare(&laptopuriScumpe, &nrLaptopuriScumpe);

	struct Laptop laptopIdentificat = getPrimulLaptopByProducator(laptop, nrLaptop, "MSI");
	printf("\n\n Laptopul Identificat:\n");
	afisare(laptopIdentificat);
	if (laptopIdentificat.producator != NULL) {
		free(laptopIdentificat.producator);
		laptopIdentificat.producator = NULL;
	}
	dezalocare(&laptop, &nrLaptop);

	return 0;
}