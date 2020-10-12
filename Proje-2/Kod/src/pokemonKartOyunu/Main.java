package pokemonKartOyunu;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main extends Thread {
    private BilgisayarOyuncusu oyuncu1;
    private Oyuncu oyuncu2;
    private boolean kartlariGor; //true ise ikinci oyuncu kartlari hep acik olur
    private List<Pokemon> kartlar;
    private ImageIcon arkasiDonuk;
    private JButton oyuncu1Kart1;
    private JButton oyuncu1Kart2;
    private JButton oyuncu1Kart3;
    private JButton oyuncu2Kart1;
    private JButton oyuncu2Kart2;
    private JButton oyuncu2Kart3;
    private JButton ortaKart1;
    private JButton ortaKart2;
    private JButton ortaKart3;
    private JButton ortaKart4;
    private List<JButton> ortaKartlar;
    private JLabel yazilar;
    private JLabel oyuncu1Yazi;
    private JLabel oyuncu2Yazi;
    private JLabel oyunSonu;
    private JFrame frame;
    private JButton buton1;
    private JButton buton2;
    private boolean hepsiniGor; //true ise oyundaki tum kartlar hep acik olur
    private JCheckBox hepsiniGorButon;

    public Main(JFrame alinanFrame) throws java.io.IOException {
        frame = alinanFrame;
        oyuncu1 = new BilgisayarOyuncusu("Bilgisayar", 1, 0);
        arkasiDonuk = new ImageIcon(ImageIO.read(new File("arkasidonuk.jpg")));
        buton1 = new JButton("Bilgisayar vs Bilgisayar");
        buton2 = new JButton("Bilgisayar vs Oyuncu");
        kartlar = new ArrayList<>();
        oyuncu1Kart1 = new JButton();
        oyuncu1Kart2 = new JButton();
        oyuncu1Kart3 = new JButton();
        oyuncu2Kart1 = new JButton();
        oyuncu2Kart2 = new JButton();
        oyuncu2Kart3 = new JButton();
        ortaKart1 = new JButton();
        ortaKart2 = new JButton();
        ortaKart3 = new JButton();
        ortaKart4 = new JButton();
        ortaKartlar = new ArrayList<>();
        yazilar = new JLabel();
        oyuncu1Yazi = new JLabel();
        oyuncu2Yazi = new JLabel();
        oyunSonu = new JLabel();
        hepsiniGorButon = new JCheckBox("Kartlar Acik Olsun");
    }

    //Oyuncu2'yi insan oyuncusu olarak atar
    public void insanOyuncusuOlustur() {
        oyuncu2 = new InsanOyuncusu("Insan", 2, 0);
    }

    //Oyuncu2'yi bilgisayar oyuncusu olarak atar
    public void bilgisayarOyuncusuOlustur() {
        oyuncu2 = new BilgisayarOyuncusu("Bilgisayar 2", 2, 0);
    }

    //Koordinal alir ve o koordinatta bir buton dondurur, default olarak buton gorunmezdir
    public JButton kartButonuOlustur(JButton buton, int x, int y) {
        buton.setIcon(arkasiDonuk);
        buton.setBounds(x, y, 110, 150);
        buton.setVisible(false);
        return buton;
    }

    //Ekrandaki nesneleri yaratıp ekrana yerlestiren fonksiyon
    public void ekranOlustur() {
        ortaKartlar.add(ortaKart1);
        ortaKartlar.add(ortaKart2);
        ortaKartlar.add(ortaKart3);
        ortaKartlar.add(ortaKart4);

        yazilar.setBounds(90, 300, 430, 100);
        yazilar.setHorizontalAlignment(SwingConstants.CENTER);
        yazilar.setFont(new Font("Constantia", Font.BOLD, 25));

        oyuncu1Yazi.setBounds(180, 10, 200, 50);
        oyuncu1Yazi.setHorizontalAlignment(SwingConstants.CENTER);
        oyuncu1Yazi.setFont(new Font("Constantia", Font.BOLD, 20));

        oyuncu2Yazi.setBounds(180, 640, 200, 50);
        oyuncu2Yazi.setHorizontalAlignment(SwingConstants.CENTER);
        oyuncu2Yazi.setFont(new Font("Constantia", Font.BOLD, 20));

        oyunSonu.setBounds(0, 270, 1000, 200);
        oyunSonu.setHorizontalAlignment(SwingConstants.CENTER);
        oyunSonu.setFont(new Font("Constantia", Font.BOLD, 60));
        oyunSonu.setForeground(Color.white);

        frame.add(oyunSonu);
        frame.add(oyuncu1Yazi);
        frame.add(oyuncu2Yazi);
        frame.add(yazilar);

        hepsiniGorButon.setBounds(430, 450, 200, 50);
        hepsiniGorButon.setOpaque(false);
        frame.add(hepsiniGorButon);

        buton1.setBounds(250, 183, 500, 100);
        buton1.setBackground(Color.lightGray);
        buton1.setFont(new Font("Arial", Font.PLAIN, 20));
        buton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                bilgisayarOyuncusuOlustur();
                kartlariGor = false;
                anaEkranCikis();
            }
        });
        frame.add(buton1);

        buton2.setBounds(250, 323, 500, 100);
        buton2.setBackground(Color.lightGray);
        buton2.setFont(new Font("Arial", Font.PLAIN, 20));
        buton2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                insanOyuncusuOlustur();
                kartlariGor = true;
                anaEkranCikis();
            }
        });
        frame.add(buton2);

        frame.add(kartButonuOlustur(oyuncu1Kart1, 90, 80));
        frame.add(kartButonuOlustur(oyuncu1Kart2, 230, 80));
        frame.add(kartButonuOlustur(oyuncu1Kart3, 370, 80));
        frame.add(kartButonuOlustur(oyuncu2Kart1, 90, 470));
        frame.add(kartButonuOlustur(oyuncu2Kart2, 230, 470));
        frame.add(kartButonuOlustur(oyuncu2Kart3, 370, 470));
        frame.add(kartButonuOlustur(ortaKart1, 660, 210));
        frame.add(kartButonuOlustur(ortaKart2, 800, 210));
        frame.add(kartButonuOlustur(ortaKart3, 660, 380));
        frame.add(kartButonuOlustur(ortaKart4, 800, 380));

        frame.setSize(1000, 750);
        frame.setLayout(null);
        frame.setVisible(true);
    }

    //Ana ekranda bir secim yapildiktan sonra bu fonksiyon cagirilir, ana ekrandaki nesneler gizlenir ve oyun baslatilir
    public void anaEkranCikis() {
        buton1.setVisible(false);
        buton2.setVisible(false);
        if (hepsiniGorButon.isSelected() == true)
            hepsiniGor = true;
        else
            hepsiniGor = false;
        hepsiniGorButon.setVisible(false);
        kartlariTanimla();
        kartDagit();
        this.start();
    }

    //Oyunun dondugu fonksiyon, Thread classinda ana fonksiyondur
    public void run() {
        kartlariSifirla();
        JButton oyuncu1SecilenKart = new JButton();
        JButton oyuncu2SecilenKart = new JButton();

        //Oyuncularin elinde kart oldugu surece oyun devam eder
        while (oyuncu1.kartlar.size() > 0 && oyuncu2.kartlar.size() > 0) {
            oyuncu1Yazi.setText(oyuncu1.getOyuncuAdi() + " : " + oyuncu1.getSkor());
            oyuncu2Yazi.setText(oyuncu2.getOyuncuAdi() + " : " + oyuncu2.getSkor());

            if (kartlariGor)
                yazilar.setText("Bir kart seçin.");
            else
                yazilar.setText(oyuncu2.getOyuncuAdi() + " kart seciyor.");

            //Oyuncu 2 kart secene kadar beklenir, sectigi kart one cikarilir
            int oyuncu2SecilenKartIndis = oyuncu2.kartSec(oyuncu2Kart1, oyuncu2Kart2, oyuncu2Kart3);
            yazilar.setText("Secilen kartlar aciliyor.");
            if (oyuncu2SecilenKartIndis == 0) {
                oyuncu2Kart1.setVisible(false);
                oyuncu2Kart1.setIcon(arkasiDonuk);
                oyuncu2Kart1.setBounds(90, 440, 110, 150);
                oyuncu2Kart1.setVisible(true);
                oyuncu2SecilenKart = oyuncu2Kart1;
            } else if (oyuncu2SecilenKartIndis == 1) {
                oyuncu2Kart2.setVisible(false);
                oyuncu2Kart2.setIcon(arkasiDonuk);
                oyuncu2Kart2.setBounds(230, 440, 110, 150);
                oyuncu2Kart2.setVisible(true);
                oyuncu2SecilenKart = oyuncu2Kart2;
            } else if (oyuncu2SecilenKartIndis == 2) {
                oyuncu2Kart3.setVisible(false);
                oyuncu2Kart3.setIcon(arkasiDonuk);
                oyuncu2Kart3.setBounds(370, 440, 110, 150);
                oyuncu2Kart3.setVisible(true);
                oyuncu2SecilenKart = oyuncu2Kart3;
            }

            //Oyuncu 1 kart secene kadar beklenir, sectigi kart one cikarilir
            yazilar.setText(oyuncu1.getOyuncuAdi() + " kart seciyor.");
            int oyuncu1SecilenKartIndis = oyuncu1.kartSec(oyuncu1Kart1, oyuncu1Kart2, oyuncu1Kart3);
            if (oyuncu1SecilenKartIndis == 0) {
                oyuncu1Kart1.setVisible(false);
                oyuncu1Kart1.setIcon(arkasiDonuk);
                oyuncu1Kart1.setBounds(90, 110, 110, 150);
                oyuncu1Kart1.setVisible(true);
                oyuncu1SecilenKart = oyuncu1Kart1;
            } else if (oyuncu1SecilenKartIndis == 1) {
                oyuncu1Kart2.setVisible(false);
                oyuncu1Kart2.setIcon(arkasiDonuk);
                oyuncu1Kart2.setBounds(230, 110, 110, 150);
                oyuncu1Kart2.setVisible(true);
                oyuncu1SecilenKart = oyuncu1Kart2;
            } else if (oyuncu1SecilenKartIndis == 2) {
                oyuncu1Kart3.setVisible(false);
                oyuncu1Kart3.setIcon(arkasiDonuk);
                oyuncu1Kart3.setBounds(370, 110, 110, 150);
                oyuncu1Kart3.setVisible(true);
                oyuncu1SecilenKart = oyuncu1Kart3;
            }

            try {
                sleep(1500);
            } catch (java.lang.InterruptedException e) {
                System.out.println("Hata");
            }

            //Iki secilen kartin da resmi gösterilir
            oyuncu1SecilenKart.setIcon(oyuncu1.kartlar.get(oyuncu1SecilenKartIndis).getResim());
            oyuncu2SecilenKart.setIcon(oyuncu2.kartlar.get(oyuncu2SecilenKartIndis).getResim());

            //Kartinin puani daha yuksek olan oyuncuya puan eklenir
            if (oyuncu1.kartlar.get(oyuncu1SecilenKartIndis).getHasarPuani() > oyuncu2.kartlar.get(oyuncu2SecilenKartIndis).getHasarPuani()) {
                yazilar.setText(oyuncu1.getOyuncuAdi() + "'a 5 puan eklendi.");
                oyuncu1.puanEkle();
            } else if (oyuncu1.kartlar.get(oyuncu1SecilenKartIndis).getHasarPuani() < oyuncu2.kartlar.get(oyuncu2SecilenKartIndis).getHasarPuani()) {
                yazilar.setText(oyuncu2.getOyuncuAdi() + "'a 5 puan eklendi.");
                oyuncu2.puanEkle();
            } else
                yazilar.setText("Berabere!");
            oyuncu1Yazi.setText(oyuncu1.getOyuncuAdi() + " : " + oyuncu1.getSkor());
            oyuncu2Yazi.setText(oyuncu2.getOyuncuAdi() + " : " + oyuncu2.getSkor());

            try {
                sleep(2500);
            } catch (java.lang.InterruptedException e) {
                System.out.println("Hata");
            }

            oyuncu1.kartlar.remove(oyuncu1SecilenKartIndis);
            oyuncu2.kartlar.remove(oyuncu2SecilenKartIndis);
            kartlariSifirla();

            //Ortada hala kart kalmissa iki oyuncudan da kart almasi istenir
            if (kartlar.size() > 0) {
                if (kartlariGor)
                    yazilar.setText("Ortadan kart al.");
                int oyuncu2AlinacakKart = oyuncu2.kartAl(ortaKartlar, kartlar);
                oyuncu2.kartlar.add(kartlar.get(oyuncu2AlinacakKart));
                kartlar.remove(oyuncu2AlinacakKart);
                kartlariSifirla();
                int oyuncu1AlinacakKart = oyuncu1.kartAl(ortaKartlar, kartlar);
                oyuncu1.kartlar.add(kartlar.get(oyuncu1AlinacakKart));
                kartlar.remove(oyuncu1AlinacakKart);
            }

            yazilar.setText("");
            kartlariSifirla();

            try {
                sleep(250);
            } catch (java.lang.InterruptedException e) {
                System.out.println("Hata");
            }

            oyuncu1Yazi.setText("");
            oyuncu2Yazi.setText("");
        }

        //Sonucu yazdir
        if (oyuncu1.getSkor() > oyuncu2.getSkor()) {
            oyunSonu.setText(oyuncu1.getOyuncuAdi() + " kazandi!");
        } else if (oyuncu1.getSkor() < oyuncu2.getSkor()) {
            oyunSonu.setText(oyuncu2.getOyuncuAdi() + " kazandi!");
        } else {
            oyunSonu.setText("Berabere!");
        }
    }

    //Tum kartlarin secilme, one cikma ve gosterilme durumlarini sifirlar, her el basi cagirilir
    public void kartlariSifirla() {
        oyuncu1Kart1.setVisible(false);
        oyuncu1Kart2.setVisible(false);
        oyuncu1Kart3.setVisible(false);
        oyuncu2Kart1.setVisible(false);
        oyuncu2Kart2.setVisible(false);
        oyuncu2Kart3.setVisible(false);
        ortaKart1.setVisible(false);
        ortaKart2.setVisible(false);
        ortaKart3.setVisible(false);
        ortaKart4.setVisible(false);

        if (oyuncu1.kartlar.size() > 0) {
            oyuncu1Kart1.setBounds(90, 80, 110, 150);
            if (hepsiniGor)
                oyuncu1Kart1.setIcon(oyuncu1.kartlar.get(0).getResim());
            else
                oyuncu1Kart1.setIcon(arkasiDonuk);
            oyuncu1Kart1.setVisible(true);
        }
        if (oyuncu1.kartlar.size() > 1) {
            oyuncu1Kart2.setBounds(230, 80, 110, 150);
            if (hepsiniGor)
                oyuncu1Kart2.setIcon(oyuncu1.kartlar.get(1).getResim());
            else
                oyuncu1Kart2.setIcon(arkasiDonuk);
            oyuncu1Kart2.setVisible(true);
        }
        if (oyuncu1.kartlar.size() > 2) {
            oyuncu1Kart3.setBounds(370, 80, 110, 150);
            if (hepsiniGor)
                oyuncu1Kart3.setIcon(oyuncu1.kartlar.get(2).getResim());
            else
                oyuncu1Kart3.setIcon(arkasiDonuk);
            oyuncu1Kart3.setVisible(true);
        }

        if (oyuncu2.kartlar.size() > 0) {
            oyuncu2Kart1.setBounds(90, 470, 110, 150);
            if (kartlariGor || hepsiniGor)
                oyuncu2Kart1.setIcon(oyuncu2.kartlar.get(0).getResim());
            else
                oyuncu2Kart1.setIcon(arkasiDonuk);
            oyuncu2Kart1.setVisible(true);
        }
        if (oyuncu2.kartlar.size() > 1) {
            oyuncu2Kart2.setBounds(230, 470, 110, 150);
            if (kartlariGor || hepsiniGor)
                oyuncu2Kart2.setIcon(oyuncu2.kartlar.get(1).getResim());
            else
                oyuncu2Kart2.setIcon(arkasiDonuk);
            oyuncu2Kart2.setVisible(true);
        }
        if (oyuncu2.kartlar.size() > 2) {
            oyuncu2Kart3.setBounds(370, 470, 110, 150);
            if (kartlariGor || hepsiniGor)
                oyuncu2Kart3.setIcon(oyuncu2.kartlar.get(2).getResim());
            else
                oyuncu2Kart3.setIcon(arkasiDonuk);
            oyuncu2Kart3.setVisible(true);
        }

        if (kartlar.size() > 0) {
            if (hepsiniGor)
                ortaKart1.setIcon(kartlar.get(0).getResim());
            else
                ortaKart1.setIcon(arkasiDonuk);
            ortaKart1.setVisible(true);
        }
        if (kartlar.size() > 1) {
            if (hepsiniGor)
                ortaKart2.setIcon(kartlar.get(1).getResim());
            else
                ortaKart2.setIcon(arkasiDonuk);
            ortaKart2.setVisible(true);
        }
        if (kartlar.size() > 2) {
            if (hepsiniGor)
                ortaKart3.setIcon(kartlar.get(2).getResim());
            else
                ortaKart3.setIcon(arkasiDonuk);
            ortaKart3.setVisible(true);
        }
        if (kartlar.size() > 3) {
            if (hepsiniGor)
                ortaKart4.setIcon(kartlar.get(3).getResim());
            else
                ortaKart4.setIcon(arkasiDonuk);
            ortaKart4.setVisible(true);
        }
    }

    public void kartlariTanimla() {
        Pikachu pikachu;
        Bulbasaur bulbasaur;
        Charmander charmender;
        Squirtle squirtle;
        Zubat zubat;
        Psyduck psyduck;
        Snorlax snorlax;
        Butterfree butterfree;
        Jigglypuff jigglypuff;
        Meowth meowth;
        pikachu = new Pikachu();
        bulbasaur = new Bulbasaur();
        charmender = new Charmander();
        squirtle = new Squirtle();
        zubat = new Zubat();
        psyduck = new Psyduck();
        snorlax = new Snorlax();
        butterfree = new Butterfree();
        jigglypuff = new Jigglypuff();
        meowth = new Meowth();
        kartlar.add(pikachu);
        kartlar.add(bulbasaur);
        kartlar.add(charmender);
        kartlar.add(squirtle);
        kartlar.add(zubat);
        kartlar.add(psyduck);
        kartlar.add(snorlax);
        kartlar.add(butterfree);
        kartlar.add(jigglypuff);
        kartlar.add(meowth);
    }

    //Rastgele ucer kart dagitan fonksiyon
    public void kartDagit() {
        Random rand = new Random();
        Pokemon kart;
        int indis;
        for (int i = 0; i < 3; i++) {
            indis = rand.nextInt(kartlar.size());
            kart = kartlar.get(indis);
            oyuncu1.kartlar.add(kart);
            kartlar.remove(indis);
            indis = rand.nextInt(kartlar.size());
            kart = kartlar.get(indis);
            oyuncu2.kartlar.add(kart);
            kartlar.remove(indis);
        }
    }

    public static void main(String[] args) throws java.io.IOException {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        JLabel arkaPlan = new JLabel(new ImageIcon(ImageIO.read(new File("arkaplan.png"))));
        frame.setContentPane(arkaPlan);
        Main oyun = new Main(frame);
        oyun.ekranOlustur();
    }
}
