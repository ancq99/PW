#include <stdio.h>
#include <stdlib.h>
#include "skorowidz.h"
#include "tab_dyn.h"

void zainicjuj_skorowidz(int argc, char **argv, skorowidz_t * skorowidz)
{
	int i;
	skorowidz->ile_slow = argc - 2;
	skorowidz->linie = malloc( sizeof(*skorowidz->linie));
	skorowidz->licznik = malloc(skorowidz->ile_slow * sizeof * skorowidz->licznik);
	skorowidz->slowa = malloc(skorowidz->ile_slow * sizeof * skorowidz->slowa);
	
	for(int i = 0 ; i < 100 ; i++){
		if(skorowidz->linie[i] == NULL)
			break;
		skorowidz->linie[i]= malloc(100*sizeof(*skorowidz->linie[i]));
	}

	for(i = 2; i < argc; i++)
	{
		skorowidz->slowa[i-2] = argv[i];
		skorowidz->licznik[i-2] = 0;
		
	}

}

void dodaj_pozycje_skorowidza(skorowidz_t *skorowidz, int i, int linia, int ilosc_elementow)
{
	skorowidz->licznik[i]++;
	dodaj_element_do_tablicy(skorowidz->linie, i,linia, ilosc_elementow);
}

void wypisz_skorowidz(skorowidz_t *skorowidz, int ile)
{
	int i, j;
	for(i = 0; i < skorowidz->ile_slow; i++)
	{
		if(skorowidz->licznik[i] > 0)
		{
		
			printf("Slowo \"%s\" wystapilo w liniach: ", skorowidz->slowa[i]);
			
			
			
			for(int j = 0 ; j <  ile; j++)
			{
				if(skorowidz->linie[i][j] != 0)
					printf("%d, ", skorowidz->linie[i][j]);
			}

			printf("\n");
		}
		else
		{
			printf("Nie napotkano slowa \"%s\"\n", skorowidz->slowa[i]);
		}

	}
}
