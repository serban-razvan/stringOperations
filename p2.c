#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


typedef struct
{
	char * cuvant;
	int aparitii;
} structura;

int compare(const void * a, const void * b)
{
	int temp = (*(structura *)b).aparitii - (*(structura *)a).aparitii;
	if (temp == 0)
	{
		return strcmp((*(structura *)a).cuvant, (*(structura *)b).cuvant);
	}
	return temp;
}

void adauga(char * temp_cuv, char ** cuvinte, int * apar, int * nr_cuv)
{
	int i, j;
	int nu_se_gaseste = 1;



	for (i = 0 ; i < *nr_cuv ; i++)
	{
		if (strcmp(cuvinte[i], temp_cuv) == 0)
		{
			nu_se_gaseste = 0;
			apar[i]++;
			break;
		}
	}
	if (nu_se_gaseste)
	{
		char *buffer = (char *)malloc(strlen(temp_cuv) * sizeof(char) + 1);
		if (buffer == NULL) return 1;

		strcpy(buffer, temp_cuv);
		cuvinte[*nr_cuv] = buffer;
		apar[*nr_cuv]++;
		(*nr_cuv)++;
	}

}

long dist(char * a, char * b)
{
	long rezultat=0;
	int lena = strlen(a);
	int lenb = strlen(b);
	int i;
	for (i = 0 ; i < MIN(lena, lenb) ; i++)
	{
		rezultat += abs(a[i] - b[i]);
	}
	for (i = MIN(lena, lenb) ; i < MAX(lena,lenb) ; i++)
	{
		if (lena > lenb)
			rezultat += a[i];
		else
			rezultat += b[i];
	}
	return rezultat;
}

void sim(structura * structura1, structura * structura2, int nr_cuv, int nr_cuv1, int nr_cuv2)
{
	long rezultat = 100 * abs(nr_cuv1 - nr_cuv2);
	long temp;
	int i;
	for (i = 0 ; i < nr_cuv ; i++)
	{
		temp = (structura1[i]).aparitii + (structura2[i]).aparitii;
		temp *= (dist((structura1[i]).cuvant, (structura2[i]).cuvant));
		rezultat += temp;
	}
	printf("%li\n", rezultat);
}


int main()
{
	char **cuvinte1 = (char **)malloc(16000 * sizeof(char *));
	int *apar1 = (int *)calloc(16000, sizeof(int));
	int *nr_cuv1 = (int *)calloc(1, sizeof(int));

	if (cuvinte1 == NULL || apar1 == NULL || nr_cuv1 == NULL) return 1;

	char **cuvinte2 = (char **)malloc(16000 * sizeof(char *));
	int *apar2 = (int *)calloc(16000, sizeof(int));
	int *nr_cuv2 = (int *)calloc(1, sizeof(int));

	if (cuvinte2 == NULL || apar2 == NULL || nr_cuv2 == NULL) return 1;


	long N, M, i, j;


	char *temp_cuv;


	scanf("%li\n", &N);
	char *temp_pointer = (char *)malloc(16000 * sizeof(char));
	if (temp_pointer == NULL) return 1;

	for (i = 0 ; i < N ; i++)
	{
		fgets(temp_pointer, 14000, stdin);

		if (strcmp(temp_pointer, "\n") == 0)
		{
			//daca e doar o linie goala
			temp_pointer[0] = '\0'; //scap de newline
		}
		else
		{
			strtok(temp_pointer, "\n"); //scapam de trailing newline de la fgets intr-un mod mai ezoteric
		}

		temp_cuv = strtok(temp_pointer, " \"\',!?");
		while (temp_cuv != NULL)
		{
			adauga(temp_cuv, cuvinte1, apar1, nr_cuv1);
			temp_cuv = strtok(NULL, " \"\',!?");
		}
	}

	scanf("%li\n", &M);

	for (i = 0 ; i < M ; i++)
	{
		fgets(temp_pointer, 14000, stdin);

		if (strcmp(temp_pointer, "\n") == 0)
		{
			//daca e doar o linie goala
			temp_pointer[0] = '\0'; //fara newline
		}
		else
		{
			//scapam de trailing newline
			strtok(temp_pointer, "\n");
		}

		temp_cuv = strtok(temp_pointer, " \"\',!?");
		while (temp_cuv != NULL)
		{
			adauga(temp_cuv, cuvinte2, apar2, nr_cuv2);
			temp_cuv = strtok(NULL, " \"\',!?");
		}
	}

	int nr_cuv = MIN( (*nr_cuv1) , (*nr_cuv2) ); //atentie este intreg nu pointer

	//facem spatiu pentru combinatia cuvant-aparitie
	structura *structura1 = (structura *)malloc(*nr_cuv1 * sizeof(structura));
	if (structura1 == NULL) return 1;
	structura *structura2 = (structura *)malloc(*nr_cuv2 * sizeof(structura));
	if (structura2 == NULL) return 1;

	for (i = 0 ; i < (*nr_cuv1) ; i++)
	{
		structura1[i].cuvant = cuvinte1[i];
		structura1[i].aparitii = apar1[i];
	}
	for (i = 0 ; i < (*nr_cuv2) ; i++)
	{
		structura2[i].cuvant = cuvinte2[i];
		structura2[i].aparitii = apar2[i];
	}

	qsort(structura1, *nr_cuv1, sizeof(structura), compare);
	qsort(structura2, *nr_cuv2, sizeof(structura), compare);


	sim(structura1, structura2, nr_cuv, *nr_cuv1, *nr_cuv2);

	return 0;
}
