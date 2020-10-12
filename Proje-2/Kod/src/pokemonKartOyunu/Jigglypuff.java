package pokemonKartOyunu;

import javax.swing.*;

public class Jigglypuff extends Pokemon {
    private int hasarPuani;
    private int ID = 8;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Jigglypuff(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("jigglypuff.png");
    }

    public Jigglypuff() {
        setPokemonAdi("pokemonKartOyunu.Jigglypuff");
        setPokemonTip("Ses");
        this.hasarPuani = 70;
        resim = new ImageIcon("jigglypuff.png");
    }

    @Override
    public ImageIcon getResim() {
        return resim;
    }

    public void setHasarPuani(int hasarPuani) {
        this.hasarPuani = hasarPuani;
    }

    public int getHasarPuani() {
        return hasarPuani;
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
