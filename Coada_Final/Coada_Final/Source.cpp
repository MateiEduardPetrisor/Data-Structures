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

struct NodCoada
{
	Student info;
	NodCoada* next;
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

void afisareNodCoada(NodCoada* nod)
{
	if (nod != NULL)
	{
		printf("%d ", nod->info.idStudent);
		printf("%s ", nod->info.numeStudent);
		printf("%d ", nod->info.numarMateriiStudent);
		for (int indexMaterii = 0; indexMaterii < nod->info.numarMateriiStudent; indexMaterii++)
		{
			printf("%s ", nod->info.listaMateriiStudent[indexMaterii]);
		}
		for (int indexNote = 0; indexNote < nod->info.numarMateriiStudent; indexNote++)
		{
			printf("%4.2f ", nod->info.noteStudent[indexNote]);
		}
		afisareFacultate(nod->info.facultateStudent);
		newLine();
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

NodCoada* creareNodCoada(Student student)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = student;
	nod->next = NULL;
	return nod;
}

NodCoada* inserareSfarsit(NodCoada* coada, NodCoada* nod)
{
	if (coada == NULL)
	{
		coada = nod;
	}
	else
	{
		NodCoada* tmp = coada;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
	return coada;
}

Student extragereInceput(NodCoada* &coada)
{
	if (coada != NULL)
	{
		Student student;
		while (coada != NULL)
		{
			NodCoada* extrage = coada;
			coada = coada->next;
			extrage->next = NULL;
			student.idStudent = extrage->info.idStudent;
			student.numeStudent = (char*)malloc(sizeof(char)*strlen(extrage->info.numeStudent) + 1);
			strcpy(student.numeStudent, extrage->info.numeStudent);
			student.numarMateriiStudent = extrage->info.numarMateriiStudent;
			student.listaMateriiStudent = (char**)malloc(sizeof(char*)*extrage->info.numarMateriiStudent + 1);
			for (int indexMaterii = 0; indexMaterii < extrage->info.numarMateriiStudent; indexMaterii++)
			{
				student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(extrage->info.listaMateriiStudent[indexMaterii]) + 1);
				strcpy(student.listaMateriiStudent[indexMaterii], extrage->info.listaMateriiStudent[indexMaterii]);
			}
			student.noteStudent = (float*)malloc(sizeof(float)*extrage->info.numarMateriiStudent + 1);
			for (int indexNote = 0; indexNote < extrage->info.numarMateriiStudent; indexNote++)
			{
				student.noteStudent[indexNote] = extrage->info.numeStudent[indexNote];
			}
			student.facultateStudent = (Facultate)extrage->info.facultateStudent;
			//printf("Sterge Nod:@%p\n", extrage);
			free(extrage->info.numeStudent);
			extrage->info.numeStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < extrage->info.numarMateriiStudent; indexMaterii++)
			{
				free(extrage->info.listaMateriiStudent[indexMaterii]);
				extrage->info.listaMateriiStudent[indexMaterii] = NULL;
			}
			free(extrage->info.listaMateriiStudent);
			extrage->info.listaMateriiStudent = NULL;
			free(extrage->info.noteStudent);
			extrage->info.noteStudent = NULL;
			free(extrage);
			extrage = NULL;
			return student;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void afisareCoada(NodCoada* coada)
{
	if (coada != NULL)
	{
		NodCoada* tmp = coada;
		while (tmp)
		{
			afisareNodCoada(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void dezalocaCoada(NodCoada* &coada)
{
	if (coada != NULL)
	{
		while (coada != NULL)
		{
			NodCoada* tmp = coada;
			coada = coada->next;
			tmp->next = NULL;
			//printf("Sterge Nod:@%p\n", tmp);
			free(tmp->info.numeStudent);
			tmp->info.numeStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < tmp->info.numarMateriiStudent; indexMaterii++)
			{
				free(tmp->info.listaMateriiStudent[indexMaterii]);
				tmp->info.listaMateriiStudent[indexMaterii] = NULL;
			}
			free(tmp->info.listaMateriiStudent);
			tmp->info.listaMateriiStudent = NULL;
			free(tmp->info.noteStudent);
			tmp->info.noteStudent = NULL;
			free(tmp);
			tmp = NULL;
		}
		free(coada);
		coada = NULL;
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	NodCoada* coada = NULL;
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
			NodCoada* nod = creareNodCoada(student);
			coada = inserareSfarsit(coada, nod);
		}
		fclose(f);

		printf("~~~ AFISARE COADA ~~~\n");
		afisareCoada(coada);
		newLine();

		printf("~~~ EXTRAGE UN ELEMENT ~~~\n");
		Student student = extragereInceput(coada);
		afisareStudent(student);
		newLine();

		printf("~~~ AFISARE COADA DUPA EXTRAGEREA UNUI ELEMENT ~~~\n");
		afisareCoada(coada);
		newLine();

		printf("~~~ DEZALOCARE COADA ~~~\n");
		dezalocaCoada(coada);
		afisareCoada(coada);
		newLine();

		_getch();
	}
	else
	{
		printf("\n Eroare\n");
		_getch();
	}
}