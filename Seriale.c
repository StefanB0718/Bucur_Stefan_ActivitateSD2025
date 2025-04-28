#include<stdio.h>
#include<stdlib.h>

struct Seriale {
	int id;
	int anAparitie;
	char* denumire ;
	float pret ;
	char categorie;
};

struct Seriale initializare(int id, int anAparitie, const char* denumire, float pret, char categorie) {
	struct Seriale s;
	s.id = id; //%d
	s.anAparitie = anAparitie; //%d
	s.denumire = (char*)malloc(sizeof(char)*(strlen(denumire)+1)); //%s
	strcpy_s(s.denumire, strlen(denumire) + 1, denumire);
	s.pret = pret; //%.2f
	s.categorie = categorie; //%c
	return s;
}

void afisare(struct Seriale s) {
	if (s.denumire != NULL) {
		printf("%d. Serialul %s a aparut in anul %d, costa %.2f$ si este de categoria %c.\n",
			s.id, s.denumire, s.anAparitie, s.pret, s.categorie);
	}
	else {
		printf("%d. Serialul a aparut in anul %d, costa %.2f$ si este de categoria %c.\n",
			s.id, s.anAparitie, s.pret, s.categorie);
	}
}

void modificaPret(struct Seriale* s, float noulPret) {
	if (noulPret > 0) {
		s->pret = noulPret;
	}
}

void dezalocare(struct Seriale *s) {
	if (s->denumire != NULL) {
		free(s->denumire);
		s->denumire = NULL;
	}
}

int main() {
	struct Seriale s;
	s = initializare(1, 2023, "Last of Us", 99.99, 'A');
	afisare(s);
	modificaPret(&s, 200);
	afisare(s);
	dezalocare(&s);
	afisare(s);

	return 0; 
}