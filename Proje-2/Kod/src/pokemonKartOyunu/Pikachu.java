package pokemonKartOyunu;

import javax.swing.*;

public class Pikachu extends Pokemon {
    private int hasarPuani;
    private int ID = 0;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Pikachu(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("pikachu.png");
    }

    public Pikachu() {
        setPokemonAdi("pokemonKartOyunu.Pikachu");
        setPokemonTip("Elektrik");
        this.hasarPuani = 40;
        resim = new ImageIcon("pikachu.png");
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
