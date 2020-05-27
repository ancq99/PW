#include "cfg.h"

int liczba_k, liczba_w;
FILE *out;

void get_k_w(int x, int y) //pobranie wymiarow trawnika oraz pomoc w formacie pliku z rozmieszczeniem podlewaczek
{
	liczba_k = x * 100;
	liczba_w = y * 100;
	out = fopen("podlewaczki_txt.txt", "w");
	fprintf(out, "Krawedzie\n");
}

int test(char **trawnik, int x, int y, int r) //sprawdza od wspolrzednych x i y, jak duzy obszar jest jeszcze niepodlany. Obszar sprawdzany a ksztalt kwadratu oraz jest zalezy od promienia podlewaczki
{
	for (int i = x - r / 10; i < x + r / 10; i++)
		for (int j = y - r / 10; j < y + r / 10; j++)
			if (j >= 0 && i >= 0 && j < liczba_k - 10 && i < liczba_w - 10)
				if (trawnik[i][j] > 5)
				{
					return 2;
				}
	for (int i = x - r / 6; i < x + r / 6; i++)
		for (int j = y - r / 6; j < y + r / 6; j++)
			if (j >= 0 && i >= 0 && j < liczba_k - 10 && i < liczba_w - 10)
				if (trawnik[i][j] > 5)
				{
					return 1;
				}

	return 0;
}
int test_360(char **trawnik, int x, int y, int r, int k) //specjalna wersja testu dla podlewaczek o zasiegu 360*
{
	if (k == 0)
		for (int i = x - r / 3.5; i < x + r / 3.5; i++)
			for (int j = y - r / 3.5; j < y + r / 3.5; j++)
				if (j >= 0 && i >= 0 && j < liczba_k - 1 && i < liczba_w - 1)
					if (trawnik[i][j] > 5)
					{
						return 1;
					}
	if (k == 1)
		for (int i = x - r / 7; i < x + r / 7; i++)
			for (int j = y - r / 7; j < y + r / 7; j++)
				if (j >= 0 && i >= 0 && j < liczba_k - 1 && i < liczba_w - 1)
					if (trawnik[i][j] > 5)
					{
						return 1;
					}

	return 0;
}

void poj_360(char **trawnik, int j, int i, int r, int k) //wstawienie pojedynczej podlewaczki r360 w zaleznosci od miejsa
{
	for (int y = i - r / 2; y < i + r / 2; y++)
		for (int x = j - r / 2; x < j + r / 2; x++)

			if (pow(x - j, 2) + pow(y - i, 2) <= pow(r / 2, 2))
				if (y < liczba_w - 10 && y >= 0 && x < liczba_k - 10 && x >= 0 && k == 1 && trawnik[y][x] >= 0) //na katach wkleslych
					trawnik[y][x] += 13;
				else if (y < liczba_w - 10 && y >= 0 && x < liczba_k - 10 && x >= 0 && k == 2 && trawnik[y][x] >= 0 && i > y) // przy krawwedzi prostej wewnetrznej "od dolu"
					trawnik[y][x] += 20;
				else if (y < liczba_w - 10 && y >= 0 && x < liczba_k - 10 && x >= 0 && k == 3 && trawnik[y][x] >= 0 && i < y) //j.w "od gory"
					trawnik[y][x] += 20;
				else if (y < liczba_w && y >= 0 && x < liczba_k && x >= 0 && k == 0 && trawnik[y][x] >= 0) // przy krawedziach prostych zewnetrznych
					trawnik[y][x] += 20;
}

void kraw_zew_90(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90) //rogi trawnika
{
	//pierwsza podwojna petla iteruje po trawniku, druga sprawdza ktore punkty znajduja sie w okregu o danym promienu
	int pom = 0;
	char *dir;
	for (int i = 0; i < liczba_w * 100; i += liczba_w * 100 - 1)
		for (int j = 0; j < liczba_k * 100; j += liczba_k * 100 - 1)
			if (trawnik[i][j] >= 0 && trawnik[i][j] < 10)
			{
				if (pom == 0)
					dir = "SE";
				else if (pom == 1)
					dir = "SW";
				else if (pom == 2)
					dir = "NE";
				else if (pom == 3)
					dir = "NW";
				pom++;
				pod_out(out, i, j, "r90", dir);
				for (int y = i - r90 / 2; y < i + r90 / 2; y++)
					for (int x = j - r90 / 2; x < j + r90 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0)
							if (pow(x - j, 2) + pow(y - i, 2) <= pow(r90 / 2, 2))
								trawnik[y][x] += 10;
			}
}

void kraw_zew_180(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90) //krawedzie proste zewnetrzne
{
	//pierwsza petla iteruje po trawniku, druga sprawdza ktore punkty znajduja sie w okregu o danym promienu
	for (int j = 0; j < liczba_k * 99; j += 10) // krawedzie poziome
	{
		if (trawnik[0][j] >= 0)
		{
			int x_j = 0;
			int pom = 0;

			for (int k = j; k < j + r270; k++) //tworzenie zmiennej w celu prawidlowego rozmieszczenia podlewaczek bez nakladania sie na siebie
			{
				if (k >= 0 && k < liczba_k * 100 && trawnik[2][k] == 0)
					x_j = j + r180 / 2;

				break;
			}
			pom = test(trawnik, 0, x_j, r180); //test niepodleanego obszaru
			if (pom == 0)
			{
				pod_out(out, 0, x_j, "r180", "S");
				for (int y = -r180 / 2; y < r180 / 2; y++)
					for (int x = x_j - r180 / 2; x < x_j + r180 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[0][x_j] > -10)
							if (pow(x - x_j, 2) + pow(y, 2) <= pow(r180 / 2, 2))
								trawnik[y][x] += 10;
			}
			else
			{
				x_j = 0;
				for (int k = j; k < j + r360; j++) //anaglogicznie, tworzenie zmiennej w celu prawidlowego rozmieszczenia podlewaczek (inny promien) bez nakladania sie na siebie
				{
					if (k >= 0 && k < liczba_k * 100 && trawnik[2][k] == 0)
						x_j = j + r360 / 2;

					break;
				}
				if (test(trawnik, 0, x_j, r360) == 0) //test niepodlanego obszaru  dla innego promienia
				{
					poj_360(trawnik, x_j, 0, r360, 0);
					pod_out(out, 0, x_j, "r360", "S");
				}
			}
		}
		if (trawnik[liczba_w * 100 - 1][j] >= 0)
		{
			int x_j = 0;
			int pom = 0;

			for (int k = j; k < j + r270; k++)
			{
				if (k >= 0 && k < liczba_k * 100 && trawnik[liczba_w * 100 - 2][k] == 0)
					x_j = j + r180 / 2;

				break;
			}
			pom = test(trawnik, liczba_w * 100 - 1, x_j, r180);
			if (pom == 0)
			{
				pod_out(out, liczba_w * 100 - 1, x_j, "r180", "N");
				for (int y = liczba_w * 100 - 1 + r180 / 2; y > liczba_w * 100 - 1 - r180 / 2; y--)
					for (int x = x_j - r180 / 2; x < x_j + r180 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[liczba_w * 100 - 1][x_j] > -10)
							if (pow(x - x_j, 2) + pow(y - liczba_w * 100 - 1, 2) <= pow(r180 / 2, 2))

								trawnik[y][x] += 10;
			}
			else
			{
				x_j = 0;
				for (int k = j; k < j + r360; j++)
				{
					if (k >= 0 && k < liczba_k * 100 && trawnik[liczba_w * 100 - 1][k] == 0)
						x_j = j + r360 / 2;

					break;
				}
				if (test(trawnik, liczba_w * 100 - 1, x_j, r360) == 0)
				{
					poj_360(trawnik, x_j, liczba_w * 100, r360, 0);
					pod_out(out, liczba_w * 100 - 1, x_j, "r360", "N");
				}
			}
		}
	}

	for (int i = 0; i < liczba_w * 100 - r90 / 2; i += 10) //krawedzie pionowe
	{

		if (trawnik[i][0] >= 0)
		{
			int x_i = 0;
			int pom = 0;
			for (int k = i; k < i + r270; k++)
			{
				if (k >= 0 && k < liczba_k * 100 && trawnik[k][0] == 0)
					x_i = i + r180 / 2;

				break;
			}
			pom = test(trawnik, x_i, 0, r180);
			if (pom == 0)
			{
				pod_out(out, x_i, 0, "r180", "E");
				for (int y = x_i - r180 / 2; y < x_i + r180 / 2; y++)
					for (int x = -r180 / 2; x < r180 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[x_i][0] > -10)

							if (pow(x, 2) + pow(y - x_i, 2) <= pow(r180 / 2, 2))

								trawnik[y][x] += 10;
			}
			else
			{
				x_i = 0;
				for (int k = i; k < i + r360; k++)
				{
					if (k >= 0 && k < liczba_k * 100 && trawnik[k][0] == 0)
						x_i = i + r360 / 2;

					break;
				}
				if (test(trawnik, x_i, 0, r360) == 0)
				{
					poj_360(trawnik, 0, x_i, r360, 0);
					pod_out(out, x_i, 0, "r360", "E");
				}
			}
		}
		if (trawnik[i][liczba_k * 100 - 1] >= 0)
		{
			int x_i = 0;
			int pom = 0;

			for (int k = i; k < i + r270; k++)
			{
				if (k >= 0 && k < liczba_k * 100 && trawnik[k][liczba_k * 100 - 1] == 0)
					x_i = i + r180 / 2;

				break;
			}
			pom = test(trawnik, x_i, liczba_k * 100 - 1, r180);
			if (pom == 0)
			{
				pod_out(out, x_i, liczba_k * 100 - 1, "r180", "W");
				for (int y = x_i - r180 / 2; y < x_i + r180 / 2; y++)
					for (int x = liczba_k * 100 - 1 + r180 / 2; x > liczba_k * 100 - 1 - r180 / 2; x--)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[x_i][liczba_k * 100 - 1] > -10)
							if (pow(x - liczba_k * 100 - 1, 2) + pow(y - x_i, 2) <= pow(r180 / 2, 2))
								trawnik[y][x] += 10;
			}
			else
			{
				x_i = 0;
				for (int k = i; k < i + r360; k++)
				{
					if (k >= 0 && k < liczba_k * 100 && trawnik[k][liczba_k * 100 - 1] == 0)
						x_i = i + r360 / 2;

					break;
				}
				if (test(trawnik, x_i, liczba_k * 100 - 1, r360) == 0)
				{
					poj_360(trawnik, liczba_k * 100 - 1, x_i, r360, 0);
					pod_out(out, x_i, liczba_k * 100 - 1, "r360", "W");
				}
			}
		}
	}
	fprintf(out, "\nWenwnatrz\n"); //formatowanie pliku wyjsciowego z rozmieszczeniem podlewaczek
}

void kraw_wew_270(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90) //katy wklesle wenetrzne
{
	//pierwsza petla iteruje po trawniku, druga sprawdza ktore punkty znajduja sie w okregu o danym promienu
	for (int i = 99; i < liczba_w * 99; i++)
		for (int j = 99; j < liczba_k * 99; j++)
			if (trawnik[i][j] < -10)
			{
				if (trawnik[i + 1][j + 1] >= 0 && trawnik[i + 1][j] >= 0 && trawnik[i][j + 1] >= 0) //sprawdzamy czy jestesmy na rogu obszaru "niepodlewanego"
					if (trawnik[i + 1][j + 1] < 10)
					{
						int tmp = test(trawnik, i, j, r270); //  test ile miejsca nie podlane
						if (tmp == 0)
						{
							pod_out(out, i, j, "r270", "SE");
							for (int y = i - r270 / 2; y < i + r270 / 2; y++)
								for (int x = j - r270 / 2; x < j + r270 / 2; x++)
									if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[y][x] >= 0)
										if (pow(x - j, 2) + pow(y - i, 2) <= pow(r270 / 2, 2))
											trawnik[y][x] += 10;
						}
						else
						{
							if (test(trawnik, i, j, r360) == 0) // ponowny test, tym razem dla obszaru r360
							{
								pod_out(out, i, j, "r360", "SE");
								poj_360(trawnik, j, i, r360, 1);
							}
						}
					}

				if (trawnik[i - 1][j - 1] >= 0 && trawnik[i - 1][j] >= 0 && trawnik[i][j - 1] >= 0)
					if (trawnik[i - 1][j - 1] < 10)
					{
						int tmp = test(trawnik, i, j, r270);
						if (tmp == 0)
						{
							pod_out(out, i, j, "r270", "NW");
							for (int y = i - r270 / 2; y < i + r270 / 2; y++)
								for (int x = j - r270 / 2; x < j + r270 / 2; x++)
									if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[y][x] >= 0)
										if (pow(x - j, 2) + pow(y - i, 2) <= pow(r270 / 2, 2))
											trawnik[y][x] += 10;
						}
						else
						{
							if (test(trawnik, i, j, r360) == 0)
							{
								pod_out(out, i, j, "r360", "NW");
								poj_360(trawnik, j, i, r360, 1);
							}
						}
					}

				if (trawnik[i - 1][j + 1] >= 0 && trawnik[i - 1][j] >= 0 && trawnik[i][j + 1] >= 0)
					if (trawnik[i - 1][j + 1] < 10)
					{
						int tmp = test(trawnik, i, j, r270);
						if (tmp == 0)
						{
							pod_out(out, i, j, "r270", "NE");
							for (int y = i - r270 / 2; y < i + r270 / 2; y++)
								for (int x = j - r270 / 2; x < j + r270 / 2; x++)
									if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[y][x] >= 0)
										if (pow(x - j, 2) + pow(y - i, 2) <= pow(r270 / 2, 2))
											trawnik[y][x] += 10;
						}
						else
						{
							if (test(trawnik, i, j, r360) == 0)
							{
								pod_out(out, i, j, "r360", "NE");
								poj_360(trawnik, j, i, r360, 1);
							}
						}
					}

				if (trawnik[i + 1][j - 1] >= 0 && trawnik[i + 1][j] >= 0 && trawnik[i][j - 1] >= 0)
					if (trawnik[i + 1][j - 1] < 10)
					{
						int tmp = test(trawnik, i, j, r270);
						if (tmp == 0)
						{
							pod_out(out, i, j, "r270", "SW");
							for (int y = i - r270 / 2; y < i + r270 / 2; y++)
								for (int x = j - r270 / 2; x < j + r270 / 2; x++)
									if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0 && trawnik[y][x] >= 0)
										if (pow(x - j, 2) + pow(y - i, 2) <= pow(r270 / 2, 2))
											trawnik[y][x] += 10;
						}
						else
						{
							if (test(trawnik, i, j, r360) == 0)
							{
								pod_out(out, i, j, "r360", "SW");
								poj_360(trawnik, j, i, r360, 1);
							}
						}
					}
			}
}

void kraw_wew_180(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90) //krawedzie proste wewnetrzne
{
	//pierwsza petla iteruje po trawniku, druga sprawdza ktore punkty znajduja sie w okregu o danym promienu
	for (int i = 50; i < liczba_w * 99; i++)
		for (int j = 50; j < liczba_k * 99; j++)
			if (trawnik[i][j] < 0)
			{
				if (trawnik[i + 1][j] == 0 && trawnik[i][j + 1] < 0 && trawnik[i][j - 1] < 0) //sprawdzemy czy jestesmy na krawedzi pomiedzy obszrem podlewanym i nie podlewanym
				{
					int x_j = 0;
					int pom = 0;

					for (int k = j; k < j + r270; k++) // petla do stworzenia nowej zmiennej j, w celu rozmieszczenia podlewaczki bez nakladania sie na poprzednia
					{
						if (k >= 0 && k < liczba_k * 100 && trawnik[i + 2][k] == 0)
							x_j = j + r180 / 2 - 1;

						break;
					}
					pom = test(trawnik, i, x_j, r180); //test obszaru niepodlanego

					if (pom == 0 && x_j < liczba_k * 99)
					{
						if (trawnik[i + 1][x_j] == 0 && trawnik[i][x_j + 1] < 0 && trawnik[i][x_j - 1] < 0) //ponowne sprawdzenie krawedzi
						{
							pod_out(out, i, x_j, "r180", "S");
							for (int y = i - r180 / 2; y < i + r180 / 2; y++)
								for (int x = x_j - r180 / 2; x < x_j + r180 / 2; x++)
									if (y < liczba_w * 99 && y >= 0 && x < liczba_k * 99 && x >= 0 && i < y)
										if (trawnik[i][x_j] < 10 && trawnik[i + 1][x_j] >= 0)
											if (pow(x - x_j, 2) + pow(y - i, 2) <= pow(r180 / 2, 2))
												trawnik[y][x] += 10;
						}
					}
					else
					{
						x_j = 0;
						for (int k = j; k < j + r360; j++) //analogicznie, tworzenie zmiennej dla prawidlowej odleglosi miedzy podlewaczkami (inny promien podlewaczki)
						{
							if (k >= 0 && k < liczba_k * 100 && trawnik[i + 2][k] == 0)
								x_j = j + r360 / 2 - 1;

							break;
						}
						if (test(trawnik, i, x_j, r360) == 0) //test dla mniejszego obszaru
						{
							poj_360(trawnik, x_j, i, r360, 3);
							pod_out(out, i, x_j, "r360", "S");
						}
					}
				}

				if (trawnik[i - 1][j] == 0 && trawnik[i][j + 1] < 0 && trawnik[i][j - 1] < 0)
				{
					int x_j = 0;
					int pom = 0;

					for (int k = j; k < j + r270; k++)
					{
						if (k >= 0 && k < liczba_k * 100 && trawnik[i - 2][k] == 0)
							x_j = j + r180 / 2 - 1;
						break;
					}
					pom = test(trawnik, i, x_j, r180);
					if (pom == 0 && x_j < liczba_k * 99)
					{
						if (trawnik[i - 1][x_j] == 0 && trawnik[i][x_j + 1] < 0 && trawnik[i][x_j - 1] < 0)
						{
							pod_out(out, i, x_j, "r180", "N");
							for (int y = i + r180 / 2; y >= i - r180 / 2; y--)
								for (int x = x_j - r180 / 2; x < x_j + r180 / 2; x++)
									if (y < liczba_w * 100 - 1 && y >= 0 && x < liczba_k * 100 - 1 && x >= 0 && i > y)
										if (trawnik[i][x_j] < 10 && trawnik[i - 1][x_j] >= 0)
											if (pow(x - x_j, 2) + pow(y - i, 2) <= pow(r180 / 2, 2))
												trawnik[y][x] += 10;
						}
					}
					else
					{
						x_j = 0;
						for (int k = j; k < j + r360; j++)
						{
							if (k >= 0 && k < liczba_k * 100 && trawnik[i - 2][k] == 0)
								x_j = j + r360 / 2 - 1;

							break;
						}

						if (test(trawnik, i, x_j, r360) == 0)
						{
							poj_360(trawnik, x_j, i, r360, 2);
							pod_out(out, i, x_j, "r360", "N");
						}
					}
				}
				if (trawnik[i - 1][j] < 0 && trawnik[i + 1][j] < 0 && trawnik[i][j - 1] == 0)
				{
					int x_i = 0;
					int pom = 0;
					for (int k = i; k < i + r270; k++)
					{
						if (k >= 0 && k < liczba_w * 99 && trawnik[k][j - 1] == 0)
							x_i = i + r180 / 2;
						break;
					}
					pom = test(trawnik, x_i, j, r180);
					if (pom == 0 && x_i < liczba_w * 99)
					{
						if (trawnik[x_i - 1][j] < 0 && trawnik[x_i][j + 1] < 0 && trawnik[x_i][j - 1] == 0)
						{
							pod_out(out, x_i, j, "r180", "W");
							for (int y = x_i - r180 / 2; y < x_i + r180 / 2; y++)
								for (int x = j + r180 / 2; x > j - r180 / 2; x--)
									if (y < liczba_w * 100 - 1 && y >= 0 && x < liczba_k * 100 - 1 && x >= 0 && x < j)
										if (trawnik[x_i][j] < 10 && trawnik[x_i][j - 1] >= 0)
											if (pow(x - j, 2) + pow(y - x_i, 2) <= pow(r180 / 2, 2))
												trawnik[y][x] += 10;
						}
					}
					else
					{
						x_i = 0;
						for (int k = i; k < i + r270; k++)
						{
							if (k >= 0 && k < liczba_w * 99 && trawnik[k][j - 1] == 0)
								x_i = i + r360 / 2;
							break;
						}
						if (test(trawnik, x_i, j, r360) == 0)
						{
							poj_360(trawnik, j, x_i, r360, 0);
							pod_out(out, x_i, j, "r360", "W");
						}
					}
				}

				if (trawnik[i + 1][j] < 0 && trawnik[i][j + 1] == 0 && trawnik[i - 1][j] < 0)
				{
					int x_i = 0;
					int pom = 0;
					for (int k = i; k < i + r270; k++)
					{
						if (k >= 0 && k < liczba_w * 100 && trawnik[k][j + 1] == 0)
							x_i = i + r180 / 2;
						break;
					}
					pom = test(trawnik, x_i, j, r180);
					if (pom == 0 && x_i < liczba_w * 99)
					{
						if (trawnik[x_i + 1][j] < 0 && trawnik[x_i][j + 1] == 0 && trawnik[x_i][j - 1] < 0)
						{
							pod_out(out, x_i, j, "r180", "E");
							for (int y = x_i - r180 / 2; y < x_i + r180 / 2; y++)
								for (int x = j - r180 / 2; x < j + r180 / 2; x++)
									if (y < liczba_w * 100 - 1 && y >= 0 && x < liczba_k * 100 - 1 && x >= 0 && x > j)
										if (trawnik[x_i][j] < 10 && trawnik[x_i][j + 1] >= 0)
											if (pow(x - j, 2) + pow(y - x_i, 2) <= pow(r180 / 2, 2))
												trawnik[y][x] += 10;
						}
					}
					else
					{
						x_i = 0;
						for (int k = i; k < i + r270; k++)
						{
							if (k >= 0 && k < liczba_w * 100 && trawnik[k][j + 1] == 0)
								x_i = i + r360 / 2;
							break;
						}
						if (test(trawnik, x_i, j, r360) == 0)
						{
							poj_360(trawnik, j, x_i, r360, 0);
							pod_out(out, x_i, j, "r360", "E");
						}
					}
				}
			}
}

void kraw_360(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90) //rozmieszczenie podlewaczek pelnych, tj. r360
{
	//pierwsza podwojna petla iteruje po trawniku, druga sprawdza ktore punkty znajduja sie w okregu o danym promienu
	for (int i = 50; i < liczba_w * 100 - 50; i++)
		for (int j = 50; j < liczba_k * 100 - 50; j++)
			if (trawnik[i][j] >= 0 && test_360(trawnik, i, j, r360, 0) == 0) //sprawdzamy czy jestesmy w obszarze podlewanym oraz rozmiar obaszur jeszcze nie podlanego
			{
				pod_out(out, i, j, "r360", "NaN");
				for (int y = i - r360 / 2; y < i + r360 / 2; y++)
					for (int x = j - r360 / 2; x < j + r360 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0)
							if (pow(x - j, 2) + pow(y - i, 2) <= pow(r360 / 2, 2))
								trawnik[y][x] += 10;
			}

	for (int i = 50; i < liczba_w * 100 - 50; i++)
		for (int j = 50; j < liczba_k * 100 - 50; j++)
		{
			if (trawnik[i][j] >= 0 && test_360(trawnik, i, j, r360, 1) == 0) //j.w. tylko test przeprowadzany jest z zezwoleniem, na wieksze nakładanie się podlewaczek
			{
				pod_out(out, i, j, "r360", "NaN");
				for (int y = i - r360 / 2; y < i + r360 / 2; y++)
					for (int x = j - r360 / 2; x < j + r360 / 2; x++)
						if (y < liczba_w * 100 && y >= 0 && x < liczba_k * 100 && x >= 0)
							if (pow(x - j, 2) + pow(y - i, 2) <= pow(r360 / 2, 2))
								trawnik[y][x] += 10;
			}
		}
}