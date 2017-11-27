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

NodLista* inserareInceputLista(NodLista* lista, NodLista* nod)
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

NodLista* inserareSfarsitLista(NodLista* lista, NodLista* nod)
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
			tmp->next = NULL;
			//printf("Sterge Nod Lista:@%p\n", tmp);
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
		free(lista);
		lista = NULL;
	}
}

struct VectorListe
{
	int indexCurent;
	int dimensiuneVector;
	NodLista** vectorListeStudenti;
};

VectorListe* creareVectorListe(int dimensiuneVector)
{
	VectorListe* vectorListe = (VectorListe*)malloc(sizeof(VectorListe));
	vectorListe->dimensiuneVector = dimensiuneVector;
	vectorListe->indexCurent = 0;
	vectorListe->vectorListeStudenti = (NodLista**)malloc(sizeof(NodLista*)*vectorListe->dimensiuneVector);
	for (int indexVector = 0; indexVector < vectorListe->dimensiuneVector; indexVector++)
	{
		vectorListe->vectorListeStudenti[indexVector] = NULL;
	}
	return vectorListe;
}

void copiereVectorListeInVectorListe(VectorListe* &rezultat, VectorListe* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorListeStudenti != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				while (sursa->vectorListeStudenti[indexVector] != NULL)
				{
					Student student;
					student.idStudent = sursa->vectorListeStudenti[indexVector]->info.idStudent;
					student.numeStudent = (char*)malloc(sizeof(char)*strlen(sursa->vectorListeStudenti[indexVector]->info.numeStudent) + 1);
					strcpy(student.numeStudent, sursa->vectorListeStudenti[indexVector]->info.numeStudent);
					student.numarMateriiStudent = sursa->vectorListeStudenti[indexVector]->info.numarMateriiStudent;
					student.listaMateriiStudent = (char**)malloc(sizeof(char*)*sursa->vectorListeStudenti[indexVector]->info.numarMateriiStudent);
					for (int indexMaterii = 0; indexMaterii < sursa->vectorListeStudenti[indexVector]->info.numarMateriiStudent; indexMaterii++)
					{
						student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(sursa->vectorListeStudenti[indexVector]->info.listaMateriiStudent[indexMaterii]) + 1);
						strcpy(student.listaMateriiStudent[indexMaterii], sursa->vectorListeStudenti[indexVector]->info.listaMateriiStudent[indexMaterii]);
					}
					student.noteStudent = (float*)malloc(sizeof(float)*sursa->vectorListeStudenti[indexVector]->info.numarMateriiStudent);
					for (int indexNote = 0; indexNote < sursa->vectorListeStudenti[indexVector]->info.numarMateriiStudent; indexNote++)
					{
						student.noteStudent[indexNote] = sursa->vectorListeStudenti[indexVector]->info.noteStudent[indexNote];
					}
					student.facultateStudent = (Facultate)sursa->vectorListeStudenti[indexVector]->info.facultateStudent;
					rezultat->vectorListeStudenti[indexVector] = inserareInceputLista(rezultat->vectorListeStudenti[indexVector], creareNodLista(student));
					//rezultat->vectorListeStudenti[indexVector] = inserareSfarsitLista(rezultat->vectorListeStudenti[indexVector], creareNodLista(student));
					rezultat->indexCurent = indexVector + 1;
					sursa->vectorListeStudenti[indexVector] = sursa->vectorListeStudenti[indexVector]->next;
				}
			}
		}
	}
}

void dezalocaVectorListe(VectorListe* &vectorListe)
{
	if (vectorListe != NULL)
	{
		if (vectorListe->vectorListeStudenti != NULL)
		{
			for (int indexVector = 0; indexVector < vectorListe->dimensiuneVector; indexVector++)
			{
				NodLista* tmp = vectorListe->vectorListeStudenti[indexVector];
				while (tmp != NULL)
				{
					//printf("Sterge Lista:@%p\n", tmp);
					deazalocaLista(tmp);
				}
			}
			free(vectorListe->vectorListeStudenti);
			vectorListe->vectorListeStudenti = NULL;
		}
		vectorListe->dimensiuneVector = 0;
		vectorListe->indexCurent = 0;
		free(vectorListe);
		vectorListe = NULL;
	}
}

void inserareStudent(VectorListe* &vectorListe, Student student)
{
	if (vectorListe->indexCurent == vectorListe->dimensiuneVector)
	{
		printf("Realocare\n");
		VectorListe* rezultat = creareVectorListe(vectorListe->dimensiuneVector * 2);
		copiereVectorListeInVectorListe(rezultat, vectorListe);
		dezalocaVectorListe(vectorListe);
		vectorListe = rezultat;
	}
	int index = vectorListe->indexCurent;
	vectorListe->vectorListeStudenti[index] = inserareInceputLista(vectorListe->vectorListeStudenti[index], creareNodLista(student));
	//vectorListe->vectorListeStudenti[index] = inserareSfarsitLista(vectorListe->vectorListeStudenti[index], creareNodLista(student));
	vectorListe->indexCurent = index + 1;
}

void afisareVectorListe(VectorListe* vectorListe)
{
	if (vectorListe != NULL)
	{
		if (vectorListe->vectorListeStudenti != NULL)
		{
			for (int indexVector = 0; indexVector < vectorListe->dimensiuneVector; indexVector++)
			{
				NodLista* tmp = vectorListe->vectorListeStudenti[indexVector];
				printf("Lista: %d \n", indexVector);
				while (tmp)
				{
					afisareNodLista(tmp);
					tmp = tmp->next;
				}
			}
		}
	}
	else
	{
		printf("Vector de Liste Gol\n");
	}
}

void afisareListaIndex(VectorListe* vectorListe, int index)
{
	if (vectorListe->vectorListeStudenti != NULL)
	{
		NodLista* tmp = vectorListe->vectorListeStudenti[index];
		while (tmp)
		{
			afisareNodLista(tmp);
			tmp = tmp->next;
		}
	}
}

void afisareDimensiuneIndex(VectorListe* vectorListe)
{
	if (vectorListe != NULL)
	{
		if (vectorListe->vectorListeStudenti != NULL)
		{
			printf("Dimensiune Vector: %d\n", vectorListe->dimensiuneVector);
			printf("Index Curent Vector: %d\n", vectorListe->indexCurent);
		}
	}
}

void main()
{
	FILE*f = fopen("Studenti.txt", "r");
	VectorListe* vectorListe = creareVectorListe(1);

	Student student;
	student.idStudent = 1234;
	student.numeStudent = (char*)malloc(sizeof(char)*strlen("ION") + 1);
	strcpy(student.numeStudent, "ION");
	student.numarMateriiStudent = 3;
	student.listaMateriiStudent = (char**)malloc(sizeof(char*)*student.numarMateriiStudent + 1);
	for (int indexMaterii = 0; indexMaterii < student.numarMateriiStudent; indexMaterii++)
	{
		student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen("materia") + 1);
		strcpy(student.listaMateriiStudent[indexMaterii], "materia");
	}
	student.noteStudent = (float*)malloc(sizeof(float)*student.numarMateriiStudent);
	for (int indexNote = 0; indexNote < student.numarMateriiStudent; indexNote++)
	{
		student.noteStudent[indexNote] = indexNote + 3;
	}
	student.facultateStudent = (Facultate)8;
	vectorListe->vectorListeStudenti[0] = inserareInceputLista(vectorListe->vectorListeStudenti[0], creareNodLista(student));
	//vectorListe->vectorListeStudenti[0] = inserareSfarsitLista(vectorListe->vectorListeStudenti[0], creareNodLista(student));

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
			inserareStudent(vectorListe, student);
		}
		fclose(f);

		printf("~~~ AFISARE VECTOR DE LISTE ~~~\n");
		afisareVectorListe(vectorListe);
		newLine();

		printf("~~~ AFISARE LISTA DE PE INDEXUL 0 ~~~\n");
		afisareListaIndex(vectorListe, 0);
		newLine();

		printf("~~~ AFIASRE INDEX SI DIMENSIUNE VECTOR LISTE ~~~\n");
		afisareDimensiuneIndex(vectorListe);
		newLine();

		printf("~~~ DEZALOCARE VECTOR DE LISTE ~~~\n");
		dezalocaVectorListe(vectorListe);
		afisareVectorListe(vectorListe);
		newLine();

		_getch();
	}
	else
	{
		printf("\n Eroare\n");
		_getch();
	}
}