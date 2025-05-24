#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct DispozitivMobil DispozitivMobil;
typedef struct heap heap;


struct DispozitivMobil {

	unsigned int id;
	char* sistem;
	float pret;
	char* defecte;
	unsigned int zile;


};

DispozitivMobil creareDispozitivMobil(unsigned int id, char* sistem, float pret, char* defecte, unsigned int zile) {

	DispozitivMobil d;
	d.id = id;
	d.sistem = (char*)malloc(sizeof(char) * strlen(sistem) + 1);
	strcpy(d.sistem, sistem);
	d.pret = pret;
	d.defecte = (char*)malloc(sizeof(char) * strlen(defecte) + 1);
	strcpy(d.defecte, defecte);
	d.zile = zile;

	return d;


}

struct heap {

	DispozitivMobil* vector;
	int dim;

};

void afisareDispozitivMobil(DispozitivMobil d) {

	printf("%d\n", d.id, d.sistem, d.pret, d.pret, d.defecte, d.zile);
}
void swap(DispozitivMobil* a, DispozitivMobil* b) {
	DispozitivMobil temp = *a;
	*a = *b;
	*b = temp;

}

void filtrare(heap h, int index) {
	int indexRad = index;
	int indexStanga = 2 * index + 1;
	int indexDrept = 2 * index + 2;

	if (indexStanga<h.dim && h.vector[indexRad].zile>h.vector[indexStanga].zile)
		indexStanga = indexRad;
	if (indexDrept<h.dim && h.vector[indexRad].zile>h.vector[indexDrept].zile)
		indexDrept = index;
	if (index != indexRad) {

		swap(&h.vector[index], &h.vector[indexRad]);
		filtrare(h, indexRad);
	}



}

heap inserareHeap(heap h, DispozitivMobil d) {
	DispozitivMobil* vectorNou = (DispozitivMobil*)malloc(sizeof(DispozitivMobil) * (h.dim + 1));
	for (int i = 0;i < h.dim;i++) {

		vectorNou[i] = h.vector[i];

	}
	vectorNou[h.dim] = creareDispozitivMobil(d.id, d.sistem, d.pret, d.defecte, d.zile);
	free(h.vector);
	h.dim++;
	h.vector = vectorNou;

	for (int i = (h.dim / 2) - 1;i >= 0;i--) {

		filtrare(h, i);

	}
	return h;

}

heap extragereHeap(heap h, DispozitivMobil* extras) {
	swap(&h.vector[0], &h.vector[h.dim - 1]);
	DispozitivMobil* vectorNou = (DispozitivMobil*)malloc(sizeof(DispozitivMobil) * (h.dim - 1));
	for (int i = 0;i < h.dim - 1;i++) {

		vectorNou[i] = h.vector[i];

	}
	*extras = creareDispozitivMobil(h.vector[h.dim - 1].id, h.vector[h.dim - 1].sistem, h.vector[h.dim - 1].pret, h.vector[h.dim - 1].defecte, h.vector[h.dim - 1].zile);
	free(h.vector);
	h.dim--;
	h.vector = vectorNou;

	for (int i = (h.dim / 2) - 1;i >= 0;i--) {

		filtrare(h, i);

	}
	return h;


}

int main() {
	heap h;
	h.vector = NULL;
	h.dim = 0;


	DispozitivMobil d1 = creareDispozitivMobil(1, "Android", 1500.0, "Ecran crapat", 5);
	DispozitivMobil d2 = creareDispozitivMobil(2, "iOS", 2000.0, "Baterie defecta", 3);
	DispozitivMobil d3 = creareDispozitivMobil(3, "Windows Phone", 1000.0, "Camera nefuntionala", 7);


	h = inserareHeap(h, d1);
	h = inserareHeap(h, d2);
	h = inserareHeap(h, d3);


	DispozitivMobil extras;
	h = extragereHeap(h, &extras);


	afisareDispozitivMobil(extras);


	free(d1.sistem);
	free(d1.defecte);
	free(d2.sistem);
	free(d2.defecte);
	free(d3.sistem);
	free(d3.defecte);
	free(h.vector);

	return 0;
}
