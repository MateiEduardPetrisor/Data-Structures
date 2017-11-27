#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

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
	int prioritate;
};

struct Heap
{
	int indexCurent;
	int dimensiuneHeap;
	Student* vectorStudenti;
};

Heap* creareHeap(int dimensiuneHeap)
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->indexCurent = 0;
	heap->dimensiuneHeap = dimensiuneHeap;
	heap->vectorStudenti = (Student*)malloc(sizeof(Student)*heap->dimensiuneHeap);
	return heap;
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

void afisareHeap(Heap* heap)
{
	if (heap != NULL)
	{
		if (heap->vectorStudenti != NULL)
		{
			for (int indexHeap = 0; indexHeap < heap->indexCurent; indexHeap++)
			{
				printf("%d ", heap->vectorStudenti[indexHeap].idStudent);
				printf("%s ", heap->vectorStudenti[indexHeap].numeStudent);
				printf("%d ", heap->vectorStudenti[indexHeap].numarMateriiStudent);
				for (int indexListaMaterii = 0; indexListaMaterii < heap->vectorStudenti[indexHeap].numarMateriiStudent; indexListaMaterii++)
				{
					printf("%s ", heap->vectorStudenti[indexHeap].listaMateriiStudent[indexListaMaterii]);
				}
				for (int indexNote = 0; indexNote < heap->vectorStudenti[indexHeap].numarMateriiStudent; indexNote++)
				{
					printf("%4.2f ", heap->vectorStudenti[indexHeap].noteStudent[indexNote]);
				}
				afisareFacultate(heap->vectorStudenti[indexHeap].facultateStudent);
				printf(" %d", heap->vectorStudenti[indexHeap].prioritate);
				newLine();
			}
		}
	}
	else
	{
		printf("Heap Gol\n");
	}
}

void afisareStudent(Student student)
{
	printf("Prioritate: %d ", student.prioritate);
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

void parcurgerePeNivele(Heap* heap, int nrElem)
{
	int NrElemNivel = 1;
	int nr = 0;
	for (int i = 0; i < nrElem; i++)
	{
		if (nr == NrElemNivel)
		{
			NrElemNivel = NrElemNivel * 2;
			printf("\n");
			nr = 0;
		}
		nr++;
		afisareStudent(heap->vectorStudenti[i]);
	}
}

void inteschimbare(Heap* heap, int index, int indexMax)
{
	Student tmp;
	tmp = heap->vectorStudenti[index];
	heap->vectorStudenti[index] = heap->vectorStudenti[indexMax];
	heap->vectorStudenti[indexMax] = tmp;
}

void filtrareHeap(Heap* heap, int index)
{
	int indexMax = index;
	int indexStg = 2 * index + 1;
	int indexDr = 2 * index + 2;
	if (indexStg < heap->indexCurent && heap->vectorStudenti[indexStg].prioritate > heap->vectorStudenti[indexMax].prioritate)
	{
		indexMax = indexStg;
	}
	if (indexDr < heap->indexCurent && heap->vectorStudenti[indexDr].prioritate > heap->vectorStudenti[indexMax].prioritate)
	{
		indexMax = indexDr;
	}
	if (index != indexMax)
	{
		inteschimbare(heap, index, indexMax);
	}
}

void dezalocaHeap(Heap* &heap)
{
	if (heap != NULL)
	{
		if (heap->vectorStudenti != NULL)
		{
			for (int indexHeap = 0; indexHeap < heap->indexCurent; indexHeap++)
			{
				free(heap->vectorStudenti[indexHeap].numeStudent);
				heap->vectorStudenti[indexHeap].numeStudent = NULL;
				for (int indexMaterii = 0; indexMaterii < heap->vectorStudenti[indexHeap].numarMateriiStudent; indexMaterii++)
				{
					free(heap->vectorStudenti[indexHeap].listaMateriiStudent[indexMaterii]);
					heap->vectorStudenti[indexHeap].listaMateriiStudent[indexMaterii] = NULL;
				}
				free(heap->vectorStudenti[indexHeap].listaMateriiStudent);
				heap->vectorStudenti[indexHeap].listaMateriiStudent = NULL;
				free(heap->vectorStudenti[indexHeap].noteStudent);
				heap->vectorStudenti[indexHeap].noteStudent = NULL;
			}
			free(heap->vectorStudenti);
			heap->vectorStudenti = NULL;
			heap->dimensiuneHeap = 0;
			heap->indexCurent = 0;
			free(heap);
			heap = NULL;
		}
	}
}

void copiereHeapInHeap(Heap* &rezultat, Heap* sursa)
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
				student.prioritate = sursa->vectorStudenti[indexVector].prioritate;
				rezultat->vectorStudenti[indexVector] = student;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

void inserareStudent(Heap* &heap, Student student)
{
	if (heap->indexCurent == heap->dimensiuneHeap)
	{
		printf("Realocare\n");
		Heap* rezultat = creareHeap(heap->dimensiuneHeap * 2);
		copiereHeapInHeap(rezultat, heap);
		dezalocaHeap(heap);
		heap = rezultat;
	}
	int	index = heap->indexCurent;
	heap->vectorStudenti[index] = student;
	heap->indexCurent = index + 1;

	for (int i = (heap->indexCurent - 1) / 2; i >= 0; i--)
	{
		filtrareHeap(heap, i);
	}
}

void afisareDimensiuneIndex(Heap* heap)
{
	if (heap != NULL)
	{
		if (heap->vectorStudenti != NULL)
		{
			printf("Dimensiune Heap: %d\n", heap->dimensiuneHeap);
			printf("Index Curent Heap: %d\n", heap->indexCurent);
		}
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	Heap* heap = creareHeap(1);
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
			fscanf(f, "%d", &student.prioritate);
			inserareStudent(heap, student);
		}
		fclose(f);

		printf("~~~ AFISARE HEAP ~~~\n");
		afisareHeap(heap);
		newLine();

		printf("~~~ PARCURGE PE NIVELE ~~~\n");
		parcurgerePeNivele(heap, heap->indexCurent);
		newLine();

		printf("~~~ AFIASRE INDEX SI DIMENSIUNE HEAP ~~~\n");
		afisareDimensiuneIndex(heap);
		newLine();

		printf("~~~ DEZALOCARE HEAP ~~~\n");
		dezalocaHeap(heap);
		afisareHeap(heap);
		newLine();

		_getch();
	}
	else
	{
		printf("Eroare\n");
		_getch();
	}
}