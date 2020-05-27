#ifndef skorowidz_h
#define skorowidz_h
#include "tab_dyn.h"

typedef struct
{
	int ile_slow;
	char **slowa;
	int *licznik;	
	int **linie;

} skorowidz_t;

void zainicjuj_skorowidz(int argc, char **argv, skorowidz_t *s);
void dodaj_pozycje_skorowidza(skorowidz_t *skorowidz, int i, int linia, int ilosc_elementow);
void wypisz_skorowidz(skorowidz_t *s, int ile);

#endif
