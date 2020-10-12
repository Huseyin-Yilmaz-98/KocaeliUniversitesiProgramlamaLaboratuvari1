package pokemonKartOyunu;

import javax.swing.*;

public class Charmander extends Pokemon {
    private int hasarPuani;
    private int ID = 2;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Charmander(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("charmander.png");
    }

    public Charmander() {
        setPokemonAdi("pokemonKartOyunu.Charmander");
        setPokemonTip("Ateş");
        this.hasarPuani = 60;
        resim = new ImageIcon("charmander.png");
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
