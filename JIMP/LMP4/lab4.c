#include <stdio.h>
#include <stdlib.h>
#include "bibl.h"


int main(int argc, char *argv[])
{
        double w_1[10];
        double  w_2[10];
        int n1;
        int n2;
        int i;
	
	if(argc !=3){
	       	printf("Podano złą ilość argumentów. Przeczytaj plik README.txt\n");	
		return 1;
	}else if(atoi(argv[1]) <= 0 || atoi(argv[1]) > 4 || atoi(argv[2]) != 0){
		printf("Podano błędne argumenty lub podano je w złej kolejności. Przeczytaj plik README.txt\n");
		return 1;
	}

	int nr = argc  > 1 ? atoi(argv[1]) : 1;

        FILE *we = argc > 2 ? fopen(argv[2], "r") : stdin; 

        if (we == NULL) { 
                fprintf(stderr, "Plik wejsciowy %s nie istnieje!\n", argv[1]);
                exit(1);
        }
        n1 = read(we, w_1, 10);

        if (n1 > 0) {
                printf("Wczytano %i-elementowy wektor:\n( ", n1);
                for (i = 0; i < n1; i++)
                        printf("%f ", w_1[i]);
                printf(")\n");
        } else {
                fprintf(stderr, "Wystapil blad przy wczytywaniu wektora: kod bledu=%i\n", n1);
                return 1;
        }

        printf("Norma L2 wczytanego wektora = %f\n", L2(w_1, n1));

        n2 = read(we, w_2, 10); 

        if (n2 > 0) {
                printf("Wczytano %i-elementowy wektor:\n( ", n2);
                for (i = 0; i < n2; i++)
                        printf("%f ", w_2[i]);
                printf(")\n");
        } else {
                fprintf(stderr, "Wystapil blad przy wczytywaniu wektora: kod bledu=%i\n", n2);
                return 1;
        }

        printf("Norma L2 wczytanego wektora = %f\n", L2(w_2, n2));

        if (n1 == n2 ) {
                printf("Iloczyn skalarny wczytanych wektorow = %f\n", dot_product(w_1, w_2, n1));
        } else {
                printf("Wczytane wektory maja rozna dlugosci i nie mozna ich pomnozyc przez siebie\n" );
        }
	printf("--------------------------\n");
	float m;
	switch(nr)
	{
		case 1:
			printf("Norma max w1: %lf\n", norma_max(w_1, n1));
			printf("Norma max w2: %lf\n", norma_max(w_2, n2));
			break;
		case 2:
			printf("Wybrano mnozenie wektorow przez liczbe\nPodaj mnoznik: ");
			scanf("%f",&m);
			mnozenie_przez_liczbe(&w_1[0], n1, m);
			mnozenie_przez_liczbe(&w_2[0], n2, m);
			break;
		case 3:
			printf("Wybrano dodawanie wektorow\n");
			dodawanie_wektorow(&w_1[0], &w_2[0], n1, n2);
			break;
		case 4:
			printf("Wybrano normalizcaje wektorow\n");
		       	normalizacja(&w_1[0], n1, L2(w_1, n1));
		       	normalizacja(&w_2[0], n2, L2(w_2, n2));	
			break;
	}
	if(nr == 2 || nr == 3 ||  nr == 4){
	        if(nr == 3){
			printf("Wektor po modyfikacji\n");
			for(int i = 0 ; i < n1 ; i++)
	                        printf("%f ", w_1[i]);
		} else {
			printf("Wektory po modyfikacji\nw1\n");
			for(int i = 0 ; i < n1 ; i++)
        	        	printf("%f ", w_1[i]);
	       		printf("\n--------------------\nw2\n");
        		for(int i = 0 ; i < n2 ; i++)
                		printf("%f ", w_2[i]);
		}
		printf("\n");
	}
	
	printf("Podaj nazwę pliku do zapisu wektorów\n");
	char *txt;
	scanf("%s",txt);
	FILE * sp = fopen(txt,"w");
	if(nr == 3){
		save(sp, w_1, n1);
	} else {
		save(sp, w_1, n1);
		save(sp, w_2, n2);
	}
	printf("Wektory zapisano do pliku %s\n", txt);
	
	return 0;
}
