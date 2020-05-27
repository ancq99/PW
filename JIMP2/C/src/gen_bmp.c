//plik odpowiedzialny za generacje bitmapy

#include "cfg.h"

//generacja bitmapy
void gen_bmp(char **trawnik, bmp_img img, int liczba_k, int liczba_w)
{
	int sum = 0, pix = 0, sum2 = 0;

	//obliczenie sredniej
	for (int i = 0; i < liczba_w * 100; i++)
		for (int j = 0; j < liczba_k * 100; j++)
			if (trawnik[i][j] >= 0)
			{
				sum += trawnik[i][j];
				pix++;
			}
	double avg = sum / pix;

	//odchylenie standardowe uzywane do "kolorowania"
	for (int i = 0; i < liczba_w * 100; i++)
		for (int j = 0; j < liczba_k * 100; j++)
			if (trawnik[i][j] >= 0)
				sum2 += pow(trawnik[i][j] - avg, 2);

	double odch = sqrt(sum2 / pix);
	double pom;

	//kolorowanie
	for (int i = 0; i < liczba_w * 100; i++)
		for (int j = 0; j < liczba_k * 100; j++)
		{
			if (trawnik[i][j] > 0)
			{
				pom = trawnik[i][j] - odch;
				if (pom >= -40)
					bmp_pixel_init(&img.img_pixels[i][j], 255, 38, 38);
				if (pom <= -30 && pom > -40)
					bmp_pixel_init(&img.img_pixels[i][j], 255, 82, 38);
				if (pom <= -20 && pom > -30)
					bmp_pixel_init(&img.img_pixels[i][j], 255, 156, 55);
				if (pom <= -10 && pom > -20)
					bmp_pixel_init(&img.img_pixels[i][j], 255, 222, 88);
				if (pom < 0 && pom > -10)
					bmp_pixel_init(&img.img_pixels[i][j], 139, 255, 88);
				if (pom >= 0 && pom < 10)
					bmp_pixel_init(&img.img_pixels[i][j], 80, 250, 161);
				if (pom >= 10 && pom < 20)
					bmp_pixel_init(&img.img_pixels[i][j], 77, 255, 244);
				if (pom >= 20 && pom < 30)
					bmp_pixel_init(&img.img_pixels[i][j], 77, 208, 255);
				if (pom >= 30 && pom < 40)
					bmp_pixel_init(&img.img_pixels[i][j], 68, 118, 255);
				if (pom >= 40)
					bmp_pixel_init(&img.img_pixels[i][j], 0, 0, 255);
			}
		}
	bmp_img_write(&img, "out_bmp.bmp");
}

//tworzenie bitmapy
void create_bmp(char **tab, bmp_img img, int liczba_k, int liczba_w)
{
	int pom1 = 0;
	int pom2 = 0;

	for (int l = 0; l < liczba_w * 100; l++)
	{
		for (int k = 0; k < liczba_k * 100; k++)
		{
			if (pom1 == liczba_w)
				break;
			if (tab[pom1][pom2] == '*' || tab[pom1][pom2] == '\n')
				bmp_pixel_init(&img.img_pixels[l][k], 252, 255, 137);
			else
				bmp_pixel_init(&img.img_pixels[l][k], 0, 0, 0);

			if ((k % 100) % 99 == 0 && k % 100 != 0)
				pom2++;
			if (liczba_k * 100 - 1 == k && k > 10)
				pom2 = 0;
		}
		if ((l % 100) % 99 == 0 && l % 100 != 0)
			pom1++;
	}
}
