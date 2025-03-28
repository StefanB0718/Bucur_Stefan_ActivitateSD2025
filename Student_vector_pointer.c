#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct student student;


typedef struct student {
	unsigned int id;//%u
	char* nume;//%s
	float medie;//%.2f
	//vector dinamic de note
	int nrMaterii;//dim -> nr de elemente din vector
	float* note; //vector
}student;

student initializareStudent(unsigned int id, char* nume, float medie, int nrMaterii, float* note) {
	student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.medie = medie;
	s.nrMaterii = nrMaterii;
	s.note = (float*)malloc(sizeof(float) * nrMaterii);
	for (int i = 0; i < nrMaterii; i++) {
		s.note[i] = note[i];
	}
	return s;
}

void afisare(student s) {
	printf("%u, %s, %.2f, %d", s.id, s.nume, s.medie, s.nrMaterii);
	for (int i = 0; i < s.nrMaterii; i++) {
		printf(" %.2f", s.note[i]);

	}
	printf("\n");
}
void main() {



	float vectorNote[3] = { 7, 8, 9 };
	student s = initializareStudent(123, "Adrian", 8.78, 3, vectorNote);
	afisare(s);

	//pointer la student
	student* ps = &s;
	printf("%u \n", s.id);
	printf("%u \n", ps->id);
	printf("%u \n", (*ps).id);
	afisare(*ps);


}