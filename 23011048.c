#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100

//Ogrenci ile ilgili işlemlerin yapıldığı struct (Çift yönlü linked list)
typedef struct Ogrenci{ 
    char *name;
    char *surname;
    char *numara;     //01234567 gibi sayıları tutabilir
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
}Ogrenci;


//Odunç alma veya teslim etme işlemlerinin yapıldığı struct
typedef struct Odunc{
    char *ogrenciNo;
    char *kitapEtiket;
    int islemTuru;
    char *tarih;
    struct Odunc *next;
}Odunc;


//Ornek kitapların tutulduğu struct
typedef struct Ornek{
    char *etiket;
    char *durum;
    struct Ornek *next;
}Ornek;


//Kitapların tutulduğu struct
typedef struct Kitap{
    char *name;
    char *ISBN;
    int adet;
    Ornek *ornekler;
    struct Kitap *next;
}Kitap;


//Kitap yazar eşleşmesinin tutulduğu struct
typedef struct Kitap_Yazar{
    char *ISBN;
    int yazarID;
}Kitap_Yazar;


//yazarların tutulduğu struct
typedef struct Yazar{
    char *name;
    char *surname;
    int yazarID;
    struct Yazar *next;
}Yazar;


// ------Öğrenci Işlemleri Fonksiyonları-------
void ogrenciEkleme(Ogrenci **ogrenci) ;
void ogrenciSilme(Ogrenci **ogrenci) ;
void ogrenciGuncelleme(Ogrenci *ogrenci);
void ogrenciBilgiGoruntuleme(Ogrenci *ogrenci, Odunc *odunc);
void kitapTeslimEtmemisleriListele(Kitap* kitap, Ogrenci* ogrenci);
void cezaliOgrencileriListele(Ogrenci* ogrenci);
void listeleCiftYonlu(void* head, void (*yazdir)(void*));
void ogrenciYazdir(void* data);
void kitapOduncIslemi(Kitap* kitap, Ogrenci* ogrenci, Odunc** odunc);

// -------Öğrenci Işlemleri Yardımcı Fonksiyonları------------
Ogrenci* ogrencilisteYukle();
Odunc* odunclisteYukle();
void ogrencidosyayaKaydet(FILE *fp,void *data);
void oduncdosyayaKaydet(FILE *fp, void *data);
int tarihToGun(char* tarih);

// -------Kitap Işlemleri Fonksiyonları---------
void kitapEkle(Kitap **kitap);
void kitapSilme(Kitap **kitap);
void kitapGuncelleme(Kitap *kitap, Odunc *odunc, Kitap_Yazar *kitap_yazar, int kitapyazar_sayi);
void kitapbilgisiGoruntuleme(Kitap *kitap);
void rafkitapListele(Kitap *kitap);
void zamanindaTeslimEdilmeyenKitaplar(Odunc* odunc) ;
void kitapYazarEslestir(Kitap *kitap,Yazar *yazar,Kitap_Yazar **kitap_yazar,int *kitapyazar_sayi);
void kitapYazarGuncelle(Kitap_Yazar* kitap_yazar, int kitapyazar_sayi);

//--------Kitap Işlemleri Yardımcı Fonksiyonları---------
Kitap *kitaplisteYukle();
Kitap_Yazar* kitapYazarListeYukle(int* kitapyazar_sayi);
void kitaplaridosyayaKaydet(FILE *fp, void *data);
void ornekleridosyayaKaydet(Kitap *kitap);
void kitapyazarDosyayaKaydet(Kitap_Yazar *kitap_yazar, int  kitapyazar_sayi);
void yazarEslesmeleriniGuncelle(Kitap_Yazar* kitap_yazar, int kitapyazar_sayi, int silinenYazarID);

//---------Yazar Işlemleri Fonksiyonları------------
void yazarEkleme(Yazar **yazar);
void yazarSilme(Yazar **yazar, Kitap_Yazar *kitap_yazar, int *kitapyazar_sayi);
void yazarGuncelleme(Yazar *yazar);
void yazarBilgiGoruntuleme(Yazar *yazar,Kitap *kitap,Kitap_Yazar *kitap_yazar,int kitapyazar_sayi);

//-------Yazar Işlemleri Yardımcı Fonksiyonları------------
Yazar* yazarlisteYukle();
void yazardosyayaKaydet(FILE *fp, void *data);


//---------Fonksiyon Pointer ile Free Etme Fonksiyonları-----------
void ciftYonluListeTemizle(void** head, void (*freeData)(void**)); 
void tekYonluListeTemizle(void** head, void (*freeData)(void**));
void freeOgrenci(void** data);
void freeOdunc(void** data);
void freeKitap(void** data);
void freeYazar(void** data);
void freeKitapYazar(void** data, int* kitapyazar_sayi);

//---------Fonksiyon Pointer Ile Dosyaya Yazma Fonksiyonu--------
void dosyayaKaydetGenel(char *dosyaAdi, void *liste, void (*kaydetFonksiyon)(FILE*, void*));



int main(){
    int kitapyazar_sayi = 0;
    Yazar *yazar = yazarlisteYukle();
    Ogrenci *ogrenci = ogrencilisteYukle();
    Kitap *kitap = kitaplisteYukle();
    Kitap_Yazar *kitap_yazar = kitapYazarListeYukle(&kitapyazar_sayi);
    Odunc *odunc = odunclisteYukle();
    int secim = -1;
    while (secim != 0) {
        printf("\n\nOGRENCI ISLEMLERI:\n");
        printf("0- Cikis\n");
        printf("1- Ogrenci Ekle\n");
        printf("2- Ogrenci Sil\n");
        printf("3- Ogrenci Guncelle\n");
        printf("4- Ogrenci Bilgi Goruntuleme\n");
        printf("5- Kitap Teslim Etmeyen Ogrencileri Listele\n");
        printf("6- Cezali Ogrencileri Listele\n");
        printf("7- Tum Ogrencileri Listele\n");
        printf("8- Kitap Odunc Al/Teslim Et\n");

        printf("\nKITAP ISLEMLERI:\n");
        printf("9- Kitap Ekle\n");
        printf("10- Kitap Sil\n");
        printf("11- Kitap Guncelle\n");
        printf("12- Kitap Bilgi Goruntuleme\n");
        printf("13- Raftaki Kitaplari Listele\n");
        printf("14- Zamaninda Teslim Edilmeyen Kitaplari Listele\n");
        printf("15- Kitap-Yazar Eslestir\n");
        printf("16- Kitabin Yazarini Guncelle\n");

        printf("\nYAZAR ISLEMLERI:\n");
        printf("17- Yazar Ekle\n");
        printf("18- Yazar Sil\n");
        printf("19- Yazar Guncelle\n");
        printf("20- Yazar Bilgi Goruntuleme\n");

        printf("\nSeciminizi giriniz: ");
        scanf("%d", &secim);

        if (secim == 1) 
        ogrenciEkleme(&ogrenci);
        else if (secim == 2) 
        ogrenciSilme(&ogrenci);
        else if (secim == 3) 
        ogrenciGuncelleme(ogrenci);
        else if (secim == 4) 
        ogrenciBilgiGoruntuleme(ogrenci, odunc);
        else if (secim == 5) 
        kitapTeslimEtmemisleriListele(kitap, ogrenci);
        else if (secim == 6) 
        cezaliOgrencileriListele(ogrenci);
        else if (secim == 7) 
        listeleCiftYonlu((void*)ogrenci, ogrenciYazdir);
        else if (secim == 8) 
        kitapOduncIslemi(kitap, ogrenci, &odunc);
        else if (secim == 9) 
        kitapEkle(&kitap);
        else if (secim == 10) 
        kitapSilme(&kitap);
        else if (secim == 11) 
        kitapGuncelleme(kitap,odunc,kitap_yazar,kitapyazar_sayi);
        else if (secim == 12) 
        kitapbilgisiGoruntuleme(kitap);
        else if (secim == 13) 
        rafkitapListele(kitap);
        else if (secim == 14) 
        zamanindaTeslimEdilmeyenKitaplar(odunc);
        else if (secim == 15) 
        kitapYazarEslestir(kitap, yazar, &kitap_yazar, &kitapyazar_sayi);
        else if (secim == 16) 
        kitapYazarGuncelle(kitap_yazar, kitapyazar_sayi);
        else if (secim == 17) 
        yazarEkleme(&yazar);
        else if (secim == 18) 
        yazarSilme(&yazar, kitap_yazar, &kitapyazar_sayi);
        else if (secim == 19) 
        yazarGuncelleme(yazar);
        else if (secim == 20) 
        yazarBilgiGoruntuleme(yazar,kitap,kitap_yazar,kitapyazar_sayi);
        else if (secim == 0) 
        printf("Programdan cikiliyor...\n");
        else printf("Gecersiz secim. Tekrar deneyin.\n");
    }

    //dinamik olarak yer açılmış değişkenler fonksiyon pointer ile free edilir
    ciftYonluListeTemizle((void**)&ogrenci, freeOgrenci);
    tekYonluListeTemizle((void**)&yazar, freeYazar);
    tekYonluListeTemizle((void**)&kitap, freeKitap);
    tekYonluListeTemizle((void**)&odunc, freeOdunc);
    if (kitap_yazar != NULL) {
        freeKitapYazar((void**)&kitap_yazar, &kitapyazar_sayi);
    }
    return 0;
}



////////  ÖĞRENCİ İŞLEMLERİ  /////////

void ogrenciEkleme(Ogrenci **ogrenci) {
    int tekrar = 0;
    char numara[100];        //01234567 gibi başı 0 olan 8 haneli sayıları alması için char tanımlandı
    Ogrenci *current = *ogrenci;
    Ogrenci* node = (Ogrenci*)malloc(sizeof(Ogrenci));
    node->name = (char*)malloc(MAX_SIZE*sizeof(char));
    node->surname = (char*)malloc(MAX_SIZE*sizeof(char));
    node->numara = (char*)malloc(MAX_SIZE*sizeof(char));

    printf("Ad: ");
    scanf(" %[^\n]",node->name);

    printf("Soyad: ");
    scanf(" %[^\n]", node->surname);

    node->puan = 100;

    while (tekrar == 0) {       //Kullanıcıdan doğru şekilde sayı alana kadar devam eder.
        printf("8 haneli Numara: ");
        scanf("%s", numara);

        tekrar = 1; // geçerli varsay

        if(strlen(numara)!=8){
            printf("Numara 8 haneli değil. Tekrar giriniz.\n");
            tekrar = 0;
        }

        while (current != NULL && tekrar!=0) {
            if (strcmp(current->numara, numara) == 0) {
                printf("Bu numarayla kayıtlı bir öğrenci zaten var. Tekrar deneyin.\n");
                tekrar = 0; // geçersiz hale getir
            }
            current = current->next;
        }
    }
    current = *ogrenci;

    strcpy(node->numara, numara);
    node->prev = node->next = NULL;

    if (*ogrenci == NULL) {
        *ogrenci = node;
    } else {
        while (current->next != NULL){
            current = current->next;
        }
        current->next = node;
        node->prev = current;
    }

    // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("Ogrenciler.csv", *ogrenci, ogrencidosyayaKaydet); 
    printf(" Öğrenci eklendi.\n");
}



void ogrenciSilme(Ogrenci **ogrenci) {
    char numara[100];
    Ogrenci *current = *ogrenci;
    Ogrenci *before = NULL;

    printf("Silmek istediğiniz öğrencinin numarasını giriniz: ");
    scanf(" %[^\n]", numara);

    while (current != NULL && strcmp(current->numara, numara) != 0) {
        before = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Öğrenci bulunamadı.\n");
        return;
    }

    if (current == *ogrenci) { // head ise
        *ogrenci = current->next;
        if (*ogrenci != NULL){ 
            (*ogrenci)->prev = NULL;
        }
    } else {
        before->next = current->next;
        if (current->next != NULL){
            current->next->prev = before;
        }
    }
    free(current->name);
    free(current->surname);
    free(current->numara);
    free(current);

    // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("Ogrenciler.csv", *ogrenci, ogrencidosyayaKaydet);
    printf("Öğrenci silindi.\n");
}



void ogrenciGuncelleme(Ogrenci *ogrenci) {
    char numara[100];
    Ogrenci *head = ogrenci;

    printf("Güncellenecek öğrencinin numarasını giriniz: ");
    scanf(" %[^\n]", numara);

    while (ogrenci != NULL && strcmp(ogrenci->numara, numara) != 0) {
        ogrenci = ogrenci->next;
    }

    if (ogrenci == NULL) {
        printf("Öğrenci bulunamadı.\n");
    } else {
        printf("Yeni adını giriniz: ");
        scanf(" %[^\n]", ogrenci->name);
        printf("Yeni soyadını giriniz: ");
        scanf(" %[^\n]", ogrenci->surname);

        printf("Yeni puanını giriniz: ");
        scanf("%d", &ogrenci->puan);


        // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
        dosyayaKaydetGenel("Ogrenciler.csv", head, ogrencidosyayaKaydet);

        printf("Öğrenci bilgisi güncellendi.\n");
    }
}




void ogrenciBilgiGoruntuleme(Ogrenci *ogrenci, Odunc *odunc) {      
    char secim, numara[100], ad[50], soyad[50];
    int temp=0;

    printf("Numara ile aramak için (N), Ad-Soyad ile aramak için (A) girin: ");  //hangi bilgiye göre arama yapılacak
    scanf(" %c", &secim);

    if (secim == 'N' || secim == 'n') {    
        printf("Öğrenci numarası: ");
        scanf(" %[^\n]", numara);

        //öğrenci numarasına göre öğrenciyi arama
        while (ogrenci != NULL && strcmp(ogrenci->numara, numara) != 0) {     
            ogrenci = ogrenci->next;
        }

    } else if(secim == 'A' || secim == 'a'){
        printf("Ad: "); 
        scanf(" %[^\n]", ad);
        printf("Soyad: "); 
        scanf(" %[^\n]", soyad);

        //öğrenci ad ve soyadına göre öğrenciyi arama
        while (ogrenci != NULL && (strcmp(ogrenci->name, ad) != 0 || strcmp(ogrenci->surname, soyad) != 0)) {    
            ogrenci = ogrenci->next;
        }
    }else printf("Gecersiz secim.\n");

    if (ogrenci == NULL) {
        printf("Öğrenci bulunamadı.\n");
    } else {
        //öğrencinin bilgilerini yazdırma
        printf("Öğrencinin bilgileri:");
        printf("Ad: %s, Soyad: %s, Numara: %s, Puan: %d\n",ogrenci->name, ogrenci->surname, ogrenci->numara, ogrenci->puan);  
    }


    //Öğrenci kitap hareketlerini bulma
    printf("Kitap hareketleri bilgisi:\n");
    while (odunc != NULL && ogrenci != NULL) {
        if (strncmp(odunc->ogrenciNo, ogrenci->numara, 8) == 0) {
            printf("%s, %s, %s\n",odunc->kitapEtiket, odunc->islemTuru == 0 ? "0" : "1", odunc->tarih);
            temp = 1;
        }
        odunc = odunc->next;
    }

    if (temp == 0) {
        printf("Kitap hareketi bulunamadı.\n");
    }
}



void kitapTeslimEtmemisleriListele(Kitap* kitap, Ogrenci* ogrenci) {
    Ornek* ornek;
    Ogrenci* ogr;
    int temp = 0;

    while (kitap != NULL) {
        ornek = kitap->ornekler;
        while (ornek != NULL) {
            if (strcmp(ornek->durum, "Rafta") != 0) {
                ogr = ogrenci;      // Öğrenci numarası eşleşmesini ara
                while (ogr != NULL) {
                    if (strcmp(ogr->numara, ornek->durum) == 0) {        //Öğrenciyi bulma

                        //Öğrencinin tüm bilgilerini ve kitap bilgisini yazdırma
                        printf("Teslim Etmemiş Öğrenci -> Ad: %s, Soyad: %s, Numara: %s, Puan: %d | Kitap Etiket: %s\n",      
                            ogr->name, ogr->surname, ogr->numara, ogr->puan, ornek->etiket);
                            temp = 1;
                    }
                    ogr = ogr->next;
                }
            }
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }
    if(temp == 0){
        printf("Kitap teslim etmemis ogrenci mevcut degildir.\n");
    }
}



//Puanı (-) olan öğrencilerin bilgilerini listeler
void cezaliOgrencileriListele(Ogrenci* ogrenci) { 
    Ogrenci* current= ogrenci;
    int bulundu = 0;

    while (current!= NULL) {
        if (current->puan < 0) {
            printf("Cezalı Öğrenci → Ad: %s, Soyad: %s, Numara: %s, Puan: %d\n",
                current->name, current->surname, current->numara, current->puan);
            bulundu = 1;
        }
        current = current->next;
    }

    if (!bulundu) {
        printf("Cezalı öğrenci bulunmamaktadır.\n");
    }
}


//fonksiyon pointer ile öğrenci bilgilerini listeler
void listeleCiftYonlu(void* head, void (*yazdir)(void*)) {  
    Ogrenci* current = (Ogrenci*)head;
    int bulundu = 0;
    while (current != NULL) {
        yazdir((void*)current);         // fonksiyon pointer ile çağır
        current = current->next;
        bulundu = 1;
    }
    if(bulundu==0){
        printf("Ogrenci yoktur.");
    }
}


//fonksiyon pointer ile bilgileri yazdırır
void ogrenciYazdir(void* data) {
    Ogrenci* ogr = (Ogrenci*)data;
    printf("Ad: %s, Soyad: %s, Numara: %s, Puan: %d\n", ogr->name, ogr->surname, ogr->numara, ogr->puan);
}




void kitapOduncIslemi(Kitap* kitap, Ogrenci* ogrenci, Odunc** odunc) {
    char tmpOgr[50], tmpISBN[50], tmpTarih[50], alisTarihi[50] = "";
    int islem, gec = 1, fark;

    Ogrenci *ogr=ogrenci;
    Kitap *ktp = kitap;
    Ornek *ornek, *raftaOrnek, *ogrenciOrnegi;
    Odunc *iteration,*node;

        gec = 1;

        printf("Öğrenci No: ");
        scanf("%s", tmpOgr);

        ogr = ogrenci;
        while (ogr != NULL && strcmp(ogr->numara, tmpOgr) != 0) { //sistemde öğrenci numarasına göre aranarak bulunur
            ogr = ogr->next;
        }

        if (ogr == NULL) {
            printf("Öğrenci sistemde kayıtlı değil.\n");
            gec = 0;
        }

        if (gec) {
            printf("Kitap ISBN No: ");
            scanf("%s", tmpISBN);

            ktp = kitap;
            while (ktp != NULL && strcmp(ktp->ISBN, tmpISBN) != 0) {
                ktp = ktp->next;
            }

            if (ktp == NULL) {
                printf("ISBN geçersiz. Kitap bulunamadı.\n");
                gec = 0;
            }

            if (gec) {
                printf("İşlem Türü (0: Ödünç Al, 1: Teslim Et): ");
                scanf("%d", &islem);

                if(islem == 0){
                    if (ogr->puan < 0) {
                        printf("Bu öğrencinin puanı negatif.Kitap verilemez.\n");
                        gec = 0;
                    }
                }
                if(gec){

                ornek = ktp->ornekler;
                raftaOrnek = NULL;
                ogrenciOrnegi = NULL;

                //kitap öğrencide veya rafta olmasına göre ayrıştırılır
                while (ornek != NULL) { 
                    if (strcmp(ornek->durum, "Rafta") == 0 && raftaOrnek == NULL) {
                        raftaOrnek = ornek;
                    } else if (strcmp(ornek->durum, tmpOgr) == 0 && ogrenciOrnegi == NULL) {
                        ogrenciOrnegi = ornek;
                    }
                    ornek = ornek->next;
                }

                if (islem == 0 && raftaOrnek == NULL) {
                    printf("ISLEM BASARISIZ.\n");
                    gec = 0;
                } else if (islem == 1 && ogrenciOrnegi == NULL) {
                    printf("Bu öğrenciye ait ödünç alınmış kitap yok. Teslim işlemi yapılamaz.\n");
                    gec = 0;
                } else if (islem != 0 && islem != 1) {
                    printf("Geçersiz işlem türü.\n");
                    gec = 0;
                }

                if (gec) {
                    printf("Tarih (gg.aa.yyyy): ");
                    scanf("%s", tmpTarih);

                    node = (Odunc*)malloc(sizeof(Odunc));
                    node->ogrenciNo = (char*)malloc(strlen(tmpOgr) + 1);
                    node->kitapEtiket = (char*)malloc(50*sizeof(char));
                    node->tarih =  (char*)malloc(strlen(tmpTarih) + 1);
                    strcpy(node->ogrenciNo, tmpOgr);
                    strcpy(node->tarih, tmpTarih);
                    node->islemTuru = islem;
                    node->next = NULL;

                    //kitap ödünç alınmışsa kitap etiket no karşısına öğrenci no bilgisi yazılır
                    if (islem==0) {
                        strcpy(node->kitapEtiket, raftaOrnek->etiket);
                        strcpy(raftaOrnek->durum, tmpOgr);
                    } else {
                        strcpy(node->kitapEtiket, ogrenciOrnegi->etiket);
                        strcpy(ogrenciOrnegi->durum, "Rafta");
                    }

                    iteration = *odunc;
                    while (iteration != NULL && islem==1){
                        if(iteration->islemTuru==0 && strcmp(iteration->ogrenciNo, tmpOgr)==0 && strcmp(iteration->kitapEtiket, ogrenciOrnegi->etiket)==0) {
                            strcpy(alisTarihi, iteration->tarih);     //ilgili öğrencinin kitabı aldığı tarih bulunur
                        }
                        iteration = iteration->next;
                    }

                    if(strlen(alisTarihi) > 0) {
                        fark = tarihToGun(tmpTarih) - tarihToGun(alisTarihi);
                        if (fark > 15) {
                            ogr->puan -= 10;
                            printf("Kitap 15 günden geç teslim edildi. Öğrencinin puanı -10 azaltıldı.\n");
                        }
                    }

                    if (*odunc == NULL) {
                        *odunc = node;
                    } else {
                        iteration = *odunc;
                        while (iteration->next != NULL) {
                            iteration = iteration->next;
                        }
                        iteration->next = node;
                    }

                     // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
                     dosyayaKaydetGenel("Ogrenciler.csv", ogrenci, ogrencidosyayaKaydet);

                    //fonksiyon pointer ile dosya işlemlerine ulaşarak dosyaya bilgileri yazar.
                    dosyayaKaydetGenel("OduncIslemleri.csv", *odunc, oduncdosyayaKaydet);      
                    ornekleridosyayaKaydet(kitap);  

                    printf("İşlem başarıyla kaydedildi.\n");
                    
                }
            }
        }
    }
}


////////// YARDIMCI ÖĞRENCİ FONKSİYONLARI ///////////////


/*program tekrar çalıştırılıp yeni işlemler yapılmak istendiğinde bilgilerin yazılı olduğu Ogrenciler.csv 
dosyasından biilgileri çeker ve üzerinde işlem yapacağımız liste yükler*/
Ogrenci* ogrencilisteYukle(){     
    int puan; 
    Ogrenci *ogrenci=NULL, *node, *temp;
    char satir[150];
    //kullanıcıdan bilgileri alıp struct içerisindeki dizilere dinamik olarak yer açmayı sağlayacak diziler
    char name[100], surname[100], numara[50]; 

    FILE *fp = fopen ("Ogrenciler.csv","r");
    if(fp == NULL){
        return NULL;
    }

    //dosyada bulunan bilgileri satır satır alarak listeye yükler
    while(fgets(satir,sizeof(satir),fp)){
        satir[strcspn(satir, "\n")] = 0;

        sscanf(satir, "%[^,],%[^,],%[^,],%d", numara, name, surname, &puan);

        //dinamik olarak yer açma
        node = (Ogrenci*)malloc(sizeof(Ogrenci));
        node->name = (char*)malloc(strlen(name) + 1);
        node->surname = (char*)malloc(strlen(surname) + 1);
        node->numara = (char*)malloc(strlen(numara) + 1);

        //statik dizilere aldığımız bilgileri dinamik olarak açtığımız yere kopyalama
        strcpy(node->name, name);
        strcpy(node->surname, surname);
        strcpy(node->numara, numara);
        node->puan = puan;
        node->next = NULL;
        node->prev = NULL;

        if(ogrenci == NULL){     //ilk olarak head kısmına bilgileri yazacağız
            ogrenci = node;
        }else{
            temp=ogrenci;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = node;
            node->prev = temp;
        }
    }
    fclose(fp);
    return ogrenci;
}



/*program tekrar çalıştırılıp yeni işlemler yapılmak istendiğinde bilgilerin yazılı olduğu OduncIslemleri.csv 
dosyasından biilgileri çeker ve üzerinde işlem yapacağımız liste yükler*/
Odunc* odunclisteYukle(){
    Odunc *odunc = NULL, *node, *temp;
    char satir[150], etiket[50], ogrenciNo[50], islemStr[50], tarih[50];

    FILE *fp = fopen("OduncIslemleri.csv", "r");
    if (fp == NULL) {
        return NULL;
    }

    //dosyada bulunan bilgileri satır satır alarak listeye yükler
    while (fgets(satir, sizeof(satir), fp)) {
        satir[strcspn(satir, "\n")] = 0;
        sscanf(satir, "%[^,],%[^,],%[^,],%[^\n]", etiket, ogrenciNo, islemStr, tarih);

        //Struct yapısında tanımlı değişkenler için dinamik olarak yer açar
        node = (Odunc*)malloc(sizeof(Odunc));
        node->kitapEtiket = (char*)malloc(strlen(etiket) + 1);
        node->ogrenciNo = (char*)malloc(strlen(ogrenciNo) + 1);
        node->tarih = (char*)malloc(strlen(tarih) + 1);
        node->islemTuru = atoi(islemStr);
        node->next = NULL;

        //dosyadan çekilen bilgiler struct yapısına kopyalanır
        strcpy(node->kitapEtiket, etiket);
        strcpy(node->ogrenciNo, ogrenciNo);
        strcpy(node->tarih, tarih);

        if (odunc == NULL) {    //head yapısı oluşturulur
            odunc = node;
        } else {
            temp = odunc;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = node;
        }
    }
    fclose(fp);
    return odunc;
}




//fonksiyon pointer ile bilgileri alarak ogrenci bilgilerini Ogrenciler.csv dosyasına yazar
void ogrencidosyayaKaydet(FILE *fp, void *data) {
    Ogrenci *ogr = (Ogrenci*)data;
    while (ogr != NULL) {
        fprintf(fp, "%s,%s,%s,%d\n", ogr->numara, ogr->name, ogr->surname, ogr->puan);
        ogr = ogr->next;
    }
}





// Odunc alınan veya teslim edilen örnek kitapları fonksiyon pointer ile OduncIslemleri.csv dosyasına yazar
void oduncdosyayaKaydet(FILE *fp, void *data) {
    Odunc *odunc = (Odunc*)data;
    while (odunc != NULL) {
        fprintf(fp, "%s,%s,%d,%s\n", odunc->kitapEtiket, odunc->ogrenciNo, odunc->islemTuru, odunc->tarih);
        odunc = odunc->next;
    }
}





// Kitap teslim tarihlerini güne çevirir
int tarihToGun(char* tarih) {   
    int gun, ay, yil, i, hesap = 0;
    sscanf(tarih, "%d.%d.%d", &gun, &ay, &yil);

    // Hangi ayın kaç gün çektiğini belirtir.
    int ay_gun[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    // Artık yıl kontrolü
    if ((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0)) {
        ay_gun[2] = 29;
    }

    // Geçmiş yıllardaki tüm günler
    for (i = 1; i < yil; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {
            hesap += 366;
        } else {
            hesap += 365;
        }
    }

    // Geçmiş ayların günlerinin toplamı
    for (i = 1; i < ay; i++) {
        hesap += ay_gun[i];
    }

    // Gün ekle
    hesap += gun;
    return hesap;
}




//////////////  KITAP ISLEMLERI  //////////////



void kitapEkle(Kitap **kitap){
    int i,tekrar=0;
    char isbn[100];

    Kitap *node = (Kitap*)malloc(sizeof(Kitap));
    if(node == NULL){
        printf("Yer acilamadi.");
        exit(0);
    }
    node->name = (char*)malloc(MAX_SIZE*sizeof(char));
    node->ISBN = (char*)malloc(MAX_SIZE*sizeof(char));

    Kitap *current = *kitap;
    Ornek *ornek, *iteration;
    node->next = NULL;
    node->ornekler = NULL;

    printf("Kitap adını giriniz:");
    scanf(" %[^\n]",node->name);

     //13 haneli ISBN numarası doğru olana kadar kullanıcıdan ister
      while (tekrar == 0) {            
        printf("13 haneli kitap ISBN bilgisini giriniz:");
        scanf("%s", isbn);

        tekrar = 1; // geçerli varsay

        if(strlen(isbn)!=13){
            printf("ISBN numarası 13 haneli değil. Tekrar giriniz.\n");
            tekrar = 0;
        }

        current = *kitap;
        while (current != NULL && tekrar != 0) {
            if (strcmp(current->ISBN, isbn) == 0) {
                printf("Böyle bir ISBN numarası zaten var. Tekrar giriniz.\n");
                tekrar = 0; // geçersiz hale getir
            }
            current = current->next;
        }
    }

    strcpy(node->ISBN,isbn);
    printf("Kitap adetini giriniz:");
    scanf("%d",&node->adet);
   
    if(*kitap == NULL){
        *kitap = node;
    }else{
        current = *kitap;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = node;
    }
    printf("Kitap eklendi.");

    for(i=0;i<node->adet;i++){              //Kitapların altında ornek kitap linked listi oluşturma
        ornek = (Ornek*)malloc(sizeof(Ornek)); // Ornek turunde bir node oluşturarak ISBN_1,Rafta || 12324454 şeklinde linked list oluşturma
        ornek->etiket = (char*)malloc(MAX_SIZE * sizeof(char));
        ornek->durum = (char*)malloc(MAX_SIZE * sizeof(char));
        ornek->next = NULL;
        sprintf(ornek->etiket, "%s_%d", node->ISBN, i + 1);    //ornek kitap etiketi hazırlama (ISBN_N)

            strcpy(ornek->durum, "Rafta");      //Kitap otomatik olarak rafa eklenir

        if(node->ornekler == NULL){         //head == NULL ise head'ı oluşturma (node->ornekler)
            node->ornekler = ornek;
        }else{
            iteration = node->ornekler;
            while(iteration->next!=NULL){
                iteration = iteration->next;
            }
            iteration->next = ornek;            //Ornek kitaplar için tek yönlü linked listi oluşturma
        }
    }
    ornekleridosyayaKaydet(*kitap);  //güncellemeler dosyaya yazılır
    //fonksiyon pointer ile dosya işlemlerine ulaşarak dosyaya yazar.
    dosyayaKaydetGenel("Kitaplar.csv", *kitap, kitaplaridosyayaKaydet);
}



void kitapSilme(Kitap **kitap){
    char isbn[50];
    printf("Silinecek kitabın ISBN numarasını girin: ");
    scanf(" %[^\n]", isbn);

    Kitap *before=NULL, *current=*kitap;
    Ornek *ornek, *temp;

     while (current != NULL && strcmp(current->ISBN, isbn) != 0) {
        before = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Kitap bulunamadı. Silme işlemi iptal.\n");
        return;
    }

    ornek=current->ornekler;
    while (ornek != NULL) {    //Kitap örneklerini (linked list) silme
       temp = ornek;
        ornek = ornek->next;
        free(temp);
        free(temp->etiket);
        free(temp->durum);
    }

    if (before == NULL) {
        *kitap = current->next;  // Head silme
    } else {
        before->next = current->next;
    }
    free(current->name);
    free(current->ISBN);
    free(current);

    //fonksiyon pointer ile dosya işlemlerine ulaşarak dosyaya yazar.
    dosyayaKaydetGenel("Kitaplar.csv", *kitap, kitaplaridosyayaKaydet); 
    ornekleridosyayaKaydet(*kitap);
    printf("Kitap ve tüm örnekleri silindi.\n");
}



void kitapGuncelleme(Kitap *kitap, Odunc *odunc, Kitap_Yazar *kitap_yazar, int kitapyazar_sayi){
    char isbn[50], yeniisbn[50], yeniad[100], eskiEtiket[50];
    int yeniAdet, eskiAdet, i = 1, silinecek, tekrar = 0;
    Ornek *node, *iteration, *before;

    // Kullanıcıdan güncellenecek kitabın ISBN bilgisini al
    printf("Kitap ISBN bilgisini giriniz: ");
    scanf(" %[^\n]", isbn);

    // Girilen ISBN'e göre ilgili kitabı listede bul
    Kitap *temp = kitap;
    while (temp != NULL && strcmp(temp->ISBN, isbn) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Kitap bulunamadı.\n");
        return;
    }

    // Yeni ad bilgisi alınıp bellekte güncelleniyor
    printf("Yeni kitap adını girin: ");
    scanf(" %[^\n]", yeniad);
    free(temp->name);
    temp->name = (char*)malloc(strlen(yeniad) + 1);
    strcpy(temp->name, yeniad);

    // Yeni adet bilgisi alınıyor
    printf("Yeni kitap adetini girin: ");
    scanf("%d", &yeniAdet);
    if (yeniAdet < 0) {
        printf("Geçersiz adet girdiniz.\n");
        return;
    }

    // Yeni ISBN alınır, 13 hane kontrolü yapılır
    while (tekrar == 0) {
        printf("Yeni 13 haneli kitap ISBN bilgisini giriniz: ");
        scanf(" %[^\n]", yeniisbn);
        tekrar = 1;
        if (strlen(yeniisbn) != 13) {
            printf("Yeni ISBN numarası 13 haneli değil. Tekrar giriniz.\n");
            tekrar = 0;
        }
    }

    // Kitap-Yazar eşleşmelerinde eski ISBN varsa güncellenir
    for (i = 0; i < kitapyazar_sayi; i++) {
        if (strcmp(kitap_yazar[i].ISBN, isbn) == 0) {
            free(kitap_yazar[i].ISBN);
            kitap_yazar[i].ISBN = malloc(strlen(yeniisbn) + 1);
            strcpy(kitap_yazar[i].ISBN, yeniisbn);
        }
    }

    // Kitabın ISBN bilgisi güncelleniyor
    free(temp->ISBN);
    temp->ISBN = (char*)malloc(strlen(yeniisbn) + 1);
    strcpy(temp->ISBN, yeniisbn);

    // Tüm örnek kitap etiketleri yeni ISBN ile güncelleniyor
    Ornek *current = temp->ornekler;
    i = 1;
    while (current != NULL) {
        sprintf(current->etiket, "%s_%d", yeniisbn, i);
        current = current->next;
        i++;
    }

    // Odunc işlemlerinde eski etiketler varsa, yeni ISBN ile güncelleniyor
    Odunc *od = odunc;
    sprintf(eskiEtiket, "%s_", isbn);  // Eski ISBN+_ şeklinde prefix
    while (od != NULL) {
        if (strncmp(od->kitapEtiket, eskiEtiket, strlen(eskiEtiket)) == 0) {
            int num;
            sscanf(od->kitapEtiket + strlen(eskiEtiket), "%d", &num); // Numarayı al
            sprintf(od->kitapEtiket, "%s_%d", yeniisbn, num); // Yeni ISBN ile değiştir
        }
        od = od->next;
    }

    // Eski adet bilgisi alınır, yeni adetle karşılaştırılır
    eskiAdet = temp->adet;
    temp->adet = yeniAdet;

    // Adet artmışsa yeni örnek kitaplar oluşturulur
    if (yeniAdet > eskiAdet) {
        for (i = eskiAdet + 1; i <= yeniAdet; i++) {
            node = (Ornek*)malloc(sizeof(Ornek));
            node->etiket = (char*)malloc(MAX_SIZE * sizeof(char));
            node->durum = (char*)malloc(MAX_SIZE * sizeof(char));
            sprintf(node->etiket, "%s_%d", temp->ISBN, i);
            strcpy(node->durum, "Rafta");
            node->next = NULL;

            if (temp->ornekler == NULL) {
                temp->ornekler = node;
            } else {
                iteration = temp->ornekler;
                while (iteration->next != NULL) {
                    iteration = iteration->next;
                }
                iteration->next = node;
            }
        }
        printf("Yeni örnekler eklendi.\n");
    }
    // Adet azalmışsa fazla örnek kitaplar silinir
    else if (yeniAdet < eskiAdet) {
        silinecek = eskiAdet - yeniAdet;
        for (i = 0; i < silinecek; i++) {
            before = NULL;
            iteration = temp->ornekler;
            while (iteration != NULL && iteration->next != NULL) {
                before = iteration;
                iteration = iteration->next;
            }

            if (iteration != NULL) {
                if (before == NULL) {
                    free(iteration->etiket);
                    free(iteration->durum);
                    free(temp->ornekler);
                    temp->ornekler = NULL;
                } else {
                    before->next = NULL;
                    free(iteration->etiket);
                    free(iteration->durum);
                    free(iteration);
                }
            }
        }
        printf("%d adet örnek silindi.\n", silinecek);
    } else {
        printf("Sadece kitap adı ve ISBN güncellendi.\n");
    }

    //fonksiyon pointer ile dosya işlemlerine ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("Kitaplar.csv", kitap, kitaplaridosyayaKaydet);

    ornekleridosyayaKaydet(kitap);
    kitapyazarDosyayaKaydet(kitap_yazar, kitapyazar_sayi);

    //fonksiyon pointer ile dosya işlemlerine ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("OduncIslemleri.csv", odunc, oduncdosyayaKaydet);  

    printf("Güncellenen bilgiler dosyaya yazıldı.\n");
}




void kitapbilgisiGoruntuleme(Kitap *kitap){
    char ad[100];
    int bulundu=0;
    Ornek *ornek;

    printf("Görüntülemek istediğiniz kitabın adını giriniz: ");
    scanf(" %[^\n]", ad);

        while (kitap!=NULL) {   
        //Ad bilgisine göre kitap bulunursa tüm bilgileri gösterilir
        if (strcmp(kitap->name, ad) == 0) {    
            bulundu = 1;
            printf("\nAd: %s, ", kitap->name);
            printf("ISBN: %s, ", kitap->ISBN);
            printf("Adet: %d\n", kitap->adet);
            printf("Örnekler:\n");

            ornek = kitap->ornekler;
            while (ornek != NULL) {
                printf(" Etiket: %s, Durum: %s\n", ornek->etiket, ornek->durum);
                ornek = ornek->next;
            }
        }
        kitap = kitap->next;
    }
    if(bulundu==0){
        printf("Bu isimde kitap yok.");
    }
}



//raftaki tüm kitapları yazdırır
void rafkitapListele(Kitap *kitap){ 
    int bulundu = 0;
    Ornek *ornek;

    printf("\n Raftaki Kitap Örnekleri:\n");

    while (kitap != NULL) {
        ornek = kitap->ornekler;
        while (ornek != NULL) {
            if (strcmp(ornek->durum, "Rafta") == 0) {
                printf(" %s, %s\n",ornek->etiket, ornek->durum);
                bulundu = 1;
            }
            ornek = ornek->next;
        }
        kitap = kitap->next;
    }

    if (bulundu==0) {
        printf(" Rafta kitap bulunmamaktadır.\n");
    }
}



//Alınmış ve 15 gün geçtikten sonra hala iade edilmemiş kitapları yazdırır
void zamanindaTeslimEdilmeyenKitaplar(Odunc* odunc) {
    Odunc* temp = odunc, *current;
    int teslim = 0, fark, tmp = 0;
    char tarih[50];

    printf("Tarih giriniz (gg.aa.yyyy): "); //Zamanı geçip geçmemiş mi kontrolü yapmak için tarih istenir
    scanf("%s", tarih);

    printf("\nZamanında Teslim Edilmeyen Kitaplar:\n");
    while (temp != NULL) {
        if (temp->islemTuru == 0) {    // Ödünç alma kaydı
            teslim = 0;

            current = odunc;
            while (current != NULL) {
                if (current->islemTuru == 1){  //Kitap teslim edilmiş mi diye bakılır, edildiyse listeye yazılmaz
                    if(strcmp(current->kitapEtiket, temp->kitapEtiket)==0 && strcmp(current->ogrenciNo, temp->ogrenciNo)==0){
                        if(tarihToGun(current->tarih) > tarihToGun(temp->tarih)){
                            teslim = 1;
                        }
                    }
                } 
                current = current->next;
            }

            if (teslim==0) {
                //Eğer teslim edilmemiş ise tarihler güne çevirilerek kullanıcıdan alınan tarihten çıkarılarak fark hesaplanır
                fark = tarihToGun(tarih) - tarihToGun(temp->tarih); 
                if (fark > 15) {
                    printf("Teslim Edilmemiş Kitap:\n Etiket: %s | Öğrenci: %s | Alış Tarihi: %s | Gün Gecikme: %d\n",
                        temp->kitapEtiket, temp->ogrenciNo, temp->tarih, fark);
                        tmp = 1;
                }
            }else if(tmp == 0)
                printf("Teslim edilmeyen kitap yoktur.\n");
        }
        temp = temp->next;
    }
}




void kitapYazarEslestir(Kitap *kitap, Yazar *yazar, Kitap_Yazar **kitap_yazar, int *kitapyazar_sayi){
    char isbn[50];
    int yazarID;
    int kitapVar = 0, yazarVar = 0, i;
    Yazar* y;

    printf("Kitap ISBN girin: ");
    scanf(" %[^\n]", isbn);
    printf("Yazar ID girin: ");
    scanf("%d", &yazarID);


    while (kitap != NULL) {             //kitap sistemde var mı kontrolü
        if (strcmp(kitap->ISBN, isbn) == 0) {
            kitapVar = 1;
        }
        kitap = kitap->next;
    }

    y = yazar;        //// Yazar sistemde var mı kontrolü
    while (y != NULL) {
        if (y->yazarID == yazarID) {
            yazarVar = 1;
        }
        y = y->next;
    }
    
    if (!kitapVar || !yazarVar) {       // Eğer kitap veya yazar sistemde yoksa işlem iptal
        printf("Geçersiz işlem: Kitap veya yazar sistemde kayıtlı değil.\n");
        return;
    }

    //Aynı yazar-kitap eşleştirmesi var mı kontrolü
    for (i = 0; i < *kitapyazar_sayi; i++) {
        if (strcmp((*kitap_yazar)[i].ISBN, isbn) == 0 && (*kitap_yazar)[i].yazarID == yazarID) {
            printf("Bu eşleşme zaten mevcut.\n");
            return;
        }
    }
    
    *kitap_yazar = realloc(*kitap_yazar, (*kitapyazar_sayi + 1) * sizeof(Kitap_Yazar));  //yeni kitap-yazar eşleştirme

    if (*kitap_yazar == NULL) {
        printf(" Bellek ayırma hatası.\n");
        return;
    }

    //Kitap_Yazar structu içerisindeki ISBN için dinamik olarak yer açma
    (*kitap_yazar)[*kitapyazar_sayi].ISBN = malloc(strlen(isbn) + 1);   
    strcpy((*kitap_yazar)[*kitapyazar_sayi].ISBN, isbn);
    (*kitap_yazar)[*kitapyazar_sayi].yazarID = yazarID;
    (*kitapyazar_sayi)++;


    kitapyazarDosyayaKaydet(*kitap_yazar,*kitapyazar_sayi);       //KitapYazar.csv dosyasına yazar
    printf(" Kitap-yazar eşleşmesi başarıyla kaydedildi.\n");
}



// Kitap-Yazar eşleşmesinde yazar güncelleme fonksiyonu
void kitapYazarGuncelle(Kitap_Yazar* kitap_yazar, int kitapyazar_sayi){
    char isbn[50];
    int eskiID, yeniID, i, bulundu=0;

    printf("Güncellemek istediğiniz kitabın ISBN'ini girin: ");
    scanf(" %[^\n]", isbn);
    printf("Eski yazar ID'sini girin: ");
    scanf("%d", &eskiID);

    for (i = 0; i < kitapyazar_sayi; i++) {
        //kitap_yazar struct dizisinde güncellenmek yazarın kitabını arar
        if (strcmp(kitap_yazar[i].ISBN, isbn) == 0 && kitap_yazar[i].yazarID == eskiID){ 
            //kitap ve yazar bulunursa yeni yazar ID'si istenerek güncelleme yapılır
            printf("Yeni yazar ID'sini girin: ");
            scanf("%d", &yeniID);
            kitap_yazar[i].yazarID = yeniID;
            bulundu = 1;
        }
    }

    if (bulundu==1) {
        printf("Yazar güncellemesi yapıldı.\n");
        kitapyazarDosyayaKaydet(kitap_yazar, kitapyazar_sayi);    //güncellenen veriyi dosyaya yazar
    } else {
        printf("Eşleşme bulunamadı.\n");
    }
}


/////////////////  YARDIMCI KITAP FONKSIYONLARI  ////////////////////



/*program tekrar çalıştırılıp yeni işlemler yapılmak istendiğinde bilgilerin yazılı olduğu Kitaplar.csv 
ve Ornek_Kitaplar.csv dosyasından biilgileri çeker ve üzerinde işlem yapacağımız liste yükler*/
Kitap *kitaplisteYukle(){
    FILE* kitapDosya = fopen("Kitaplar.csv", "r");
    FILE* ornekDosya = fopen("Ornek_Kitaplar.csv", "r");

    if (kitapDosya==NULL || ornekDosya==NULL) {
        return NULL;
    }
    Kitap *kitapHead=NULL, *node, *current;
    Ornek *ornek,*temp;
    int i=0;
    char satir[150],name[50],ISBN[50],etiket[50],durum[50];

    while (fgets(satir, sizeof(satir), kitapDosya)){     //Kitapları linked liste yukleme
        satir[strcspn(satir, "\n")] = 0;
        node = (Kitap*)malloc(sizeof(Kitap));
        sscanf(satir,"%[^,],%[^,],%d", name, ISBN, &node->adet);
        node->next = NULL;
        node->ornekler = NULL;

        node->name = (char*)malloc(strlen(name) + 1);
        node->ISBN = (char*)malloc(strlen(ISBN) + 1);
        strcpy(node->name, name);
        strcpy(node->ISBN, ISBN);

         if(kitapHead == NULL){
            kitapHead = node;
        }else{
            current = kitapHead;
            while (current->next != NULL){
                 current = current->next;
            }
            current->next = node;
        }
    }

    while (fgets(satir, sizeof(satir), ornekDosya)){        //Ornek Kitapları linked liste yukleme
        sscanf(satir, "%[^,],%[^\n]", etiket, durum);
        satir[strcspn(satir, "\n")] = 0; // newline temizleme

        i=0;
        while (etiket[i] != '_' && etiket[i] != '\0') {     //ISBN ayırma
            ISBN[i] = etiket[i];
            i++;
        }
        ISBN[i] = '\0';

        current = kitapHead;
        while(current != NULL && strcmp(current->ISBN, ISBN) != 0){
            current=current->next;
        }

        if (current != NULL){
            ornek = (Ornek*)malloc(sizeof(Ornek));      //Ornek kitapların listeye yüklenmesi
            ornek->etiket = (char*)malloc(MAX_SIZE*sizeof(char));
            ornek->durum = (char*)malloc(MAX_SIZE*sizeof(char));
            strcpy(ornek->etiket, etiket);
            strcpy(ornek->durum, durum);
            ornek->next = NULL;

            if (current->ornekler == NULL){
                current->ornekler = ornek;
            }else{
                temp =current->ornekler;
                while (temp->next != NULL){
                    temp=temp->next;
                }
                 temp->next = ornek;
            }
        }
    }
    fclose(kitapDosya);
    fclose(ornekDosya);
    return kitapHead;
}




/*program tekrar çalıştırılıp yeni işlemler yapılmak istendiğinde bilgilerin yazılı olduğu KitapYazar.csv 
dosyasından biilgileri çeker ve üzerinde işlem yapacağımız liste yükler*/
Kitap_Yazar* kitapYazarListeYukle(int* kitapyazar_sayi){
    FILE* fp = fopen("KitapYazar.csv", "r");
    if (fp == NULL) {
        *kitapyazar_sayi = 0;
        return NULL;
    }

    Kitap_Yazar* kitap_yazar = NULL;
    char satir[100], tempISBN[50];
    int yazarID;

    *kitapyazar_sayi = 0;       //kaç adet yazar ve kitap eşleştirdiğimizi tutar

    while (fgets(satir, sizeof(satir), fp)) {      //satır satır okuyarak ilgili yerlere bilgileri yerleştirir
        satir[strcspn(satir, "\n")] = 0;
        sscanf(satir, "%[^,],%d", tempISBN, &yazarID);

        kitap_yazar = (Kitap_Yazar*)realloc(kitap_yazar, (*kitapyazar_sayi + 1) * sizeof(Kitap_Yazar));
        if (kitap_yazar == NULL) {
            printf("Bellek ayırma hatası.\n");
            free(kitap_yazar);
            return NULL;
        }

        kitap_yazar[*kitapyazar_sayi].ISBN = malloc(strlen(tempISBN) + 1);
        strcpy(kitap_yazar[*kitapyazar_sayi].ISBN, tempISBN);
        kitap_yazar[*kitapyazar_sayi].yazarID = yazarID;

        (*kitapyazar_sayi)++;
    }

    fclose(fp);
    return kitap_yazar;
}


//Kitapları Kitaplar.csv dosyasına yazar
void kitaplaridosyayaKaydet(FILE *fp, void *data){
    Kitap *kitap = (Kitap*)data;
    while (kitap != NULL) {
        fprintf(fp, "%s,%s,%d\n", kitap->name, kitap->ISBN, kitap->adet);
        kitap = kitap->next;
    }
}




//Ornek kitapları Ornek_Kitaplar.csv dosyasına yazar
void ornekleridosyayaKaydet(Kitap *kitap){
    Ornek *temp;
    FILE *fp = fopen("Ornek_Kitaplar.csv","w");
    if(fp == NULL){
        printf("dosya açılamadı.");
        exit(0);
    }

    while(kitap != NULL){
        temp = kitap->ornekler;
        while(temp != NULL){
            fprintf(fp,"%s,%s\n",temp->etiket, temp->durum);
            temp = temp->next;
        }
        kitap = kitap->next;
    }
    fclose(fp);
}



//kitap-yazar eşleştirmesini dosyaya yazar
void kitapyazarDosyayaKaydet(Kitap_Yazar *kitap_yazar, int  kitapyazar_sayi){ 
    int i;
    FILE* fp = fopen("KitapYazar.csv", "w");

    if (fp == NULL) {
        printf("KitapYazar.csv dosyasına yazılamadı.\n");
        return;
    }
    for(i=0;i< kitapyazar_sayi;i++){
    fprintf(fp, "%s,%d\n", kitap_yazar[i].ISBN, kitap_yazar[i].yazarID);
    }
    fclose(fp);
}




//kitap-yazar eşleştirmesinde yazarsilme fonksiyonunda silinen yazarı -1 yapar
void yazarEslesmeleriniGuncelle(Kitap_Yazar* kitap_yazar, int kitapyazar_sayi, int silinenYazarID){
    int i;
    for (i = 0; i < kitapyazar_sayi; i++) {
        if (kitap_yazar[i].yazarID == silinenYazarID) {     //ilgili yazarı bularak -1 e çevirir
            kitap_yazar[i].yazarID = -1;
        }
    }

    //KitapYazar.csv dosyasını güncelleyerek silinen yazarı -1 yapar
    kitapyazarDosyayaKaydet(kitap_yazar, kitapyazar_sayi);   
    printf("Kitap-yazar eşleşmeleri güncellendi. Silinen yazarlar -1 olarak işaretlendi.\n");
}



////////////////// YAZAR İŞLEMLERİ /////////////////////


void yazarEkleme(Yazar **yazar){
    int maxID=1;
    Yazar *n = (Yazar*)malloc(sizeof(Yazar));
    if(n == NULL){
        printf("Yer açılamadı.");
        exit(0);
    }
    n->name = (char*)malloc(MAX_SIZE*sizeof(char)); //dinamik olarak yer açma
    n->surname = (char*)malloc(MAX_SIZE*sizeof(char));

    n->next = NULL;
    Yazar *current = *yazar;

    printf("Yazar ismini giriniz:");
    scanf(" %[^\n]", n->name);
    printf("Yazar soyismini giriniz:");
    scanf(" %[^\n]", n->surname);

    if(current==NULL){
        n->yazarID = maxID;
        *yazar=n;
    }else{
        while(current->next!=NULL){
            current=current->next;
        }
        maxID=current->yazarID;   //1 2 3 4 ... N şeklinde artarak yazarlara ID verir
        n->yazarID = maxID+1;
        current->next = n;
    }
    // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("yazarlar.csv", *yazar, yazardosyayaKaydet);
    printf(" Yazar eklendi.\n");
}



void yazarSilme(Yazar **yazar, Kitap_Yazar *kitap_yazar, int *kitapyazar_sayi){
    Yazar *before = NULL;
    Yazar *current = *yazar;
    int ID;

    //yazarın ID bilgisine göre arar ve siler
    printf("Silmek istediğniz yazar ID bilgisini giriniz:");  
    scanf(" %d",&ID);

    while(current!=NULL && current->yazarID!=ID){
        before=current;
        current=current->next;
    }

    if(current==NULL){
        printf("Yazar bulunamadı.");
    }else{
        if(current == *yazar){   // eğer ID head ID sine eşitse head değişir.
            *yazar = current->next;
        }else{
            before->next = current->next;
            printf("Yazar silindi.\n");
        }
    }
    // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
    dosyayaKaydetGenel("yazarlar.csv", *yazar, yazardosyayaKaydet);      
    //kitap-yazar eşleştirmesinde silinen yazarı -1 yapma fonksiyonu
    if(current != NULL){
        yazarEslesmeleriniGuncelle(kitap_yazar, *kitapyazar_sayi, ID);  
    }
    free(current->name);
    free(current->surname);
    free(current);
}



void yazarGuncelleme(Yazar *yazar){
    int ID;
    Yazar *temp = yazar;

    //yazarın ID bilgisine göre yazarı arar
    printf("Güncelleyeceğiniz yazarın ID'sini giriniz:");
    scanf("%d",&ID);

    while(temp!=NULL && temp->yazarID!=ID){
        temp = temp->next;
    }

    if(temp==NULL){
        printf("Yazar bulunamadı.");
    }else{
        //yazarın ad ve soyad bilgileri değişir
        printf("Yazar ismini giriniz:");
        scanf(" %[^\n]", temp->name);
        printf("Yazar soyismini giriniz:");
        scanf(" %[^\n]", temp->surname);
        // Fonksiyon pointer ile ogrencidosyayaKaydet fonksiyonuna ulaşarak dosyaya bilgileri yazar.
        dosyayaKaydetGenel("yazarlar.csv", yazar, yazardosyayaKaydet);
        printf("Yazar bilgisi güncellendi.");
    }
}



void yazarBilgiGoruntuleme(Yazar *yazar, Kitap *kitap, Kitap_Yazar *kitap_yazar, int kitapyazar_sayi){             
    char listName[100];
    int bulundu = 0, i, tmp = 0;
    Kitap *ktp;
    Ornek* ornek;

    printf("Listelemek istediğiniz yazarın adını giriniz:");
    scanf(" %[^\n]",listName);

    printf("------Yazar------\n");
    while(yazar!=NULL ){
        if(strcmp(yazar->name, listName) == 0){  
            printf("Ad:%s  Soyad:%s  ID:%d\n",yazar->name, yazar->surname, yazar->yazarID); //yazarın bilgileri yazdırılır
            bulundu=1;

            printf("Kitaplar:\n");  
            for(i = 0; i < kitapyazar_sayi; i++){
                if(kitap_yazar[i].yazarID == yazar->yazarID){  //yazarın kitabı bulunur
                    ktp = kitap;
                    while (ktp != NULL) {
                        if (strcmp(ktp->ISBN, kitap_yazar[i].ISBN) == 0) {  
                            //yazarın kitabının bilgileri yazdırılır
                            printf("Ad: %s | ISBN: %s | Adet: %d\n", ktp->name, ktp->ISBN, ktp->adet);
                            ornek = ktp->ornekler;
                            while (ornek != NULL) {
                                //ornek kitapların bilgileri yazdırılır
                                printf("  Etiket: %s | Durum: %s\n", ornek->etiket, ornek->durum);  
                                ornek = ornek->next;
                                tmp = 1;
                            }
                        }
                        ktp = ktp->next;
                    }
                }
            }
            printf("\n");
        }
        yazar = yazar->next;
    }

    if(bulundu == 0){
        printf("yazar bulunamadı.");
    }
    if(tmp == 0){
        printf("Kitabı bulunamadı.");
    }
}



////////////////////  YAZAR YARDIMCI FONKSIYONLAR  //////////////////////



/*program tekrar çalıştırılıp yeni işlemler yapılmak istendiğinde bilgilerin yazılı olduğu yazarlar.csv 
dosyasından biilgileri çeker ve üzerinde işlem yapacağımız liste yükler*/
Yazar* yazarlisteYukle(){
    Yazar *yazar = NULL, *node, *temp;
    //geçici diziler
    char satir[150],ad[50],soyad[50];

    FILE* fp = fopen("yazarlar.csv", "r");
    if (fp == NULL) {
    return NULL;
    }

    while (fgets(satir, sizeof(satir), fp)) {
        satir[strcspn(satir, "\n")] = 0;
        node = (Yazar*)malloc(sizeof(Yazar));
        node->next = NULL;
        sscanf(satir, "%[^,],%[^,],%d", ad, soyad, &node->yazarID);

        node->name = (char*)malloc(strlen(ad) + 1);     //dinamik olarak yer açma
        node->surname = (char*)malloc(strlen(soyad) + 1);
        strcpy(node->name, ad);
        strcpy(node->surname, soyad);
        

        if (yazar==NULL || node->yazarID < yazar->yazarID) {
            node->next = yazar;
            yazar = node;
        } else {
            temp = yazar;
            while (temp->next && temp->next->yazarID < node->yazarID){
                temp = temp->next;
            }
            node->next = temp->next;
            temp->next = node;
        }
    }
    fclose(fp);
    return yazar;
}


//fonksiyon pointer ile bilgileri alarak ogrenci bilgilerini yazarlar.csv dosyasına yazar
void yazardosyayaKaydet(FILE *fp, void *data) {
    Yazar* yazar = (Yazar*)data;
    while (yazar != NULL) {
        fprintf(fp, "%s,%s,%d\n", yazar->name, yazar->surname, yazar->yazarID);
        yazar = yazar->next;
    }
}




///////////////  FREE ETME FONKSIYONLARI  /////////////////

// Çift yönlü liste temizleme (Ogrenci gibi)
void ciftYonluListeTemizle(void** head, void (*freeData)(void**)) { //fonksiyon pointer kullanılarak free edilmekte
    Ogrenci** list = (Ogrenci**)head;
    while (*list != NULL) {
        Ogrenci* temp = *list;
        *list = (*list)->next;
        if (freeData) {
            freeData((void**)&temp);
        }
    }
}

// Tek yönlü liste temizleme (Odunc, Kitap gibi)
void tekYonluListeTemizle(void** head, void (*freeData)(void**)) { //fonksiyon pointer kullanılarak free edilmekte
    Odunc** list = (Odunc**)head;
    while (*list != NULL) {
        Odunc* temp = *list;
        *list = (*list)->next;
        if (freeData) {
            freeData((void**)&temp);
        }
    }
}

// Öğrenci temizleme
void freeOgrenci(void** data) { 
    Ogrenci* ogrenci = *(Ogrenci**)data;
    free(ogrenci->name);
    free(ogrenci->surname);
    free(ogrenci->numara);
    free(ogrenci);
}

// Ödünç temizleme
void freeOdunc(void** data) {
    Odunc* odunc = *(Odunc**)data;
    free(odunc->ogrenciNo);
    free(odunc->kitapEtiket);
    free(odunc->tarih);
    free(odunc);
}

// Kitap temizleme
void freeKitap(void** data) {
    Kitap* kitap = *(Kitap**)data;
    Ornek *temp, *ornek;
    free(kitap->name);
    free(kitap->ISBN);
    
    // Örnekleri temizle
    ornek = kitap->ornekler;
    while (ornek != NULL) {
        temp = ornek;
        ornek = ornek->next;
        free(temp->etiket);
        free(temp->durum);
        free(temp);
    }
    
    free(kitap);
}

// Yazar temizleme
void freeYazar(void** data) {
    Yazar* yazar = *(Yazar**)data;
    free(yazar->name);
    free(yazar->surname);
    free(yazar);
}

// Kitap-Yazar struct dizisini temizleme
void freeKitapYazar(void** data, int* kitapyazar_sayi) {
    int i;
    Kitap_Yazar* array = *(Kitap_Yazar**)data;

    if (array != NULL && *kitapyazar_sayi > 0) {
        for (i = 0; i < *kitapyazar_sayi; i++) {
            free(array[i].ISBN);  // Her ISBN string'ini free ediyoruz
        }
        free(array);  // Dizinin kendisini free ediyoruz
        *(Kitap_Yazar**)data = NULL;  // Pointer'ı NULL yapıyoruz
        *kitapyazar_sayi = 0;  
    }
}



////////////  DOSYAYA KAYDETME FONKSİYONU  ////////////

//fonksiyon pointer ile dosyayı acar ve kaydetmesi için fonksiyon çağırır
void dosyayaKaydetGenel(char *dosyaAdi, void *liste, void (*kaydetFonksiyon)(FILE*, void*)) {
    FILE *fp = fopen(dosyaAdi, "w");
    if (fp == NULL) {
        printf("%s dosyası açılamadı.\n", dosyaAdi);
        exit(1);
    }
    kaydetFonksiyon(fp, liste);  
    fclose(fp);
}
