package jimp2_final;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Gen {

    public void pod_out(int y, int x, String typ, String dir) throws IOException {
        //metoda generujaca plik z rozmieszczenim podleaczek
        Podlewanie obj = new Podlewanie();
        String path = obj.get_path();

        try (FileWriter te = new FileWriter(path + "\\podlewaczki_txt.txt", true)) {
            te.write(String.format("%s:  %s  %d x %d", typ, dir, x, y));
            te.write(System.lineSeparator());
        }
    }

    public void gen_bmp_txt(int trawnik[][], String path, int liczba_k, int liczba_w) throws IOException {
        //metoda generujaca plik z bitmapa w wersji txt
        File out = new File(path + "\\bmp_txt.txt");
        if (out.exists()) {
            out.delete();
        }
        out.createNewFile();

        try (FileWriter writer = new FileWriter(path + "\\bmp_txt.txt")) {
            for (int i = 0; i < liczba_w * 100; i++) {
                for (int j = 0; j < liczba_k * 100; j++) {
                    writer.write(String.format(" %s ", Integer.toString(trawnik[i][j])));
                }
                writer.write(System.lineSeparator());
            }
        }
    }

    public int[][] gen_trawnik(char tab[][], int liczba_k, int liczba_w) {
        //metoda tworzaca liczbowa tablice z mapa trawnika
        int[][] trawnik = new int[liczba_w * 100][liczba_k * 100];

        int pom1 = 0;
        int pom2 = 0;
        for (int l = 0; l < liczba_w * 100; l++) {
            for (int k = 0; k < liczba_k * 100; k++) {
                if (pom1 == liczba_w) {
                    break;
                }
                //wartosc 0- pole do podlania, wartosc -99- przeszkoda
                if (tab[pom1][pom2] == '*' || tab[pom1][pom2] == '\n') {
                    trawnik[l][k] = 0;
                } else {
                    trawnik[l][k] = -99;
                }

                if ((k % 100) % 99 == 0 && k % 100 != 0) {
                    pom2++;
                }

                if (liczba_k * 100 - 1 == k && k > 10) {
                    pom2 = 0;
                }
            }
            if ((l % 100) % 99 == 0 && l % 100 != 0) {
                pom1++;
            }
        }
        return trawnik;
    }

    public char[][] gen_tab(String path, int liczba_k, int liczba_w) throws IOException {
        //metoda odczytujaca plik do tablicy 2d
        char tab[][] = new char[liczba_w][liczba_k];
        File myObj = new File(path);
        String[] pom;

        try (Scanner myReader = new Scanner(myObj)) {
            //pominiecie 2 pierszych wersow z wymiarami
            for (int i = 0; i < 2; ++i) {
                myReader.nextLine();
            }
            //odczyt pliku wejsciowego
            pom = new String[liczba_w];
            int n = 0;
            while (myReader.hasNextLine()) {
                pom[n++] = myReader.nextLine();
            }
        }
        //wczytanie pliku to tablicy 2d
        int i = 0;
        int j = 0;

        for (String x : pom) {
            char[] k;
            k = x.replaceAll("\\s", "").toCharArray();
            for (char y : k) {

                tab[i][j++] = y;

            }
            i++;
            j = 0;
        }

        return tab;
    }
}
