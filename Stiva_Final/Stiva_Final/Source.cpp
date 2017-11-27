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

struct NodStiva
{
	Student info;
	NodStiva* next;
};

NodStiva* creareNodStiva(Student student)
{
	NodStiva* nod = (NodStiva*)malloc(sizeof(NodStiva));
	nod->info = student;
	nod->next = NULL;
	return nod;
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

void afisareNodStiva(NodStiva* nod)
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

NodStiva* inserareInceput(NodStiva* stiva, NodStiva* nod)
{
	if (stiva == NULL)
	{
		stiva = nod;
	}
	else
	{
		nod->next = stiva;
		stiva = nod;
	}
	return stiva;
}

Student extragereInceput(NodStiva* &stiva)
{
	if (stiva != NULL)
	{
		Student student;
		while (stiva != NULL)
		{
			NodStiva* extrage = stiva;
			stiva = stiva->next;
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
				student.noteStudent[indexNote] = extrage->info.noteStudent[indexNote];
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
		printf("Stiva Goala\n");
	}
}

void afisareStiva(NodStiva* stiva)
{
	if (stiva != NULL)
	{
		NodStiva* tmp = stiva;
		while (tmp)
		{
			afisareNodStiva(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Stiva Goala\n");
	}
}

void dezalocaStiva(NodStiva *&stiva)
{
	if (stiva != NULL)
	{
		while (stiva != NULL)
		{
			NodStiva* tmp = stiva;
			stiva = stiva->next;
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
		free(stiva);
		stiva = NULL;
	}
}

void sortareSelectie(NodStiva* &stiva)
{
	for (NodStiva *nodCurent = stiva; nodCurent->next != NULL; nodCurent = nodCurent->next)
	{
		for (NodStiva *nodUrmator = nodCurent->next; nodUrmator != NULL; nodUrmator = nodUrmator->next)
		{
			if (nodCurent->info.numarMateriiStudent > nodUrmator->info.numarMateriiStudent) //">" for ascending "<" for descending
			{
				Student aux = nodCurent->info;
				nodCurent->info = nodUrmator->info;
				nodUrmator->info = aux;
			}
		}
	}
}

void sortareStiva(NodStiva* &stiva, NodStiva* nodNou)
{
	NodStiva* nodCurent;
	if (stiva == NULL || stiva->info.idStudent > nodNou->info.idStudent) // ">" for ascending "<" for descending
	{
		nodNou->next = stiva;
		stiva = nodNou;
	}
	else
	{
		nodCurent = stiva;
		while (nodCurent->next != NULL && nodCurent->next->info.idStudent < nodNou->info.idStudent) // "<" for ascending ">" for descending
		{
			nodCurent = nodCurent->next;
		}
		nodNou->next = nodCurent->next;
		nodCurent->next = nodNou;
	}
}

void sortareInsertie(NodStiva* &stiva)
{
	NodStiva* stivaSortata = NULL;
	NodStiva* nodCurent = stiva;
	while (nodCurent != NULL)
	{
		NodStiva *next = nodCurent->next;
		sortareStiva(stivaSortata, nodCurent);
		nodCurent = next;
	}
	stiva = stivaSortata;
}

void sortareBule(NodStiva* &stiva)
{
	bool stare = true;
	NodStiva* auxSort = NULL;
	while (stare == true)
	{
		stare = false;
		auxSort = stiva;
		while (auxSort->next)
		{
			if (auxSort->info.numarMateriiStudent < auxSort->next->info.numarMateriiStudent) // "<" for descending ">" for ascending
			{
				Student aux = auxSort->info;
				auxSort->info = auxSort->next->info;
				auxSort->next->info = aux;
				stare = true;
			}
			auxSort = auxSort->next;
		}
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	NodStiva* stiva = NULL;
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
			NodStiva* nod = creareNodStiva(student);
			stiva = inserareInceput(stiva, nod);
		}
		fclose(f);

		printf("~~~ AFISARE STIVA ~~~\n");
		afisareStiva(stiva);
		newLine();

		printf("~~~ EXTRAGE ULTIMUL STUDENT INTRODUS ~~~\n");
		Student student = extragereInceput(stiva);
		afisareStudent(student);
		newLine();

		printf("~~~ SORTARE STIVA BUBBLE SORT ~~~\n");
		sortareBule(stiva);
		afisareStiva(stiva);
		newLine();

		printf("~~~ SORTARE STIVA SELECTION SORT ~~~\n");
		sortareSelectie(stiva);
		afisareStiva(stiva);
		newLine();

		printf("~~~ SORTARE STIVA INSERTION SORT ~~~\n");
		sortareInsertie(stiva);
		afisareStiva(stiva);
		newLine();

		printf("~~~ DEZALOCA STIVA ~~~\n");
		dezalocaStiva(stiva);
		newLine();

		printf("~~~ AFISARE STIVA ~~~\n");
		afisareStiva(stiva);
		newLine();
		_getch();
	}
	else
	{
		printf("\nEroare \n");
		_getch();
	}
}