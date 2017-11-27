#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

void newLine()
{
	printf("\n");
}

enum Facultate
{
	CSIE = 1,
	REI = 2,
	FABBV = 3,
	FABIZ = 4,
	MRK = 5,
};

struct Student
{
	int idStudent;
	char* numeStudent;
	int numarMateriiStudent;
	char** listaMateriiStudent;
	float* noteStudent;
	Facultate facultateStudent;
};

struct Vector
{
	int indexCurent;
	int dimensiuneVector;
	Student* vectorStudenti;
};

Vector* creareVector(int dimensiuneVector)
{
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	vector->vectorStudenti = (Student*)malloc(sizeof(Student)*dimensiuneVector);
	vector->dimensiuneVector = dimensiuneVector;
	vector->indexCurent = 0;
	return vector;
}

void afisareFacultate(Facultate facultateStudent)
{
	switch (facultateStudent)
	{
	case 1:
		printf("CSIE");
		break;
	case 2:
		printf("REI");
		break;
	case 3:
		printf("FABBV");
		break;
	case 4:
		printf("FABIZ");
		break;
	case 5:
		printf("MRK");
		break;
	default:
		printf("UKF");
		break;
	}
}

void afisareStudent(Student student)
{
	printf("%d ", student.idStudent);
	printf("%s ", student.numeStudent);
	printf("%d ", student.numarMateriiStudent);
	for (int indexMaterii = 0; indexMaterii < student.numarMateriiStudent; indexMaterii++)
	{
		printf("%s ", student.listaMateriiStudent[indexMaterii]);
	}
	for (int indexNote = 0; indexNote < student.numarMateriiStudent; indexNote++)
	{
		printf("%4.2f ", student.noteStudent[indexNote]);
	}
	afisareFacultate(student.facultateStudent);
	newLine();
}

void afisareVector(Vector* vector)
{
	if (vector != NULL)
	{
		for (int indexVector = 0; indexVector < vector->indexCurent; indexVector++)
		{
			afisareStudent(vector->vectorStudenti[indexVector]);
		}
	}
	else
	{
		printf("\nVector Gol\n");
	}
}

void dezalocaVector(Vector* &vector)
{
	if (vector != NULL)
	{
		for (int indexVector = 0; indexVector < vector->indexCurent; indexVector++)
		{
			free(vector->vectorStudenti[indexVector].numeStudent);
			vector->vectorStudenti[indexVector].numeStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < vector->vectorStudenti[indexVector].numarMateriiStudent; indexMaterii++)
			{
				free(vector->vectorStudenti[indexVector].listaMateriiStudent[indexMaterii]);
				vector->vectorStudenti[indexVector].listaMateriiStudent[indexMaterii] = NULL;
			}
			free(vector->vectorStudenti[indexVector].listaMateriiStudent);
			vector->vectorStudenti[indexVector].listaMateriiStudent = NULL;
			free(vector->vectorStudenti[indexVector].noteStudent);
			vector->vectorStudenti[indexVector].noteStudent = NULL;
		}
		free(vector->vectorStudenti);
		vector->vectorStudenti = NULL;
		vector->indexCurent = 0;
		vector->dimensiuneVector = 0;
		free(vector);
		vector = NULL;
	}
}

void copiereVectorInVector(Vector* &rezultat, Vector* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorStudenti != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				Student student;
				student.idStudent = sursa->vectorStudenti[indexVector].idStudent;
				student.numeStudent = (char*)malloc(sizeof(char)*strlen(sursa->vectorStudenti[indexVector].numeStudent) + 1);
				strcpy(student.numeStudent, sursa->vectorStudenti[indexVector].numeStudent);
				student.numarMateriiStudent = sursa->vectorStudenti[indexVector].numarMateriiStudent;
				student.listaMateriiStudent = (char**)malloc(sizeof(char*)*sursa->vectorStudenti[indexVector].numarMateriiStudent);
				for (int indexMaterii = 0; indexMaterii < sursa->vectorStudenti[indexVector].numarMateriiStudent; indexMaterii++)
				{
					student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(sursa->vectorStudenti[indexVector].listaMateriiStudent[indexMaterii]) + 1);
					strcpy(student.listaMateriiStudent[indexMaterii], sursa->vectorStudenti[indexVector].listaMateriiStudent[indexMaterii]);
				}
				student.noteStudent = (float*)malloc(sizeof(float)*sursa->vectorStudenti[indexVector].numarMateriiStudent);
				for (int indexNote = 0; indexNote < sursa->vectorStudenti[indexVector].numarMateriiStudent; indexNote++)
				{
					student.noteStudent[indexNote] = sursa->vectorStudenti[indexVector].noteStudent[indexNote];
				}
				student.facultateStudent = (Facultate)sursa->vectorStudenti[indexVector].facultateStudent;
				rezultat->vectorStudenti[indexVector] = student;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

void inserareStudent(Vector* &vector, Student student)
{
	if (vector->indexCurent == vector->dimensiuneVector)
	{
		printf("Realocare\n");
		Vector* rezultat = creareVector(vector->dimensiuneVector * 2);
		copiereVectorInVector(rezultat, vector);
		dezalocaVector(vector);
		vector = rezultat;
	}
	int index = vector->indexCurent;
	vector->vectorStudenti[index] = student;
	vector->indexCurent = index + 1;
}

void afisareDimensiuneIndex(Vector* vector)
{
	if (vector != NULL)
	{
		if (vector->vectorStudenti != NULL)
		{
			printf("Dimensiune Vector: %d\n", vector->dimensiuneVector);
			printf("Index Curent Vector: %d\n", vector->indexCurent);
		}
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	Vector* vector = creareVector(1);
	if (f)
	{
		while (!feof(f))
		{
			Student student;
			fscanf(f, "%d", &student.idStudent);
			char buf[100];
			fscanf(f, "%s", buf);
			student.numeStudent = (char*)malloc(sizeof(char)*(strlen(buf) + 1));
			strcpy(student.numeStudent, buf);
			fscanf(f, "%d", &student.numarMateriiStudent);
			student.listaMateriiStudent = (char**)malloc(sizeof(char*)*student.numarMateriiStudent);
			for (int indexMaterii = 0; indexMaterii < student.numarMateriiStudent; indexMaterii++)
			{
				fscanf(f, "%s", buf);
				student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(buf) + 1);
				strcpy(student.listaMateriiStudent[indexMaterii], buf);
			}
			student.noteStudent = (float*)malloc(sizeof(float)*student.numarMateriiStudent);
			for (int indexNote = 0; indexNote < student.numarMateriiStudent; indexNote++)
			{
				fscanf(f, "%f", &student.noteStudent[indexNote]);
			}
			int facultateStudent;
			fscanf(f, "%d", &facultateStudent);
			student.facultateStudent = (Facultate)facultateStudent;
			inserareStudent(vector, student);
		}
		fclose(f);
		printf("~~~ AFIASRE VECTOR STUDENTI ~~~\n");
		afisareVector(vector);
		newLine();

		printf("~~~ AFIASRE INDEX SI DIMENSIUNE VECTOR ~~~\n");
		afisareDimensiuneIndex(vector);
		dezalocaVector(vector);
		newLine();

		printf("~~~ AFIASRE VECTOR STUDENTI ~~~\n");
		afisareVector(vector);

		_getch();
	}
	else
	{
		printf("Eroare\n");
		_getch();
	}
}