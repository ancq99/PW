#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double minimum(double a[], int n)
{
	double pom=a[0];
	for(int i=0;i<n;i++)
	{
		if(a[i]<pom)
			pom=a[i];
	}
	return pom;
}

double euqlides(double a[], int n)
{
	double sum_kw = 0;
	for(int i=0;i<n;i++)
	{
		sum_kw+=(a[i]*a[i]);
	}
	return sqrt(sum_kw);
}

int main(int argc, char *argv[])
{	
	double *tab;	
	FILE	*in=argc>1?fopen(argv[1],"r"):stdin;
	if(in != NULL)
	{
		double x;
		int n=0;
		while(fscanf(in,"%lf" ,&x)==1){
			tab[n] = x;
			n++;	
		}
	fclose(in);	
	printf("Wartosc minmalna = %f\n",minimum(tab,n));
	printf("Dlugosc euqlidesowa = %f\n",euqlides(tab,n)); 
	return 0;
	}else
		return 1;
}
