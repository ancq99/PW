package jimp2_final;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.NoSuchElementException;
import java.util.Scanner;
import javax.swing.JOptionPane;

public class Start_prog {

    //deklaracja promieni
    private static final int r360 = 100;
    private static final int r270 = 200;
    private static final int r180 = 300;
    private static final int r90 = 400;

    //uruchomienie programu poklilknieciu przycisku start
    //metoda odpowiedziallna za poprawne uruchomienie programu
    public static int run(int cykle, boolean odbicia, String input_path, String output_path) {

        int liczba_w = 0;
        int liczba_k = 0;

        //odczyt liczby kolumn i wierszy oraz ich weryfikacja 
        File myObj = new File(input_path);
        Scanner myReader = null;

        try {
            myReader = new Scanner(myObj);
        } catch (FileNotFoundException ex) {
            JOptionPane.showMessageDialog(null, "NIE UDALO SIE ODCZYTAC PLIKU!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }
        try {
            liczba_k = Integer.parseInt(myReader.nextLine());
            liczba_w = Integer.parseInt(myReader.nextLine());
        } catch (NumberFormatException | NoSuchElementException e) {
            JOptionPane.showMessageDialog(null, "WYSTAPIL BLAD!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }

        System.out.println(liczba_w + "x" + liczba_k);
        if (liczba_k == 0 || liczba_w == 0 || liczba_k > 80 || liczba_w > 40) {
            JOptionPane.showMessageDialog(null, "NIE PODANO ROZMIARU TRAWNIKA LUB PODANY ROMIAR JEST BLEDNY!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }
        if (cykle <= 0) {
            JOptionPane.showMessageDialog(null, "BLEDNA ILOSC CYKLI!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }
        //generacja trawnik
        Gen generate = new Gen();
        char tab[][] = null;
        try {
            tab = generate.gen_tab(input_path, liczba_k, liczba_w);
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "NIE UDALO SIE WYGENEROWAC MAPY TRAWNIKA Z PLIKU!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }
        int trawnik[][] = generate.gen_trawnik(tab, liczba_k, liczba_w);

        //generacja bitmapy
        Gen_bmp bitmapa = new Gen_bmp();
        BufferedImage img = new BufferedImage(liczba_k * 100, liczba_w * 100, BufferedImage.TYPE_INT_RGB);
        bitmapa.create_bmp(tab, img, liczba_k, liczba_w);

        //podlewanie
        Podlewanie konewka = new Podlewanie();
        try {
            konewka.get_k_w(liczba_k, liczba_w, output_path);
            konewka.kraw_zew_90(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
            konewka.kraw_zew_180(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
            konewka.kraw_wew_270(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
            konewka.kraw_wew_180(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
            konewka.kraw_360(trawnik, liczba_k, liczba_w, r360, r270, r180, r90);
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "PODLEWANIE ZAKONCZYLO SIE NIEPOWODZENIEM!", "Error!", JOptionPane.ERROR_MESSAGE);
        }
        if (odbicia) {
            Odbicia mirror = new Odbicia();
            mirror.get_k_w_2(liczba_k, liczba_w);
            mirror.odbicia(trawnik, r360, r270, r180, r90);
        }

        //cykle
        for (int i = 0; i < liczba_w * 100; i++) {
            for (int j = 0; j < liczba_k * 100; j++) {
                if (trawnik[i][j] > 0) {
                    trawnik[i][j] *= cykle;
                }
            }
        }

        //kolorowanie bitmapy
        try {
            bitmapa.gen_bmp(trawnik, img, liczba_k, liczba_w);
            generate.gen_bmp_txt(trawnik, output_path, liczba_k, liczba_w);
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "NIE UDALO SIE WYGENEROWAC BITMAPY!", "Error!", JOptionPane.ERROR_MESSAGE);
            return -1;
        }
        return 0;
    }

}
