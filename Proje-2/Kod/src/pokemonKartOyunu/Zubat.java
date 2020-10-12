package pokemonKartOyunu;

import javax.swing.*;

public class Zubat extends Pokemon {
    private int hasarPuani;
    private int ID = 4;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Zubat(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("zubat.png");
    }

    public Zubat() {
        setPokemonAdi("pokemonKartOyunu.Zubat");
        setPokemonTip("Hava");
        this.hasarPuani = 50;
        resim = new ImageIcon("zubat.png");
    }

    public void setHasarPuani(int hasarPuani) {
        this.hasarPuani = hasarPuani;
    }

    public int getHasarPuani() {
        return hasarPuani;
    }

    @Override
    public ImageIcon getResim() {
        return resim;
    }

    public void setKartKullanildiMi(boolean kartKullanildiMi) {
        this.kartKullanildiMi = kartKullanildiMi;
    }

    public boolean getkartKullanildiMi() {
        return kartKullanildiMi;
    }

    @Override
    public void hasarPuaniGoster() {
        System.out.println("Hasar Puanı: " + this.hasarPuani);
    }
}
