package pokemonKartOyunu;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class InsanOyuncusu extends Oyuncu {
    private ActionListener kartSecButon1;
    private ActionListener kartSecButon2;
    private ActionListener kartSecButon3;
    private ActionListener kartSecButon4;
    private int secilenKart;

    //Insan oyuncusu icin her karta bir actionlistener eklenir.
    public InsanOyuncusu(String oyuncuAdi, int oyuncuID, int skor) {
        super(oyuncuAdi, oyuncuID, skor);
        secilenKart = -1;
        kartSecButon1 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 0;
            }
        };
        kartSecButon2 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 1;
            }
        };
        kartSecButon3 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 2;
            }
        };
        kartSecButon4 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 3;
            }
        };

    }

    public InsanOyuncusu() {
        secilenKart = -1;
        kartSecButon1 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 0;
            }
        };
        kartSecButon2 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 1;
            }
        };
        kartSecButon3 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 2;
            }
        };
        kartSecButon4 = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                secilenKart = 3;
            }
        };
    }

    //Insan oyuncusunda kart secimi elle yapilir, tiklanan kartin indisi dondurulur
    @Override
    public int kartSec(JButton buton1, JButton buton2, JButton buton3) {
        secilenKart = -1;
        buton1.addActionListener(kartSecButon1);
        buton2.addActionListener(kartSecButon2);
        buton3.addActionListener(kartSecButon3);
        while (secilenKart == -1) {
            try {
                Thread.sleep(250);
            } catch (java.lang.InterruptedException e) {
                System.out.println("Hata");
            }
        }
        buton1.removeActionListener(kartSecButon1);
        buton2.removeActionListener(kartSecButon2);
        buton3.removeActionListener(kartSecButon3);
        return secilenKart;
    }

    //Insan oyuncusunda kart alimi elle yapilir, tiklanan kartin indisi dondurulur
    @Override
    public int kartAl(List<JButton> kartlar, List<Pokemon> kartlar2) {
        secilenKart = -1;
        kartlar.get(0).addActionListener(kartSecButon1);
        kartlar.get(1).addActionListener(kartSecButon2);
        kartlar.get(2).addActionListener(kartSecButon3);
        kartlar.get(3).addActionListener(kartSecButon4);
        while (secilenKart == -1) {
            try {
                Thread.sleep(250);
            } catch (java.lang.InterruptedException e) {
                System.out.println("Hata");
            }
        }
        kartlar.get(0).removeActionListener(kartSecButon1);
        kartlar.get(1).removeActionListener(kartSecButon2);
        kartlar.get(2).removeActionListener(kartSecButon3);
        kartlar.get(3).removeActionListener(kartSecButon4);
        System.out.println(secilenKart);
        return secilenKart;
    }
}
