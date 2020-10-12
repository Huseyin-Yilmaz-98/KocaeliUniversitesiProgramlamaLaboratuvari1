#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>

struct noktastruct
{
    double x;
    double y;
    double z;
    int r;
    int g;
    int b;
};

struct dosyabilgi
{
    char dosyaadi[100]; //.nkt kismi da dahil olmak üzere dosyanin adini saklar
    int kontrol; //baslik bilgileri ve noktalar kontrol edildikten sonra dosyada islem yapilip yapilmayacagina karar verir
    int rgb; //dosyadaki noktalarin rgb bilgisiyle beraber verilip verilmedigi bilgisini saklar
    int noktasayi; //basliktan okunan nokta sayisini saklar
    char noktalar[20]; //basliktaki noktalar satirini saklar
    char datatype[20]; //basliktaki data satirini saklar
    char version[30]; //basliktaki version satirini saklar
    char tanim[50]; //dosyanin ilk satirini saklar
    int enuzak1; //en uzak noktalardan ilkinin indisini saklar
    int enuzak2; //en uzak noktalardan ikincinin indisini saklar
    int enyakin1; //en yakin noktalardan ilkinin indisini saklar
    int enyakin2; //en yakin noktalardan ikincinin indisini saklar
    int freekontrol; //noktastruct structi için malloc kullanilip kullanilmadigini, free gerekip gerekmeyecegi bilgisini saklar
    double ortalama; //dosyadaki noktalarin mesafelerinin ortalamasidir
    struct noktastruct *nokta; //nokta bilgilerini saklar
};

double noktalararasiuzaklik(double x1,double y1,double z1,double x2,double y2,double z2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2)); //iki üç boyutlu nokta arasindaki mesafeyi döndürür
}
void menu();
struct dosyabilgi baslikkontrol();
struct dosyabilgi noktalarioku();
struct dosyabilgi binarynoktaoku();
struct dosyabilgi enyakinenuzakveortalama();
void kureyazdir();
void kupkoordinat();

int main()
{
    char dosyaismi[100];
    char dosyaadlari[50][100];
    int dosyasayisi=0;
    struct dirent *okunandosya;
    DIR *klasor = opendir("."); //programin çalistirildigi dizini açar
    while ((okunandosya = readdir(klasor)) != NULL) //dosya kalmayana kadar okur
    {
        strcpy(dosyaismi,okunandosya->d_name); //o anki dosyanin adini dosyaismi isimli stringe geçici olarak atar
        if(dosyaismi[strlen(dosyaismi)-4]=='.' &&dosyaismi[strlen(dosyaismi)-3]=='n' && dosyaismi[strlen(dosyaismi)-2]=='k' && dosyaismi[strlen(dosyaismi)-1]=='t' && strcmp(dosyaismi,"output.nkt"))
        {
            strcpy(dosyaadlari[dosyasayisi],dosyaismi); //son 4 harf ".nkt" ise dosyaadlarina ekler
            dosyasayisi++;
        }
    }
    closedir(klasor); //dizini kapatir
    if(dosyasayisi==0)
    {
        printf("Hic .nkt uzantili dosya bulunamadi!");
        return 0; //dizinde hic .nkt uzantili dosya bulunamadiysa programi sonlandirir
    }
    struct dosyabilgi dosyalar[dosyasayisi]; //tespit edilen dosya sayisi kadar dosyabilgi structindan yer ayirir
    for(int i=0; i<dosyasayisi; i++)
    {
        dosyalar[i].ortalama=-1; //ortalamanin hesaplanip hesaplanmadigini tespit etmek için önce -1 atiyoruz
        dosyalar[i].freekontrol=0; //malloc kullanilip kullanilmadigini tespit etmek için önce 0 atiyoruz
        dosyalar[i].kontrol=-1; //1. islemin çalisip çalismadigini tespit etmek için kontrole önce -1 atiyoruz
        strcpy(dosyalar[i].dosyaadi,dosyaadlari[i]); //sirayla dosyaadlarini struct dizisindeki yerlerine atiyoruz
        printf("%s\n",dosyalar[i].dosyaadi);
    }
    printf("\n");
    menu(dosyalar,dosyasayisi); //menü fonksiyonuna dosyalarin bulundugu struct dizisini ve dosyasayisini yolluyoruz
    return 0; //menü fonksiyonu sonlandiktan sonra programi sonlandiriyoruz
}
void menu(struct dosyabilgi dosyalar[],int dosyasayisi){
    int secim;
    FILE *dosya;
    while(1)
    {
        do
        {
            printf("\n\nIslemler:\n\n1. Dosyalari kontrol et\n2. En yakin ve en uzak noktalari bul\n3. Kup koordinatlari bul\n4. Kurenin icinde kalan noktalari bul\n5. Nokta uzakliklarinin ortalamasini bul\n0. Cikis\n\nSeciminiz: ");
            scanf("%d",&secim);
            if(!(secim>=0 && secim<=5))
            {
                system("@cls||clear"); //hem linux hem de windowsta ekran temizleme komutunun düzgün çalismasi için bu kullanim tercih edilmistir
                printf("Hatali secim yaptiniz!\n");
            }
        }
        while(!(secim>=0 && secim<=5)); //seçim 0'dan küçük veya 5'ten büyük olduðu sürece tekrar seçim yapilmasini ister
        if(secim==0)
        {
            for(int i=0; i<dosyasayisi; i++)
            {
                if(dosyalar[i].freekontrol==1)
                    free(dosyalar[i].nokta); //dosya structinda malloc kullanildiysa free ile bellek temizlenir
            }
            return; //fonksiyon sonlandirilir
        }
        else if(secim==1)
        {
            system("@cls||clear");
            dosya=fopen("output.nkt","w"); //islem 1 yapildiginda dosya write formatinda açilir ve varsa önceki output.nkt dosyasi temizlenir
            fprintf(dosya,"SECIM 1\n");
            fclose(dosya);
            for(int i=0; i<dosyasayisi; i++)
            {
                dosyalar[i]=baslikkontrol(dosyalar[i]); //Tek tek tüm dosyalarda baslik kontrolü gerçeklesir
                if(dosyalar[i].kontrol==1) //yalnizca kontrolü 1 olan dosyalarin noktalari okunur
                {
                    dosyalar[i].nokta=(struct noktastruct*)malloc(sizeof(struct noktastruct) * dosyalar[i].noktasayi); //basliktan okunan nokta sayisi kadar bellekte yer açilir
                    dosyalar[i].freekontrol=1; //malloc kullanildigini belirtmek için freekontrol 1'e esitlenir
                    if(!strcmp(dosyalar[i].datatype,"DATA ascii\n"))
                        dosyalar[i]=noktalarioku(dosyalar[i]); //ascii formatindaki dosyalarin noktalarini okumak için noktalarioku fonksiyonu çagirilir
                    else
                        dosyalar[i]=binarynoktaoku(dosyalar[i]); //binary formatindaki dosyalarin noktalarini okumak için binarynoktaoku fonksiyonu çagirilir
                }
            }
            printf("Secim 1 tamamlandi.\n\n");
        }
        else if(secim==2)
        {
            system("@cls||clear");
            if(dosyalar[0].kontrol==-1) //ilk dosyada kontrol -1'e esitse 1. islemin yapilmadigina dair uyari verilir ve herhangi bir hesaplama yapilmaz
            {
                printf("Once 1. islemi calistirmaniz gerekmektedir!\n\n");
                continue;
            }
            dosya=fopen("output.nkt","a"); //bundan sonra dosya hep append formatinda açilir ve üstüne ekleme yapilir
            fprintf(dosya,"\n\nSECIM 2\n");
            fclose(dosya);
            printf("SECIM 2...\n\n");
            for(int i=0; i<dosyasayisi; i++)
            {
                if(dosyalar[i].kontrol==1) //yalnizca kontrolü 1 olan dosyalar için islemler yapilir
                {
                    dosyalar[i]=enyakinenuzakveortalama(dosyalar[i],2); //enyakinenuzakveortalama fonksiyonuna çikti dosyasina 2. islemin sonuçlarinin yazdirilacagi bildirilir
                }
            }
            printf("Secim 2 tamamlandi.\n\n");
        }
        else if(secim==3)
        {
            system("@cls||clear");
            if(dosyalar[0].kontrol==-1)
            {
                printf("Once 1. islemi calistirmaniz gerekmektedir!\n\n");
                continue;
            }
            dosya=fopen("output.nkt","a");
            fprintf(dosya,"\n\nSECIM 3\n");
            fclose(dosya);
            printf("SECIM 3...\n\n");
            for(int i=0; i<dosyasayisi; i++)
            {
                if(dosyalar[i].kontrol==1)
                {
                    kupkoordinat(dosyalar[i]); //kupkoordinat fonksiyonu çagirilir
                }
            }
            printf("Secim 3 tamamlandi.\n\n");
        }
        else if(secim==4)
        {
            system("@cls||clear");
            if(dosyalar[0].kontrol==-1)
            {
                printf("Once 1. islemi calistirmaniz gerekmektedir!\n\n");
                continue;
            }
            dosya=fopen("output.nkt","a");
            fprintf(dosya,"\n\nSECIM 4\n");
            fclose(dosya);
            printf("SECIM 4\n\n\n");
            double merkezx,merkezy,merkezz,yaricap; //kullanicidan sirasiyla kiyaslama yapilacak kürenin merkez koordinat bilgileri ve yariçap uzunlugu alinir
            printf("Merkez x: ");
            scanf("%lf",&merkezx);
            printf("Merkez y: ");
            scanf("%lf",&merkezy);
            printf("Merkez z: ");
            scanf("%lf",&merkezz);
            printf("Yaricap uzunlugu: ");
            scanf("%lf",&yaricap);
            printf("\n\n");
            for(int i=0; i<dosyasayisi; i++)
            {
                if(dosyalar[i].kontrol==1)
                {
                    kureyazdir(dosyalar[i],merkezx,merkezy,merkezz,yaricap); //kürenin merkez koordinat bilgileri ve yariçap uzunluðu dosya structiyla birlikte kureyazdir fonksiyonuna yollanir
                }
            }
            printf("Secim 4 tamamlandi.\n\n");
        }
        else if(secim==5)
        {
            system("@cls||clear");
            if(dosyalar[0].kontrol==-1)
            {
                printf("Once 1. islemi calistirmaniz gerekmektedir!\n\n");
                continue;
            }
            dosya=fopen("output.nkt","a");
            fprintf(dosya,"\n\nSECIM 5\n");
            fclose(dosya);
            printf("SECIM 5...\n\n");
            for(int i=0; i<dosyasayisi; i++)
            {
                if(dosyalar[i].kontrol==1)
                {
                    dosyalar[i]=enyakinenuzakveortalama(dosyalar[i],5); //enyakinenuzakveortalama fonksiyonuna çikti dosyasina 5. islemin sonuçlarinin yazdirilacagi bildirilir
                }
            }
            printf("Secim 5 tamamlandi.\n\n");
        }
    }
}
struct dosyabilgi baslikkontrol(struct dosyabilgi anlikdosya)
{
    int sayac=0; //kaçinci satirin okundugunu belirtir
    char alanlar[50];
    char noktalar[20];
    int noktasayi;
    FILE *dosya;
    if((dosya=fopen(anlikdosya.dosyaadi,"r"))==NULL) //fopen fonksiyonu null deger döndürürse dosyanin açilamadigi belirtilir ve fonksiyon sonlandrilir
    {
        dosya=fopen("output.nkt","a");
        fprintf(dosya,"%s dosyasi acilamadi.\n",anlikdosya.dosyaadi);
        fclose(dosya);
        anlikdosya.kontrol=0;
        return anlikdosya;
    }
    while(!feof(dosya)) //dosyanin sonuna gelindiginde döngüden çikilmasi gerektigini belirtir
    {
        if(sayac==0) //birinci satirin tamami o anki dosya structinin tanim degiskenine atanir
        {
            fgets(anlikdosya.tanim,50,dosya);
            sayac+=1;
        }
        else if(sayac==1) //ikinci satirda yalnizca "VERSION 1" mi yaziyor kontrol edilir
        {
            fgets(anlikdosya.version,50,dosya);
            sayac+=1;
            if(strcmp(anlikdosya.version,"VERSION 1\n")!=0)
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinin version satiri hatalidir.\n",anlikdosya.dosyaadi);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
        }
        else if(sayac==2) //alanlar satiri okunur, uygun formattaysa rgb degiskenine sonuç yollanir, degilse hata yazdirilir
        {
            fgets(alanlar,50,dosya);
            sayac+=1;
            if (!strcmp(alanlar,"ALANLAR x y z r g b\n"))
            {
                anlikdosya.rgb=1;
            }
            else if(!strcmp(alanlar,"ALANLAR x y z\n"))
            {
                anlikdosya.rgb=0;
            }
            else
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinin alanlar satiri hatalidir.\n",anlikdosya.dosyaadi);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
        }
        else if(sayac==3) //nokta sayisi alinir
        {
            fgets(anlikdosya.noktalar,20,dosya);
            sayac+=1;
            noktasayi=-1;
            sscanf(anlikdosya.noktalar,"%s %d",noktalar,&noktasayi);
            if(strcmp(noktalar,"NOKTALAR")!=0 || noktasayi==-1)
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinin noktalar satiri hatalidir.\n",anlikdosya.dosyaadi);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
            anlikdosya.noktasayi=noktasayi;
        }
        else if(sayac==4) //data tipi belirlenir
        {
            fgets(anlikdosya.datatype,20,dosya);
            sayac+=1;
            if(strcmp(anlikdosya.datatype,"DATA ascii\n")!=0 && strcmp(anlikdosya.datatype,"DATA binary\n")!=0)
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinin data satiri hatalidir.\n",anlikdosya.dosyaadi);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
        }
        else //baslik bilgileri sorunsuz okunduysa ve dosya henüz bitmediyse uygun nokta okuma fonksiyonuna gönderilmesi için kontrol 1'e atanip struct geri döndürülür
        {
            fclose(dosya);
            anlikdosya.kontrol=1;
            return anlikdosya;
        }
    }
    if(sayac<=1) //eger dosyada hiç yazi yoksa hata yazdirilir
    {
        fclose(dosya);
        dosya=fopen("output.nkt","a");
        fprintf(dosya,"%s dosyasi bos.\n",anlikdosya.dosyaadi);
        fclose(dosya);
        anlikdosya.kontrol=0;
        return anlikdosya;
    }
    anlikdosya.kontrol=0;
    return anlikdosya;
}

struct dosyabilgi noktalarioku(struct dosyabilgi anlikdosya)
{
    FILE *dosya=fopen(anlikdosya.dosyaadi,"r");
    int sayac=0;
    int okunannokta=0;
    char okunan[100];
    while(!feof(dosya))
    {
        if(sayac<=4) //ilk 5 satir daha önce baslikkontrol fonksiyonunda kontrol edildigi için atlanir
        {
            fgets(okunan,100,dosya);
            sayac+=1;
        }
        else
        {
            if(fgets(okunan,100,dosya)==NULL) //tamami bos bir satira gelindiginde döngü sonlandirilir
                break;
            if(okunannokta==anlikdosya.noktasayi) //eger ki okunan nokta sayisina gelindiyse ve döngü devam ediyorsa mallocla ayrilan alani geçecegi için okunan nokta sayisi -1'e atanip döngü bozulur
            {
                okunannokta=-1;
                break;
            }
            if(!strcmp(okunan,"\n")) //bos satir varsa kontrol 0'a atanip fonksiyondan çiklir
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinda bos satir bulunuyor.\n",anlikdosya.dosyaadi);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }

            anlikdosya.nokta[okunannokta].z=-1;
            anlikdosya.nokta[okunannokta].r=-1;
            anlikdosya.nokta[okunannokta].b=-1;
            sscanf(okunan,"%lf %lf %lf %d %d %d",&anlikdosya.nokta[okunannokta].x,&anlikdosya.nokta[okunannokta].y,&anlikdosya.nokta[okunannokta].z,&anlikdosya.nokta[okunannokta].r,&anlikdosya.nokta[okunannokta].g,&anlikdosya.nokta[okunannokta].b);
            if(anlikdosya.nokta[okunannokta].z==-1) //z degeri -1'de kaldiysa en az bir koordinat verisi eksik okunmus olacagi için hata yazdirilir
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinda %d. noktanin koordinat bilgisi yanlis verilmis: %s",anlikdosya.dosyaadi,okunannokta+1,okunan);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
            if(anlikdosya.rgb==0 && anlikdosya.nokta[okunannokta].r!=-1) //r degiskenine bir deger atandiysa rgb bilgisi verilmis olacaðý için hata yazdirilir
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinda %d. nokta rgb bilgileriyle verilmis!: %s",anlikdosya.dosyaadi,okunannokta+1,okunan);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
            if(anlikdosya.rgb==1 && anlikdosya.nokta[okunannokta].b==-1) //b degiskenine herhangi bir deger atanmadiysa rgb bilgileri eksik olacagi için hata yazdirilir
            {
                fclose(dosya);
                dosya=fopen("output.nkt","a");
                fprintf(dosya,"%s dosyasinda %d. noktanin rgb bilgileri eksik verilmis!: %s",anlikdosya.dosyaadi,okunannokta+1,okunan);
                fclose(dosya);
                anlikdosya.kontrol=0;
                return anlikdosya;
            }
            okunannokta+=1;
        }
    }
    fclose(dosya);
    if(okunannokta!=anlikdosya.noktasayi) //okunan nokta sayisiyla baslikta verilen nokta sayisi denk degilse hata yazdirilir
    {
        dosya=fopen("output.nkt","a");
        fprintf(dosya,"%s dosyasindan okunan nokta sayisi ile verilen nokta sayisi uyusmuyor!\n",anlikdosya.dosyaadi);
        fclose(dosya);
        anlikdosya.kontrol=0;
        return anlikdosya;
    }
    dosya=fopen("output.nkt","a");
    fprintf(dosya,"%s dosyasi butunuyle uyumludur.\n",anlikdosya.dosyaadi);
    fclose(dosya);
    anlikdosya.kontrol=1; //eger tüm kontroller asildiysa kontrol 1'e esitlenir ve dosyanin islemler için uygun oldugu belirtilir
    return anlikdosya;
}

struct dosyabilgi binarynoktaoku(struct dosyabilgi anlikdosya)
{
    FILE *dosya=fopen(anlikdosya.dosyaadi,"rb"); //dosya binary okuma modunda açýlýr
    int sayac=0;
    int okunannokta=0;
    char okunan[100];
    float xyz[3]; // xyz bilgilerini geçici olarak saklamasi için bir float dizisi tanimlanir
    int rgb[3]; // rgb bilgilerini geçici olarak saklamasi için bir int dizisi tanimlanir
    while(!feof(dosya))
    {
        if(sayac<=4) //ilk 5 satir atlanir
        {
            fgets(okunan,100,dosya);
            sayac+=1;
        }
        else
        {
            if(anlikdosya.rgb==0)
            {
                if(fread(&xyz,3*sizeof(float),1,dosya)==0) //fread fonksiyonu bir deger okuyamazsa döngü bozulur
                    break;
                if(okunannokta==anlikdosya.noktasayi)
                {
                    okunannokta=-1; //eger fread fonksiyonu bir deger okumussa ve baslikta verilen nokta sayisi asilmissa mallocla ayrilan alani asmamak için okunan nokta degiskeni -1'e esitlenip döngüden çikilir
                    break;
                }
                anlikdosya.nokta[okunannokta].x=(double)xyz[0]; //okunan x,y,z koordinatlari double biçimine çevrilerek structa atanir
                anlikdosya.nokta[okunannokta].y=(double)xyz[1];
                anlikdosya.nokta[okunannokta].z=(double)xyz[2];
            }
            else
            {
                if(fread(&xyz,3*sizeof(float),1,dosya)==0) //fread fonksiyonu bir deger okuyamazsa döngü bozulur
                    break;
                if(fread(&rgb,3*sizeof(int),1,dosya)==0) //fread fonksiyonu bir deger okuyamazsa döngü bozulur
                    break;
            }
            if(okunannokta==anlikdosya.noktasayi)
            {
                okunannokta=-1; //eger fread fonksiyonu bir deger okumussa ve baslikta verilen nokta sayisi asilmissa mallocla ayrilan alani asmamak için okunan nokta degiþkeni -1'e esitlenip döngüden çikilir
                break;
            }
            anlikdosya.nokta[okunannokta].x=(double)xyz[0];
            anlikdosya.nokta[okunannokta].y=(double)xyz[1];
            anlikdosya.nokta[okunannokta].z=(double)xyz[2];
            anlikdosya.nokta[okunannokta].r=rgb[0];
            anlikdosya.nokta[okunannokta].g=rgb[1];
            anlikdosya.nokta[okunannokta].b=rgb[2];
            okunannokta+=1;
        }
    }
    fclose(dosya);
    if(okunannokta!=anlikdosya.noktasayi) //okunan nokta sayisiyla baslikta verilen nokta sayisi uyusmuyorsa hata yazdirilir
    {
        dosya=fopen("output.nkt","a");
        fprintf(dosya,"%s dosyasindan okunan nokta sayisi ile verilen nokta sayisi uyusmuyor!\n",anlikdosya.dosyaadi);
        fclose(dosya);
        anlikdosya.kontrol=0;
        return anlikdosya;
    }
    dosya=fopen("output.nkt","a");
    fprintf(dosya,"%s dosyasi butunuyle uyumludur.\n",anlikdosya.dosyaadi);
    fclose(dosya);
    anlikdosya.kontrol=1; //tüm kontroller asildiysa kontrol 1'e atanir ve dosyanin islemler için uygun oldugu bildirilir
    return anlikdosya;
}

struct dosyabilgi enyakinenuzakveortalama(struct dosyabilgi anlikdosya,int secim)
{
    FILE *dosya=fopen("output.nkt","a");
    if(anlikdosya.ortalama==-1) //ortalama -1 ise daha önce bu fonksiyon çalismamis demektir, hesaplama islemlerinin yapilmasi gerektigi anlasilir
    {
        //kiyas alinmasi için enyakinmesafe'ye ilk iki noktanin arasindaki uzaklik atanir
        double anlikmesafe, enuzakmesafe=0,enyakinmesafe=noktalararasiuzaklik(anlikdosya.nokta[0].x,anlikdosya.nokta[0].y,anlikdosya.nokta[0].z,anlikdosya.nokta[1].x,anlikdosya.nokta[1].y,anlikdosya.nokta[1].z);
        int enuzak1,enuzak2,enyakin1,enyakin2;
        double islemsayi=0; //kaç tane islem yapildigini kaydeder
        double toplam=0; //mesafelerin toplamini saklar
        for(int i=0; i<anlikdosya.noktasayi-1; i++)
        {
            for(int j=i+1; j<anlikdosya.noktasayi; j++)
            {
                islemsayi+=1;
                anlikmesafe=noktalararasiuzaklik(anlikdosya.nokta[i].x,anlikdosya.nokta[i].y,anlikdosya.nokta[i].z,anlikdosya.nokta[j].x,anlikdosya.nokta[j].y,anlikdosya.nokta[j].z);
                //tüm noktalarin kendinden sonra gelen tüm noktalarla arasindaki mesafe kontrol edilir
                toplam+=anlikmesafe; //döngü her döndügünde bulunan deger toplam fonksiyonuna eklenir
                if(anlikmesafe>=enuzakmesafe) //anlikmesafe daha önceki en büyük mesafeden büyükse noktalarin indisleri ve aralarindaki mesafe kaydedilir
                {
                    enuzakmesafe=anlikmesafe;
                    enuzak1=i;
                    enuzak2=j;
                }
                if(anlikmesafe<=enyakinmesafe)//anlikmesafe daha önceki en küçük mesafeden küçükse noktalarin indisleri ve aralarindaki mesafe kaydedilir
                {
                    enyakinmesafe=anlikmesafe;
                    enyakin1=i;
                    enyakin2=j;
                }
            }
        }
        anlikdosya.enyakin1=enyakin1; //en son bulunan en yakin ve en uzak noktalarin indisleri structa kaydedilir
        anlikdosya.enyakin2=enyakin2;
        anlikdosya.enuzak1=enuzak1;
        anlikdosya.enuzak2=enuzak2;
        anlikdosya.ortalama=toplam/islemsayi; //mesafeler toplami islem sayisina bölünerek uzakliklarin ortalamasi bulunur, bu deger artik -1 olmayacagi için bu fonksiyon bir sonraki çalismasinda su ana kadarki islemleri atlayacaktir
    }
    dosya=fopen("output.nkt","a");
    if(secim==2) //eger fonksiyon ikinci seçimden çagirildiysa en yakin ve en uzak noktalar çikti dosyasina yazdirilir, rgb degeri birse yanlarina rgb bilgileri de eklenir
    {
        fprintf(dosya,"%s:\nEn yakin noktalar:\n%d. %lf %lf %lf",anlikdosya.dosyaadi,anlikdosya.enyakin1+1,anlikdosya.nokta[anlikdosya.enyakin1].x,anlikdosya.nokta[anlikdosya.enyakin1].y,anlikdosya.nokta[anlikdosya.enyakin1].z);
        if(anlikdosya.rgb==1)
        {
            fprintf(dosya," %d %d %d",anlikdosya.nokta[anlikdosya.enyakin1].r,anlikdosya.nokta[anlikdosya.enyakin1].g,anlikdosya.nokta[anlikdosya.enyakin1].b);
        }
        fprintf(dosya,"\n%d. %lf %lf %lf",anlikdosya.enyakin2+1,anlikdosya.nokta[anlikdosya.enyakin2].x,anlikdosya.nokta[anlikdosya.enyakin2].y,anlikdosya.nokta[anlikdosya.enyakin2].z);
        if(anlikdosya.rgb==1)
        {
            fprintf(dosya," %d %d %d",anlikdosya.nokta[anlikdosya.enyakin2].r,anlikdosya.nokta[anlikdosya.enyakin2].g,anlikdosya.nokta[anlikdosya.enyakin2].b);
        }
        fprintf(dosya,"\nEn uzak noktalar:\n%d. %lf %lf %lf",anlikdosya.enuzak1+1,anlikdosya.nokta[anlikdosya.enuzak1].x,anlikdosya.nokta[anlikdosya.enuzak1].y,anlikdosya.nokta[anlikdosya.enuzak1].z);
        if(anlikdosya.rgb==1)
        {
            fprintf(dosya," %d %d %d",anlikdosya.nokta[anlikdosya.enuzak1].r,anlikdosya.nokta[anlikdosya.enuzak1].g,anlikdosya.nokta[anlikdosya.enuzak1].b);
        }
        fprintf(dosya,"\n%d. %lf %lf %lf",anlikdosya.enuzak2+1,anlikdosya.nokta[anlikdosya.enuzak2].x,anlikdosya.nokta[anlikdosya.enuzak2].y,anlikdosya.nokta[anlikdosya.enuzak2].z);
        if(anlikdosya.rgb==1)
        {
            fprintf(dosya," %d %d %d\n\n",anlikdosya.nokta[anlikdosya.enuzak2].r,anlikdosya.nokta[anlikdosya.enuzak2].g,anlikdosya.nokta[anlikdosya.enuzak2].b);
        }

        else
        {
            fprintf(dosya,"\n\n");
        }
    }
    else if(secim==5) //eger fonksiyon seçim 5'ten çagirildiysa noktalar arasi uzakliklarin ortalamasi çikti dosyasina yazdirilir
    {
        fprintf(dosya,"%s: %lf\n",anlikdosya.dosyaadi,anlikdosya.ortalama);
    }
    fclose(dosya);
    return anlikdosya; //çikti dosyasi kapatilarak ortalama ve en yakin en uzak noktalarin indis bilgileriyle struct geri döndürülür
}

void kureyazdir(struct dosyabilgi anlikdosya,double merkezx,double merkezy,double merkezz,double yaricap)
{
    FILE *dosya;
    dosya=fopen("output.nkt","a");
    fprintf(dosya,"%s:\n",anlikdosya.dosyaadi);
    if(anlikdosya.rgb==1)
        fprintf(dosya,"ALANLAR x y z r g b\n");
    else
        fprintf(dosya,"ALANLAR x y z\n");
    fprintf(dosya,"%s%s",anlikdosya.noktalar,anlikdosya.datatype);
    for(int i=0; i<anlikdosya.noktasayi; i++) //her noktanin tek tek küre merkeziyle arasindaki mesafe hesaplanir, mesafe yariçaptan küçükse veya esitse nokta bilgileri yazdirilir
    {
        if(noktalararasiuzaklik(anlikdosya.nokta[i].x,anlikdosya.nokta[i].y,anlikdosya.nokta[i].z,merkezx,merkezy,merkezz)<=yaricap)
        {
            if(anlikdosya.rgb==1)
            {
                fprintf(dosya,"%lf %lf %lf %d %d %d\n",anlikdosya.nokta[i].x,anlikdosya.nokta[i].y,anlikdosya.nokta[i].z,anlikdosya.nokta[i].r,anlikdosya.nokta[i].g,anlikdosya.nokta[i].b);
            }
            else
            {
                fprintf(dosya,"%lf %lf %lf\n",anlikdosya.nokta[i].x,anlikdosya.nokta[i].y,anlikdosya.nokta[i].z);
            }
        }
    }
    fprintf(dosya,"\n");
    fclose(dosya);
}

void kupkoordinat(struct dosyabilgi anlikdosya)
{
    FILE *dosya;
    dosya=fopen("output.nkt","a");
    //ilk dosyanin x,y,z degerleri kiyas için en küçük ve en büyük x,y ve z degerleri olarak atanir
    double enkucukx=anlikdosya.nokta[0].x,enkucuky=anlikdosya.nokta[0].y,enkucukz=anlikdosya.nokta[0].z,enbuyukx=anlikdosya.nokta[0].x,enbuyuky=anlikdosya.nokta[0].y,enbuyukz=anlikdosya.nokta[0].z;
    for(int i=0; i<anlikdosya.noktasayi; i++) //sirasiyla o anki noktanin x,y ve z degeri daha önceki en büyük ve en küçük degerle kiyaslanip, uygunsa o degerin yerine atanir
    {
        if(anlikdosya.nokta[i].x<enkucukx)
            enkucukx=anlikdosya.nokta[i].x;
        if(anlikdosya.nokta[i].x>enbuyukx)
            enbuyukx=anlikdosya.nokta[i].x;
        if(anlikdosya.nokta[i].y<enkucuky)
            enkucuky=anlikdosya.nokta[i].y;
        if(anlikdosya.nokta[i].y>enbuyuky)
            enbuyuky=anlikdosya.nokta[i].y;
        if(anlikdosya.nokta[i].z<enkucukz)
            enkucukz=anlikdosya.nokta[i].z;
        if(anlikdosya.nokta[i].z>enbuyukz)
            enbuyukz=anlikdosya.nokta[i].z;
    }
    double xfark=enbuyukx-enkucukx,yfark=enbuyuky-enkucuky,zfark=enbuyukz-enkucukz; //en büyük ve en küçük degerlerin kendi aralarindaki farklar bulunur
    double kenaruzunluk;
    if(xfark>yfark && xfark>zfark) //en büyük ve en küçük x arasindaki fark en büyükse kenar uzunlugu olarak alinir
        kenaruzunluk=xfark;
    else if(yfark>xfark && yfark>zfark) //en büyük ve en küçük y arasindaki fark en büyükse kenar uzunlugu olarak alinir
        kenaruzunluk=yfark;
    else //en büyük ve en küçük z arasindaki fark en büyükse kenar uzunlugu olarak alinir
        kenaruzunluk=zfark;
    //bulunan kenar uzunlugu, en küçük x,y ve z degerlerine eklenerek küpün köse koordinat bilgileri yazdirilir
    fprintf(dosya,"%s:\n%lf %lf %lf\n",anlikdosya.dosyaadi,enkucukx,enkucuky,enkucukz); //1. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx+kenaruzunluk,enkucuky,enkucukz); //2. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx+kenaruzunluk,enkucuky+kenaruzunluk,enkucukz); //3. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx,enkucuky+kenaruzunluk,enkucukz); //4. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx+kenaruzunluk,enkucuky+kenaruzunluk,enkucukz+kenaruzunluk); //5. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx,enkucuky+kenaruzunluk,enkucukz+kenaruzunluk); //6. köse
    fprintf(dosya,"%lf %lf %lf\n",enkucukx,enkucuky,enkucukz+kenaruzunluk); //7. köse
    fprintf(dosya,"%lf %lf %lf\n\n",enkucukx+kenaruzunluk,enkucuky,enkucukz+kenaruzunluk); //8. köse
    fclose(dosya);
}
