#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Film Film;
typedef struct nod nod;
typedef struct hashTabel hashTabel;

typedef struct Film {
    char* titlu;
    float rating;
    unsigned char durata;
    char* gen;


}Film;
Film creareFilm(char* titlu, float rating, unsigned char durata, char* gen) {
    Film f;
    f.rating = rating;
    f.durata = durata;
    f.titlu = (char*)malloc(sizeof(char) * strlen(titlu) + 1);
    strcpy(f.titlu, titlu);
    f.gen = (char*)malloc(sizeof(char) * strlen(gen) + 1);
    strcpy(f.gen, gen);

    return f;

}
typedef struct nod {
    Film info;
    nod* next;


}nod;

typedef struct hashTabel {

    int dim;
    nod** vector;

};


int functiaHash(hashTabel tabela, const char* gen) {

    return gen[0] % tabela.dim;


}

int inserareHash(hashTabel tabela, Film f) {
    int poz = 0;
    if (tabela.vector) {

        poz = functiaHash(tabela, f.gen);
        nod* nou = (nod*)malloc(sizeof(nod));
        nou->info = creareFilm(f.titlu, f.rating, f.durata, f.gen);
        nou->next = NULL;
        if (tabela.vector[poz] == NULL) {

            tabela.vector[poz] = nou;
        }
        else {
            nod* aux = tabela.vector[poz];
            while (aux->next) {

                aux = aux->next;


            }

            aux->next = nou;


        }


    }
    return poz;


}

void afisare(hashTabel tabela) {
    if (tabela.vector) {
        for (int i = 0;i < tabela.dim;i++) {
            if (tabela.vector[i]) {

                printf("Pozitia: %d\n", i);
                nod* aux = tabela.vector[i];
                while (aux) {

                    printf("%s,%s,%u,%.2f\n", aux->info.titlu, aux->info.gen, aux->info.durata, aux->info.rating);
                    aux = aux->next;
                }

            }

        }

    }

}
void dezalocare(hashTabel tabela) {
    if (tabela.vector) {
        for (int i = 0;i < tabela.dim;i++) {
            if (tabela.vector[i]) {
                nod* aux = tabela.vector[i];
                while (aux) {
                    free(aux->info.titlu);
                    free(aux->info.gen);
                    nod* temp = aux->next;
                    free(aux);
                    temp = aux;
                }

            }

        }
        free(tabela.vector);
    }



}

void main() {


    Film f;
    hashTabel tabela;
    tabela.dim = 10;
    tabela.vector = (nod*)malloc(sizeof(nod) * tabela.dim);
    for (int i = 0;i < tabela.dim;i++) {

        tabela.vector[i] = NULL;
    }





    char LinierBuffer[128];
    char* token;
    char delimitator[] = ",\n";
    FILE* l = fopen("Text.txt", "r");
    if (l) {

        while (fgets(LinierBuffer, sizeof(LinierBuffer), l)) {
            //pt titlul
            token = strtok(LinierBuffer, delimitator);
            f.titlu = (char*)malloc(sizeof(char) * strlen(token) + 1);
            strcpy(f.titlu, token);
            //rating
            token = strtok(NULL, delimitator);
            f.rating = atof(token);
            //durata
            token = strtok(NULL, delimitator);
            f.durata = atoi(token);
            //gen
            token = strtok(NULL, delimitator);
            f.gen = (char*)malloc(sizeof(char) * strlen(token) + 1);
            strcpy(f.gen, token);


            inserareHash(tabela, f);

            free(f.titlu);
            free(f.gen);
        }


    }
    fclose(l);
    afisare(tabela);







}