//plik odpowiedzialny za odbicia podlewania od scian
#include "cfg.h"

int liczba_k, liczba_w;

void get_k_w2(int x, int y)
{
    //funkcja pobierajaca wymiary trawnika z pliku main
    liczba_k = x * 100;
    liczba_w = y * 100;
}

void odbicia(char **trawnik, int r360, int r270, int r180, int r90)
{
    //petla do podzialu odbicia na rogach po przekatnej kwadratu o boku 100
    for (int i = 50; i < liczba_w - 50; i++)
        for (int j = 50; j < liczba_k - 50; j++)
            if (trawnik[i][j] < 0 && trawnik[i][j] > -99)
            {
                if (trawnik[i - 1][j] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0 && trawnik[i][j - 1] > 0)
                {
                    for (int k = 0; k < 100; k++)
                        if (trawnik[i - k][j + k] == -89)
                            trawnik[i - k][j + k] -= 10;
                }
                if (trawnik[i - 1][j] < 0 && trawnik[i][j - 1] < 0 && trawnik[i + 1][j] > 0 && trawnik[i][j + 1] > 0)
                {
                    for (int k = 0; k < 100; k++)
                        if (trawnik[i - k][j - k] == -89)
                            trawnik[i - k][j - k] -= 10;
                }
                if (trawnik[i - 1][j] > 0 && trawnik[i][j - 1] < 0 && trawnik[i + 1][j] < 0 && trawnik[i][j + 1] > 0)
                {
                    for (int k = 0; k < 100; k++)
                        if (trawnik[i + k][j - k] == -89)
                            trawnik[i + k][j - k] -= 10;
                }
                if (trawnik[i - 1][j] > 0 && trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i][j + 1] < 0)
                {
                    for (int k = 0; k < 100; k++)
                        if (trawnik[i + k][j + k] == -89)
                            trawnik[i + k][j + k] -= 10;
                }
            }
    odbicie_poziom_g(trawnik);
    odbicie_poziom_d(trawnik);
    odbicie_pionowe_l(trawnik);
    odbicie_pionowe_p(trawnik);
}

void odbicie_poziom_g(char **trawnik)
{
    //petle podzielowne na pol wzgledem ilosci kolumn w celu prawidlowego dzialania odbic
    for (int i = 50; i < liczba_w / 2; i++)
        for (int j = 50; j < liczba_k - 50; j++)
            if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i - 1][j] > 0) // sprawdzenie czy jestesmy na krawedzi obszaru podlewania z tym niepodlewanym
            {
                int pom = 0; //zmiena przechowujaca ilosc pikseli do obicia

                for (int k = i;; k++)
                {
                    if (k >= 0 && k < liczba_w && trawnik[k][j] == -89)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++) //petla odbijajaca 
                {
                    trawnik[i - k][j] += abs(-99 - trawnik[i + k][j]);
                    trawnik[i + k][j] = -99;
                }
            }

    for (int i = liczba_w - 50; i > liczba_w / 2; i--)
        for (int j = 50; j < liczba_k - 50; j++)
            if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i - 1][j] > 0)
            {
                int pom = 0;

                for (int k = i;; k++)
                {
                    if (k >= 0 && k < liczba_w && trawnik[k][j] == -89)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i - k][j] += abs(-99 - trawnik[i + k][j]);
                    trawnik[i + k][j] = -99;
                }
            }
}
void odbicie_poziom_d(char **trawnik)
{
    for (int i = 50; i < liczba_w / 2; i++)
        for (int j = 50; j < liczba_k - 50; j++)
            if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0)
            {
                int pom = 0;
                for (int k = i;; k--)
                {
                    if (k >= 0 && k < liczba_w && trawnik[k][j] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i + k][j] += abs(-99 - trawnik[i - k][j]);
                    trawnik[i - k][j] = -99;
                }
            }

    for (int i = liczba_w - 50; i > liczba_w / 2; i--)
        for (int j = 50; j < liczba_k - 50; j++)
            if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0)
            {
                int pom = 0;
                for (int k = i;; k--)
                {
                    if (k >= 0 && k < liczba_w && trawnik[k][j] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i + k][j] += abs(-99 - trawnik[i - k][j]);
                    trawnik[i - k][j] = -99;
                }
            }
}
void odbicie_pionowe_l(char **trawnik)
{
    for (int i = 50; i < liczba_w - 50; i++)
        for (int j = 50; j < liczba_k / 2; j++)
            if (trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0)
            {
                int pom = 0;
                for (int k = j;; k++)
                {
                    if (k >= 0 && k < liczba_k && trawnik[i][k] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i][j - k] += abs(-99 - trawnik[i][j + k]);
                    trawnik[i][j + k] = -99;
                }
            }
    for (int i = 50; i < liczba_w - 50; i++)
        for (int j = liczba_k - 50; j > liczba_k / 2; j--)
            if (trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0)
            {
                int pom = 0;
                for (int k = j;; k++)
                {
                    if (k >= 0 && k < liczba_k && trawnik[i][k] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i][j - k] += abs(-99 - trawnik[i][j + k]);
                    trawnik[i][j + k] = -99;
                }
            }
}
void odbicie_pionowe_p(char **trawnik)
{
    for (int i = 50; i < liczba_w - 50; i++)
        for (int j = 50; j < liczba_k / 2; j++)
            if (trawnik[i][j + 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0)
            {
                int pom = 0;
                for (int k = j;; k--)
                {
                    if (k >= 0 && k < liczba_k && trawnik[i][k] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i][j + k] += abs(-99 - trawnik[i][j - k]);
                    trawnik[i][j - k] = -99;
                }
            }

    for (int i = 50; i < liczba_w - 50; i++)
        for (int j = liczba_k - 50; j > liczba_k / 2; j--)
            if (trawnik[i][j + 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0)
            {
                int pom = 0;
                for (int k = j;; k--)
                {
                    if (k >= 0 && k < liczba_k && trawnik[i][k] != -99)
                        pom++;
                    else
                        break;
                }

                for (int k = 0; k < pom; k++)
                {
                    trawnik[i][j + k] += abs(-99 - trawnik[i][j - k]);
                    trawnik[i][j - k] = -99;
                }
            }
}