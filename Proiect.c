#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>


typedef struct  {
	unsigned int codProiect;
	char* titluProiect;
	char* beneficiar;
	unsigned char nrExecutanti;
	float bugetAlocat;
}Proiect;

typedef struct nod {
	Proiect info;
	struct nod* prev;
	struct nod* next;
} nod;
Proiect initializare( unsigned int codProiect, char* titluProiect, char* beneficiar, unsigned char nrExecutanti, float bugetAlocat) {
	Proiect p;
	p.codProiect = codProiect;
	p.titluProiect = (char*)malloc(sizeof(char) * (strlen(titluProiect) + 1));
	strcpy(p.titluProiect, titluProiect);
	p.beneficiar = (char*)malloc(sizeof(char) * (strlen(beneficiar) + 1));
	strcpy(p.beneficiar, beneficiar);
	p.nrExecutanti = nrExecutanti;
	p.bugetAlocat = bugetAlocat;

	return p;
	}
typedef struct ListaDubla {
	nod* prim;
	nod* ultim;
}ListaDubla;
ListaDubla inserare(ListaDubla lista, Proiect p) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializare(p.codProiect, p.titluProiect, p.beneficiar, p.nrExecutanti, p.bugetAlocat);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.prim == NULL) {
		lista.prim = nou;
		lista.ultim = nou;
	}
	else {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	return lista;
}

ListaDubla inserareFinal(ListaDubla lista, Proiect p) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializare(p.codProiect, p.titluProiect, p.beneficiar, p.nrExecutanti, p.bugetAlocat);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.prim == NULL) {
		lista.prim = nou;
		lista.ultim = nou;
	}
	else {
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		lista.ultim = nou;

		/*nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou*/;
	}
	return lista;
}
	void afisareInceput(ListaDubla lista) {
		nod* aux = lista.prim;
		while (aux) {
			printf("%u, %s, %s, %u, %.2f \n", aux->info.codProiect, aux->info.titluProiect, aux->info.beneficiar, aux->info.nrExecutanti, 
				aux->info.bugetAlocat);
			aux = aux->next;
		}
	}

	void dezalocare(ListaDubla lista) {
		nod* aux = lista.prim;
		while (aux) {
			nod* temp = aux;
			aux = aux->next;
			free(temp->info.titluProiect);
			free(temp->info.beneficiar);
			free (temp);
		}
	}


int main() {
	Proiect p = initializare(1,"Proiect A", "PMB", 5, 1000.00);
	Proiect p1 = initializare(2,"Proiect B", "P Cluj", 8, 999.99);
	Proiect p2 = initializare(3,"Proiect C", "P Buzau", 12, 456.90);
	Proiect p3 = initializare(4,"Proiect D", "P Bacau", 4, 124.89);
	Proiect p4 = initializare(5,"Proiect E", "P Constanta", 9, 345.86);
	
	ListaDubla lista;
	lista.prim = lista.ultim = NULL;
	lista = inserare(lista, p);
	lista = inserare(lista, p1);
	lista = inserare(lista, p2);
	lista = inserare(lista, p3);
	lista = inserare(lista, p4);

	afisareInceput(lista);

	return 0;
}