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

struct NodArbore
{
	Student info;
	NodArbore* stanga;
	NodArbore* dreapta;
	int gradEchilibru;
};

NodArbore* creareNodArbore(Student student)
{
	NodArbore* nod = (NodArbore*)malloc(sizeof(NodArbore));
	nod->info = student;
	nod->stanga = NULL;
	nod->dreapta = NULL;
	nod->gradEchilibru = 0;
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

void afisareNodArbore(NodArbore* nod)
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
		printf(" GE: %d", nod->gradEchilibru);
		newLine();
	}
}

int maxim(int x, int y)
{
	return x > y ? x : y;
}

int inaltimeArbore(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		return 1 + maxim(inaltimeArbore(radacina->stanga), inaltimeArbore(radacina->dreapta));
	}
	else
	{
		return 0;
	}
}

void calculeazaGradEchilibru(NodArbore* nod)
{
	if (nod != NULL)
	{
		nod->gradEchilibru = inaltimeArbore(nod->dreapta) - inaltimeArbore(nod->stanga);
	}
}

NodArbore* rotatieSimplaDreapta(NodArbore* pivot)
{
	NodArbore* tmp = pivot->stanga;
	pivot->stanga = tmp->dreapta;
	tmp->dreapta = pivot;
	calculeazaGradEchilibru(pivot);
	calculeazaGradEchilibru(tmp);
	printf("Roatie Simpla Dreapta\n");
	pivot = tmp;
	return pivot;
}

NodArbore* rotatieSimplaStanga(NodArbore* pivot)
{
	NodArbore* tmp = pivot->dreapta;
	pivot->dreapta = tmp->stanga;
	tmp->stanga = pivot;
	calculeazaGradEchilibru(pivot);
	calculeazaGradEchilibru(tmp);
	printf("Rotatie Simpla Stanga\n");
	pivot = tmp;
	return pivot;
}

NodArbore* rotatieDublaDreapta(NodArbore* pivot)
{
	pivot->stanga = rotatieSimplaStanga(pivot->stanga);
	pivot = rotatieSimplaDreapta(pivot);
	printf("Rotatie Dubla Dreapta\n");
	return pivot;
}

NodArbore* rotatieDublaStanga(NodArbore* pivot)
{
	pivot->dreapta = rotatieSimplaDreapta(pivot->dreapta);
	pivot = rotatieSimplaStanga(pivot);
	printf("Rotatie Dubla Stanga\n");
	return pivot;
}

NodArbore* reechilibrare(NodArbore* radacina)
{
	calculeazaGradEchilibru(radacina);
	if (radacina->gradEchilibru == 2)
	{
		if (radacina->dreapta->gradEchilibru == 1)
		{
			radacina = rotatieSimplaStanga(radacina);
		}
		else
		{
			radacina = rotatieDublaStanga(radacina);
		}
	}
	else
	{
		if (radacina->gradEchilibru == -2)
		{
			if (radacina->stanga->gradEchilibru == -1)
			{
				radacina = rotatieSimplaDreapta(radacina);
			}
			else
			{
				radacina = rotatieDublaDreapta(radacina);
			}
		}
	}
	return radacina;
}

void adaugaStangaDreaptaRecursiv(NodArbore* &radacina, NodArbore* nod)
{
	if (radacina == NULL)
	{
		radacina = nod;
	}
	else
	{
		if (radacina->info.idStudent < nod->info.idStudent)
		{
			if (radacina->dreapta != NULL)
			{
				adaugaStangaDreaptaRecursiv(radacina->dreapta, nod);
			}
			else
			{
				radacina->dreapta = nod;
			}
		}
		else
		{
			if (radacina->info.idStudent == nod->info.idStudent)
			{
				printf("Exista\n");
			}
			else
			{
				if (radacina->info.idStudent > nod->info.idStudent)
				{
					if (radacina->stanga != NULL)
					{
						adaugaStangaDreaptaRecursiv(radacina->stanga, nod);
					}
					else
					{
						radacina->stanga = nod;
					}
				}
			}
		}
	}
	radacina = reechilibrare(radacina);
}

void parcurgeInordineRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		parcurgeInordineRecursiv(radacina->stanga);
		afisareNodArbore(radacina);
		parcurgeInordineRecursiv(radacina->dreapta);
	}
}

struct NodStiva
{
	NodArbore* info;
	NodStiva* next;
};

NodStiva* creareNodStiva(NodArbore* nodArbore)
{
	NodStiva* nod = (NodStiva*)malloc(sizeof(NodArbore));
	nod->info = nodArbore;
	nod->next = NULL;
	return nod;
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

NodArbore* extragereInceput(NodStiva* &stiva)
{
	if (stiva != NULL)
	{
		NodArbore* nodExtras = NULL;
		while (stiva != NULL)
		{
			NodStiva* extrage = stiva;
			stiva = stiva->next;
			extrage->next = NULL;
			nodExtras = extrage->info;
			free(extrage);
			extrage = NULL;
			return nodExtras;
		}
	}
	else
	{
		printf("Stiva Goala\n");
	}
}

void parcurgeInordineNonRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		NodArbore* nodCurent = radacina;
		NodStiva* stiva = NULL;
		int gata = 0;
		while (gata == 0)
		{
			if (nodCurent != NULL)
			{
				NodStiva* nod = creareNodStiva(nodCurent);
				stiva = inserareInceput(stiva, nod);
				nodCurent = nodCurent->stanga;
			}
			else
			{
				if (stiva != NULL)
				{
					nodCurent = extragereInceput(stiva);
					afisareNodArbore(nodCurent);

					nodCurent = nodCurent->dreapta;
				}
				else
				{
					gata = 1;
				}
			}
		}
	}
}

void parcurgePreordineRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		afisareNodArbore(radacina);
		parcurgePreordineRecursiv(radacina->stanga);
		parcurgePreordineRecursiv(radacina->dreapta);
	}
}

struct NodCoada
{
	NodArbore* info;
	NodCoada* next;
};

NodCoada* creareNodCoada(NodArbore* nodArbore)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = nodArbore;
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

NodArbore* extragereInceput(NodCoada* &coada)
{
	if (coada != NULL)
	{
		NodArbore* nodExtras = NULL;
		while (coada != NULL)
		{
			NodCoada* extrage = coada;
			coada = coada->next;
			extrage->next = NULL;
			nodExtras = extrage->info;
			free(extrage);
			extrage = NULL;
			return nodExtras;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void parcurgePreordineNonRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		NodArbore* nodCurent = radacina;
		NodStiva* stiva = NULL;
		NodStiva* nod = creareNodStiva(nodCurent);
		stiva = inserareInceput(stiva, nod);
		while (stiva != NULL)
		{
			NodArbore* nod = extragereInceput(stiva);
			afisareNodArbore(nod);
			if (nod->dreapta != NULL)
			{
				NodStiva* nodDreapta = creareNodStiva(nod->dreapta);
				stiva = inserareInceput(stiva, nodDreapta);
			}
			if (nod->stanga != NULL)
			{
				NodStiva* nodStanga = creareNodStiva(nod->stanga);
				stiva = inserareInceput(stiva, nodStanga);
			}
		}
	}
}

void parcurgePostordineRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		parcurgePostordineRecursiv(radacina->stanga);
		parcurgePostordineRecursiv(radacina->dreapta);
		afisareNodArbore(radacina);
	}
}

void parcurgePostordineNonRecursiv(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		NodStiva* stiva1 = NULL;
		NodStiva* stiva2 = NULL;
		stiva1 = inserareInceput(stiva1, creareNodStiva(radacina));
		NodArbore* nod = NULL;
		while (stiva1 != NULL)
		{
			nod = extragereInceput(stiva1);
			stiva2 = inserareInceput(stiva2, creareNodStiva(nod));

			if (nod->stanga != NULL)
			{
				stiva1 = inserareInceput(stiva1, creareNodStiva(nod->stanga));
			}
			if (nod->dreapta != NULL)
			{
				stiva1 = inserareInceput(stiva1, creareNodStiva(nod->dreapta));
			}
		}
		while (stiva2 != NULL)
		{
			nod = extragereInceput(stiva2);
			afisareNodArbore(nod);
		}
	}
}

void afisareFrunze(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		afisareFrunze(radacina->stanga);
		if (radacina->stanga == NULL && radacina->dreapta == NULL)
		{
			afisareNodArbore(radacina);
		}
		afisareFrunze(radacina->dreapta);
	}
}

int calculNrFrunze(NodArbore* radacina)
{
	if (radacina == NULL)
	{
		return 0;
	}
	if (radacina->stanga == NULL && radacina->dreapta == NULL)
	{
		return 1;
	}
	else
	{
		return calculNrFrunze(radacina->stanga) + calculNrFrunze(radacina->dreapta);
	}
}

void afisareArborePeNivele(NodArbore* radacina, int indexStart)
{
	if (radacina != NULL)
	{
		for (int j = 0; j < indexStart; j++)
		{
			printf("\t");
		}
		afisareNodArbore(radacina);
		indexStart++;
		afisareArborePeNivele(radacina->stanga, indexStart);
		afisareArborePeNivele(radacina->dreapta, indexStart);
	}
	else
	{
		for (int j = 0; j < indexStart; j++)
		{
			printf("\t");
		}
		printf("==\n");
	}
}

void dezalocaArboreRecursiv(NodArbore* &radacina)
{
	if (radacina != NULL)
	{
		dezalocaArboreRecursiv(radacina->stanga);
		dezalocaArboreRecursiv(radacina->dreapta);
		{
			//printf("Sterge Nod @:%p\n", radacina);
			free(radacina->info.numeStudent);
			radacina->info.numeStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < radacina->info.numarMateriiStudent; indexMaterii++)
			{
				free(radacina->info.listaMateriiStudent[indexMaterii]);
				radacina->info.listaMateriiStudent[indexMaterii] = NULL;
			}
			free(radacina->info.listaMateriiStudent);
			radacina->info.listaMateriiStudent = NULL;
			free(radacina->info.noteStudent);
			radacina->info.noteStudent = NULL;
			radacina->stanga = NULL;
			radacina->dreapta = NULL;
			free(radacina);
			radacina = NULL;
		}
	}
}

void dezalocaArboreNonRecursiv(NodArbore* &radacina)
{
	if (radacina != NULL)
	{
		NodCoada* coada = NULL;
		coada = inserareSfarsit(coada, creareNodCoada(radacina));
		while (coada != NULL)
		{
			NodArbore* nod = extragereInceput(coada);
			if (nod->stanga != NULL)
			{
				coada = inserareSfarsit(coada, creareNodCoada(nod->stanga));
			}
			if (nod->dreapta != NULL)
			{
				coada = inserareSfarsit(coada, creareNodCoada(nod->dreapta));
			}
			//printf("Sterge Nod @:%p\n", nod);
			free(nod->info.numeStudent);
			nod->info.numeStudent = NULL;
			free(nod->info.noteStudent);
			nod->info.noteStudent = NULL;
			for (int indexMaterii = 0; indexMaterii < nod->info.numarMateriiStudent; indexMaterii++)
			{
				free(nod->info.listaMateriiStudent[indexMaterii]);
				nod->info.listaMateriiStudent[indexMaterii] = NULL;
			}
			free(nod->info.listaMateriiStudent);
			nod->info.listaMateriiStudent = NULL;
			free(nod);
			nod = NULL;
		}
		radacina = NULL;
	}
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	NodArbore* arbore = NULL;
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
			NodArbore* nod = creareNodArbore(student);
			adaugaStangaDreaptaRecursiv(arbore, nod);
		}
		fclose(f);

		printf("~~~ PARCURGEREA INORDINE ~~~\n");
		printf("~~~~ INORDINE RECURSIV ~~~~\n");
		parcurgeInordineRecursiv(arbore);
		newLine();
		printf("~~~~ INORDINE NON RECURSIV ~~~~\n");
		parcurgeInordineNonRecursiv(arbore);
		newLine();

		printf("~~~ PARCURGEREA PREORDINE ~~~\n");
		printf("~~~~ PREORDINE RECURSIV ~~~~\n");
		parcurgePreordineRecursiv(arbore);
		newLine();
		printf("~~~~ PREORDINE NON RECURSIV ~~~~\n");
		parcurgePreordineNonRecursiv(arbore);
		newLine();

		printf("~~~ PARCURGEREA POSTORDINE ~~~\n");
		printf("~~~~ POSTORDINE RECURSIV ~~~~\n");
		parcurgePostordineRecursiv(arbore);
		newLine();
		printf("~~~~ POSTORDINE NON RECURSIV ~~~~\n");
		parcurgePostordineNonRecursiv(arbore);
		newLine();

		printf("~~~ AFISRE FRUNZE ~~~\n");
		afisareFrunze(arbore);
		newLine();

		printf("~~~ CALCUL NR FRUNZE ~~~\n");
		int nrFrunza = calculNrFrunze(arbore);
		printf("Nr Frunze: %d\n", nrFrunza);

		printf("~~~ AFISARE PE NIVELE ~~~\n");
		afisareArborePeNivele(arbore, 0);
		newLine();

		printf("~~~ DEZALOCARE ARBORE ~~~\n");
		dezalocaArboreRecursiv(arbore);
		parcurgeInordineRecursiv(arbore);

		_getch();
	}
	else
	{
		printf("\n Eroare\n");
		_getch();
	}
}