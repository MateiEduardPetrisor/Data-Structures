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
	int numarVecini;
};

struct NodVecin
{
	int idStudent;
	NodVecin* next;
};

struct NodGraf
{
	Student info;
	NodVecin* next;
};

struct GrafStudenti
{
	int indexCurent;
	int dimensiuneGraf;
	NodGraf** vectorNoduri;
};

NodVecin* creareNodVecin(int idStudent)
{
	NodVecin* nod = (NodVecin*)malloc(sizeof(NodVecin));
	nod->idStudent = idStudent;
	nod->next = NULL;
	return nod;
}

NodGraf* creareNodGraf(Student student)
{
	NodGraf* nod = (NodGraf*)malloc(sizeof(NodGraf));
	nod->info = student;
	nod->next = NULL;
	return nod;
}

GrafStudenti* creareGraf(int dimensiuneGraf)
{
	GrafStudenti* graf = (GrafStudenti*)malloc(sizeof(GrafStudenti));
	graf->indexCurent = 0;
	graf->dimensiuneGraf = dimensiuneGraf;
	graf->vectorNoduri = (NodGraf**)malloc(sizeof(NodGraf*)*graf->dimensiuneGraf);
	for (int indexVector = 0; indexVector < graf->dimensiuneGraf; indexVector++)
	{
		graf->vectorNoduri[indexVector] = NULL;
	}
	return graf;
}

NodVecin* inserareVecinInceput(NodVecin* listaVecini, NodVecin* nod)
{
	if (listaVecini == NULL)
	{
		listaVecini = nod;
	}
	else
	{
		nod->next = listaVecini;
		listaVecini = nod;
	}
	return listaVecini;
}

NodVecin* inserareVecinSfarsit(NodVecin* listaVecini, NodVecin* nod)
{
	if (listaVecini == NULL)
	{
		listaVecini = nod;
	}
	else
	{
		NodVecin* tmp = listaVecini;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = nod;
		nod = tmp;
	}
	return listaVecini;
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

void afisareNodGraf(NodGraf* nod)
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
		printf(" %d ", nod->info.numarVecini);
		newLine();
	}
}

void afisareNodVecin(NodVecin* nod)
{
	if (nod != NULL)
	{
		printf(" %d ", nod->idStudent);
	}
}

void afisareGraf(GrafStudenti* graf)
{
	if (graf != NULL)
	{
		if (graf->vectorNoduri != NULL)
		{
			for (int indexVector = 0; indexVector < graf->indexCurent; indexVector++)
			{
				if (graf->vectorNoduri[indexVector] != NULL)
				{
					afisareNodGraf(graf->vectorNoduri[indexVector]);
					NodVecin* tmp = graf->vectorNoduri[indexVector]->next;
					printf("Vecini:");
					while (tmp)
					{
						afisareNodVecin(tmp);
						tmp = tmp->next;
					}
					newLine();
				}
			}
		}
	}
	else
	{
		printf("Graf Gol\n");
	}
}

void dezalocaListaVecini(NodVecin* &lista)
{
	if (lista != NULL)
	{
		while (lista != NULL)
		{
			NodVecin* tmp = lista;
			lista = lista->next;
			tmp->next = NULL;
			//printf("Sterge Nod Vecin:@%p\n", tmp);
			free(tmp);
			tmp = NULL;
		}
		lista = NULL;
	}
}

void dezalocareGraf(GrafStudenti* &graf)
{
	if (graf != NULL)
	{
		if (graf->vectorNoduri != NULL)
		{
			for (int indexVector = 0; indexVector < graf->indexCurent; indexVector++)
			{
				NodVecin* tmp = graf->vectorNoduri[indexVector]->next;
				dezalocaListaVecini(tmp);
				NodGraf* sterge = graf->vectorNoduri[indexVector];
				sterge->next = NULL;
				//printf("Sterge Nod Graf:@%p\n", sterge);
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
			free(graf->vectorNoduri);
			graf->vectorNoduri = NULL;
			free(graf);
			graf = NULL;
		}
	}
}

void copiereGrafInGraf(GrafStudenti* &rezultat, GrafStudenti* sursa)
{
	if (sursa != NULL)
	{
		if (sursa->vectorNoduri != NULL)
		{
			for (int indexVector = 0; indexVector < sursa->indexCurent; indexVector++)
			{
				Student student;
				student.idStudent = sursa->vectorNoduri[indexVector]->info.idStudent;
				student.numeStudent = (char*)malloc(sizeof(char)*strlen(sursa->vectorNoduri[indexVector]->info.numeStudent) + 1);
				strcpy(student.numeStudent, sursa->vectorNoduri[indexVector]->info.numeStudent);
				student.numarMateriiStudent = sursa->vectorNoduri[indexVector]->info.numarMateriiStudent;
				student.listaMateriiStudent = (char**)malloc(sizeof(char*)*sursa->vectorNoduri[indexVector]->info.numarMateriiStudent);
				for (int indexMaterii = 0; indexMaterii < sursa->vectorNoduri[indexVector]->info.numarMateriiStudent; indexMaterii++)
				{
					student.listaMateriiStudent[indexMaterii] = (char*)malloc(sizeof(char)*strlen(sursa->vectorNoduri[indexVector]->info.listaMateriiStudent[indexMaterii]) + 1);
					strcpy(student.listaMateriiStudent[indexMaterii], sursa->vectorNoduri[indexVector]->info.listaMateriiStudent[indexMaterii]);
				}
				student.noteStudent = (float*)malloc(sizeof(float)*sursa->vectorNoduri[indexVector]->info.numarMateriiStudent);
				for (int indexNote = 0; indexNote < sursa->vectorNoduri[indexVector]->info.numarMateriiStudent; indexNote++)
				{
					student.noteStudent[indexNote] = sursa->vectorNoduri[indexVector]->info.noteStudent[indexNote];
				}
				student.facultateStudent = (Facultate)sursa->vectorNoduri[indexVector]->info.facultateStudent;
				student.numarVecini = sursa->vectorNoduri[indexVector]->info.numarVecini;
				NodGraf* nodGraf = creareNodGraf(student);
				while (sursa->vectorNoduri[indexVector]->next)
				{
					//nodGraf->next = inserareVecinInceput(nodGraf->next, creareNodVecin(sursa->vectorNoduri[indexVector]->next->idStudent));
					nodGraf->next = inserareVecinSfarsit(nodGraf->next, creareNodVecin(sursa->vectorNoduri[indexVector]->next->idStudent));
					sursa->vectorNoduri[indexVector]->next = sursa->vectorNoduri[indexVector]->next->next;
				}
				rezultat->vectorNoduri[indexVector] = nodGraf;
				rezultat->indexCurent = indexVector + 1;
			}
		}
	}
}

GrafStudenti* inserareNodGraf(GrafStudenti* &graf, NodGraf* nod)
{
	if (graf->indexCurent == graf->dimensiuneGraf)
	{
		printf("Realocare\n");
		GrafStudenti* rezultat = creareGraf(graf->dimensiuneGraf * 2);
		copiereGrafInGraf(rezultat, graf);
		dezalocareGraf(graf);
		graf = rezultat;
	}
	int index = graf->indexCurent;
	graf->vectorNoduri[index] = nod;
	graf->indexCurent = index + 1;
	return graf;
}

void afisareDimensiuneIndex(GrafStudenti* graf)
{
	if (graf != NULL)
	{
		if (graf->vectorNoduri != NULL)
		{
			printf("Dimensiune Graf: %d\n", graf->dimensiuneGraf);
			printf("Index Curent Graf: %d\n", graf->indexCurent);
		}
	}
}

struct NodCoada
{
	int varfGraf;
	NodCoada* next;
};

NodCoada* creareNodCoada(int varf)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->varfGraf = varf;
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

int extragereInceput(NodCoada* &coada)
{
	if (coada != NULL)
	{
		int varfGraf;
		while (coada != NULL)
		{
			NodCoada* extrage = coada;
			coada = coada->next;
			extrage->next = NULL;
			varfGraf = extrage->varfGraf;
			free(extrage);
			extrage = NULL;
			return varfGraf;
		}
	}
	else
	{
		printf("Coada Goala\n");
	}
}

void parcurgeBF(GrafStudenti* graf, int nodStart)
{
	int* vectorVarfuriVizitate = (int*)malloc(sizeof(int)*graf->dimensiuneGraf);
	for (int i = 0; i < graf->dimensiuneGraf; i++)
	{
		vectorVarfuriVizitate[i] = 0;
	}
	NodCoada* coada = NULL;
	vectorVarfuriVizitate[nodStart - 1] = 1;
	NodCoada* nod = creareNodCoada(nodStart);
	coada = inserareSfarsit(coada, nod);
	while (coada != NULL)
	{
		nodStart = extragereInceput(coada);
		printf("%d ", nodStart);
		if (graf->vectorNoduri[nodStart - 1]->next != NULL)
		{
			NodVecin* tmp = graf->vectorNoduri[nodStart - 1]->next;
			while (tmp)
			{
				int vecin = tmp->idStudent;
				if (vectorVarfuriVizitate[vecin - 1] != 1)
				{
					vectorVarfuriVizitate[vecin - 1] = 1;
					NodCoada* nod = creareNodCoada(vecin);
					coada = inserareSfarsit(coada, nod);
				}
				tmp = tmp->next;
			}
		}
	}
	newLine();
	free(vectorVarfuriVizitate);
	vectorVarfuriVizitate = NULL;
}

struct NodStiva
{
	int varfGraf;
	NodStiva* next;
};

NodStiva* creareNodStiva(int varf)
{
	NodStiva* nod = (NodStiva*)malloc(sizeof(NodStiva));
	nod->varfGraf = varf;
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

int extragereInceput(NodStiva* &stiva)
{
	if (stiva != NULL)
	{
		int varfGraf;
		while (stiva != NULL)
		{
			NodStiva* extrage = stiva;
			stiva = stiva->next;
			extrage->next = NULL;
			varfGraf = extrage->varfGraf;
			free(extrage);
			extrage = NULL;
			return varfGraf;
		}
	}
	else
	{
		printf("Stiva Goala\n");
	}
}

void parcurgeDF(GrafStudenti* graf, int nodStart)
{
	int* vectorVarfuriVizitate = (int*)malloc(sizeof(int)*graf->dimensiuneGraf);
	for (int i = 0; i < graf->dimensiuneGraf; i++)
	{
		vectorVarfuriVizitate[i] = 0;
	}
	NodStiva* stiva = NULL;
	vectorVarfuriVizitate[nodStart - 1] = 1;
	NodStiva* nod = creareNodStiva(nodStart);
	stiva = inserareInceput(stiva, nod);
	while (stiva != NULL)
	{
		nodStart = extragereInceput(stiva);
		printf("%d ", nodStart);
		if (graf->vectorNoduri[nodStart - 1]->next != NULL)
		{
			NodVecin* tmp = graf->vectorNoduri[nodStart - 1]->next;
			while (tmp)
			{
				int vecin = tmp->idStudent;
				if (vectorVarfuriVizitate[vecin - 1] != 1)
				{
					vectorVarfuriVizitate[vecin - 1] = 1;
					NodStiva* nod = creareNodStiva(vecin);
					stiva = inserareInceput(stiva, nod);
				}
				tmp = tmp->next;
			}
		}
	}
	newLine();
	free(vectorVarfuriVizitate);
	vectorVarfuriVizitate = NULL;
}

void main()
{
	FILE* f = fopen("Studenti.txt", "r");
	GrafStudenti* grafStudenti = creareGraf(1);
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
			fscanf(f, "%d", &student.numarVecini);
			NodGraf* nodGraf = creareNodGraf(student);
			for (int indexVecini = 0; indexVecini < student.numarVecini; indexVecini++)
			{
				int idStudent;
				fscanf(f, "%d", &idStudent);
				//nodGraf->next = inserareVecinInceput(nodGraf->next, creareNodVecin(idStudent));
				nodGraf->next = inserareVecinSfarsit(nodGraf->next, creareNodVecin(idStudent));
			}
			grafStudenti = inserareNodGraf(grafStudenti, nodGraf);
		}
		fclose(f);

		printf("~~~ AFISARE GRAF SI VECINII NODURILOR ~~~\n");
		afisareGraf(grafStudenti);
		newLine();

		printf("~~~ AFIASRE INDEX SI DIMENSIUNE GRAF ~~~\n");
		afisareDimensiuneIndex(grafStudenti);
		newLine();

		printf("~~~ PARCURGEREA BF A GRAFULUI 1 ~~~\n");
		int varfStartBF1 = 3;
		printf("Varf Start: %d\n", varfStartBF1);
		parcurgeBF(grafStudenti, varfStartBF1);
		newLine();

		printf("~~~ PARCURGEREA DF A GRAFULUI 1 ~~~\n");
		int varfStartDF1 = 3;
		printf("Varf Start: %d\n", varfStartDF1);
		parcurgeDF(grafStudenti, varfStartDF1);
		newLine();

		printf("~~~ PARCURGEREA BF A GRAFULUI 2 ~~~\n");
		int varfStartBF2 = 11;
		printf("Varf Start: %d\n", varfStartBF2);
		parcurgeBF(grafStudenti, varfStartBF2);
		newLine();

		printf("~~~ PARCURGEREA DF A GRAFULUI 2 ~~~\n");
		int varfStartDF2 = 11;
		printf("Varf Start: %d\n", varfStartDF2);
		parcurgeDF(grafStudenti, varfStartDF2);
		newLine();

		printf("~~~ DEZALOCARE GRAF ~~~\n");
		dezalocareGraf(grafStudenti);
		afisareGraf(grafStudenti);
		newLine();

		_getch();
	}
	else
	{
		printf("\nEroare\n");
		_getch();
	}
}