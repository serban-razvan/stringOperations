#include<stdio.h>
#include<string.h>
#include<stdlib.h>



void printare(char **strarray, long N)
{
	int i;
	for (i = 0 ; i < N ; i++)
	{
		printf("%s\n", strarray[i]);
	}
}

int one_of(char *caracter)
{
	char *poi = NULL;
	poi = strchr(" \"\',!?", *caracter);
	if (poi)
	{
		return 1;
	}
	else
	{
		if (*caracter == '\0')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int op_1(char **strarray, long N)
{
	//sa fim siguri am zis ca un cuvant are 1000 caractere
	char *cuvant = (char *)malloc(1000 * sizeof(char));
	char *buffer = (char *)malloc(16000 * sizeof(char));
	char *temp = (char *)malloc(1000 * sizeof(char));
	long i, count = 0;
	if (cuvant == NULL) return 1;
	if (buffer == NULL) return 1;
	if (temp == NULL) return 1;


	scanf("%s", cuvant);

	for (i = 0 ; i < N ; i++)
	{
		strcpy(buffer, strarray[i]);
		temp = strtok(buffer, " \"\',!?");
		while (temp != NULL)
		{
			if (strcmp(temp, cuvant) == 0)
			{
				count++;
			}
			temp = strtok(NULL, " \"\',!?");
		}
	}

	printf("%li\n", count);
	return 0;

}


int op_2(char **strarray, long N)
{
	char *cuvant1 = (char *)malloc(1000 * sizeof(char));
	char *cuvant2 = (char *)malloc(1000 * sizeof(char));
	if (cuvant1 == NULL || cuvant2 == NULL) return 1;

	scanf("%s", cuvant1);
	scanf("%s", cuvant2);



	int i;
	char *gasit = NULL;
	char *buffer = NULL;
	char *temp = NULL;
	char *offset = NULL;



	for (i = 0 ; i < N ; i++)
	{
		offset = strarray[i];
		do
		{
			gasit = strstr(offset, cuvant1);

			if (gasit != NULL)
			{
				if (one_of(gasit-1) && one_of(gasit + strlen(cuvant1)))
				{
					//daca e cuvant(incadrat de necifre si nelitere)

					buffer = (char *)malloc(16000 * sizeof(char));
					if (buffer == NULL) return 1;

					//ia toate caracterele pana la primul gasit
					memcpy(buffer,
						   strarray[i],
						   gasit-strarray[i]);

					//baga cuvantu 2
					memcpy(buffer + (gasit - strarray[i]),
						   cuvant2,
						   strlen(cuvant2));

					//ia toate caracterele dupa cuvantul 1
					strcpy(buffer + (gasit-strarray[i]) + strlen(cuvant2),
						   gasit + strlen(cuvant1));

					strarray[i] = realloc(buffer, strlen(buffer) * sizeof(char) + 1);
					if (strarray[i] == NULL) return 1;

					// reincepem cautarile de la inceput
					offset = strarray[i];

				}
				else
				{
					//daca e gasit dar nu e cuvant
					if (offset < strarray[i] + strlen(strarray[i]))
					{
						offset++; //mergem cu cautarea mai departe
					}
				}
			}
		} while (gasit);
	}

	printare(strarray, N);
	return 0;

}

int rot_word(char *line, int start, int end, long perm)
{
	//facem permutarile mai mici, nu folosim numere mari
	//facem modulo cu lungimea cuvantului
	perm = perm % (end - start);

	char *buffer = (char *)malloc((end - start + 1) * sizeof(char));
	if (buffer == NULL) return 1;

	memcpy(buffer, line + end - perm, perm);
	memcpy(buffer + perm, line + start, end - start - perm);
	memcpy(line + start, buffer, end - start);
}

int op_3(char **strarray, long N)
{
	long perm;
	scanf("%li", &perm);

	int i, j;

	int inceput;

	int stare = 0; //0-nu suntem in cuvant 1-suntem in cuvant
	for (i = 0 ; i < N ; i++)
	{
		for (j = 0 ; j <= strlen(strarray[i]) ; j++)
		{
			// <= pt ca luam si backslash 0

			if (stare == 0)
			{
				if ( ! (one_of(&strarray[i][j])) )
				{
					//daca am ajuns la un cuvant;
					inceput = j;
					stare = 1;
				}
			}
			else //daca stare==1
			{
				if (one_of(&strarray[i][j]))
				{
					stare = 0;
					rot_word(strarray[i], inceput, j, perm);

				}
			}
		}
	}
	printare(strarray, N);
	return 0;

}

int main()
{

	long N, i;
	scanf("%li\n", &N);
	char **strarray = (char **)malloc(N * sizeof(char *));
	if (strarray == NULL) return 1;

	for (i = 0 ; i < N ; i++)
	{
		//sa fim siguri in cazuri de linii lungi
		char *temp_pointer = (char *)malloc(16000 * sizeof(char));
		if (temp_pointer == NULL) return 1;

		fgets(temp_pointer, 14000, stdin);

		if (strcmp(temp_pointer, "\n") == 0)
		{
			//daca e doar o linie goala
			temp_pointer[0]='\0'; //scap de newline
		}
		else
		{
			//scapam de trailing newline de la fgets
			//intr-un mod mai scurt si concis
			strtok(temp_pointer, "\n");
		}

		strarray[i] = realloc(temp_pointer, strlen(temp_pointer) * sizeof(char) + 1);
		if (strarray[i] == NULL) return 1;
	}

	int nr_op, op, j, rezultat;
	scanf("%d", &nr_op);
	for (j=0 ; j < nr_op ; j++)
	{
		scanf("%d", &op);
		switch(op)
		{
			case 1:
				rezultat = op_1(strarray, N);
				break;
			case 2:
				rezultat = op_2(strarray, N);
				break;
			case 3:
				rezultat = op_3(strarray, N);
				break;
			default:
				return 1;
		}
		if (rezultat) return 1; //nu s-a alocat memoria cum trebuie
	}

	return 0;
}
