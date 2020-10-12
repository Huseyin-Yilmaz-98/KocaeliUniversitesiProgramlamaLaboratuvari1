package pokemonKartOyunu;

import javax.swing.*;

public class Meowth extends Pokemon {
    private int hasarPuani;
    private int ID = 9;
    private boolean kartKullanildiMi = false;
    private ImageIcon resim;

    public Meowth(String pokemonAdi, String pokemonTip, int hasarPuani) {
        super(pokemonAdi, pokemonTip);
        this.hasarPuani = hasarPuani;
        resim = new ImageIcon("meowth.png");
    }

    public Meowth() {
        setPokemonAdi("pokemonKartOyunu.Meowth");
        setPokemonTip("Normal");
        this.hasarPuani = 40;
        resim = new ImageIcon("meowth.png");
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
