
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

struct sporcu{
int lisans_no;
char ad[16];
char soyad[26];
char tc_kimlik_no[12];
char dogum_tarihi[8];
int il_plaka_kodu;
char club_ad[30];
int ukd_puani;
struct sporcu *tcye_gore_sonraki;
struct sporcu *ada_gore_sonraki;
struct sporcu *il_plaka_kodu_sonraki;
struct sporcu *il_plaka_kodu_onceki;

};
int hash1(char*);
int has2(char *);
void tcye_gore_ekle(struct sporcu*,struct sporcu *);
int menu_secim(void);
struct sporcu *tcye_gore_ara(struct sporcu*,int);
void soyada_gore_ekle(struct sporcu *,struct sporcu*);
void il_plaka_koduna_gore_ekle(struct sporcu*,struct sporcu *);
void ad_guncelle(struct sporcu*,int ,char*);
void tcye_gore_bilgi_goruntule(struct sporcu *);
void soyada_gore_listele(struct sporcu *);
void ada_gore_sirala(struct sporcu*);
void ukdye_gore_en_guclu(struct sporcu *);
void ukdye_gore_en_zayif(struct sporcu *);
void ikibin_ustu_ukd(struct sporcu*);
void dogum_gunune_gore_listele(struct sporcu*,char *);
void tcyi_guncelle(struct sporcu *,int,char *);
void illere_gore_oyuncu_say(struct sporcu *);
void bas_harfe_gore_listele(struct sporcu*,char);
void ada_gore_listele(struct sporcu*,char *);
void tc_ukd_guncelle(struct sporcu *,int,int);
void ad_ukd_guncelle(struct sporcu*,int,int);
void il_plaka_hash_guncelle(struct sporcu*,int,char*);
void il_plaka_hash_ukd_guncelle(struct sporcu*,int,int);
void tc_sil(struct sporcu*,int);
void soyad_sil(struct sporcu*,int);
void il_plaka_sil(struct sporcu *,int);
int main(int argc, char** argv) {


int i;
struct sporcu * max;
max=malloc(sizeof(struct sporcu));
max->ukd_puani=0;
int j;
int gosterilenler=-1;

int secim;
char karakter;
int eleman_say;
struct sporcu tc_kimlik_no_hash[99];
struct sporcu soyad_hash[30];
struct sporcu il_plaka_kodu_hash[81];
struct sporcu *lisans_no[9999]={NULL};
int tc_indeks,lisans_num,plaka_kod,ukd_point,indeks2;
char tc_no[12];
char nameref[16];
char sporcu_ad[16],sporcu_soyad[26],sporcu_dogum[8],klup_ad[30];
struct sporcu *yeni_sporcu;
for(i=0;i<30;i++)
{
soyad_hash[i].ada_gore_sonraki=&soyad_hash[i];
}
for(i=0;i<99;i++){
tc_kimlik_no_hash[i].tcye_gore_sonraki=&tc_kimlik_no_hash[i];

}

for(i=0;i<81;i++){
il_plaka_kodu_hash[i].il_plaka_kodu_onceki=&il_plaka_kodu_hash[i];
il_plaka_kodu_hash[i].il_plaka_kodu_sonraki=&il_plaka_kodu_hash[i];

}

do{
        secim=menu_secim();
        switch (secim){
			case 1:
			printf("Eklenecek urunun tcsini giriniz\n");
			scanf("%s",tc_no);
			tc_indeks=hash1(tc_no);
			if(tcye_gore_ara(&tc_kimlik_no_hash[tc_indeks],tc_indeks)==NULL)
			{
				yeni_sporcu=malloc(sizeof(struct sporcu));

				strcpy(yeni_sporcu->tc_kimlik_no,tc_no);
				printf("Sporcunun lisans nosunu giriniz\n");
				fflush(stdin);
				scanf("%d",&lisans_num);
				printf("Sporcunun adini giriniz\n");
				fflush(stdin);
				scanf("%s",sporcu_ad);
				printf("Sporcunun soyadini giriniz\n");
				fflush(stdin);
				scanf("%s",sporcu_soyad);
				indeks2=hash2(sporcu_soyad);
				printf("Sporcunun dogum tarihini giriniz\n");
				fflush(stdin);
				scanf("%s",sporcu_dogum);
				printf("Sporcunun il plaka kodunu giriniz\n");
				fflush(stdin);
				scanf("%d",&plaka_kod);
				printf("Sporcunun kulup adini giriniz\n");
				fflush(stdin);
				scanf("%s",klup_ad);
				printf("Sporcunun ukd puanini giriniz\n");
				fflush(stdin);
				scanf("%d",&ukd_point);
				yeni_sporcu->lisans_no=lisans_num;
				strcpy(yeni_sporcu->ad,sporcu_ad);
				strcpy(yeni_sporcu->soyad,sporcu_soyad);
				strcpy(yeni_sporcu->dogum_tarihi,sporcu_dogum);

				yeni_sporcu->il_plaka_kodu=plaka_kod;
				strcpy(yeni_sporcu->club_ad,klup_ad);
				yeni_sporcu->ukd_puani=ukd_point;
				tcye_gore_ekle(&tc_kimlik_no_hash[tc_indeks],yeni_sporcu);
				il_plaka_koduna_gore_ekle(&il_plaka_kodu_hash[plaka_kod],yeni_sporcu);
				soyada_gore_ekle(&soyad_hash[indeks2],yeni_sporcu);
                ada_gore_sirala(&soyad_hash[indeks2]);
				lisans_no[yeni_sporcu->lisans_no]=yeni_sporcu;
			}break;
			case 2:
			printf("Transfer edilecek oyuncunun lisans nosunu giriniz\n");
			fflush(stdin);
			scanf("%d",&lisans_num);
			if(lisans_no[lisans_num]!=NULL)
			{
                strcpy(tc_no,lisans_no[lisans_num]->tc_kimlik_no);
                strcpy(sporcu_soyad,lisans_no[lisans_num]->soyad);
                plaka_kod=lisans_no[lisans_num]->il_plaka_kodu;
                tc_indeks=hash1(tc_no);
                indeks2=hash2(sporcu_soyad);
                printf("Aradiginiz oyuncu bulunmaktadir transfer edilecek klubu seciniz\n");
                fflush(stdin);
                scanf("%s",klup_ad);
                tcyi_guncelle(&tc_kimlik_no_hash[tc_indeks],lisans_num,klup_ad);
                ad_guncelle(&soyad_hash[indeks2],lisans_num,klup_ad);
                plaka_kod=lisans_no[lisans_num]->il_plaka_kodu;
                il_plaka_hash_guncelle(&il_plaka_kodu_hash[plaka_kod],lisans_num,klup_ad);
			}

			if(lisans_num>1&&lisans_num<10000&&lisans_no[lisans_num]!=NULL)
			{

                strcpy(lisans_no[lisans_num]->club_ad,klup_ad);


                printf("Transfer basariyla gerceklestirildi\n");
			}
			else{
			printf("Hatali giris tekrar deneyiniz\n");
			}break;
			case 3:
			printf("Ukd puani guncellenecek oyuncunun   lisans nosunu giriniz\n");
			fflush(stdin);
			scanf("%d",&lisans_num);
			if(lisans_no[lisans_num]!=NULL)
			{
                printf("Aradiginiz oyuncu bulunmaktadir yeni ukd puanini giriniz\n");
                fflush(stdin);
                scanf("%d",&ukd_point);

                strcpy(tc_no,lisans_no[lisans_num]->tc_kimlik_no);
                strcpy(sporcu_soyad,lisans_no[lisans_num]->soyad);
                plaka_kod=lisans_no[lisans_num]->il_plaka_kodu;
                tc_indeks=hash1(tc_no);
                indeks2=hash2(sporcu_soyad);
                tc_ukd_guncelle(&tc_kimlik_no_hash[tc_indeks],lisans_num,ukd_point);
                ad_ukd_guncelle(&soyad_hash[indeks2],lisans_num,ukd_point);
                plaka_kod=lisans_no[lisans_num]->il_plaka_kodu;
                il_plaka_hash_ukd_guncelle(&il_plaka_kodu_hash[plaka_kod],lisans_num,ukd_point);


			}
            if(lisans_num>1&&lisans_num<10000&&lisans_no[lisans_num]!=NULL)
            {

                lisans_no[lisans_num]->ukd_puani=ukd_point;
                printf("Basariyla guncellenmistir\n");

            }else{
            printf("Hatali giris\n");
            }break;
            case 4:
            printf("Plaka kodu guncellenecek Ile Tc kimlik no ile erismek icin tcyi giriniz\n");
            fflush(stdin);
            scanf("%s",tc_no);
            tc_indeks=hash1(tc_no);
            if(tcye_gore_ara(&tc_kimlik_no_hash[tc_indeks],tc_indeks)==NULL) printf("Boyle bir tc yoktur\n");
            else
            {
                printf("Yeni plaka kodunu gırınız\n");
                fflush(stdin);
                scanf("%d",&plaka_kod);

                yeni_sporcu=tcye_gore_ara(&tc_kimlik_no_hash[tc_indeks],tc_indeks);
                yeni_sporcu->il_plaka_kodu=plaka_kod;
                indeks2=hash2(yeni_sporcu->soyad);
                tcye_gore_ekle(&tc_kimlik_no_hash[tc_indeks],yeni_sporcu);
                soyada_gore_ekle(&soyad_hash[indeks2],yeni_sporcu);
                il_plaka_koduna_gore_ekle(&il_plaka_kodu_hash[yeni_sporcu->il_plaka_kodu],yeni_sporcu);
                lisans_no[yeni_sporcu->lisans_no]->il_plaka_kodu=plaka_kod;
                printf("Basariyla guncellenmistir\n");

            }break;
            case 5:
            printf("Iptal edilecek lisan noyu giriniz\n");
            fflush(stdin);
            scanf("%d",&lisans_num);
            if(lisans_no[lisans_num]!=NULL)
            {
                strcpy(tc_no,lisans_no[lisans_num]->tc_kimlik_no);
                tc_indeks=hash1(tc_no);
                strcpy(sporcu_soyad,lisans_no[lisans_num]->soyad);
                indeks2=hash2(sporcu_soyad);
                plaka_kod=lisans_no[lisans_num]->il_plaka_kodu;
                tc_sil(&tc_kimlik_no_hash[tc_indeks],lisans_num);
                soyad_sil(&soyad_hash[indeks2],lisans_num);
                //il_plaka_sil(&il_plaka_kodu_hash[plaka_kod],lisans_num);




            }
            if(lisans_num>1&&lisans_num<10000&&lisans_no[lisans_num]!=NULL)
            {
                lisans_no[lisans_num]=NULL;
                printf("Basariyla silinmistir\n");

            }else
            {
            printf("Boyle bir oyuncu yoktur\n");}break;
            case 6:
            printf("Goruntulenmek istenen tcyi giriniz\n");
            fflush(stdin);
            scanf("%s",tc_no);
            tc_indeks=hash1(tc_no);
            if(tcye_gore_ara(&tc_kimlik_no_hash[tc_indeks],tc_indeks)==NULL)
            {
                printf("Boyle bir tc yoktur\n");
            }
            else{
            tcye_gore_bilgi_goruntule(tcye_gore_ara(&tc_kimlik_no_hash[tc_indeks],tc_indeks));
            } break;
            case 7:
                 printf("Aranacak soyadlarin bas harfini giriniz\n");
                fflush(stdin);
                scanf(" %c",&karakter);
                indeks2=toupper(karakter)-'A';



                    bas_harfe_gore_listele(&soyad_hash[indeks2],karakter);






            break;
            case 8:
            printf("Metin parcasini giriniz\n");
            fflush(stdin);
            scanf("%s",nameref);
            eleman_say=strlen(nameref);
            for(i=0;i<26;i++)
            {

                    if(strncmp(soyad_hash[i].ada_gore_sonraki->soyad,nameref,eleman_say)==0){

                        printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
                        printf("%2d            %2s      %2s       %2s       %2s             %2d               %2s               %2d  \n",soyad_hash[i].ada_gore_sonraki->lisans_no,soyad_hash[i].ada_gore_sonraki->tc_kimlik_no,soyad_hash[i].ada_gore_sonraki->ad,soyad_hash[i].ada_gore_sonraki->soyad,soyad_hash[i].ada_gore_sonraki->dogum_tarihi,soyad_hash[i].ada_gore_sonraki->il_plaka_kodu,soyad_hash[i].ada_gore_sonraki->club_ad,soyad_hash[i].ada_gore_sonraki->ukd_puani);
                    }




            }break;

            case 9:


                printf("Bir ad giriniz\n");

                fflush(stdin);
                scanf("%s",nameref);

                for(i=0;i<26;i++)
                {
                    ada_gore_listele(&soyad_hash[i],nameref);

                }



                break;
            case 10:
            printf("Plaka kodunu giriniz\n");
            fflush(stdin);
            scanf("%d",&plaka_kod);
            ukdye_gore_en_guclu(&il_plaka_kodu_hash[plaka_kod]);
            ukdye_gore_en_zayif(&il_plaka_kodu_hash[plaka_kod]);break;
            case 11:
                printf("Plaka kodunu giriniz\n");
                fflush(stdin);
                scanf("%d",&plaka_kod);
                ikibin_ustu_ukd(&il_plaka_kodu_hash[plaka_kod]);break;


            case 12:
             printf("Plaka kodunu giriniz\n");
             fflush(stdin);
             scanf("%d",&plaka_kod);
             printf("Dogum gunu tarihini  giriniz\n");
             fflush(stdin);
             scanf("%s",sporcu_dogum);
             dogum_gunune_gore_listele(&il_plaka_kodu_hash[plaka_kod],sporcu_dogum);break;
             case 13:




for(i=0;i<10;i++){
    for(j=0;j<9999;j++)
    {
        if(lisans_no[j]!=NULL){
            if(lisans_no[j]->ukd_puani>max->ukd_puani&&lisans_no[j]->ukd_puani!=gosterilenler){
                max=lisans_no[j];
                gosterilenler=lisans_no[j]->ukd_puani;

            }
        }

    }
printf("----- -------- ------- ------- ------- ------- ------- -------\n");
printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");

printf("%2d          %2s        %2s       %2s       %2s             %2d               %2s             %2d  \n",max->lisans_no,max->tc_kimlik_no,max->ad,max->soyad,max->dogum_tarihi,max->il_plaka_kodu,max->club_ad,max->ukd_puani);
max->ukd_puani=0;
}

for(i=0;i<9999;i++){
    if(lisans_no[i]!=NULL){
        if(lisans_no[i]->ukd_puani==gosterilenler){
            printf("----- -------- ------- ------- ------- ------- ------- -------\n");
            printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
            printf("%2d           %2s       %2s       %2s        %2s            %2d               %2s              %2d  \n",lisans_no[i]->lisans_no,lisans_no[i]->tc_kimlik_no,lisans_no[i]->ad,lisans_no[i]->soyad,lisans_no[i]->dogum_tarihi,lisans_no[i]->il_plaka_kodu,lisans_no[i]->club_ad,lisans_no[i]->ukd_puani);


        }
    }
}break;
             case 14:
                for(i=0;i<81;i++){

                    illere_gore_oyuncu_say(&il_plaka_kodu_hash[i]);
                }break;

             case 15:
                printf("Kulup adini giriniz\n");
                fflush(stdin);
                scanf("%s",klup_ad);
                for(i=0;i<9999;i++)
                {
                    if(lisans_no[i]!=NULL)
                        {
                            if(strcmp(lisans_no[i]->club_ad,klup_ad)==0)
                             printf("%d lisans nolu sporcunun klup adi %sdir",i,klup_ad);
                        }
                }break;
}


}while (secim!=16);
printf("Basariyla cikildi\n");
return (EXIT_SUCCESS);
}

int menu_secim(void){
    int secim;

    printf("\n");
    printf("********************MENU************************************\n");
    printf("1.Yeni bir urun ekleme\n");
    printf("2.Bir oyuncunun baska bir klube transferi\n");
    printf("3.Bir oyuncunun ukd puaninin guncellenmesi\n");
    printf("4.Tc kimlik noyla il guncellenmesi\n");
    printf("5.Lisans iptali\n");
    printf("6.Tcye gore bilgi goruntule\n");
    printf("7.Harf ile baslayan soyadlarina sahip oyunculari listele\n");
    printf("8.Bir metin parcasiyla baslayan soyadlarina sahip oyunculari listele\n");
    printf("9.Ada gore listele\n");
    printf("10.Plaka koduna gore en yuksek ve en dusuk 5 ukd listele\n");
    printf("11.Ikibin ustu ukd listele\n");
    printf("12.Dogum gunune gore ukd bazlı sirala\n");
    printf("13.Ukd puanina gore en guclu sporcu sirala\n");
    printf("14.Illere gore oyuncu sayilari\n");
    printf("15.Klube gore oyuncu ara\n");
    printf("16.EXIT\n");
    printf("\n");
    do {
        printf("\nSeciminizi Giriniz:  ");
        scanf("%d", &secim);
    }while(secim<1 || secim>16);

    return secim;
}
int hash1(char *str){
int i;
int toplam=0;
    for ( i = 0; str[i] != '\0'; ++i)
    {
        toplam = toplam+str[i] - '0';


    }
return toplam;
}
int hash2(char *soyadi)
{
    return toupper(soyadi[0])-'A';
}
void tcye_gore_ekle(struct sporcu*liste_basiptr,struct sporcu *yeni)
{
	struct sporcu *onceki,*gecici;
	onceki=liste_basiptr;
	gecici=liste_basiptr->tcye_gore_sonraki;
	while(gecici!=liste_basiptr&&strcmp(gecici->tc_kimlik_no,yeni->tc_kimlik_no)<0)
	{	onceki=gecici;
		gecici=gecici->tcye_gore_sonraki;

	}
	onceki->tcye_gore_sonraki=yeni;
	yeni->tcye_gore_sonraki=gecici;


}
struct sporcu * tcye_gore_ara(struct sporcu*liste_basi_ptr,int aranan_tc){
struct sporcu *gecici;

gecici=liste_basi_ptr->tcye_gore_sonraki;
while(gecici!=liste_basi_ptr){
if(hash1(gecici->tc_kimlik_no)==aranan_tc)return gecici;

gecici=gecici->tcye_gore_sonraki;
}
return NULL;
}

void il_plaka_koduna_gore_ekle(struct sporcu *ilk_ptr,struct sporcu * yeni)
{ struct sporcu *gecici;

	gecici=ilk_ptr->il_plaka_kodu_sonraki;

	while(gecici!=ilk_ptr&&gecici->ukd_puani<=yeni->ukd_puani)
	{
		if(gecici->ukd_puani==yeni->ukd_puani)
		{
            gecici=ilk_ptr->ada_gore_sonraki;

			while(gecici!=ilk_ptr&&(strcmp(gecici->dogum_tarihi,yeni->dogum_tarihi))<0)
			{
				gecici=gecici->il_plaka_kodu_sonraki;
                gecici->il_plaka_kodu_onceki=gecici;

			}

            gecici->il_plaka_kodu_onceki->il_plaka_kodu_sonraki=yeni;
            yeni->il_plaka_kodu_sonraki=gecici;
            yeni->il_plaka_kodu_onceki=gecici->il_plaka_kodu_onceki;




		}
				gecici=gecici->il_plaka_kodu_sonraki;
                gecici->il_plaka_kodu_onceki=gecici;;


	}
	if(gecici->ukd_puani!=yeni->ukd_puani)
	{
			 gecici->il_plaka_kodu_onceki->il_plaka_kodu_sonraki=yeni;
            yeni->il_plaka_kodu_sonraki=gecici;
            yeni->il_plaka_kodu_onceki=gecici->il_plaka_kodu_onceki;

	}

}
void soyada_gore_ekle(struct sporcu *ilk_ptr, struct sporcu *yeni){
struct sporcu *gecici,*onceki;
gecici=malloc(sizeof(struct sporcu));
onceki=malloc(sizeof(struct sporcu));
onceki=ilk_ptr;
gecici=ilk_ptr->ada_gore_sonraki;
while(gecici!=ilk_ptr){
    onceki=gecici;
    gecici=gecici->ada_gore_sonraki;
}

onceki->ada_gore_sonraki=yeni;
yeni->ada_gore_sonraki=gecici;





}

void tcye_gore_bilgi_goruntule(struct sporcu *ilk_ptr){
printf("----- -------- ------- ------- ------- ------- ------- -------\n");
printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
printf("%2d          %2s       %2s       %2s        %2s            %2d               %2s              %2d  \n",ilk_ptr->lisans_no,ilk_ptr->tc_kimlik_no,ilk_ptr->ad,ilk_ptr->soyad,ilk_ptr->dogum_tarihi,ilk_ptr->il_plaka_kodu,ilk_ptr->club_ad,ilk_ptr->ukd_puani);

}
void soyada_gore_listele(struct sporcu *ilk_ptr)
{
struct sporcu*gecici;
gecici=ilk_ptr->ada_gore_sonraki;

while(gecici!=ilk_ptr)
{

printf("----- -------- ------- ------- ------- ------- ------- -------\n");
printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
printf("%2d           %2s       %2s       %2s        %2s             %2d              %2s            %2d  \n",gecici->lisans_no,gecici->tc_kimlik_no,gecici->ad,gecici->soyad,gecici->dogum_tarihi,gecici->il_plaka_kodu,gecici->club_ad,gecici->ukd_puani);
gecici=gecici->ada_gore_sonraki;
}


}
void ada_gore_sirala(struct sporcu*ilk_ptr)
{
    struct sporcu * gecici;
    struct sporcu * gecici2;
    gecici=ilk_ptr->ada_gore_sonraki;
    gecici2=ilk_ptr->ada_gore_sonraki;
    char adref[16];
    while(gecici!=ilk_ptr)
    {
        while(gecici2!=ilk_ptr)
        {


            if(strcmp(gecici->ad,gecici2->ad)>0)
            {
                strcpy(adref,gecici->ad);
                strcpy(gecici->ad,gecici2->ad);
                strcpy(gecici2->ad,adref);
            }

            gecici2=gecici2->ada_gore_sonraki;
        }
        gecici=gecici->ada_gore_sonraki;
    }

}
void ukdye_gore_en_guclu(struct sporcu * ilk_ptr)
{
int i=0;
int sayac=0;
struct sporcu *gecici,*gecici2;
int eleman_say=0;
gecici2=ilk_ptr->il_plaka_kodu_sonraki;
struct sporcu *max;
max=malloc(sizeof(struct sporcu));
max->ukd_puani=0;
int gosterilenler=0;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici2!=ilk_ptr){
    eleman_say++;
    gecici2=gecici2->il_plaka_kodu_sonraki;
}


for(i=0;i<eleman_say;i++){
    while(gecici!=ilk_ptr){
    if(gecici->ukd_puani>max->ukd_puani&&gecici->ukd_puani!=gosterilenler){
            max=gecici;
            gosterilenler=gecici->ukd_puani;
    }
    gecici=gecici->il_plaka_kodu_sonraki;
    }
if(sayac<5){
    printf("----- -------- ------- ------- ------- ------- ------- -------\n");
    printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
    printf("%2d           %2s       %2s       %2s        %2s            %2d               %2s              %2d  \n",max->lisans_no,max->tc_kimlik_no,max->ad,max->soyad,max->dogum_tarihi,max->il_plaka_kodu,max->club_ad,max->ukd_puani);
    sayac++;

}
max->ukd_puani=0;
 gecici=ilk_ptr->il_plaka_kodu_sonraki;

}



}
void ukdye_gore_en_zayif(struct sporcu *ilk_ptr){
int i=0;
int sayac=0;
struct sporcu *gecici,*gecici2;
int eleman_say=0;
gecici=malloc(sizeof(struct sporcu));
gecici2=malloc(sizeof(struct sporcu));
gecici2=ilk_ptr->il_plaka_kodu_sonraki;
struct sporcu *min;
min=malloc(sizeof(struct sporcu));
min->ukd_puani=9999;
int gosterilenler=0;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici2!=ilk_ptr){
    eleman_say++;
    gecici2=gecici2->il_plaka_kodu_sonraki;
}


for(i=0;i<eleman_say;i++){
    while(gecici!=ilk_ptr){
    if(gecici->ukd_puani<min->ukd_puani&&gecici->ukd_puani!=gosterilenler){
            min=gecici;
            gosterilenler=gecici->ukd_puani;
    }
gecici=gecici->il_plaka_kodu_sonraki;
}
if(sayac<5){
    printf("----- -------- ------- ------- ------- ------- ------- -------\n");
    printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
    printf("%2d           %2s       %2s       %2s        %2s            %2d                %2s             %2d  \n",min->lisans_no,min->tc_kimlik_no,min->ad,min->soyad,min->dogum_tarihi,min->il_plaka_kodu,min->club_ad,min->ukd_puani);
    sayac++;
}
min->ukd_puani=9999;
gecici=ilk_ptr->il_plaka_kodu_sonraki;

}
}
void ikibin_ustu_ukd(struct sporcu*ilk_ptr){
struct sporcu *gecici;
gecici=malloc(sizeof(struct sporcu));
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici!=ilk_ptr){
 if(gecici->ukd_puani>2000){
     printf("----- -------- ------- ------- ------- ------- ------- -------\n");
    printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
    printf("%2d           %2s       %2s       %2s     %2s                %2d              %2s             %2d  \n",gecici->lisans_no,gecici->tc_kimlik_no,gecici->ad,gecici->soyad,gecici->dogum_tarihi,gecici->il_plaka_kodu,gecici->club_ad,gecici->ukd_puani);
 }

gecici=gecici->il_plaka_kodu_sonraki;
}

}
void dogum_gunune_gore_listele(struct sporcu* ilk_ptr,char *dogum_gunu){
struct sporcu *gecici;
int i=0;
int j=0;
int gosterilenler=-1;
struct sporcu *gecici2;
struct sporcu * max;
int eleman_say=0;
max=malloc(sizeof(struct sporcu));
gecici2=malloc(sizeof(struct sporcu));
gecici=malloc(sizeof(struct sporcu));
max->ukd_puani=0;
gecici2=ilk_ptr->il_plaka_kodu_sonraki;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici2!=ilk_ptr)
{
    eleman_say++;
    gecici2=gecici2->il_plaka_kodu_sonraki;
}
struct sporcu *depo[eleman_say];
gecici=ilk_ptr->il_plaka_kodu_sonraki;
    while(gecici!=ilk_ptr){
        if(strcmp(gecici->dogum_tarihi,dogum_gunu)==0){
          depo[i]=gecici;
          i++;
        }
        gecici=gecici->il_plaka_kodu_sonraki;
    }

for(i=0;i<eleman_say;i++)
{
    for(j=0;j<eleman_say;j++){
        if(depo[j]->ukd_puani>max->ukd_puani&&depo[j]->ukd_puani!=gosterilenler)
        {
            max=depo[j];
            gosterilenler=max->ukd_puani;
        }
    }
printf("----- -------- ------- ------- ------- ------- ------- -------\n");
printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
printf("%2d           %2s       %2s       %2s        %2s            %2d               %2s            %2d  \n",max->lisans_no,max->tc_kimlik_no,max->ad,max->soyad,max->dogum_tarihi,max->il_plaka_kodu,max->club_ad,max->ukd_puani);
max->ukd_puani=0;
}



}

void illere_gore_oyuncu_say(struct sporcu*ilk_ptr){
int oyuncu_say=0;
struct sporcu *gecici;
struct sporcu *gecici2;
gecici2=ilk_ptr->il_plaka_kodu_sonraki;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
    while(gecici!=ilk_ptr)
    {
        oyuncu_say++;
        gecici=gecici->il_plaka_kodu_sonraki;

    }

if(oyuncu_say!=0){
    printf("Plaka kodu %d olan sehirde %d oyuncu vardir\n",gecici2->il_plaka_kodu,oyuncu_say);

}
}
void bas_harfe_gore_listele(struct sporcu *ilk_ptr,char karakter)
{
    struct sporcu * gecici;
    gecici=malloc(sizeof(struct sporcu));
    gecici=ilk_ptr->ada_gore_sonraki;

    while(gecici!=ilk_ptr)
    {
        if(gecici->soyad[0]==karakter){
            printf("----- -------- ------- ------- ------- ------- ------- -------\n");
        printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
        printf("%2d           %2s       %2s       %2s     %2s               %2d              %2s               %2d  \n",gecici->lisans_no,gecici->tc_kimlik_no,gecici->ad,gecici->soyad,gecici->dogum_tarihi,gecici->il_plaka_kodu,gecici->club_ad,gecici->ukd_puani);
        }
    gecici=gecici->ada_gore_sonraki;
    }
}
void ada_gore_listele(struct sporcu *ilk_ptr,char *nameref)
{
struct sporcu *gecici;
gecici=malloc(sizeof(struct sporcu));
gecici=ilk_ptr->ada_gore_sonraki;

while(gecici!=ilk_ptr&&gecici!=NULL){
            if(strcmp(gecici->ad,nameref)==0){
                    printf("----- ----------  --------- ------- ------- ------- ------- -------\n");
                    printf("Lisans no     Tc no     Ad       Soyad    Dogum Tarihi    İl plaka kodu     Klup adi        Ukd puani    \n");
                    printf("%2d          %2s        %2s       %2s        %2s            %2d              %2s     %2d  \n",gecici->lisans_no,gecici->tc_kimlik_no,gecici->ad,gecici->soyad,gecici->dogum_tarihi,gecici->il_plaka_kodu,gecici->club_ad,gecici->ukd_puani);
            }
gecici=gecici->ada_gore_sonraki;
}




}
void tcyi_guncelle(struct sporcu * ilk_ptr,int lisans,char *yeni_ad)
{
    struct sporcu * gecici;
    gecici=ilk_ptr->tcye_gore_sonraki;
    while(gecici!=ilk_ptr)
    {
        if(gecici->lisans_no==lisans)
        {
            strcpy(gecici->club_ad,yeni_ad);

        }
    gecici=gecici->tcye_gore_sonraki;
    }

}
void il_plaka_hash_guncelle(struct sporcu*ilk_ptr,int lisans,char*yeni_ad)
{
struct sporcu * gecici;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici!=ilk_ptr)
{
    if(gecici->lisans_no==lisans)
    {
        strcpy(gecici->club_ad,yeni_ad);

    }
gecici=gecici->il_plaka_kodu_sonraki;
}


}
void ad_guncelle(struct sporcu*ilk_ptr,int lisans,char*yeni_ad)
{
struct sporcu *gecici;
gecici=ilk_ptr->ada_gore_sonraki;
while(gecici!=ilk_ptr)
{
    if(gecici->lisans_no==lisans)
    {
        strcpy(gecici->club_ad,yeni_ad);

    }
gecici=gecici->ada_gore_sonraki;
}


}
void tc_ukd_guncelle(struct sporcu*ilk_ptr,int lisans_num,int ukd)
{
struct sporcu*gecici;
gecici=ilk_ptr->tcye_gore_sonraki;
while(gecici!=ilk_ptr)
{
if(gecici->lisans_no==lisans_num)
{
    gecici->ukd_puani=ukd;
}
gecici=gecici->tcye_gore_sonraki;
}

}
void ad_ukd_guncelle(struct sporcu *ilk_ptr,int lisans_num,int ukd)
{

struct sporcu*gecici;
gecici=ilk_ptr->ada_gore_sonraki;
while(gecici!=ilk_ptr)
{
if(gecici->lisans_no==lisans_num)
{
    gecici->ukd_puani=ukd;
}
gecici=gecici->ada_gore_sonraki;
}

}


void il_plaka_hash_ukd_guncelle(struct sporcu*ilk_ptr,int lisans_num,int ukd)
{

struct sporcu * gecici;
gecici=ilk_ptr->il_plaka_kodu_sonraki;
while(gecici!=ilk_ptr)
{
    if(gecici->lisans_no==lisans_num)
    {
        gecici->ukd_puani=ukd;

    }
gecici=gecici->il_plaka_kodu_sonraki;
}




}
void tc_sil(struct sporcu *ilk_ptr,int lisans)
{
    struct sporcu*gecici;
    struct sporcu *onceki;
    gecici=malloc(sizeof(struct sporcu));
    onceki=malloc(sizeof(struct sporcu));
    onceki=ilk_ptr;
    gecici=ilk_ptr->tcye_gore_sonraki;
    while(gecici!=ilk_ptr)
    {
        if(gecici->lisans_no==lisans)
        {
            onceki->tcye_gore_sonraki=gecici->tcye_gore_sonraki;
            free(gecici);

        }
        onceki=gecici;
        gecici=gecici->tcye_gore_sonraki;

    }


}
void soyad_sil(struct sporcu*ilk_ptr,int lisans)
{
 struct sporcu*gecici;
    struct sporcu *onceki;
    gecici=malloc(sizeof(struct sporcu));
    onceki=malloc(sizeof(struct sporcu));
    onceki=ilk_ptr;
    gecici=ilk_ptr->ada_gore_sonraki;
    while(gecici!=ilk_ptr)
    {
        if(gecici->lisans_no==lisans)
        {
            onceki->tcye_gore_sonraki=gecici->ada_gore_sonraki;
            free(gecici);

        }
        onceki=gecici;
        gecici=gecici->ada_gore_sonraki;

    }




}
void il_plaka_sil(struct sporcu *ilk_ptr,int lisans)
{
    struct sporcu*gecici;
    gecici=malloc(sizeof(struct sporcu));

    gecici=ilk_ptr->il_plaka_kodu_sonraki;
    while(gecici!=ilk_ptr)
    {
        if(gecici->lisans_no==lisans)
        {
            gecici->il_plaka_kodu_onceki->il_plaka_kodu_sonraki=gecici->il_plaka_kodu_sonraki;
            free(gecici);


        }
        gecici=gecici->il_plaka_kodu_sonraki;

    }





}


