package pokemonKartOyunu;

import javax.swing.*;

public class Snorlax extends Pokemon {
    private int hasarPuani;
    private int ID = 6;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Snorlax(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("snorlax.png");
    }

    public Snorlax() {
        setPokemonAdi("pokemonKartOyunu.Snorlax");
        setPokemonTip("Normal");
        this.hasarPuani = 30;
        resim = new ImageIcon("snorlax.png");
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
