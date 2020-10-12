#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sehirdugum
{
    int plaka;
    char sehiradi[30];
    char bolge[5];
    int komsusayisi;
    struct sehirdugum *onceki;
    struct sehirdugum *sonraki;
    struct komsudugum *ilkkomsu;
};

struct komsudugum
{
    int plaka;
    struct komsudugum *sonraki;
};

char *sehiradidondur(struct sehirdugum *ilk, int plaka);
char *tambolgeadidondur(char bolgekodu[]);
struct komsudugum *komsudugumolustur(int plaka);
struct sehirdugum *dugumolustur(int plaka, char sehiradi[], char bolge[]);
int plakadondur(struct sehirdugum *ilk, char sehirismi[]);
void komsuekle(struct sehirdugum **ilk, int anaplaka, int komsuplaka);
void sehirekle(struct sehirdugum **ilk, struct sehirdugum *eklenecekdugum);
void dosyadanoku(struct sehirdugum **ilk);
void dosyadankomsularioku(struct sehirdugum **ilk);
void listeyazdir(struct sehirdugum *ilk);
int plakavarmi(struct sehirdugum *ilk, int plaka);
void yenisehirekle(struct sehirdugum **ilk, int plaka, char sehiradi[], char bolge[]);
char *bolgedondur(struct sehirdugum *ilk, int plaka);
void plakayagoreyazdir(struct sehirdugum **ilk, int plaka);
void komsuluksil(struct sehirdugum **ilk, int plaka1, int plaka2);
void sehiradinagoreyazdir(struct sehirdugum **ilk, char sehiradi[]);
void bolgeyegoreyazdir(struct sehirdugum *ilk, char bolge[]);
void komsusayisinagoreyazdir(struct sehirdugum *ilk, int minimumkomsu, int maksimumkomsu);
void sehirsil(struct sehirdugum **ilk, int plaka);
void menu(struct sehirdugum **ilk);
int komsularindavarmi(struct sehirdugum *ilk, int plaka1, int plaka2);
void bonus(struct sehirdugum *ilk, int min, int max);

int main()
{
    //ilk dugumu bos sekilde olustur
    struct sehirdugum *ilk = NULL;
    ilk = (struct sehirdugum *)malloc(sizeof(struct sehirdugum));
    ilk->onceki = NULL;
    ilk->sonraki = NULL;
    ilk->ilkkomsu = NULL;
    strcpy(ilk->sehiradi, "bos");

    //dosyadan sehirleri oku
    dosyadanoku(&ilk);
    listeyazdir(ilk);

    //programi calistir
    menu(&ilk);
    return 0;
}

//bagli listenin ilk dugumunu ve bir plaka alip, o plakaya sahip sehrin adini dondurur
char *sehiradidondur(struct sehirdugum *ilk, int plaka)
{
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (plaka == anlik->plaka)
        {
            return anlik->sehiradi;
        }
        if (anlik->sonraki == NULL)
        {
            break;
        }
        anlik = anlik->sonraki;
    }
    return "hata";
}

//bolge kodu alip, o koda sahip bolgenin adini dondurur
char *tambolgeadidondur(char bolgekodu[])
{
    if (!strcmp(bolgekodu, "MA"))
    {
        return "Marmara";
    }
    else if (!strcmp(bolgekodu, "EG"))
    {
        return "Ege";
    }
    else if (!strcmp(bolgekodu, "AK"))
    {
        return "Akdeniz";
    }
    else if (!strcmp(bolgekodu, "DA"))
    {
        return "Dogu Anadolu";
    }
    else if (!strcmp(bolgekodu, "GA"))
    {
        return "Guneydogu Anadolu";
    }
    else if (!strcmp(bolgekodu, "IA"))
    {
        return "Ic Anadolu";
    }
    else if (!strcmp(bolgekodu, "KA"))
    {
        return "Karadeniz";
    }
    return "Hatali Bolge Kodu!";
}

//bir plaka alip o plakaya sahip bir komsudugum dondurur
struct komsudugum *komsudugumolustur(int plaka)
{
    struct komsudugum *dugum = NULL;
    dugum = (struct komsudugum *)malloc(sizeof(struct komsudugum));
    dugum->sonraki = NULL;
    dugum->plaka = plaka;
    return dugum;
};

//bir sehir dugumu olusturup dondurur
struct sehirdugum *dugumolustur(int plaka, char sehiradi[], char bolge[])
{
    struct sehirdugum *dugum = NULL;
    dugum = (struct sehirdugum *)malloc(sizeof(struct sehirdugum));
    dugum->ilkkomsu = NULL;
    dugum->onceki = NULL;
    dugum->sonraki = NULL;
    dugum->plaka = plaka;
    dugum->komsusayisi = 0;
    strcpy(dugum->sehiradi, sehiradi);
    strcpy(dugum->bolge, bolge);
    return dugum;
};

//sehir adi alip o ada sahip sehrin plakasini dondurur
int plakadondur(struct sehirdugum *ilk, char sehirismi[])
{
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (!strcmp(sehirismi, anlik->sehiradi))
        {
            return anlik->plaka;
        }
        if (anlik->sonraki == NULL)
        {
            break;
        }
        anlik = anlik->sonraki;
    }
    return -1;
}

//komsu eklenecek sehir ve komsusunun plakasini alip komsu olarak ekler
void komsuekle(struct sehirdugum **ilk, int anaplaka, int komsuplaka)
{
    if (!strcmp(sehiradidondur(*ilk, komsuplaka), "hata"))
    {
        printf("Komsu eklenmek istenen sehir bulunamadi.\n\n");
        return;
    }
    struct sehirdugum *anliksehir = *ilk;
    struct komsudugum *eklenecekdugum = komsudugumolustur(komsuplaka);

    while (1)
    {
        if (anaplaka == anliksehir->plaka)
        {
            if (anliksehir->ilkkomsu == NULL)
            {
                anliksehir->ilkkomsu = eklenecekdugum;
                anliksehir->komsusayisi++;
                return;
            }
            if (komsuplaka < anliksehir->ilkkomsu->plaka)
            {
                eklenecekdugum->sonraki = anliksehir->ilkkomsu;
                anliksehir->ilkkomsu = eklenecekdugum;
                anliksehir->komsusayisi++;
                return;
            }
            if (komsuplaka == anliksehir->ilkkomsu->plaka)
            {
                printf("Zaten %s sehrinin komsulari arasinda %s bulunuyor.\n\n", anliksehir->sehiradi, sehiradidondur(*ilk, komsuplaka));
                return;
            }

            struct komsudugum *anlikkomsu = anliksehir->ilkkomsu;
            while (1)
            {
                if (anlikkomsu->sonraki == NULL)
                {
                    anlikkomsu->sonraki = eklenecekdugum;
                    anliksehir->komsusayisi++;
                    return;
                }
                if (komsuplaka == anlikkomsu->sonraki->plaka)
                {
                    printf("Zaten %s sehrinin komsulari arasinda %s bulunuyor.\n\n", anliksehir->sehiradi, sehiradidondur(*ilk, komsuplaka));
                    return;
                }
                if (eklenecekdugum->plaka < anlikkomsu->sonraki->plaka)
                {
                    eklenecekdugum->sonraki = anlikkomsu->sonraki;
                    anlikkomsu->sonraki = eklenecekdugum;
                    anliksehir->komsusayisi++;
                    return;
                }
                anlikkomsu = anlikkomsu->sonraki;
            }
        }
        if (anliksehir->sonraki == NULL)
        {
            break;
        }
        anliksehir = anliksehir->sonraki;
    }
    printf("Eklenecek sehir bulunamadi.\n\n");
    return;
}

//bir sehir dugumu alip bagli listedeki siralamada yerine ekler
void sehirekle(struct sehirdugum **ilk, struct sehirdugum *eklenecekdugum)
{
    struct sehirdugum *anlik = *ilk;
    if (!strcmp("bos", anlik->sehiradi))
    {
        *ilk = eklenecekdugum;
        return;
    }
    if (eklenecekdugum->plaka < anlik->plaka)
    {
        eklenecekdugum->sonraki = *ilk;
        (*ilk)->onceki = eklenecekdugum;
        *ilk = eklenecekdugum;
        return;
    }
    while (1)
    {
        if (anlik->sonraki == NULL)
        {
            eklenecekdugum->onceki = anlik;
            anlik->sonraki = eklenecekdugum;
            break;
        }
        if (anlik->sonraki->plaka > eklenecekdugum->plaka)
        {
            eklenecekdugum->sonraki = anlik->sonraki;
            eklenecekdugum->onceki = anlik;
            anlik->sonraki->onceki = eklenecekdugum;
            anlik->sonraki = eklenecekdugum;
            break;
        }
        anlik = anlik->sonraki;
    }
}

//dosyadan sehirleri okuyup bagli listeye ekler
void dosyadanoku(struct sehirdugum **ilk)
{
    FILE *dosya = fopen("sehirler.txt", "r");
    char satir[300];
    int plaka;
    char sehiradi[50];
    char bolge[5];
    while ((fgets(satir, 300, dosya)) != NULL)
    {
        char *token = strtok(satir, ",");
        plaka = atoi(token);
        token = strtok(NULL, ",");
        strcpy(sehiradi, token);
        token = strtok(NULL, ",");
        strcpy(bolge, token);
        sehirekle(&(*ilk), dugumolustur(plaka, sehiradi, bolge));
    }
    dosyadankomsularioku(&(*ilk));
    listeyazdir(*ilk);
    printf("Dosyadaki tum sehirler okunup cikti dosyasina yazdirilmistir.\n\n\n");
};

//dosyadan sehirlerin komsularini okur ve bagli listeye ekler
void dosyadankomsularioku(struct sehirdugum **ilk)
{
    FILE *dosya = fopen("sehirler.txt", "r");
    char satir[300];
    int plaka;
    while ((fgets(satir, 300, dosya)) != NULL)
    {
        satir[strlen(satir) - 1] = '\0';
        char *token = strtok(satir, ",");
        plaka = atoi(token);
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        while (1)
        {
            token = strtok(NULL, ",");
            if (token == NULL)
            {
                break;
            }
            komsuekle(&(*ilk), plaka, plakadondur(*ilk, token));
        }
    }
}

//cikti dosyasina bagli listeyi yazdirir
void listeyazdir(struct sehirdugum *ilk)
{
    FILE *dosya = fopen("cikti.txt", "w");
    struct sehirdugum *anliksehir = ilk;
    struct komsudugum *anlikkomsu;
    while (1)
    {
        fprintf(dosya, "%s \n%d            ", anliksehir->sehiradi, anliksehir->plaka);
        anlikkomsu = anliksehir->ilkkomsu;
        while (1)
        {
            fprintf(dosya, "   ==> %d ", anlikkomsu->plaka);
            if (anlikkomsu->sonraki == NULL)
            {
                break;
            }
            anlikkomsu = anlikkomsu->sonraki;
        }
        fprintf(dosya, "\n%s\nKomsu Sayisi: %d\n\n", tambolgeadidondur(anliksehir->bolge), anliksehir->komsusayisi);
        if (anliksehir->sonraki == NULL)
        {
            break;
        }
        fprintf(dosya, " |  / \\\n");
        fprintf(dosya, " |   |\n");
        fprintf(dosya, "\\ /  |\n\n");
        anliksehir = anliksehir->sonraki;
    }
    fclose(dosya);
}

//plakanin bagli listede olup olmadigini dondurur
int plakavarmi(struct sehirdugum *ilk, int plaka)
{
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (plaka == anlik->plaka)
        {
            return 1;
        }
        if (anlik->sonraki == NULL)
        {
            break;
        }
        anlik = anlik->sonraki;
    }
    return 0;
}

//sehirdugum listesine yeni sehir ekler
void yenisehirekle(struct sehirdugum **ilk, int plaka, char sehiradi[], char bolge[])
{
    if (plaka < 1)
    {
        printf("Plaka 0'dan buyuk bir sayi olmalidir!\n\n");
        return;
    }
    if (!strcmp(tambolgeadidondur(bolge), "Hatali Bolge Kodu!"))
    {
        printf("Hatali bolge kodu girdiniz!\n\n");
        return;
    }
    if (plakavarmi(*ilk, plaka) == 1)
    {
        printf("Zaten bu plakaya sahip bir sehir var!\n\n");
        return;
    }
    else if (plakadondur(*ilk, sehiradi) != -1)
    {
        printf("Zaten bu adda bir sehir var!\n\n");
        return;
    }
    struct sehirdugum *yenidugum = dugumolustur(plaka, sehiradi, bolge);
    sehirekle(&(*ilk), yenidugum);
    int komsuplaka;
    while (1)
    {
        printf("%s sehrine eklenecek komsunun plakasi (-1 bozar):  ", sehiradi);
        scanf("%d", &komsuplaka);
        if (komsuplaka == -1)
        {
            break;
        }
        if (plakavarmi(*ilk, komsuplaka) == 0)
        {
            printf("Bu plakaya sahip bir il bulunamadi!\n\n");
            continue;
        }
        komsuekle(&(*ilk), komsuplaka, plaka);
        komsuekle(&(*ilk), plaka, komsuplaka);
        printf("Islem tamamlandi.\n\n");
    }
}

//plaka alip o sehrin bulundugu bolgeyi dondurur
char *bolgedondur(struct sehirdugum *ilk, int plaka)
{
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (plaka == anlik->plaka)
        {
            return anlik->bolge;
        }
        if (anlik->sonraki == NULL)
        {
            break;
        }
        anlik = anlik->sonraki;
    }
    return "hata";
}

//verilen plakadaki sehri cikti dosyasina yazdirir
void plakayagoreyazdir(struct sehirdugum **ilk, int plaka)
{
    if (!plakavarmi(*ilk, plaka))
    {
        int secim;
        printf("Plaka bulunamadi, eklemek icin 1 gecmek icin 0 giriniz: ");
        scanf("%d", &secim);
        if (secim)
        {
            char sehiradi[50];
            char bolge[5];
            printf("Sehir adi giriniz: ");
            while ((getchar()) != '\n')
                ;
            fgets(sehiradi, 50, stdin);
            sehiradi[strlen(sehiradi) - 1] = '\0';
            printf("Bolge kodu giriniz: ");
            fgets(bolge, 20, stdin);
            bolge[strlen(bolge) - 1] = '\0';
            yenisehirekle(&(*ilk), plaka, sehiradi, bolge);
        }
    }
    else
    {
        struct sehirdugum *anliksehir = *ilk;
        struct komsudugum *anlikkomsu;
        while (1)
        {
            if (plaka == anliksehir->plaka)
            {
                printf("Plaka: %d -- Sehir adi: %s -- Bolge: %s -- Komsu sayisi: %d\n\nKomsular:\n\n", anliksehir->plaka, anliksehir->sehiradi, tambolgeadidondur(anliksehir->bolge), anliksehir->komsusayisi);
                anlikkomsu = anliksehir->ilkkomsu;
                while (1)
                {
                    printf("Plaka: %d -- Sehir adi: %s -- Bolge: %s\n", anlikkomsu->plaka, sehiradidondur(*ilk, anlikkomsu->plaka), tambolgeadidondur(bolgedondur(*ilk, anlikkomsu->plaka)));
                    if (anlikkomsu->sonraki == NULL)
                    {
                        printf("\n\n");
                        return;
                    }
                    anlikkomsu = anlikkomsu->sonraki;
                }
            }
            if (anliksehir->sonraki == NULL)
            {
                break;
            }
            anliksehir = anliksehir->sonraki;
        }
    }
    return;
}

//iki sehir arasindaki komsuluk iliskisini siler
void komsuluksil(struct sehirdugum **ilk, int plaka1, int plaka2)
{
    struct sehirdugum *anliksehir = *ilk;
    if (!strcmp(sehiradidondur(*ilk, plaka1), "hata"))
    {
        printf("%d plakali bir sehir yok!\n\n", plaka1);
        return;
    }
    while (1)
    {
        if (plaka1 == anliksehir->plaka)
        {
            struct komsudugum *anlikkomsu = anliksehir->ilkkomsu;
            if (plaka2 == anliksehir->ilkkomsu->plaka)
            {
                struct komsudugum *silinecek = anliksehir->ilkkomsu;
                anliksehir->ilkkomsu = anliksehir->ilkkomsu->sonraki;
                free(silinecek);
                anliksehir->komsusayisi--;
                printf("%s sehrinin komsulari arasinda artik %s bulunmuyor.\n\n", sehiradidondur(*ilk, plaka1), sehiradidondur(*ilk, plaka2));
                return;
            }
            while (1)
            {
                if (anlikkomsu->sonraki == NULL)
                {
                    printf("%d plakali sehrin komsulari arasinda %d plakali sehir bulunamadi!\n\n", plaka1, plaka2);
                    return;
                }
                if (plaka2 == anlikkomsu->sonraki->plaka)
                {
                    struct komsudugum *silinecek = anlikkomsu->sonraki;
                    anlikkomsu->sonraki = anlikkomsu->sonraki->sonraki;
                    free(silinecek);
                    anliksehir->komsusayisi--;
                    printf("%s sehrinin komsulari arasinda artik %s bulunmuyor.\n\n", sehiradidondur(*ilk, plaka1), sehiradidondur(*ilk, plaka2));
                    return;
                }
                anlikkomsu = anlikkomsu->sonraki;
            }
        }
        anliksehir = anliksehir->sonraki;
    }
}

//verilen ada sahip sehrin bilgilerini yazdirir
void sehiradinagoreyazdir(struct sehirdugum **ilk, char sehiradi[])
{
    if (plakadondur(*ilk, sehiradi) == -1)
    {
        int secim;
        printf("Boyle bir sehir bulunamadi, eklemek icin 1 gecmek icin 0 giriniz: ");
        scanf("%d", &secim);
        if (secim)
        {
            int plaka;
            char bolge[5];
            printf("Plaka giriniz:  ");
            scanf("%d", &plaka);
            while ((getchar()) != '\n')
                ;
            printf("Bolge kodu giriniz: ");
            fgets(bolge, 20, stdin);
            bolge[strlen(bolge) - 1] = '\0';
            yenisehirekle(&(*ilk), plaka, sehiradi, bolge);
        }
    }
    else
    {
        struct sehirdugum *anliksehir = *ilk;
        struct komsudugum *anlikkomsu;
        while (1)
        {
            if (!strcmp(sehiradi, anliksehir->sehiradi))
            {
                printf("Plaka: %d -- Sehir adi: %s -- Bolge: %s -- Komsu sayisi: %d\n\nKomsular:\n\n", anliksehir->plaka, anliksehir->sehiradi, tambolgeadidondur(anliksehir->bolge), anliksehir->komsusayisi);
                anlikkomsu = anliksehir->ilkkomsu;
                while (1)
                {
                    printf("Plaka: %d -- Sehir adi: %s -- Bolge: %s\n", anlikkomsu->plaka, sehiradidondur(*ilk, anlikkomsu->plaka), tambolgeadidondur(bolgedondur(*ilk, anlikkomsu->plaka)));
                    if (anlikkomsu->sonraki == NULL)
                    {
                        printf("\n\n");
                        return;
                    }
                    anlikkomsu = anlikkomsu->sonraki;
                }
            }
            if (anliksehir->sonraki == NULL)
            {
                break;
            }
            anliksehir = anliksehir->sonraki;
        }
    }
    return;
}

//verilen bolgedeki sehirleri yazdirir
void bolgeyegoreyazdir(struct sehirdugum *ilk, char bolge[])
{
    printf("%s bolgeindeki sehirler:\n", tambolgeadidondur(bolge));
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (!strcmp(anlik->bolge, bolge))
        {
            printf("plaka : %d -- sehir adi: %s -- komsu sayisi: %d \n", anlik->plaka, anlik->sehiradi, anlik->komsusayisi);
        }
        if (anlik->sonraki == NULL)
        {
            printf("\n\n");
            break;
        }
        anlik = anlik->sonraki;
    }
}

//belirli deger araliginda komsu sayisina sahip sehirleri yazdirir
void komsusayisinagoreyazdir(struct sehirdugum *ilk, int minimumkomsu, int maksimumkomsu)
{
    printf("%d'den fazla komsusu olan sehirler:\n ", minimumkomsu);
    struct sehirdugum *anlik = ilk;
    while (1)
    {
        if (anlik->komsusayisi >= minimumkomsu && anlik->komsusayisi <= maksimumkomsu)
        {
            printf("plaka : %d -- sehir adi: %s -- bolge: %s -- komsu sayisi: %d\n", anlik->plaka, anlik->sehiradi, tambolgeadidondur(anlik->bolge), anlik->komsusayisi);
        }
        if (anlik->sonraki == NULL)
        {
            printf("\n\n");
            break;
        }
        anlik = anlik->sonraki;
    }
}

//listeden komsuluk iliskileriyle birlikte sehir siler
void sehirsil(struct sehirdugum **ilk, int plaka)
{
    int komsular[20];
    int sayac = 0;
    if (!strcmp(sehiradidondur(*ilk, plaka), "hata"))
    {
        printf("%d plakali bir sehir bulunamadi!\n\n", plaka);
        return;
    }
    struct sehirdugum *anliksehir = *ilk;
    struct komsudugum *anlikkomsu;
    if (anliksehir->plaka == plaka)
    {
        anlikkomsu = anliksehir->ilkkomsu;
        while (1)
        {
            komsular[sayac] = anlikkomsu->plaka;
            sayac++;
            if (anlikkomsu->sonraki == NULL)
            {
                break;
            }
            anlikkomsu = anlikkomsu->sonraki;
        }

        for (int i = 0; i < sayac; i++)
        {
            komsuluksil(&(*ilk), plaka, komsular[i]);
            komsuluksil(&(*ilk), komsular[i], plaka);
        }
        printf("%s sehri butunuyle silinmistir.\n\n", anliksehir->sehiradi);
        *ilk = (*ilk)->sonraki;
        (*ilk)->onceki = NULL;
        free(anliksehir);
        return;
    }
    while (1)
    {
        if (anliksehir->sonraki->plaka == plaka)
        {
            anlikkomsu = anliksehir->sonraki->ilkkomsu;
            while (1)
            {
                komsular[sayac] = anlikkomsu->plaka;
                sayac++;
                if (anlikkomsu->sonraki == NULL)
                {
                    break;
                }
                anlikkomsu = anlikkomsu->sonraki;
            }
            for (int i = 0; i < sayac; i++)
            {
                komsuluksil(&(*ilk), plaka, komsular[i]);
                komsuluksil(&(*ilk), komsular[i], plaka);
            }
            struct sehirdugum *silinecek = anliksehir->sonraki;
            anliksehir->sonraki = anliksehir->sonraki->sonraki;
            anliksehir->sonraki->onceki = anliksehir;
            printf("%s sehri butunuyle silinmistir.\n\n", silinecek->sehiradi);
            free(silinecek);
            return;
        }
        anliksehir = anliksehir->sonraki;
    }
}

//programin calistigi fonksiyondur, bu fonksiyon sonunda program sonlandirilir
void menu(struct sehirdugum **ilk)
{
    int secim;
    while (1)
    {
        printf("1. Yeni sehir ekle\n2. Yeni komsuluk ekle\n3. Isimle sehir ara\n4. Plakayla sehir ara\n");
        printf("5. Sehir sil\n6. Komsuluk sil\n7. Bolgedeki sehirleri listele\n8. Komsu sayisina gore sehir listele\n");
        printf("9. Belirli aralikta komsu sayisina ve belirli ortak komsulara sahip sehirler\n0. Cikis\n\nSeciminiz: ");
        scanf("%d", &secim);

        //ekrani temizle
        system("clear||cls");
        if (secim == 0)
        {
            printf("Program sonlandirildi...");
            break;
        }
        else if (secim == 1)
        {
            int plaka;
            printf("Plaka giriniz: ");
            scanf("%d", &plaka);
            char sehiradi[50];
            char bolge[5];
            printf("Sehir adi giriniz: ");
            //input bufferini temizle
            while ((getchar()) != '\n')
                ;
            fgets(sehiradi, 50, stdin);
            sehiradi[strlen(sehiradi) - 1] = '\0';
            printf("Bolge kodu giriniz: ");
            fgets(bolge, 20, stdin);
            bolge[strlen(bolge) - 1] = '\0';
            yenisehirekle(&(*ilk), plaka, sehiradi, bolge);
        }
        else if (secim == 2)
        {
            printf("Baglanacak sehirlerden birincisinin plakasi: ");
            int plaka1, plaka2;
            scanf("%d", &plaka1);
            printf("Baglanacak sehirlerden ikincisinin plakasi: ");
            scanf("%d", &plaka2);
            komsuekle(&(*ilk), plaka1, plaka2);
            komsuekle(&(*ilk), plaka2, plaka1);
        }
        else if (secim == 3)
        {
            printf("Aramak istediginiz sehrin adini giriniz: ");
            char sehiradi[50];
            //input bufferini temizle
            while ((getchar()) != '\n')
                ;
            fgets(sehiradi, 50, stdin);
            sehiradi[strlen(sehiradi) - 1] = '\0';
            sehiradinagoreyazdir(&(*ilk), sehiradi);
        }
        else if (secim == 4)
        {
            printf("Plaka giriniz: ");
            int plaka;
            scanf("%d", &plaka);
            plakayagoreyazdir(&(*ilk), plaka);
        }
        else if (secim == 5)
        {
            printf("Silmek istedginiz sehrin plakasini giriniz: ");
            int plaka;
            scanf("%d", &plaka);
            sehirsil(&(*ilk), plaka);
        }
        else if (secim == 6)
        {
            int plaka1, plaka2;
            printf("Komsulugu silmek istediginiz birinci plakayi giriniz: ");
            scanf("%d", &plaka1);
            printf("Komsulugu silmek istediginiz ikinci plakayi giriniz: ");
            scanf("%d", &plaka2);
            komsuluksil(&(*ilk), plaka1, plaka2);
            komsuluksil(&(*ilk), plaka2, plaka1);
        }
        else if (secim == 7)
        {
            printf("Sehirlerini yazdirmak istediginiz bolgenin kodunu giriniz: ");
            char bolge[50];
            //input bufferini temizle
            while ((getchar()) != '\n')
                ;
            fgets(bolge, 50, stdin);
            bolge[strlen(bolge) - 1] = '\0';
            bolgeyegoreyazdir(*ilk, bolge);
        }
        else if (secim == 8)
        {
            printf("Minimum komsu sayisi: ");
            int min, max;
            scanf("%d", &min);
            printf("Maksimum komsu sayisi: ");
            scanf("%d", &max);
            komsusayisinagoreyazdir(*ilk, min, max);
        }
        else if (secim == 9)
        {
            printf("Minimum komsu sayisi: ");
            int min, max;
            scanf("%d", &min);
            printf("Maksimum komsu sayisi: ");
            scanf("%d", &max);
            bonus(*ilk, min, max);
        }
        else
        {
            printf("Hatali giris yaptiniz!\n\n\n");
        }
        listeyazdir(*ilk);
    }
}

//iki sehrin komsu olup olmadigini dondurur
int komsularindavarmi(struct sehirdugum *ilk, int plaka1, int plaka2)
{
    struct sehirdugum *anlik = ilk;
    if (!strcmp(sehiradidondur(ilk, plaka1), "hata"))
    {
        printf("%d plakali bir sehir bulunamadi!\n", plaka1);
        return 0;
    }
    while (1)
    {
        if (anlik->plaka == plaka1)
        {
            struct komsudugum *anlikkomsu = anlik->ilkkomsu;
            while (1)
            {
                if (anlikkomsu->plaka == plaka2)
                {
                    return 1;
                }
                if (anlikkomsu->sonraki == NULL)
                    break;
                anlikkomsu = anlikkomsu->sonraki;
            }
            return 0;
        }
        anlik = anlik->sonraki;
    }
    return 0;
}

//proje dosyasinda bu fonksiyonun tam islevi bonus kisminda yazmaktadir
void bonus(struct sehirdugum *ilk, int min, int max)
{
    int komsular[20];
    int sayac = 0;
    struct sehirdugum *anliksehir = ilk;
    while (1)
    {
        printf("Aranacak ortak komsulardan %d.'sinin plakasini giriniz (-1 bozar): ", sayac + 1);
        scanf("%d", &komsular[sayac]);
        if (komsular[sayac] == -1)
        {
            break;
        }
        sayac++;
    }
    while (1)
    {
        if (anliksehir->komsusayisi >= min && anliksehir->komsusayisi <= max)
        {
            int kontrol = 1;
            for (int i = 0; i < sayac; i++)
            {
                if (komsularindavarmi(ilk, anliksehir->plaka, komsular[i]) == 0)
                {
                    kontrol = 0;
                }
            }
            if (kontrol == 1)
            {
                printf("%s\n", anliksehir->sehiradi);
            }
        }
        if (anliksehir->sonraki == NULL)
        {
            break;
        }
        anliksehir = anliksehir->sonraki;
    }
}
