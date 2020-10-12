package pokemonKartOyunu;

import javax.swing.*;

public class Bulbasaur extends Pokemon {
    private int hasarPuani;
    private int ID = 1;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Bulbasaur(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("bulbasaur.png");
    }

    public Bulbasaur() {
        setPokemonAdi("pokemonKartOyunu.Bulbasaur");
        setPokemonTip("Çim");
        this.hasarPuani = 50;
        resim = new ImageIcon("bulbasaur.png");
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
