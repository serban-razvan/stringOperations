#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void parse(char *expresie)
{
	int i = 0;
	while (i < strlen(expresie))
	{
		//daca avem * langa *
		if ((expresie[i] == '*') && (expresie[i+1] == '*'))
		{
			//shiftam de toate caracterele cu o pozitie inapoi
			memcpy(&expresie[i], &expresie[i+1], strlen(&expresie[i+1])+1);
		}
		else
		{
			//mergem mai departe cu cautatul
			i++;
		}
	}
}


long regex(char * cuvant, char * expresie)
/*returneaza 0 daca expresia nu se potriveste pe cuvant
**returneaza 1 daca expresia se potriveste
**actioneaza recursiv
*/
{
	int i = 0;


	if ((strcmp(expresie,"") == 0) && (strcmp(cuvant,"") == 0)){
		return 1;
	}

	if (strcmp(expresie,"") == 0){
		return 0;
	}



	if (expresie[0] == '.') //cazul 1
	{
		if (strcmp(cuvant,"") == 0) //daca am ajuns la finalul cuvantului
		{
			return 0;
		}
		// scapam de punct si de prima litera din cuvant
		return regex(cuvant + 1, expresie + 1);
	}
	else{
		if (expresie[0] == '*') //cazul 2
		{
			for (i = 0 ; i <= strlen(cuvant) ; i++)
			{
				//scapam de steluta si luam fiecare combinatie de cuvant
				if (regex(cuvant + i, expresie + 1))
				{
					return 1;
				}
			}
			return 0;
		}
		else
		{
			if (cuvant[0] == expresie[0]) //cazul 3 daca e litera/cifra
			{
				return regex(cuvant + 1, expresie + 1);
			}
			else
			{
				return 0;
			}
		}
	}


}


int main()
{
	long N, i;
	scanf("%li\n", &N);
	char **strarray = (char **)malloc(N * sizeof(char *));
	if (strarray == NULL) return 1;

	for (i = 0 ; i < N ; i++)
	{
		char *temp_pointer = (char *)malloc(16000 * sizeof(char));
		if (temp_pointer == NULL) return 1;

		fgets(temp_pointer, 14000, stdin);

		if (strcmp(temp_pointer, "\n") == 0)
		{
			//daca e doar o linie goala
			//scap de newline facandu-l sir vid
			temp_pointer[0] = '\0';
		}
		else
		{
			//scap de newline
			strtok(temp_pointer, "\n");
		}
		strarray[i] = realloc(temp_pointer, strlen(temp_pointer) * sizeof(char) + 1);
		if (strarray[i] == NULL) return 1;
	}


	char *temp_pointer = (char *)malloc(16000 * sizeof(char));
	if (temp_pointer == NULL) return 1;
	char *expresie = (char *)malloc(16000 * sizeof(char));
	if (expresie == NULL) return 1;
	char *cuvant = (char *)malloc(2000 * sizeof(char));
	if (cuvant == NULL) return 1;



	long nr_regex;
	int linie;

	long rezultat;

	scanf("%li\n", &nr_regex);


	for (i = 0 ; i < nr_regex ; i++)
	{
		fgets(expresie, 14000, stdin);
		strtok(expresie, "\n"); //scapam de newline
		parse(expresie); //scapam de multiple *

		rezultat = 0;

		for (linie = 0 ; linie < N ; linie++)
		{
			//pentru fiecare rand
			strcpy(temp_pointer, strarray[linie]);
			cuvant = strtok(temp_pointer, " \"\',!?");
			while (cuvant != NULL)
			{
				if (regex(cuvant, expresie))
				{
					rezultat++;
				}
				cuvant = strtok(NULL, " \"\',!?");
			}
		}
		printf("%li\n", rezultat);
	}


	return 0;
}
