package pokemonKartOyunu;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public abstract class Oyuncu {
    public List<Pokemon> kartlar = new ArrayList<>();
    private int oyuncuID;
    private String oyuncuAdi;
    private int skor;

    public Oyuncu(String oyuncuAdi, int oyuncuID, int skor) {
        this.oyuncuAdi = oyuncuAdi;
        this.oyuncuID = oyuncuID;
        this.skor = skor;
    }

    public Oyuncu() {
        this.skor = 0;
    }

    public int getSkor() {
        return skor;
    }

    public String getOyuncuAdi() {
        return oyuncuAdi;
    }

    public void puanEkle() {
        this.skor += 5;
    }

    public abstract int kartSec(JButton buton1, JButton buton2, JButton buton3);

    public abstract int kartAl(List<JButton> kartlar, List<Pokemon> kartlar2);

}
