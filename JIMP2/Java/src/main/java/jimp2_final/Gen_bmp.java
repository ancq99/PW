package jimp2_final;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;
import javax.imageio.ImageIO;

public class Gen_bmp {

    public void gen_bmp(int trawnik[][], BufferedImage img, int liczba_k, int liczba_w) throws IOException {
        //metoda tworzaca bitmape wyjsciowa

        Podlewanie obj = new Podlewanie();
        String path = obj.get_path();

        int sum = 0, pix = 0, sum2 = 0;

        //obliczenie sredniej na podswaie wrtosci wszystkich pol >= 0 oraz ilosci pixeli
        for (int i = 0; i < liczba_w * 100; i++) {
            for (int j = 0; j < liczba_k * 100; j++) {
                if (trawnik[i][j] >= 0) {
                    sum += trawnik[i][j];
                    pix++;
                }
            }
        }
        double avg = sum / pix;

        //odchylenie standardowe uzywane do "kolorowania"
        for (int i = 0; i < liczba_w * 100; i++) {
            for (int j = 0; j < liczba_k * 100; j++) {
                if (trawnik[i][j] >= 0) {
                    sum2 += pow(trawnik[i][j] - avg, 2);
                }
            }
        }

        double odch = sqrt(sum2 / pix);
        double pom;

        for (int i = 0; i < liczba_w * 100; i++) {
            for (int j = 0; j < liczba_k * 100; j++) {
                if (trawnik[i][j] > 0) {
                    pom = trawnik[i][j] - odch;
                    //zmienna pom jest zmienna pomocniczą, odpowiedzialna za przypisanie koloru w zaleznosci od roznicy miedzy wartoscia trawnika w danym punkcie i odchyleniem standardowym wzgledem calosci
                    //wartosci te zostaly wybrane doswiadczalnie i moga byc dowolnie modyfikowane
                    //img.setRGB jest odpowiedzialny za kolorowanie bitmapy, a wartosci "w srodku", w new Color(x,x,x).getRGB() to wortosc koloru RGB

                    if (pom >= -40) {
                        img.setRGB(j, i, new Color(255, 38, 38).getRGB());
                    }
                    if (pom <= -30 && pom > -40) {
                        img.setRGB(j, i, new Color(255, 82, 38).getRGB());
                    }
                    if (pom <= -20 && pom > -30) {
                        img.setRGB(j, i, new Color(255, 156, 55).getRGB());
                    }
                    if (pom <= -10 && pom > -20) {
                        img.setRGB(j, i, new Color(255, 222, 88).getRGB());
                    }
                    if (pom < 0 && pom > -10) {
                        img.setRGB(j, i, new Color(139, 255, 88).getRGB());
                    }
                    if (pom >= 0 && pom < 10) {
                        img.setRGB(j, i, new Color(80, 250, 161).getRGB());
                    }
                    if (pom >= 10 && pom < 20) {
                        img.setRGB(j, i, new Color(77, 255, 244).getRGB());
                    }
                    if (pom >= 20 && pom < 30) {
                        img.setRGB(j, i, new Color(77, 208, 255).getRGB());
                    }
                    if (pom >= 30 && pom < 40) {
                        img.setRGB(j, i, new Color(68, 118, 255).getRGB());
                    }
                    if (pom >= 40) {
                        img.setRGB(j, i, new Color(0, 0, 255).getRGB());
                    }
                }
            }
        }
        File output = new File(path + "\\out_bmp.bmp");
        if (output.exists()) {
            output.delete();
        }
        output.createNewFile();

        ImageIO.write(img, "bmp", output);

    }

    public void create_bmp(char tab[][], BufferedImage img, int liczba_k, int liczba_w) {
        //metoda tworzaca kszatlt trawnika w bitmapie wartosci w "new Color(x,x,x)" to wartosci RGB
        //zmienne pomocnicze w celu prawidlowego tworzenia bitmapy
        int pom1 = 0;
        int pom2 = 0;

        for (int l = 0; l < liczba_w * 100; l++) {
            for (int k = 0; k < liczba_k * 100; k++) {
                if (pom1 == liczba_w) {
                    break;
                }
                if (tab[pom1][pom2] == '*') {
                    img.setRGB(k, l, new Color(252, 255, 137).getRGB());
                } else {
                    img.setRGB(k, l, new Color(0, 0, 0).getRGB());
                }

                if ((k % 100) % 99 == 0 && k % 100 != 0) {
                    pom2++;
                }
                if (liczba_k == pom2) {
                    pom2 = 0;

                }
            }
            if ((l % 100) % 99 == 0 && l % 100 != 0) {
                pom1++;

            }
        }
    }
}
