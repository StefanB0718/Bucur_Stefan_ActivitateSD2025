#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Rezervare Rezervare;
typedef struct Nod Nod;

struct Rezervare {

	unsigned int id;
	char* hotel;
	unsigned char camere;
	char* client;
	float plata;


};

Rezervare creareRezervare(unsigned int id, char* hotel, unsigned char camere, char* client, float plata) {
	Rezervare r;
	r.id = id;
	r.hotel = (char*)malloc(sizeof(char) * strlen(hotel) + 1);
	strcpy(r.hotel, hotel);
	r.camere = camere;
	r.client = (char*)malloc(sizeof(char) * strlen(client) + 1);
	strcpy(r.client, client);
	r.plata = plata;

	return r;

}

struct Nod {

	Rezervare info;
	Nod* stang;
	Nod* dreapta;

};

Nod* creareNod(Nod* stang, Nod* dreapta, Rezervare info) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->dreapta = dreapta;
	nou->stang = stang;
	nou->info = creareRezervare(info.id, info.hotel, info.camere, info.client, info.plata);
	return nou;

}

Nod* inserareNod(Nod* rad, Rezervare r) {
	if (rad) {
		if (r.id < rad->info.id) {
			rad->stang = inserareNod(rad->stang, r);
		}
		else if (r.id > rad->info.id) {

			rad->dreapta = inserareNod(rad->dreapta, r);


		}
		else {

			return rad;
		}

	}
	else {

		return creareNod(NULL, NULL, r);
	}

	return rad;


}

Nod* afisarepreordine(Nod* rad) {
	if (rad) {
		printf("%u,%s,%u,%s,%.2f \n", rad->info.id, rad->info.hotel, rad->info.camere, rad->info.client, rad->info.plata);
		afisarepreordine(rad->stang);
		afisarepreordine(rad->dreapta);


	}


}

Nod* afisareInordine(Nod* rad) {
	if (rad) {
		afisareInordine(rad->stang);
		printf("%u,%s,%u,%s,%.2f\n", rad->info.id, rad->info.hotel, rad->info.camere, rad->info.client, rad->info.plata);
		afisareInordine(rad->dreapta);

	}


}

Nod* afisarePostordine(Nod* rad) {
	if (rad) {

		afisarePostordine(rad->stang);
		afisarePostordine(rad->dreapta);
		printf("%u,%s,%u,%s,%.2f\n", rad->info.id, rad->info.hotel, rad->info.camere, rad->info.client, rad->info.plata);

	}

}



void dezalocareNod(Nod* rad) {
	if (rad) {
		Nod* fiustang = rad->stang;
		Nod* fiudrept = rad->dreapta;
		free(rad->info.hotel);
		free(rad->info.client);
		free(rad);
		dezalocareNod(fiustang);
		dezalocareNod(fiudrept);


	}

}

int nrcamerefrunze(Nod* rad) {

	int contor = 0;
	if (rad) {
		if (rad->stang == NULL && rad->dreapta == NULL) {

			contor += rad->info.camere;

		}
		contor += nrcamerefrunze(rad->stang);
		contor += nrcamerefrunze(rad->dreapta);



	}

	return contor;

}
int maximCamere(int a, int b) {
	if (a > b) {

		return a;
	}
	else {

		return b;

	}


}

int inaltime(Nod* rad) {

	if (rad) {
		int inaltimestanga = inaltime(rad->stang);
		int inaltimedreapta = inaltime(rad->dreapta);

		return 1 + maximCamere(inaltimestanga, inaltimedreapta);





	}
	else {

		return 0;
	}


}



void main() {
	Rezervare r;
	Nod* rad = NULL;
	FILE* e = fopen("Text.txt", "r");
	char liniebuffer[100];
	char* token;
	char sep[5] = ",";
	while (fgets(liniebuffer, 100, e)) {
		token = strtok(liniebuffer, sep);
		r.id = atoi(token);
		token = strtok(NULL, sep);
		r.hotel = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(r.hotel, token);
		token = strtok(NULL, sep);
		r.camere = atoi(token);
		token = strtok(NULL, sep);
		r.client = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(r.client, token);
		token = strtok(NULL, sep);
		r.plata = atof(token);
		rad = inserareNod(rad, r);




	}
	afisareInordine(rad);



	printf("%d\n", nrcamerefrunze(rad));
	printf("%d\n", inaltime(rad));



}