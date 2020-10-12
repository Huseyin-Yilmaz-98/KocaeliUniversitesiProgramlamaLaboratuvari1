package pokemonKartOyunu;

import javax.swing.*;

public class Psyduck extends Pokemon {
    private int hasarPuani;
    private int ID = 5;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Psyduck(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("psyduck.png");
    }

    public Psyduck() {
        setPokemonAdi("pokemonKartOyunu.Psyduck");
        setPokemonTip("Su");
        this.hasarPuani = 20;
        resim = new ImageIcon("psyduck.png");
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
