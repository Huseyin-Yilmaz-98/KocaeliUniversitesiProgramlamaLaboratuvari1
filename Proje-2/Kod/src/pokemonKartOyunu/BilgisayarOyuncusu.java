package pokemonKartOyunu;

import javax.swing.*;
import java.util.List;
import java.util.Random;

public class BilgisayarOyuncusu extends Oyuncu {
    public BilgisayarOyuncusu(String oyuncuAdi, int oyuncuID, int skor) {
        super(oyuncuAdi, oyuncuID, skor);
    }

    public BilgisayarOyuncusu() {
    }

    //Bilgisayar oyuncusu için kart secme islemi rastgele yapilir
    @Override
    public int kartSec(JButton buton1, JButton buton2, JButton buton3) {
        try {
            Thread.sleep(1250);
        } catch (java.lang.InterruptedException e) {
            System.out.println("Hata");
        }
        Random rand = new Random();
        int indis = rand.nextInt(kartlar.size());
        return indis;
    }

    //Bilgisayar oyuncusu icin kart alma islemi rastgele yapilir
    @Override
    public int kartAl(List<JButton> kartlar, List<Pokemon> kartlar2) {
        try {
            Thread.sleep(1250);
        } catch (java.lang.InterruptedException e) {
            System.out.println("Hata");
        }
        Random rand = new Random();
        int indis = rand.nextInt(kartlar2.size());
        return indis;
    }
}
