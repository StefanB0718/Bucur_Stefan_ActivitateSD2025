#include<stdio.h>
#include<stdlib.h>

struct Casti {
	int id;
	int anAparitie;
	char* producator;
	float pret;
	char categorie;
};
	struct Casti initializare(int id, int anAparitie, const char* producator, float pret, char categorie) {
		struct Casti c;
		c.id = id;
		c.anAparitie = anAparitie;
		c.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
		strcpy_s(c.producator, strlen(producator) + 1, producator);
		c.pret = pret;
		c.categorie = categorie;
		return c;
	}
	
	void afisare(struct Casti c) {
		printf("%d. Castile produse de catre %s in anul %d, costa %.2f si sunt in categoria %c.\n",
			c.id, c.producator, c.anAparitie, c.pret, c.categorie);
	}
	void dezalocare(struct Casti* c) {
		if (c->producator != NULL) {
			free(c->producator);
			c->producator = NULL;
		}
	}
	void modificaPret(struct Casti* c, float noulPret) {
		if (noulPret > 0) {
			c->pret = noulPret;
		}
	}

	void modificaAn(struct Casti* c, int noulAn) {
		if (noulAn > 2000) {
			c->anAparitie = noulAn;
		}
	}
		


int main() {
	struct Casti c;
	c = initializare(1, 2024, "Samsung", 699.99, 'A');
	afisare(c);
	modificaPret(&c, 2000.99);
	afisare(c);
	modificaAn(&c, 2025);
	afisare(c);
	dezalocare(&c);
	afisare(c);
	
	return 0;
}