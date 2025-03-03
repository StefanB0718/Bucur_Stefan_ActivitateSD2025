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
	m.Serie = Serie;
	return m;
}

void afisare(struct Masina m) {
	printf("ID-ul masinii: %d\n", m.id);
	printf("Anul de fabricatie al masinii: %d\n", m.anFabricatie);
	printf("Producatorul masinii este: %s\n", m.Producator);
	printf("Seria masinii este: %c\n", m.Serie);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}
//
//struct Sablon* copiazaPrimeleNElemente(struct Sablon* vector, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	struct Sablon *vectorNou=NULL;
//
//	return vectorNou;
//}
//
//void dezalocare(struct Masina** vector, int* nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		free((*vector)[i].nume);
//		*nrElemente = 0;
//		*vector = NULL;
//	}
//}
//
//void copiazaAnumiteElemente(struct Sablon* vector, char nrElemente, float prag, struct Sablon** vectorNou, int* dimensiune) {
//	//parametrul prag poate fi modificat in functie de 
//	// tipul atributului ales pentru a indeplini o conditie
//	//este creat un nou vector cu elementele care indeplinesc acea conditie
//}
//
//struct Sablon getPrimulElementConditionat(struct Sablon* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Sablon s;
//	s.id = 1;
//
//	return s;
//}
	


int main() {
	struct Masina masina = initializare(1, 2020, "BMW", 35000.99, 'M');
	afisare(masina);

	int nrMasini = 2;
	struct Masina* masini;
	masini = (struct Masina*)malloc(nrMasini * sizeof(struct Masina));
	masini[0] = initializare(2, 2024, "Mercedes", 50000.09, 'V');
	masini[1] = initializare(3, 2000, "Skoda", 9999.89, 'R');
	printf("\n");
	afisare(masini[0]);
	printf("\n");
	afisare(masini[1]);


	return 0;
}