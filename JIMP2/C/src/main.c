#include "cfg.h"

//srednice podelwaczek
#define r360 100
#define r270 200
#define r180 300
#define r90 400

int main(int argc, char *argv[])
{
	char **tab;
	char **trawnik;
	int liczba_k = 0;
	int liczba_w = 0;
	int cykle = argc > 2 ? atoi(argv[2]) : 1;
	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
	FILE *bmptxt = fopen("out_bmp_txt.txt", "w");

	if (in != NULL)
	{
		//odczyt wumiarow trawnika

		if (fscanf(in, "%i", &liczba_k) == 1 && fscanf(in, "%i", &liczba_w) == 1)
		{
			if (liczba_k == 0 || liczba_w == 0 || liczba_k > 80 || liczba_w > 40)
			{
				printf("NIE PODANO ROZMAIRU TRAWNIKA LUB PODANY WYMIAR JEST BLEDNY!\n");
				return -1;
			}
		}
		else
		{
			printf("NIE UDALO POBRAC SIE ROZMIARU TRAWNIK\n");
			return -1;
		}

		printf("Wymiary trawnika: %ix%i\nIlosc cykli: %i\n", liczba_k, liczba_w, cykle);

		if (cykle <= 0)
		{
			printf("BLEDNA ILOSC CYKLI PODLEWANIA\n");
			return -1;
		}

		//generacja trawik
		tab = gen_tab(in, liczba_k, liczba_w);
		trawnik = gen_trawnik(tab, liczba_k, liczba_w);

		//generacja bmp
		bmp_img img;
		bmp_img_init_df(&img, liczba_k * 100, liczba_w * 100);
		create_bmp(tab, img, liczba_k, liczba_w);
		get_k_w(liczba_k, liczba_w);
		get_k_w2(liczba_k, liczba_w);

		//podlewanie
		kraw_zew_90(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
		kraw_zew_180(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
		kraw_wew_270(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
		kraw_wew_180(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
		kraw_360(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
		odbicia(trawnik, r360, r270, r180, r90);

		//cykle
		for (int i = 0; i < liczba_w * 100; i++)
			for (int j = 0; j < liczba_k * 100; j++)
				if (trawnik[i][j] > 0)
					trawnik[i][j] *= cykle;

		//bitmapa
		gen_bmp(trawnik, img, liczba_k, liczba_w);
		gen_bmp_txt(trawnik, bmptxt, liczba_k, liczba_w);

		bmp_img_free(&img);
		fclose(bmptxt);
		fclose(in);
		free(trawnik);
		free(tab);

		return 0;
	}
	else
		printf("PLIK JEST PUSTY LUB NIE ISTNIEJE");
	return 1;
}
