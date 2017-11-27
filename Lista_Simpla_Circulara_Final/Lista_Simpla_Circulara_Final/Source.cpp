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

struct NodLista
{
	Student info;
	NodLista* next;
};

NodLista* creareNodLista(Student student)
{
	NodLista* nod = (NodLista*)malloc(sizeof(NodLista));
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

void afisareNodLista(NodLista* nod)
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

void afisareListaCirculara(NodLista* lista)
{
	if (lista != NULL)
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			afisareNodLista(temp);
			temp = temp->next;
		}
		afisareNodLista(temp);
	}
	else
	{
		printf("Lista Goala\n");
	}
}

NodLista* inserareInceputListaCirculara(NodLista* lista, NodLista* nod)
{
	if (lista == NULL)
	{
		lista = nod;
		lista->next = lista;
	}
	else
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			temp = temp->next;
		}
		temp->next = nod;
		nod->next = lista;
		lista = nod;
	}
	return lista;
}

NodLista* inserareSfarsitListaCirculara(NodLista* lista, NodLista* nod)
{
	if (lista == NULL)
	{
		lista = nod;
		lista->next = lista;
	}
	else
	{
		NodLista* temp = lista;
		while (temp->next != lista)
		{
			temp = temp->next;
		}
		temp->next = nod;
		nod->next = lista;
	}
	return lista;
}

void deazalocaListaCirculara(NodLista* &lista)
{
	if (lista != NULL)
	{
		NodLista* tmp = lista;
		while (tmp->next != lista)
		{
			NodLista* sterge = tmp;
			tmp = tmp->next;
			sterge->next = NULL;
			//printf("Sterge Nod:@%p\n", sterge);
			free(sterge->info.numeStudent);
			sterge->info.numeStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < sterge->info.numarMateriiStudent; indexMaterii++)
			{
				free(sterge->info.listaMateriiStudent[indexMaterii]);
				sterge->info.listaMateriiStudent[indexMaterii] = NULL;
			}
			free(sterge->info.listaMateriiStudent);
			sterge->info.listaMateriiStudent = NULL;
			free(sterge->info.noteStudent);
			sterge->info.noteStudent = NULL;
			free(sterge);
			sterge = NULL;
		}
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
		lista = NULL;
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	NodLista* lista = NULL;
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
			NodLista* nod = creareNodLista(student);
			//lista = inserareInceputListaCirculara(lista, nod);
			lista = inserareSfarsitListaCirculara(lista, nod);
		}
		fclose(f);

		printf("~~~ AFISARE LISTA ~~~\n");
		afisareListaCirculara(lista);
		newLine();

		printf("~~~ DEZALOCARE LISTA ~~~\n");
		deazalocaListaCirculara(lista);
		afisareListaCirculara(lista);
		newLine();
		_getch();
	}
	else
	{
		printf("\n Eroare \n");
		_getch();
	}
}