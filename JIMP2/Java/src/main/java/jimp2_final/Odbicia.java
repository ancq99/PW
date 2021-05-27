package jimp2_final;

import static java.lang.Math.abs;

public class Odbicia {

    static int liczba_w;
    static int liczba_k;

    public void get_k_w_2(int x, int y) {
        //metoda pomocnicza, pobiera wymiary trawnika
        liczba_w = y * 100;
        liczba_k = x * 100;
    }

    public void odbicia(int trawnik[][], int r360, int r270, int r180, int r90) {
        //petla do podzialu odbicia na rogach po przekatnej kwadratu o boku 100, kazdy if odpowiedzialny jest za 1 z 4 typów narożników
        for (int i = 50; i < liczba_w - 50; i++) {
            for (int j = 50; j < liczba_k - 50; j++) {
                if (trawnik[i][j] < 0 && trawnik[i][j] > -99) {
                    if (trawnik[i - 1][j] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0 && trawnik[i][j - 1] > 0) {
                        for (int k = 0; k < 100; k++) {
                            if (trawnik[i - k][j + k] == -89) {
                                trawnik[i - k][j + k] -= 10;
                            }
                        }
                    }
                    if (trawnik[i - 1][j] < 0 && trawnik[i][j - 1] < 0 && trawnik[i + 1][j] > 0 && trawnik[i][j + 1] > 0) {
                        for (int k = 0; k < 100; k++) {
                            if (trawnik[i - k][j - k] == -89) {
                                trawnik[i - k][j - k] -= 10;
                            }
                        }
                    }
                    if (trawnik[i - 1][j] > 0 && trawnik[i][j - 1] < 0 && trawnik[i + 1][j] < 0 && trawnik[i][j + 1] > 0) {
                        for (int k = 0; k < 100; k++) {
                            if (trawnik[i + k][j - k] == -89) {
                                trawnik[i + k][j - k] -= 10;
                            }
                        }
                    }
                    if (trawnik[i - 1][j] > 0 && trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i][j + 1] < 0) {
                        for (int k = 0; k < 100; k++) {
                            if (trawnik[i + k][j + k] == -89) {
                                trawnik[i + k][j + k] -= 10;
                            }
                        }
                    }
                }
            }
        }
        odbicie_poziom_g(trawnik);
        odbicie_poziom_d(trawnik);
        odbicie_pionowe_l(trawnik);
        odbicie_pionowe_p(trawnik);
    }

    private static void odbicie_poziom_g(int trawnik[][]) {
        //petle podzielowne na pol wzgledem ilosci kolumn w celu prawidlowego dzialania odbic
        for (int i = 50; i < liczba_w / 2; i++) {
            for (int j = 50; j < liczba_k - 50; j++) {
                if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i - 1][j] > 0) // sprawdzenie czy jestesmy na krawedzi obszaru podlewania z tym niepodlewanym
                {
                    int pom = 0; //zmiena przechowujaca ilosc pikseli do obicia

                    for (int k = i;; k++) {
                        if (k >= 0 && k < liczba_w && trawnik[k][j] == -89) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) //petla odbijajaca 
                    {
                        trawnik[i - k][j] += abs(-99 - trawnik[i + k][j]); //wartosć bezwględna z różnicy między wartością domyślą pola niepodlewanego a aktualna wartoscia tego pola
                        trawnik[i + k][j] = -99; // przypisanie wartosci -99 w celu nie obijania podlewania ponownie
                    }
                }
            }
        }

        for (int i = liczba_w - 50; i > liczba_w / 2; i--) {
            for (int j = 50; j < liczba_k - 50; j++) {
                if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i - 1][j] > 0) {
                    int pom = 0;

                    for (int k = i;; k++) {
                        if (k >= 0 && k < liczba_w && trawnik[k][j] == -89) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i - k][j] += abs(-99 - trawnik[i + k][j]);
                        trawnik[i + k][j] = -99;
                    }
                }
            }
        }
    }

    private static void odbicie_poziom_d(int trawnik[][]) {
        for (int i = 50; i < liczba_w / 2; i++) {
            for (int j = 50; j < liczba_k - 50; j++) {
                if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0) {
                    int pom = 0;
                    for (int k = i;; k--) {
                        if (k >= 0 && k < liczba_w && trawnik[k][j] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i + k][j] += abs(-99 - trawnik[i - k][j]);
                        trawnik[i - k][j] = -99;
                    }
                }
            }
        }

        for (int i = liczba_w - 50; i > liczba_w / 2; i--) {
            for (int j = 50; j < liczba_k - 50; j++) {
                if (trawnik[i][j - 1] < 0 && trawnik[i][j + 1] < 0 && trawnik[i + 1][j] > 0) {
                    int pom = 0;
                    for (int k = i;; k--) {
                        if (k >= 0 && k < liczba_w && trawnik[k][j] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i + k][j] += abs(-99 - trawnik[i - k][j]);
                        trawnik[i - k][j] = -99;
                    }
                }
            }
        }
    }
    

    

    private static void odbicie_pionowe_l(int trawnik[][]){
        for (int i = 50; i < liczba_w - 50; i++) {
            for (int j = 50; j < liczba_k / 2; j++) {
                if (trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0) {
                    int pom = 0;
                    for (int k = j;; k++) {
                        if (k >= 0 && k < liczba_k && trawnik[i][k] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i][j - k] += abs(-99 - trawnik[i][j + k]);
                        trawnik[i][j + k] = -99;
                    }
                }
            }
        }
        for (int i = 50; i < liczba_w - 50; i++) {
            for (int j = liczba_k - 50; j > liczba_k / 2; j--) {
                if (trawnik[i][j - 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0) {
                    int pom = 0;
                    for (int k = j;; k++) {
                        if (k >= 0 && k < liczba_k && trawnik[i][k] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i][j - k] += abs(-99 - trawnik[i][j + k]);
                        trawnik[i][j + k] = -99;
                    }
                }
            }
        }
    }

    private static void odbicie_pionowe_p(int trawnik[][]) {
        for (int i = 50; i < liczba_w - 50; i++) {
            for (int j = 50; j < liczba_k / 2; j++) {
                if (trawnik[i][j + 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0) {
                    int pom = 0;
                    for (int k = j;; k--) {
                        if (k >= 0 && k < liczba_k && trawnik[i][k] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i][j + k] += abs(-99 - trawnik[i][j - k]);
                        trawnik[i][j - k] = -99;
                    }
                }
            }
        }

        for (int i = 50; i < liczba_w - 50; i++) {
            for (int j = liczba_k - 50; j > liczba_k / 2; j--) {
                if (trawnik[i][j + 1] > 0 && trawnik[i + 1][j] < 0 && trawnik[i - 1][j] < 0) {
                    int pom = 0;
                    for (int k = j;; k--) {
                        if (k >= 0 && k < liczba_k && trawnik[i][k] != -99) {
                            pom++;
                        } else {
                            break;
                        }
                    }

                    for (int k = 0; k < pom; k++) {
                        trawnik[i][j + k] += abs(-99 - trawnik[i][j - k]);
                        trawnik[i][j - k] = -99;
                    }
                }
            }
        }
    }

}
