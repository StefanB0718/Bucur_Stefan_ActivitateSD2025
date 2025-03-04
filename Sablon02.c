#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	int anFabricatie;
	char* Producator;
	float Pret;
	char Serie;
};
struct Masina initializare(int id, int anFabricatie, const char* Producator, float Pret, char Serie) {
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	m.Producator = (char*)malloc((strlen(Producator) + 1) * sizeof(char));
	strcpy_s(m.Producator, strlen(Producator) + 1, Producator);
	m.Pret = Pret;
	m.Serie = Serie;
	return m;
}

void afisare(struct Masina m) {
	printf("ID-ul masinii: %d\n", m.id);
	printf("Anul de fabricatie al masinii: %d\n", m.anFabricatie);
	printf("Producatorul masinii este: %s\n", m.Producator);
	printf("Pretul masinii este: %.2f\n", m.Pret);
	printf("Seria masinii este: %c\n", m.Serie);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	struct Masina *vectorNou=NULL;
	if (nrElementeCopiate <= nrElemente) {
		vectorNou = (struct Masina*)malloc(sizeof(struct Masina) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i].id = vector[i].id;
			vectorNou[i].anFabricatie = vector[i].anFabricatie;
			vectorNou[i].Pret = vector[i].Pret;
			vectorNou[i].Serie = vector[i].Serie;
			vectorNou[i].Producator = (char*)malloc(strlen(vector[i].Producator) + 1);
			strcpy_s(vectorNou[i].Producator, strlen(vector[i].Producator) + 1, vector[i].Producator);
		}
	}

	return vectorNou;
}
//
void dezalocare(struct Masina** vector, int* nrElemente) {
	if (*vector) {
    for (int i = 0; i < *nrElemente; i++) {
        free((*vector)[i].Producator);
    }
    free(*vector);
    *vector = NULL;
}
*nrElemente = 0;
	}

void copiazaMasiniScumpe(struct Masina* vector, int nrElemente, float pretMinim, struct Masina** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].Pret >= pretMinim) {
			(*dimensiune)++;
		}
	}
	if (*dimensiune == 0) {
		*vectorNou = NULL;
		return;
	}
		*vectorNou = (struct Masina*)malloc(sizeof(struct Masina) * (*dimensiune));
		if (!*vectorNou) {
			*vectorNou = NULL;
			*dimensiune = 0;
			return;
		}
		int k = 0;
		for (int i = 0; i < nrElemente; i++) {
			if (vector[i].Pret >= pretMinim) {
				(*vectorNou)[k].id = vector[i].id;
				(*vectorNou)[k].anFabricatie = vector[i].anFabricatie;
				(*vectorNou)[k].Pret = vector[i].Pret;  
				(*vectorNou)[k].Serie = vector[i].Serie;
				(*vectorNou)[k].Producator = (char*)malloc(strlen(vector[i].Producator) + 1);
				if ((*vectorNou)[k].Producator) {
					strcpy((*vectorNou)[k].Producator, vector[i].Producator);
				}
				k++;
			}
		}
}


int main() {
	struct Masina masina = initializare(1, 2020, "BMW", 35000.99, 'M');
	afisare(masina);

	int nrMasini = 3;
	struct Masina* masini;
	masini = (struct Masina*)malloc(nrMasini * sizeof(struct Masina));
	masini[0] = initializare(2, 2024, "Mercedes", 50000.09, 'V');
	masini[1] = initializare(3, 2000, "Skoda", 9999.89, 'R');
	masini[2] = initializare(4, 2025, "Ford", 98000.98, 'F');
	printf("\n");
	afisare(masini[0]);
	printf("\n");
	afisare(masini[1]);
	printf("\n");
	afisare(masini[2]);

	int masiniFiabile = 1;
	int nrElemente = nrMasini;
	struct Masina* vectorScurt = copiazaPrimeleNElemente(masini, nrElemente, masiniFiabile);
	printf("\n\nMasini fiabile:\n");
	afisareVector(vectorScurt, masiniFiabile);

	float pretMinim = 50000.99;
	int nrMasiniScumpe=0;
	struct Masina* masiniScumpe = NULL;
	copiazaMasiniScumpe(masini, nrMasini, pretMinim, &masiniScumpe, &nrMasiniScumpe);
	if (masiniScumpe != NULL && nrMasiniScumpe > 0) {
		printf("\nMasinile scumpe sunt:\n");
		afisareVector(masiniScumpe, nrMasiniScumpe);
		dezalocare(&masiniScumpe, &nrMasiniScumpe);
	}
	else {
		printf("\nNu exista masini scumpe!\n");
	}


	return 0;
}