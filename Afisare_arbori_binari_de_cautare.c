e
//
//
//typedef struct persoana persoana;
//typedef struct nod nod;
//
//struct persoana {
//	char* nume;
//	int varsta;
//	float inaltime;
//};
//
//persoana crearePersoana(char* nume, int varsta, float inaltime) {
//	persoana p;
//	p.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
//	strcpy(p.nume, nume);
//	p.varsta = varsta;
//	p.inaltime = inaltime;
//
//	return p;
//}
//
//struct nod {
//	persoana info;
//	nod* stang;
//	nod* drept;
//};
//
//nod* creareNod(persoana p, nod* stang, nod* drept) {
//	nod* nou = (nod*)malloc(sizeof(nod));
//	nou->info = crearePersoana(p.nume, p.varsta, p.inaltime);
//	nou->stang = stang;
//	nou->drept = drept;
//
//	return nou;
//}
//
//nod* inserareArbore(nod* rad, persoana p) {
//	if (rad) {
//		if (p.varsta < rad->info.varsta) {
//			rad->stang = inserareArbore(rad->stang, p);
//			return rad;
//		}
//		else if (p.varsta > rad->info.varsta) {
//			rad->drept = inserareArbore(rad->drept, p);
//			return rad;
//		}
//		else {
//			return rad;
//		}
//
//	}
//	else {
//		return creareNod(p, NULL, NULL);
//	}
//}
//
//
////preordine- RSD
//void preordine(nod* rad) {
//	if (rad) {
//		printf("%s, %d, %.2f \n", rad->info.nume, rad->info.varsta, rad->info.inaltime);
//		preordine(rad->stang);
//		preordine(rad->drept);
//	}
//}
//
//
////parcurgere inordine- SRD
//void inordine(nod* rad) {
//	if (rad) {
//
//		inordine(rad->stang);
//		printf("%s, %d, %.2f \n", rad->info.nume, rad->info.varsta, rad->info.inaltime);
//		inordine(rad->drept);
//	}
//}
//
////parcurgere postordine- SDR
//void postordine(nod* rad) {
//	if (rad) {
//
//		postordine(rad->stang);
//		postordine(rad->drept);
//		printf("%s, %d, %.2f \n", rad->info.nume, rad->info.varsta, rad->info.inaltime);
//	}
//}
//
//
//void dezalocare(nod* rad) {
//	if (rad) {
//		nod* arbStang = rad->stang;
//		nod* arbDrept = rad->drept;
//		free(rad->info.nume);
//		free(rad);
//
//		dezalocare(arbStang);
//		dezalocare(arbDrept);
//
//	}
//}
//
//
//void main() {
//	nod* rad = NULL;
//	persoana p;
//
//	char liniebuffer[100];
//	char sep[] = ",\n";
//	char* token;
//
//	FILE* f = fopen("Persoane.txt", "r");
//	if (f) {
//		while (fgets(liniebuffer, 100, f)) {
//
//			token = strtok(liniebuffer, sep);
//			p.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
//			strcpy(p.nume, token);
//
//			token = strtok(NULL, sep);
//			p.varsta = atoi(token);
//
//			token = strtok(NULL, sep);
//			p.inaltime = atof(token);
//
//			rad = inserareArbore(rad, p);
//
//			free(p.nume);
//
//		}
//	}
//	else {
//		printf("Fisier invalid!");
//	}
//
//	fclose(f);
//
//
//	preordine(rad);
//}