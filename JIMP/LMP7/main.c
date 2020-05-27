#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab_dyn.h"
#include "skorowidz.h"

#define BUFSIZE 8192

int main(int argc, char *argv[])
{
	int i, ile_linii;
	char buf[BUFSIZE];

	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;

	skorowidz_t skorowidz;
	zainicjuj_skorowidz(argc, argv, &skorowidz);

	if(skorowidz.ile_slow == 0)
	{
		fprintf(stderr, "%s: blad, prosze podac slowa do wyszukiwania.\n", argv[0]);
		return EXIT_FAILURE;
	}

	if(in == NULL)
	{
		fprintf(stderr, "%s: blad, nie moge czytac pliku: %s", argv[0], argv[1]);
		return EXIT_FAILURE;
	}

	char c;
	int ile_wyrazow = 0;
	while((c = fgetc(in)) != EOF) {
        if(c == ' ' || c=='\n')
            ile_wyrazow++;
    	}
	
	
	ile_linii = 0;
	
	fseek(in, 0 , SEEK_SET);
	while(fgets(buf, BUFSIZE, in) != NULL)
	{
		int ilosc_elementow = 0;
		ile_linii++;
		char * schowek;
		schowek = strtok(buf, " \n");
		int napotkane[skorowidz.ile_slow];
		
		for(i = 0; i < skorowidz.ile_slow; i++)
			napotkane[i] = 0;

		while(schowek != NULL)
		{	
	       		
			 for(i = 0; i < skorowidz.ile_slow; i++)
			 {
				 if(strcmp(schowek, skorowidz.slowa[i]) == 0 && napotkane[i] == 0)
				 {
					 dodaj_pozycje_skorowidza(&skorowidz, i, ile_linii, ile_wyrazow);
					 napotkane[i]++;
				 	
				 }
			
			 }
			 
		 schowek = strtok(NULL, " \n");
		 }
	}

	wypisz_skorowidz(&skorowidz, ile_wyrazow);

	return EXIT_SUCCESS;
}
