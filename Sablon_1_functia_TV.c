#include<stdio.h>
#include<stdlib.h>

struct TV {
	int id;
	int diagonala;
	char* producator;
	float pret;
	char model;
};

struct TV initializare(int id, int diagonala, const char* producator, float pret, char model) {
	struct TV t;
	t.id = id;
	t.diagonala = diagonala;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator)+1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.model = model;
	//initializare structura 
	return t;
}

void afisare(struct TV t) {
	if(t.producator != NULL ) {
		printf("%d. Tv-ul produs de catre %s, model %c, are %d inch si costa %5.2f RON.\n", t.id,
			t.producator, t.model, t.diagonala, t.pret);
	}
	else
	{
		printf("%d. Modelul de TV %c, are %d inch si costa %5.2f RON.\n", t.id,
			t.model, t.diagonala, t.pret);
	}

}

void modificaPret(struct TV* t, float PretNou) {
	if (PretNou > 0) {
		t->pret = PretNou;
	}
}

void dezalocare(struct TV *t) {
	if (t->producator != NULL) {
		free(t->producator);
		t->producator = NULL;
	}
}

int main() {
	struct TV t;
	t = initializare(1, 83, "Samsung", 1000.99, 'S');
	afisare(t);
	modificaPret(&t, 500.99);
	afisare(t);
	dezalocare(&t);
	afisare(t);
	return 0;
}