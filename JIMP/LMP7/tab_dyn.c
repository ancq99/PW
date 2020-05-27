#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab_dyn.h"

void dodaj_element_do_tablicy(int **tab,int i, int n , int ile)
{
	tab = realloc(tab, sizeof(*tab)+1);
	tab[i] = realloc(tab[i], ile*sizeof(*tab[i]));
	
	for(int x = 0 ; x < ile ; x++)
		if(tab[i][x] != 0)
			continue;
		else{
			tab[i][x] = n;
			break;
		}


	
}
	
