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

NodLista* inserareInceput(NodLista* lista, NodLista* nod)
{
	if (lista == NULL)
	{
		lista = nod;
	}
	else
	{
		nod->next = lista;
		lista = nod;
	}
	return lista;
}

NodLista* inserareSfarsit(NodLista* lista, NodLista* nod)
{
	if (lista == NULL)
	{
		lista = nod;
	}
	else
	{
		NodLista* tmp = lista;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
	return lista;
}

void afisareLista(NodLista* lista)
{
	if (lista != NULL)
	{
		NodLista* tmp = lista;
		while (tmp)
		{
			afisareNodLista(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Lista Goala\n");
	}
}

void deazalocaLista(NodLista* &lista)
{
	if (lista != NULL)
	{
		while (lista != NULL)
		{
			NodLista* tmp = lista;
			lista = lista->next;
			printf("Sterge Nod Lista:@%p\n", tmp);
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
			tmp->next = NULL;
			free(tmp);
			tmp = NULL;
		}
		free(lista);
		lista = NULL;
	}
}

struct ListaDeListe
{
	NodLista* info;
	ListaDeListe* next;
};

ListaDeListe* creareNodListaDeListe(NodLista* nod)
{
	ListaDeListe* nodListaDeListe = (ListaDeListe*)malloc(sizeof(ListaDeListe));
	nodListaDeListe->info = nod;
	nodListaDeListe->next = NULL;
	return nodListaDeListe;
}

ListaDeListe* inserareInceputListaDeListe(ListaDeListe* listaDeListe, ListaDeListe* nod)
{
	if (listaDeListe == NULL)
	{
		listaDeListe = nod;
	}
	else
	{
		nod->next = listaDeListe;
		listaDeListe = nod;
	}
	return listaDeListe;
}

ListaDeListe* inserareSfarsitListaDeListe(ListaDeListe* listaDeListe, ListaDeListe* nod)
{
	if (listaDeListe == NULL)
	{
		listaDeListe = nod;
	}
	else
	{
		ListaDeListe* tmp = listaDeListe;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
	return listaDeListe;
}

void afisareNodListaDeListe(ListaDeListe* nod)
{
	if (nod != NULL)
	{
		//afisareLista(nod->info);
		NodLista* lista = nod->info;
		while (lista != NULL)
		{
			NodLista* tmp = lista;
			lista = lista->next;
			printf("%d ", tmp->info.idStudent);
			printf("%s ", tmp->info.numeStudent);
			printf("%d ", tmp->info.numarMateriiStudent);
			for (int indexMaterii = 0; indexMaterii < tmp->info.numarMateriiStudent; indexMaterii++)
			{
				printf("%s ", tmp->info.listaMateriiStudent[indexMaterii]);
			}
			for (int indexNote = 0; indexNote < tmp->info.numarMateriiStudent; indexNote++)
			{
				printf("%4.2f ", tmp->info.noteStudent[indexNote]);
			}
			afisareFacultate(tmp->info.facultateStudent);
			newLine();
		}
	}
}

void afisareListaDeListe(ListaDeListe* listaDeListe)
{
	if (listaDeListe != NULL)
	{
		ListaDeListe* tmp = listaDeListe;
		while (tmp)
		{
			//afisareLista(tmp->info);
			afisareNodListaDeListe(tmp);
			newLine();
			tmp = tmp->next;
		}
	}
	else
	{
		printf("Lista de liste Goala\n");
	}
}

void dezalocareListaDeListe(ListaDeListe* &listaDeListe)
{
	if (listaDeListe != NULL)
	{
		while (listaDeListe != NULL)
		{
			ListaDeListe* tmp = listaDeListe;
			listaDeListe = listaDeListe->next;
			//printf("Sterge Lista:@%p\n", tmp);
			//deazalocaLista(tmp->info);
			tmp->next = NULL;
			NodLista* lista = tmp->info;
			//printf("Sterge Lista:@%p\n", lista);
			while (lista != NULL)
			{
				NodLista* sterge = lista;
				lista = lista->next;
				sterge->next = NULL;
				//printf("Sterge Nod Lista:@%p\n", sterge);
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
			free(lista);
			lista = NULL;
		}
		free(listaDeListe);
		listaDeListe = NULL;
	}
}

Student generareStudent(int idStudent, char* nume, int nrMaterii, Facultate facultate)
{
	Student student;
	student.idStudent = idStudent;
	student.numeStudent = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(student.numeStudent, nume);
	student.numarMateriiStudent = nrMaterii;
	student.listaMateriiStudent = (char**)malloc(sizeof(char*)*student.numarMateriiStudent + 1);
	for (int indexMaterii = 0; indexMaterii < student.numarMateriiStudent; indexMaterii++)
	{
		student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen("MAT") + 1);
		strcpy(student.listaMateriiStudent[indexMaterii], "MAT");
	}
	student.noteStudent = (float*)malloc(sizeof(float)*student.numarMateriiStudent + 1);
	for (int indexNote = 0; indexNote < student.numarMateriiStudent; indexNote++)
	{
		student.noteStudent[indexNote] = 10;
	}
	student.facultateStudent = facultate;
	return student;
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	ListaDeListe* listaDeListe = NULL;
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
			ListaDeListe* nod = creareNodListaDeListe(creareNodLista(student));
			listaDeListe = inserareInceputListaDeListe(listaDeListe, nod);
		}
		fclose(f);

		Student test1 = generareStudent(10, "PRENUME", 4, (Facultate)1);
		NodLista* nodTest1 = creareNodLista(test1);
		listaDeListe->info = inserareSfarsit(listaDeListe->info, nodTest1);

		Student test2 = generareStudent(20, "NUME", 7, (Facultate)2);
		NodLista* nodTest2 = creareNodLista(test2);
		listaDeListe->info = inserareInceput(listaDeListe->info, nodTest2);

		printf("~~~ AFISARE LISTA DE LISTE ~~~\n");
		afisareListaDeListe(listaDeListe);
		newLine();

		printf("~~~ DEZALOCARE LISTA DE LISTE ~~~\n");
		dezalocareListaDeListe(listaDeListe);
		afisareListaDeListe(listaDeListe);
		newLine();
		_getch();
	}
	else
	{
		printf("\nEroare \n");
		_getch();
	}
}