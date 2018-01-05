#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct gorusme
{
    char aranan_no[11];
    char tarih[9];
    char bas_zamani[5];
    int sure;
    struct gorusme *sonraki;
    struct gorusme *onceki;
};

struct abone
{
    int tel_no;
    char ad[11];
    char soyad[13];
    char adres[26];
    char abone_tip;
    struct abone *tel_noya_gore_sonraki;
    struct abone *soyada_gore_sonraki;
    struct gorusme gorusme_bas;

};


typedef struct abone aboneler;
typedef struct gorusme gorusmeler;

int hash1(int);
int hash2(char *);

void tel_no_sirali_ekle(aboneler **, aboneler *);//oncelik kuyruguna sirali ekleme
void soyada_gore_sirali_ekle(aboneler *, aboneler *);
void sonuc_gorusme_listele(gorusmeler *);
aboneler *tel_noya_gore_ara(aboneler *, int);
void gorusme_ekle(gorusmeler *,gorusmeler *);
void kucukten_buyuge_listele(gorusmeler *);
void ilk_ucbasamaga_gore_listele(aboneler *);
void harf_ile_listeleme(aboneler *);
void Kelime_ile_listeleme(aboneler *,char *);
void tarihe_gore_arama(gorusmeler *,aboneler *,char *);
int abone_tip_dondur(char);
char * abone_tip_yazdirma(char );
char * abone_tip_yazdirma1(int);
void gorusme_yazdir(aboneler *,gorusmeler *);
void Belli_bir_tarihe_kadar_arama_yapmayanlarin_listesi(gorusmeler *,aboneler *,char *);
void Aranan_noya_gore_listele(gorusmeler *,aboneler *,char *);
aboneler *tel_listesinden_cikar(aboneler **,aboneler *);
gorusmeler *ara(gorusmeler *,gorusmeler *);
void cikar(gorusmeler *);
void soyad_listesinden_cikar(aboneler *,char *);
int menu_secim(void);

int main()
{
    aboneler *Tel_hash[900]= {NULL};
    aboneler Hash_soyad[26]= {};
    aboneler *abonem;
    gorusmeler *gorusmem;
    gorusmeler *gecici;
    int i,secim,HAFIZA[4][3]= {};
    char karar,karakter,aranan[26]= {};
    int telefon_no,indeks1,indeks2;
    for(i=0; i<26; i++)
        Hash_soyad[i].soyada_gore_sonraki=&Hash_soyad[i];//liste basi dugumune sahip dairesel tek bagli listeler ilkleniyor

    do
    {
        secim=menu_secim();
        switch (secim)
        {
            case 1:

                printf("lutfen yeni bir telefon numarasi giriniz:");
                scanf("%d",&telefon_no);
                indeks1=hash1(telefon_no);
                if(tel_noya_gore_ara(Tel_hash[indeks1],telefon_no)==0)  //ayni koda sahip telefon yoksa...
                {

                    abonem=malloc(sizeof(aboneler));//yeni  icin bellekten yer ayriliyor
                    if(abonem!=NULL)
                    {
                        abonem->tel_no=telefon_no;

                        printf("abone adini giriniz:");
                        fflush(stdin);
                        scanf("%s",abonem->ad);

                        printf("abone soyadini giriniz:");
                        fflush(stdin);
                        scanf("%s",abonem->soyad);

                        printf("abone adresini giriniz:");
                        fflush(stdin);
                        scanf("%s",abonem->adres);

                        printf("abone tipini giriniz giriniz:");
                        fflush(stdin);
                        scanf("%c",&abonem->abone_tip);

                        HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][0]++;

                        tel_no_sirali_ekle(&Tel_hash[indeks1],abonem);//yeni abone, numarasina gore ilgili listeye eklenir

                        indeks2=hash2(abonem->soyad);
                        soyada_gore_sirali_ekle(&Hash_soyad[indeks2],abonem);
                    }
                    else
                    {
                        printf( "Yetersiz hafıza\n");
                    }
                }
                else
                    printf("Boyle bir abone var!\n");
                break;
            case 2:

                printf("Lutfen nakil yapmak icin telefon nosunu giriniz:");
                scanf("%i",&telefon_no);
                printf("\n");
                abonem=tel_noya_gore_ara(Tel_hash[hash1(telefon_no)],telefon_no);
                if(abonem!=NULL)
                {
                    printf("lutfen yeni adres giriniz: ");
                    fflush(stdin);
                    gets(aranan);
                    strcpy(abonem->adres,aranan);
                    printf("telefon numarasini degistirecek misiniz (evet icin E yada e giriniz): ");
                    fflush(stdin);
                    scanf("%c",&karar);
                    if(karar=='e' || karar=='E')
                    {
                        printf("Lutfen yeni telefon numarasini giriniz: ");
                        scanf("%i",&telefon_no);
                        while(tel_noya_gore_ara(Tel_hash[hash1(telefon_no)],telefon_no)!=NULL)
                        {
                                printf("Boyle bir abone vardir lutfen dogru bir numara giriniz: ");
                                scanf("%i",&telefon_no);
                        }
                        tel_listesinden_cikar(&Tel_hash[hash1(abonem->tel_no)],abonem);
                        soyad_listesinden_cikar(&Hash_soyad[hash2(abonem->soyad)],abonem->soyad);
                        abonem->tel_no=telefon_no;
                        tel_no_sirali_ekle(&Tel_hash[hash1(abonem->tel_no)],abonem);
                        soyada_gore_sirali_ekle(&Hash_soyad[hash2(abonem->soyad)],abonem);
                    }
                }else
                {
                    printf("Boyle bir abone yoktur");
                }

                break;
            case 3:
                printf("Gorusme eklemek istediginiz numarayi giriniz:");
                scanf("%d",&telefon_no);

                indeks1=hash1(telefon_no);
                abonem=tel_noya_gore_ara(Tel_hash[indeks1],telefon_no);
                if(abonem!=0)
                {

                    do
                    {


                        gorusmem=malloc(sizeof(gorusmeler));
                        if(gorusmem!=NULL)
                        {
                            printf("Aranan numarayi giriniz:");
                            fflush(stdin);
                            gets(gorusmem->aranan_no);

                            printf("Arama tarihini giriniz:");
                            fflush(stdin);
                            gets(gorusmem->tarih);

                            printf("Arama zamanini giriniz:");
                            fflush(stdin);
                            gets(gorusmem->bas_zamani);

                            printf("Lutfen gorusme surenizi giriniz:");
                            scanf("%i",&(gorusmem->sure));

                            gorusme_ekle(&(abonem->gorusme_bas),gorusmem);

                            HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][1]++;
                            HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][2]+=gorusmem->sure;
                        }

                        else
                            printf("Boyle bir abone yoktur!\n");
                        printf("Baska gorusme kaydi eklemek istermisiniz?(Evet:e,E Hayir:H,h):");
                        do
                        {
                            scanf("%c", &karar);
                        }
                        while (karar == '\n');
                        printf("\n");

                    }
                    while(karar=='e' || karar=='E');
                }
                else
                {
                    printf("hafiza yetersiz\n");
                }
                break;
            case 4:
                printf("Lutfen telefon numarasini giriniz:");
                scanf("%i",&telefon_no);
                indeks1=hash1(telefon_no);

                if((abonem=tel_noya_gore_ara(Tel_hash[indeks1],telefon_no))!=NULL)
                {
                    abonem=tel_listesinden_cikar(&Tel_hash[indeks1],abonem);
                    printf("%i nolu abone listeden cikarildi",abonem->tel_no);
                    HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][0]--;
                    gecici=ara(&(abonem->gorusme_bas),abonem->gorusme_bas.sonraki);
                    while(gecici!=NULL){
                        HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][1]--;
                        HAFIZA[abone_tip_dondur(abonem->abone_tip)-1][2]-=gecici->sure;
                        cikar(gecici);
                        gecici=ara(&(abonem->gorusme_bas),abonem->gorusme_bas.sonraki);
                    }
                    soyad_listesinden_cikar(&Hash_soyad[hash2(abonem->soyad)],abonem->soyad);
                    free(abonem);
                    }

                break;
            case 5:
                printf("Listelemek istediginiz numarayi giriniz:");
                scanf("%d",&telefon_no);
                indeks1=hash1(telefon_no);
                abonem=tel_noya_gore_ara(Tel_hash[indeks1],telefon_no);
                if(abonem==NULL)
                {
                    printf("Boyle bir abone yoktur!\n");
                }
                else
                {
                    printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                    printf("----------  ------  -----   -----------  ----------\n");
                    printf("%-10d  %-6s  %-5s   %-11s  %s\n",abonem->tel_no,abonem->ad,abonem->soyad,abonem->adres,abone_tip_yazdirma(abonem->abone_tip));
                    kucukten_buyuge_listele(&(abonem->gorusme_bas));
                }
                printf("\n");

                break;
            case 6:

                printf("Son uc gorusmesini listelemek istediginiz numarayi giriniz:");
                scanf("%d",&telefon_no);
                indeks1=hash1(telefon_no);
                abonem=tel_noya_gore_ara(Tel_hash[indeks1],telefon_no);
                if(abonem==NULL)
                {
                    printf("Boyle bir abone yoktur!\n");
                }
                else
                {
                    printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                    printf("----------  ------  -----   -----------  ----------\n");
                    printf("%-10d  %-6s  %-5s   %-11s  %s\n",abonem->tel_no,abonem->ad,abonem->soyad,abonem->adres,abone_tip_yazdirma(abonem->abone_tip));

                    printf("\n");
                    sonuc_gorusme_listele(&(abonem->gorusme_bas));
                }

                break;
            case 7:

                printf("Alan Kodunu uc basamakli giriniz:");
                scanf("%d",&telefon_no);
                abonem=Tel_hash[telefon_no-100];
                if(abonem==NULL)
                {
                    printf("Boyle bir abone yoktur!\n");
                }
                else
                {
                    printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                    printf("----------  ------  -----   -----------  ----------\n");
                    ilk_ucbasamaga_gore_listele(abonem);
                }

                break;

            case 8:

                printf("Bir harf giriniz :");
                fflush(stdin);
                scanf("%c",&karakter);
                int c=toupper(karakter)-'A';
                abonem=&Hash_soyad[c];
                harf_ile_listeleme(abonem);

                break;

            case 9:

                printf("lutfen aradiginiz kelimeyi giriniz: ");
                fflush(stdin);
                scanf("%s",aranan);
                indeks2=hash2(aranan);
                abonem=&Hash_soyad[indeks2];
                Kelime_ile_listeleme(abonem,aranan);

                break;

            case 10:
                printf("          Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                printf("          ----------  ------  -----   -----------  ----------\n");

                for(i=0; i<900; i++)
                {
                    if(Tel_hash[i]!=NULL)
                    {
                        printf("%i.liste ---------------------------------------------\n",i);
                        ilk_ucbasamaga_gore_listele(Tel_hash[i]);
                    }
                }
                printf("Abone Tipi  Abone Sayisi  Gorusme Sayisi  Toplam Sure  Ortalama\n");
                printf("----------  ------------  --------------  -----------  --------\n");
                for(i=0; i<4; i++)
                    if(HAFIZA[i][1]==0)
                    {
                        printf("%-12s%-15i%-16i%-13i%.2f\n",abone_tip_yazdirma1(i),HAFIZA[i][0],HAFIZA[i][1],HAFIZA[i][2],0.00);
                    }
                    else
                    {
                        printf("%-12s%-15i%-16i%-13i%.2f\n",abone_tip_yazdirma1(i),HAFIZA[i][0],HAFIZA[i][1],HAFIZA[i][2],(float)(HAFIZA[i][2])/(float)(HAFIZA[i][1]));
                    }


                break;

            case 11:
                printf("Aradiginiz Tarihi Giriniz:");
                fflush(stdin);
                gets(aranan);

                printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                printf("----------  ------  -----   -----------  ----------\n");

                for(i=0; i<900; i++)
                {
                    if(Tel_hash[i]!=NULL)
                    {
                        abonem=Tel_hash[i];
                        while(abonem!=NULL)
                        {
                            Belli_bir_tarihe_kadar_arama_yapmayanlarin_listesi(&(abonem->gorusme_bas),abonem,aranan);
                            abonem=abonem->tel_noya_gore_sonraki;
                        }
                    }
                }

                break;

            case 12:

                printf("Aradiginiz Numarayi Giriniz:");
                fflush(stdin);
                gets(aranan);

                printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
                printf("----------  ------  -----   -----------  ----------\n");

                for(i=0; i<26; i++)
                {
                    if(Hash_soyad[i].soyada_gore_sonraki!=&Hash_soyad[i])
                    {
                        abonem=Hash_soyad[i].soyada_gore_sonraki;
                        while(abonem!=&Hash_soyad[i])
                        {
                            Aranan_noya_gore_listele(&(abonem->gorusme_bas),abonem,aranan);
                            abonem=abonem->soyada_gore_sonraki;
                        }
                    }
                }

                break;

            case 13:

                printf("Aradiginiz Tarihi Giriniz:");
                fflush(stdin);
                gets(aranan);

                printf("Arayan No   Aranan No     Tarih       Bas Zamani  Sure\n");
                printf("---------   -----------   ----------  ----------  -----\n");
                for(i=0; i<900; i++)
                {
                    if(Tel_hash[i]!=NULL)
                    {
                        abonem=Tel_hash[i];
                        while(abonem!=NULL)
                        {
                            tarihe_gore_arama(&(abonem->gorusme_bas),abonem,aranan);
                            abonem=abonem->tel_noya_gore_sonraki;
                        }
                    }
                }
                break;

        }

    }
    while (secim!=14);

    return 0;
}

int menu_secim(void)
{
    int secim;
    printf("\n/-----------MENU---------\\\n");
    printf("01.Yeni Bir Abonenin Eklenmesi\n");
    printf("02.Abone Nakil Yapimi\n");
    printf("03.Gorusme Ekleme\n");
    printf("04.Abone Silme\n");
    printf("05.Abone Bilgi ve Tum Gorusmelerinin Listelenmesi\n");
    printf("06.Abone Bilgi ve Son Uc Gorusmesinin Listelenmesi\n");
    printf("07.Alan Koduna Gore Abone Bilgi Listeleme\n");//Telefon Numarasi Belirli Bir Uc Basamakli Sayi ile Baslayan Abonelerin Bilgileri
    printf("08.Soyad Bas Harfine Gore Abone Bilgi Listeleme\n");
    printf("09.Soyad Belli Bir Metin ile Baslayanlarin Listelenmesi\n");
    printf("10.Tum abonelerin bilgileri ve Istatistiklerinin Listelenmesi\n");
    printf("11.Belirlenen Tarihten Sonra Gorusme Yapmamis Abonelerin Listelenmesi\n");
    printf("12.Belirli Bir Numarayi Arayan Abonelerin Listelenmesi\n");
    printf("13.Belirli Bir Tarihteki Gorusme Listesi\n");
    printf("\n");
    printf("14.Cikis\n");
    printf("\n");
    do
    {
        printf("SECIMINIZ: ");
        scanf("%d",&secim);
    }
    while(secim<1 || secim>14);

    return secim;
}

int hash1(int tel_no)
{
    return (tel_no / 10000)-100;
}

int hash2(char *abone_ad)
{
    return toupper(abone_ad[0])-'A';
}

void tel_no_sirali_ekle(aboneler **bas,aboneler *yeni)
{
    aboneler *gecici, *onceki;

    if (*bas==NULL)  //kuyruk bossa
    {
        yeni->tel_noya_gore_sonraki=NULL;
        *bas=yeni;
    }
    else if (yeni->tel_no<(*bas)->tel_no)   //en basa eklenecekse
    {
        yeni->tel_noya_gore_sonraki=*bas;
        *bas=yeni;
    }
    else    //araya ya da sona eklenecekse
    {
        onceki=*bas;
        gecici=(*bas)->tel_noya_gore_sonraki;
        while ((gecici!=NULL) && (gecici->tel_no<yeni->tel_no))  //eklenecek uygun yer araniyor
        {
            onceki=gecici;
            gecici=gecici->tel_noya_gore_sonraki;
        }
        yeni->tel_noya_gore_sonraki=gecici;//gecici NULL ise en sona, degilse onceki dugumu ile gecici dugumu arasina ekleniyor
        onceki->tel_noya_gore_sonraki=yeni;
    }
    yeni->gorusme_bas.sonraki=&(yeni->gorusme_bas);//gorusme ilkleme yapılıyor
    yeni->gorusme_bas.onceki=&(yeni->gorusme_bas);
    printf("Abone basari ile eklenmistir.");
}

aboneler *tel_noya_gore_ara(struct abone *bas, int aranan_tel_no)//urun listede bulunursa isaretcisi dondurulur, bulunamazsa NULL dondurulur
{
    while (bas!=0 && bas->tel_no<=aranan_tel_no)
    {
        if (bas->tel_no==aranan_tel_no) return bas;
        bas=bas->tel_noya_gore_sonraki;
    }
    return 0;
}

void gorusme_ekle(gorusmeler *listebas_ptr,gorusmeler *yeni)
{

    gorusmeler *gecici;
    gecici=listebas_ptr->sonraki;

    while (gecici!=listebas_ptr && strcmp(gecici->tarih,yeni->tarih)==-1)
        gecici=gecici->sonraki;

    yeni->sonraki=gecici;
    yeni->onceki=gecici->onceki;
    gecici->onceki->sonraki=yeni;
    gecici->onceki=yeni;
}

void kucukten_buyuge_listele(gorusmeler *liste_basi_ptr)
{
    gorusmeler *gecici;
    int toplam_gorusme=0;
    int toplam_gorusme_suresi=0;

    printf("Aranan No     Tarih       Bas Zamani  Sure\n");
    printf("-----------   ----------  ----------  -----\n");

    gecici=liste_basi_ptr->sonraki;
    while (gecici!=liste_basi_ptr)
    {
        toplam_gorusme++;
        toplam_gorusme_suresi=toplam_gorusme_suresi+gecici->sure;
            char dizi[9],dizi2[5],dizi3[10];

            strcpy(dizi3,gecici->aranan_no);
            printf("%-1c%-1c%-1c-%-1c%-1c%-1c%-1c%-1c%-1c%-1c   ",dizi3[0],dizi3[1],dizi3[2],dizi3[3],dizi3[4],dizi3[5],dizi3[6],dizi3[7],dizi3[8],dizi3[9]);
            strcpy(dizi,gecici->tarih);
            printf("%-1c%-1c.%-1c%-1c.%-1c%-1c%-1c%-1c  ",dizi[6],dizi[7],dizi[4],dizi[5],dizi[0],dizi[1],dizi[2],dizi[3]);
            strcpy(dizi2,gecici->bas_zamani);
            printf("%-1c%-1c:%-1c%-6c  %d\n",dizi2[0],dizi2[1],dizi2[2],dizi2[3],gecici->sure);
        gecici=gecici->sonraki;
    }
    if(toplam_gorusme!=0)
    {
        printf("Toplam Gorusme Sayisi:%d\n",toplam_gorusme);
        printf("Toplam Gorusme Suresi:%d\n",toplam_gorusme_suresi);
        float ortalama=(float)(toplam_gorusme_suresi)/(float)(toplam_gorusme);
        printf("Ortalama Gorusme Suresi:%.2f\n",ortalama);
    }
    else printf("bu abone gorusme yapmamistir\n");
}

void soyada_gore_sirali_ekle(aboneler *liste_basi_ptr, aboneler *yeni)
{
    struct abone *onceki, *gecici;
    char *dizi = strupr(yeni->soyad);
    strcpy(yeni->soyad,dizi);
    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->soyada_gore_sonraki;
    while(gecici!=liste_basi_ptr && strcmp(yeni->soyad,gecici->soyad)==1)
    {
        onceki=gecici;
        gecici=gecici->soyada_gore_sonraki;
    }

    yeni->soyada_gore_sonraki=gecici;
    onceki->soyada_gore_sonraki=yeni;
}

void sonuc_gorusme_listele(gorusmeler *liste_basi_ptr)
{
    gorusmeler *gecici;
    int sayac=0;

    printf("Aranan No     Tarih       Bas Zamani  Sure\n");
    printf("-----------   ----------  ----------  -----\n");

    gecici=liste_basi_ptr->onceki;
    while(gecici!=liste_basi_ptr && sayac<3)
    {
            char dizi[9],dizi2[5],dizi3[10];

            strcpy(dizi3,gecici->aranan_no);
            printf("%-1c%-1c%-1c-%-1c%-1c%-1c%-1c%-1c%-1c%-1c   ",dizi3[0],dizi3[1],dizi3[2],dizi3[3],dizi3[4],dizi3[5],dizi3[6],dizi3[7],dizi3[8],dizi3[9]);

            strcpy(dizi,gecici->tarih);
            printf("%-1c%-1c.%-1c%-1c.%-1c%-1c%-1c%-1c  ",dizi[6],dizi[7],dizi[4],dizi[5],dizi[0],dizi[1],dizi[2],dizi[3]);

            strcpy(dizi2,gecici->bas_zamani);
            printf("%-1c%-1c:%-1c%-6c  %d\n",dizi2[0],dizi2[1],dizi2[2],dizi2[3],gecici->sure);
        sayac++;
        gecici=gecici->onceki;
    }

}

void ilk_ucbasamaga_gore_listele(aboneler *bas)//kuyrugun ilk dugumunun adresi call-by-value ile aktariliyor
{
    while(bas!=NULL)
    {
        printf("           %-10d  %-6s  %-5s   %-11s  %s\n",bas->tel_no,bas->ad,bas->soyad,bas->adres,abone_tip_yazdirma(bas->abone_tip));
        bas=bas->tel_noya_gore_sonraki;//bas 1 oteleniyor
    }
}

void harf_ile_listeleme(aboneler *bas)
{
    aboneler *gecici;
    printf("Telefon No  Ad      Soyad   Adres        Abone Tipi\n");
    printf("----------  ------  -----   -----------  ----------\n");

    gecici=bas->soyada_gore_sonraki;
    while(gecici!=bas)
    {
        printf("%-10d  %-6s  %-5s   %-11s  %s\n",gecici->tel_no,gecici->ad,gecici->soyad,gecici->adres,abone_tip_yazdirma(gecici->abone_tip));
        gecici=gecici->soyada_gore_sonraki;//bas 1 oteleniyor
    }
}

void Kelime_ile_listeleme(aboneler *bas,char *eleman)
{
    aboneler *gecici;
    strupr(eleman);
    printf("Telefon No  Ad      Soyad     Adres        Abone Tipi\n");
    printf("----------  ------  -------   -----------  ----------\n");

    gecici=bas->soyada_gore_sonraki;
    while(gecici!=bas)
    {
        if(strncmp(eleman,gecici->soyad,strlen(eleman))==0)
        {
            printf("%-10d  %-8s  %-5s   %-11s  %s\n",gecici->tel_no,gecici->ad,gecici->soyad,gecici->adres,abone_tip_yazdirma(gecici->abone_tip));
        }
        gecici=gecici->soyada_gore_sonraki;//bas 1 oteleniyor
    }
}

int abone_tip_dondur(char tip)
{
    switch(tip)
    {
    case 'S':
    case 's':
        return 1;
    case 'I':
    case 'i':
        return 2;
    case 'K':
    case 'k':
        return 3;
    case 'G':
    case 'g':
        return 4;
    }
    return 0;
}

char * abone_tip_yazdirma(char tip)
{
    switch(tip)
    {
    case 'S':
    case 's':
        return "Sahis";
    case 'I':
    case 'i':
        return "Isletme";
    case 'K':
    case 'k':
        return "Kamu";
    case 'G':
    case 'g':
        return "Guvenlik";
    }
    return NULL;
}

char * abone_tip_yazdirma1(int sayi)
{
    switch(sayi)
    {
    case 0:
        return "Sahis";
    case 1:
        return "Isletme";
    case 2:
        return "Kamu";
    case 3:
        return "Guvenlik";
    }
    return NULL;
}

void tarihe_gore_arama(gorusmeler *birGorusme,aboneler *birAbone,char *tarih)
{
    gorusmeler *gecici;
    int bulundu=0;
    gecici=birGorusme->sonraki;
    while(gecici!=birGorusme && strcmp(gecici->tarih,tarih)!=1)
    {
        if(strcmp(gecici->tarih,tarih)==0)
        {
            bulundu=1;
            gorusme_yazdir(birAbone,gecici);
        }
        gecici=gecici->sonraki;
    }
    if(bulundu==0)
    {
        printf("Bu Tarihte Hic Gorusme Yapilmamistir\n");
    }
}

void gorusme_yazdir(aboneler *birAbone,gorusmeler *gecici)
{
    char dizi[9],dizi2[5],dizi3[10];

    strcpy(dizi3,gecici->aranan_no);
    printf("%-10i  %-1c%-1c%-1c-%-1c%-1c%-1c%-1c%-1c%-1c%-1c   ",birAbone->tel_no,dizi3[0],dizi3[1],dizi3[2],dizi3[3],dizi3[4],dizi3[5],dizi3[6],dizi3[7],dizi3[8],dizi3[9]);
    strcpy(dizi,gecici->tarih);
    printf("%-1c%-1c.%-1c%-1c.%-1c%-1c%-1c%-1c  ",dizi[6],dizi[7],dizi[4],dizi[5],dizi[0],dizi[1],dizi[2],dizi[3]);
    strcpy(dizi2,gecici->bas_zamani);
    printf("%-1c%-1c:%-1c%-6c  %d\n",dizi2[0],dizi2[1],dizi2[2],dizi2[3],gecici->sure);
}

void Belli_bir_tarihe_kadar_arama_yapmayanlarin_listesi(gorusmeler *birGorusme,aboneler *bas,char *tarih)
{
    gorusmeler *gecici;
    gecici=birGorusme->onceki;

    if(strcmp(gecici->tarih,tarih)==-1)
    {
        printf("%-10d  %-6s  %-5s   %-11s  %s\n",bas->tel_no,bas->ad,bas->soyad,bas->adres,abone_tip_yazdirma(bas->abone_tip));
    }

}

void Aranan_noya_gore_listele(gorusmeler *listebas,aboneler *bas,char *numara)
{
    gorusmeler *gecici;
    gecici=listebas->sonraki;
    while(gecici!=listebas)
    {
        if(strcmp(gecici->aranan_no,numara)==0)
        {
            printf("%-10d  %-6s  %-5s   %-11s  %s\n",bas->tel_no,bas->ad,bas->soyad,bas->adres,abone_tip_yazdirma(bas->abone_tip));
            break;
        }
        gecici=gecici->sonraki;
    }
}

aboneler *tel_listesinden_cikar(aboneler **ilk_ptr,aboneler *cikarilacak_ptr)
{
    aboneler *onceki, *gecici;

    onceki=*ilk_ptr;
    gecici=(*ilk_ptr)->tel_noya_gore_sonraki;

    if(*ilk_ptr==cikarilacak_ptr)//cikarilacak dugum, ilk dugum ise
    {
        (*ilk_ptr)=(*ilk_ptr)->tel_noya_gore_sonraki;//ilk_ptr'yi guncelle
        return onceki;
    }
    else
    {
        while(gecici!=cikarilacak_ptr)
        {
            onceki=gecici;
            gecici=gecici->tel_noya_gore_sonraki;
        }

        onceki->tel_noya_gore_sonraki=gecici->tel_noya_gore_sonraki;
        return gecici;
    }
}

gorusmeler *ara(gorusmeler *liste_basi_ptr,gorusmeler *aranan)//ogrenci listede bulunursa isaretcisi dondurulur, bulunamazsa NULL dondurulur
{
    gorusmeler *gecici;

    gecici=liste_basi_ptr->sonraki;
    while (gecici!=liste_basi_ptr)
    {
        if (gecici==aranan) return gecici;
        gecici=gecici->sonraki;
    }

    return NULL;
}

void cikar(gorusmeler *cikarilacak)
{
    cikarilacak->onceki->sonraki=cikarilacak->sonraki;
    cikarilacak->sonraki->onceki=cikarilacak->onceki;
}

void soyad_listesinden_cikar(aboneler *liste_basi_ptr,char *soyad)
{
    aboneler *onceki, *gecici;

    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->soyada_gore_sonraki;
    while(gecici!=liste_basi_ptr && strcmp(gecici->soyad,soyad)!=0)
    {
        onceki=gecici;
        gecici=gecici->soyada_gore_sonraki;
    }

    if(strcmp(gecici->soyad,soyad)!=0)
    {
        printf("Boyle bir abone yoktur\n");
    }
    else {
        onceki->soyada_gore_sonraki=gecici->soyada_gore_sonraki;
    }
}
