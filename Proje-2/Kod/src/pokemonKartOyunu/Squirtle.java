package pokemonKartOyunu;

import javax.swing.*;

public class Squirtle extends Pokemon {
    private int hasarPuani;
    private int ID = 3;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Squirtle(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("squirtle.png");
    }

    public Squirtle() {
        setPokemonAdi("pokemonKartOyunu.Squirtle");
        setPokemonTip("Su");
        this.hasarPuani = 30;
        resim = new ImageIcon("squirtle.png");
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
