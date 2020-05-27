#include "cfg.h"
//tworzy tablice na podstawie otrzymanego pliku
char **gen_tab(FILE *in, int liczba_k, int liczba_w)
{
	char **tab;
	char tmp;
	int n = 0;
	int m = 0;
	tab = malloc(sizeof(*tab) * (liczba_w));
	for (int i = 0; i < liczba_w; i++)
		tab[i] = malloc(sizeof(*tab) * (liczba_k));

	while (fscanf(in, "%c", &tmp) == 1)
	{
		if (tmp != '\n')
		{
			if (n != liczba_w)
				tab[n][m++] = tmp;
			else
				break;
			if (m == liczba_k && n < liczba_w)
			{
				m = 0;
				n++;
			}
		}
	}
	return tab;
}

//tworzy tablice trawnika na podstawie tablicy
char **gen_trawnik(char **tab, int liczba_k, int liczba_w)
{
	int pom1 = 0;
	int pom2 = 0;
	char **trawnik;

	trawnik = malloc(sizeof(*tab) * liczba_w * 100);
	for (int i = 0; i < liczba_w * 100; i++)
		trawnik[i] = malloc(sizeof(*trawnik) * liczba_k * 100);

	for (int l = 0; l < liczba_w * 100; l++)
	{
		for (int k = 0; k < liczba_k * 100; k++)
		{
			if (pom1 == liczba_w)
				break;

			if (tab[pom1][pom2] == '*' || tab[pom1][pom2] == '\n')
				trawnik[l][k] = 0;
			else
				trawnik[l][k] = -99;

			if ((k % 100) % 99 == 0 && k % 100 != 0)
				pom2++;

			if (liczba_k * 100 - 1 == k && k > 10)
				pom2 = 0;
		}
		if ((l % 100) % 99 == 0 && l % 100 != 0)
			pom1++;
	}
	return trawnik;
}

//funckja odpowiedzialna za plik wyjsciowy zawierajacy bitmape w wersji txt
void gen_bmp_txt(char **trawnik, FILE *out, int liczba_k, int liczba_w)
{
	for (int i = 0; i < liczba_w * 100; i++)
	{
		for (int j = 0; j < liczba_k * 100; j++)
			fprintf(out, "%i ", trawnik[i][j]);

		fprintf(out, "\n");
	}
	fclose(out);
}

//funckja tworzaca plik z rozmieszczeniem podlewaczek
void pod_out(FILE *out, int y, int x, char *typ, char *dir)
{
	fprintf(out, "%s:	%s	%i x %i\n", typ, dir, x, y);
}
