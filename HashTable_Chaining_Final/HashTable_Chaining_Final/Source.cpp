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

struct HashTable
{
	int dimensiuneHashTable;
	NodLista** vectorListe;
};

HashTable* creareHashTable(int dimensiuneHashTable)
{
	HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
	hashTable->dimensiuneHashTable = dimensiuneHashTable;
	hashTable->vectorListe = (NodLista**)malloc(sizeof(NodLista*)*hashTable->dimensiuneHashTable);
	for (int indexHashTable = 0; indexHashTable < hashTable->dimensiuneHashTable; indexHashTable++)
	{
		hashTable->vectorListe[indexHashTable] = NULL;
	}
	return hashTable;
}

int functiaHash(HashTable* hashTable, int idStudent)
{
	return idStudent%hashTable->dimensiuneHashTable;
}

float calculeazaGradulDeIncarcare(HashTable* hashTable)
{
	int pozitiiOcupate = 0;
	if (hashTable != NULL)
	{
		if (hashTable->vectorListe != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < hashTable->dimensiuneHashTable; indexHashTable++)
			{
				NodLista* tmp = hashTable->vectorListe[indexHashTable];
				if (tmp != NULL)
				{
					pozitiiOcupate++;
				}
			}
			return (float)pozitiiOcupate / (float)hashTable->dimensiuneHashTable;
		}
	}
}

void afiseazaListaIndex(HashTable* hashTable, int index)
{
	if (hashTable != NULL)
	{
		if (hashTable->vectorListe != NULL)
		{
			NodLista* tmp = hashTable->vectorListe[index];
			while (tmp)
			{
				afisareNodLista(tmp);
				tmp = tmp->next;
			}
		}
	}
}

void afisareHashTable(HashTable* hashTable)
{
	if (hashTable != NULL)
	{
		if (hashTable->vectorListe != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < hashTable->dimensiuneHashTable; indexHashTable++)
			{
				NodLista* tmp = hashTable->vectorListe[indexHashTable];
				printf("Lista: %d \n", indexHashTable);
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
		printf("Tabela Hash Goala\n");
	}
}

void dezalocaHashTable(HashTable* &hashTable)
{
	if (hashTable != NULL)
	{
		if (hashTable->vectorListe != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < hashTable->dimensiuneHashTable; indexHashTable++)
			{
				NodLista* tmp = hashTable->vectorListe[indexHashTable];
				while (tmp != NULL)
				{
					//printf("Sterge Lista:@%p\n", tmp);
					deazalocaLista(tmp);
				}
			}
			free(hashTable->vectorListe);
			hashTable->vectorListe = NULL;
			hashTable->dimensiuneHashTable = 0;
			free(hashTable);
			hashTable = NULL;
		}
	}
}

HashTable* inserareHashTableChaining(HashTable* &hashTable, NodLista* nod);

void copiereHashTableinHashTable(HashTable* &rezultat, HashTable* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorListe != NULL)
		{
			for (int indexHashTable = 0; indexHashTable < sursa->dimensiuneHashTable; indexHashTable++)
			{
				if (sursa->vectorListe[indexHashTable] != NULL)
				{
					while (sursa->vectorListe[indexHashTable] != NULL)
					{
						Student student;
						student.idStudent = sursa->vectorListe[indexHashTable]->info.idStudent;
						student.numeStudent = (char*)malloc(sizeof(char)*strlen(sursa->vectorListe[indexHashTable]->info.numeStudent) + 1);
						strcpy(student.numeStudent, sursa->vectorListe[indexHashTable]->info.numeStudent);
						student.numarMateriiStudent = sursa->vectorListe[indexHashTable]->info.numarMateriiStudent;
						student.listaMateriiStudent = (char**)malloc(sizeof(char*)*sursa->vectorListe[indexHashTable]->info.numarMateriiStudent);
						for (int indexMaterii = 0; indexMaterii < sursa->vectorListe[indexHashTable]->info.numarMateriiStudent; indexMaterii++)
						{
							student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(sursa->vectorListe[indexHashTable]->info.listaMateriiStudent[indexMaterii]) + 1);
							strcpy(student.listaMateriiStudent[indexMaterii], sursa->vectorListe[indexHashTable]->info.listaMateriiStudent[indexMaterii]);
						}
						student.noteStudent = (float*)malloc(sizeof(float)*sursa->vectorListe[indexHashTable]->info.numarMateriiStudent);
						for (int indexNote = 0; indexNote < sursa->vectorListe[indexHashTable]->info.numarMateriiStudent; indexNote++)
						{
							student.noteStudent[indexNote] = sursa->vectorListe[indexHashTable]->info.noteStudent[indexNote];
						}
						student.facultateStudent = (Facultate)sursa->vectorListe[indexHashTable]->info.facultateStudent;
						inserareHashTableChaining(rezultat, creareNodLista(student));
						sursa->vectorListe[indexHashTable] = sursa->vectorListe[indexHashTable]->next;
					}
				}
			}
		}
	}
}

HashTable* inserareHashTableChaining(HashTable* &hashTable, NodLista* nod)
{
	if (calculeazaGradulDeIncarcare(hashTable) >= 0.75)
	{
		printf("Realocare\n");
		printf("Gradul De Ocupare %4.2f \n", calculeazaGradulDeIncarcare(hashTable));
		HashTable* rezultat = creareHashTable(hashTable->dimensiuneHashTable * 2);
		copiereHashTableinHashTable(rezultat, hashTable);
		dezalocaHashTable(hashTable);
		hashTable = rezultat;
	}
	int index = functiaHash(hashTable, nod->info.idStudent);
	hashTable->vectorListe[index] = inserareInceput(hashTable->vectorListe[index], nod);
	//hashTable->vectorListe[index] = inserareSfarsit(hashTable->vectorListe[index], nod);
	return hashTable;
}

void main()
{
	FILE*f = fopen("Studenti.txt", "r");
	HashTable* hashTable = creareHashTable(1);
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
			hashTable = inserareHashTableChaining(hashTable, creareNodLista(student));
		}
		fclose(f);

		printf("~~~ AFISARE HASH TABLE ~~~\n");
		afisareHashTable(hashTable);
		newLine();

		newLine();
		printf("~~~ GRADUL DE INCARCARE: %4.2f %s ~~~\n", calculeazaGradulDeIncarcare(hashTable) * 100, "%");
		printf("~~~ DIMENSIUNE HASH TABLE: %d ~~~\n", hashTable->dimensiuneHashTable);
		newLine();

		printf("~~~ DEZALOCA HASH TABLE ~~~\n");
		dezalocaHashTable(hashTable);
		afisareHashTable(hashTable);

		_getch();
	}
	else
	{
		printf("\n Eroare\n");
		_getch();
	}
}