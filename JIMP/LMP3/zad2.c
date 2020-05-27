#include <stdio.h>

int usun_ujemne(double tab[], int n)
{                                  	
	
	int j=0;
        for(int i = 0; i<n ; i++){
		if(tab[i]>=0)
			tab[j++]=tab[i];
	}
	return j;
}

void pwekt(double *v, int n)
{
        printf("[ ");
        while (n--) {
                printf("%g ", *v);
                v++;
        }
        printf("]");
}

int main()
{
        double          v[] = {-10, 0, 10, -20, 30, 1.1, -2.2, -3.3, 300.003, 1024.5};
        int             n = sizeof v / sizeof v[0];

        printf("Wektor: ");
        pwekt(v, n);
        printf(" (%d elementow)\n", n);

        int k = usun_ujemne(v, n);

        printf("Wektor po usunieciu ujemnych elementow: ");
        pwekt(v, k);
        printf(" (%d elementow)\n", k);

        return 0;
}
