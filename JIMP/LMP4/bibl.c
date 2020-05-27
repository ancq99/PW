#include "bibl.h"              

#include <stdlib.h>
#include <stdio.h>
#include <math.h>                                   
              
                                                                          
int                                                                          
read(FILE * p, double v[], int max_l_e)                                      
{                                                                            
        int             n, i;                         

       if (fscanf(p, "%i", &n) != 1 || n <= 0 || n > max_l_e) {
	       return -1;
        }
        while ((i = fgetc(p)) == ' ')  
                ;

        
        if (i != '[')
                return -1;  

        for (i = 0; i < n; i++)
                if (fscanf(p, "%lf", &(v[i])) != 1)    
			return -1;      /* to znaczy, ze format pliku jest
                                         * zly */

        /* mamy liczby, teraz szukamy zamykajacego nawiasu: */
        while ((i = fgetc(p)) == ' ')   /* pomijamy spacje */
                ;

        /* mamy znak rozny od spacji - powinien to byc znak ']' */
        if (i != ']')
                return -1;      /* nie jest - bledny format pliku */

        /*
         * jesli doszlismy juz tu, to wszystko jest ok, mamy w wektorze n
         * liczb
         */
        return n;
}

/*
 * L2: oblicza norme L2 (pierwiastek z sumy kwadratow) wektora double v[] o
 * dlugosci n
 */
double
L2(double v[], int n)
{
        int             i;
        int             l2 = 0; /* wazne jest, aby nadac l2 wartosc
                                 * poczatkowa */
        for (i = 0; i < n; i++)
                l2 += v[i] * v[i];
        return sqrt(l2);
}

/*
 * dot_product: oblicza iloczyn skalarny wektorow double v[] i u[] v i u maja
 * dlugosc n
 */
double
dot_product(double v[], double u[], int n)
{
        int             i;
        double           dp = 0; /* wazne jest, aby nadac dp wartosc
                                 * poczatkowa */
        for (i = 0; i < n; i++)
                dp += v[i] * u[i];
        return dp;
}

double norma_max(double v[], int n)
{
	double maxi = 0.0;
	for(int i = 0; i < n; i++)
	{
		if(fabs(v[i]) > maxi)
			maxi = fabs(v[i]);
		}

	return maxi;
}


void mnozenie_przez_liczbe(double *v, int n, int mnoznik)
{
	for(int i = 0; i < n; i++)
	{
		*v = *v * mnoznik;
		v++;
	}
}

void dodawanie_wektorow(double *v, double *u, int dl1, int dl2)
{
	if(dl1 == dl2)
	{
		for(int i = 0; i < dl1; i++)
		{
			*v += *u;
			v++;
			u++;
		}
	}
	else
	{
		printf("Wektory sa roznej dlugosci");
	}
}

void normalizacja(double *v, int n, double l2)
{
	if(l2 != 0){
		for(int i = 0; i < n ; i++)
		{
			*v /= l2;
			v++;
		}
	}else {
		printf("L2 = 0");
	}
}

int save(FILE * s, double v[], int max_l_e)
{	
	if(s == NULL)
	{	
		printf("Brak nazwy pliku");
		return 1;
	} else {
		fprintf(s,"[");
		for(int i = 0; i < max_l_e; i++)
			fprintf(s,"%f ",v[i]);
		fprintf(s,"]\n");
	}
}


