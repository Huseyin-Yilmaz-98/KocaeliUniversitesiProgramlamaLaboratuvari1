package pokemonKartOyunu;

import javax.swing.*;

public class Pokemon {
    private String pokemonAdi;
    private String pokemonTip;
    private int pokemonID;
    private ImageIcon resim;

    public Pokemon(String pokemonAdi, String pokemonTip) {
        this.pokemonAdi = pokemonAdi;
        this.pokemonTip = pokemonTip;
    }

    public Pokemon() {
    }

    ;

    public String getPokemonTip() {
        return pokemonTip;
    }

    public void setPokemonTip(String pokemonTip) {
        this.pokemonTip = pokemonTip;
    }

    public int getHasarPuani() {
        return 0;
    }


    public String getPokemonAdi() {
        return pokemonAdi;
    }

    public void setPokemonAdi(String pokemonAdi) {
        this.pokemonAdi = pokemonAdi;
    }

    public ImageIcon getResim() {
        return resim;
    }

    public void hasarPuaniGoster() {
    }

    ;
}
