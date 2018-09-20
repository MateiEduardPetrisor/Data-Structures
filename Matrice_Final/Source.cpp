#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

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

struct Matrice
{
	int numarLinii;
	int numarColoane;
	int indexCurentLinie;
	int indexCurentColoane;
	Student** matriceStudenti;
};

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

void afisareElement(Student student)
{
	if (!(student.idStudent == 0 && student.numeStudent == NULL &&
		student.numarMateriiStudent == 0 && student.listaMateriiStudent == NULL &&
		student.noteStudent == NULL && student.facultateStudent == (Facultate)0))
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
}

Matrice* creareMatrice(int numarLinii, int numarColoane)
{
	Matrice* matrice = (Matrice*)malloc(sizeof(Matrice));
	matrice->numarLinii = numarLinii;
	matrice->numarColoane = numarColoane;
	matrice->indexCurentLinie = 0;
	matrice->indexCurentColoane = 0;
	matrice->matriceStudenti = (Student**)malloc(sizeof(Student*) * matrice->numarLinii);
	for (int indexLinie = 0; indexLinie < matrice->numarLinii; indexLinie++)
	{
		matrice->matriceStudenti[indexLinie] = (Student*)malloc(sizeof(Student) * matrice->numarColoane);
		for (int indexColoana = 0; indexColoana < matrice->numarColoane; indexColoana++)
		{
			matrice->matriceStudenti[indexLinie][indexColoana].idStudent = 0;
			matrice->matriceStudenti[indexLinie][indexColoana].numeStudent = NULL;
			matrice->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent = 0;
			matrice->matriceStudenti[indexLinie][indexColoana].listaMateriiStudent = NULL;
			matrice->matriceStudenti[indexLinie][indexColoana].noteStudent = NULL;
			matrice->matriceStudenti[indexLinie][indexColoana].facultateStudent = (Facultate)0;
		}
	}
	return matrice;
}

void afisareMatrice(Matrice* matrice)
{
	if (matrice != NULL)
	{
		if (matrice->matriceStudenti != NULL)
		{
			for (int indexLinie = 0; indexLinie < matrice->numarLinii; indexLinie++)
			{
				printf("Linia %d:\n", indexLinie);
				if (matrice->matriceStudenti[indexLinie] != NULL)
				{
					for (int indexColoana = 0; indexColoana < matrice->numarColoane; indexColoana++)
					{
						afisareElement(matrice->matriceStudenti[indexLinie][indexColoana]);
					}
					printf("\n");
				}
			}
		}
	}
	else
	{
		printf("Matrice Goala\n");
	}
}

void dezalocaMatrice(Matrice* &matrice)
{
	if (matrice != NULL)
	{
		for (int indexLinie = 0; indexLinie < matrice->numarLinii; indexLinie++)
		{
			if (matrice->matriceStudenti[indexLinie] != NULL)
			{
				for (int indexColoane = 0; indexColoane < matrice->numarColoane; indexColoane++)
				{
					free(matrice->matriceStudenti[indexLinie][indexColoane].numeStudent);
					matrice->matriceStudenti[indexLinie][indexColoane].numeStudent = NULL;
					for (int indexMaterii = 0; indexMaterii < matrice->matriceStudenti[indexLinie][indexColoane].numarMateriiStudent; indexMaterii++)
					{
						free(matrice->matriceStudenti[indexLinie][indexColoane].listaMateriiStudent[indexMaterii]);
						matrice->matriceStudenti[indexLinie][indexColoane].listaMateriiStudent[indexMaterii] = NULL;
					}
					free(matrice->matriceStudenti[indexLinie][indexColoane].listaMateriiStudent);
					matrice->matriceStudenti[indexLinie][indexColoane].listaMateriiStudent = NULL;
					free(matrice->matriceStudenti[indexLinie][indexColoane].noteStudent);
					matrice->matriceStudenti[indexLinie][indexColoane].noteStudent = NULL;
				}
				free(matrice->matriceStudenti[indexLinie]);
				matrice->matriceStudenti[indexLinie] = NULL;
			}
		}
		free(matrice->matriceStudenti);
		matrice->matriceStudenti = NULL;
		free(matrice);
		matrice = NULL;
	}
	else
	{
		printf("Matrice Goala\n");
	}
}

void copiereMatriceInMatrice(Matrice* destinatie, Matrice* sursa);

void inserareElement(Matrice* &matrice, Student student)
{
	if (matrice->indexCurentLinie < matrice->numarLinii && matrice->indexCurentColoane < matrice->numarColoane)
	{
		matrice->matriceStudenti[matrice->indexCurentLinie][matrice->indexCurentColoane] = student;
		matrice->indexCurentColoane = matrice->indexCurentColoane + 1;
	}
	else if (matrice->indexCurentLinie < matrice->numarLinii && matrice->indexCurentColoane == matrice->numarColoane)
	{
		matrice->indexCurentLinie = matrice->indexCurentLinie + 1;
		if (matrice->indexCurentLinie == matrice->numarLinii)
		{
			printf("Realocare\n");
			Matrice* rezultat = creareMatrice(matrice->numarLinii * 2, matrice->numarColoane * 2);
			copiereMatriceInMatrice(rezultat, matrice);
			dezalocaMatrice(matrice);
			matrice = rezultat;
			if (matrice->indexCurentLinie < matrice->numarLinii && matrice->indexCurentColoane < matrice->numarColoane)
			{
				matrice->matriceStudenti[matrice->indexCurentLinie][matrice->indexCurentColoane] = student;
				matrice->indexCurentColoane = matrice->indexCurentColoane + 1;
			}
			else
			{
				matrice->indexCurentLinie = matrice->indexCurentLinie + 1;
				matrice->indexCurentColoane = 0;
				matrice->matriceStudenti[matrice->indexCurentLinie][matrice->indexCurentColoane] = student;
				matrice->indexCurentColoane = matrice->indexCurentColoane + 1;
			}
		}
		else
		{
			matrice->indexCurentColoane = 0;
			matrice->matriceStudenti[matrice->indexCurentLinie][matrice->indexCurentColoane] = student;
			matrice->indexCurentColoane = matrice->indexCurentColoane + 1;
		}
	}
}

void copiereMatriceInMatrice(Matrice* destinatie, Matrice* sursa)
{
	if (sursa != NULL)
	{
		for (int indexLinie = 0; indexLinie < sursa->numarLinii; indexLinie++)
		{
			if (sursa->matriceStudenti[indexLinie] != NULL)
			{
				for (int indexColoana = 0; indexColoana < sursa->numarColoane; indexColoana++)
				{
					Student student;
					student.idStudent = sursa->matriceStudenti[indexLinie][indexColoana].idStudent;
					student.numeStudent = (char*)malloc(sizeof(char) * strlen(sursa->matriceStudenti[indexLinie][indexColoana].numeStudent) + 1);
					strcpy(student.numeStudent, sursa->matriceStudenti[indexLinie][indexColoana].numeStudent);
					student.numarMateriiStudent = sursa->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent;
					student.listaMateriiStudent = (char**)malloc(sizeof(char*)* sursa->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent);
					for (int indexMaterii = 0; indexMaterii < sursa->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent; indexMaterii++)
					{
						student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char) * strlen(sursa->matriceStudenti[indexLinie][indexColoana].listaMateriiStudent[indexMaterii]) + 1);
						strcpy(student.listaMateriiStudent[indexMaterii], sursa->matriceStudenti[indexLinie][indexColoana].listaMateriiStudent[indexMaterii]);
					}
					student.noteStudent = (float*)malloc(sizeof(float)* sursa->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent);
					for (int indexNote = 0; indexNote < sursa->matriceStudenti[indexLinie][indexColoana].numarMateriiStudent; indexNote++)
					{
						student.noteStudent[indexNote] = sursa->matriceStudenti[indexLinie][indexColoana].noteStudent[indexNote];
					}
					student.facultateStudent = sursa->matriceStudenti[indexLinie][indexColoana].facultateStudent;
					inserareElement(destinatie, student);
				}
			}
		}
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	Matrice* matrice = creareMatrice(1, 1);
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
			student.listaMateriiStudent = (char**)malloc(sizeof(char*)*student.numarMateriiStudent + 1);
			for (int indexMaterii = 0; indexMaterii < student.numarMateriiStudent; indexMaterii++)
			{
				fscanf(f, "%s", buf);
				student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(buf) + 1);
				strcpy(student.listaMateriiStudent[indexMaterii], buf);
			}
			student.noteStudent = (float*)malloc(sizeof(float)*student.numarMateriiStudent + 1);
			for (int indexNote = 0; indexNote < student.numarMateriiStudent; indexNote++)
			{
				fscanf(f, "%f", &student.noteStudent[indexNote]);
			}
			int facultateStudent;
			fscanf(f, "%d", &facultateStudent);
			student.facultateStudent = (Facultate)facultateStudent;
			inserareElement(matrice, student);
		}
		fclose(f);

		afisareMatrice(matrice);

		dezalocaMatrice(matrice);

		afisareMatrice(matrice);

		_getch();
	}
	else
	{
		printf("Fisierul Nu Exista\n");
	}
}