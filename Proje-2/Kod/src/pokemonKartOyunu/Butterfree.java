package pokemonKartOyunu;

import javax.swing.*;

public class Butterfree extends Pokemon {
    private int hasarPuani;
    private int ID = 7;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Butterfree(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("butterfree.png");
    }

    public Butterfree() {
        setPokemonAdi("pokemonKartOyunu.Butterfree");
        setPokemonTip("Hava");
        this.hasarPuani = 10;
        resim = new ImageIcon("butterfree.png");
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
