#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>
#include <iomanip>
#define info(P) P->info
#define nextEcom(P) P->nextEcom
#define nextToko(T) T->nextToko
#define prevToko(T) T->prevToko
#define nextRelasi(R) R->nextRelasi
#define first(L) L.first
#define last(L) L.last
#define Ecom(R) R->Ecom
#define Toko(R) R->Toko

using namespace std;

//info parents
struct ECommerce{
    string id;
    string nama;
};

//info child
struct TokoOnline{
    string id;
    string nama;
};

//infotype parent dan child
typedef ECommerce infoEcom;
typedef TokoOnline infoToko;

//pointer
typedef struct ElmECommerce *adrECom;
typedef struct ElmTokoOnline *adrToko;
typedef struct ElmRelasi *adrRelasi;

//elemenECommerce
struct ElmECommerce {
    infoEcom info;
    adrECom nextEcom;
};
//elemen Toko Online
struct ElmTokoOnline {
    infoToko info;
    adrToko nextToko;
    adrToko prevToko; //DLL
};
//elemen relasi
struct ElmRelasi {
    adrECom Ecom;
    adrToko Toko;
    adrRelasi nextRelasi;
};

//list ecommerce
struct ListECom{
    adrECom first;
};
//list toko
struct ListToko{
    adrToko first;
    adrToko last;
};
//list relasi
struct ListRelasi{
    adrRelasi first;
};

//prosedur create list
void createListEcom(ListECom &L);
void createListToko(ListToko &L);
void createListRelasi(ListRelasi &L);

//function create elemen
adrECom createElmEcom(infoEcom data);
adrToko createElmToko(infoToko data);
adrRelasi createElmRelasi(adrECom Ec, adrToko To);

//Parent
void insertLastEcom(ListECom &L, adrECom P);
void deleteFirstEcom(ListECom &L, adrECom &P);
void printListEcom(ListECom L);
void printListEcomdanToko(ListECom E, ListRelasi R);
int jumlahToko(ListRelasi L, string namaEcom);
adrECom findEcommerce(ListECom L, string id);
void deleteRelasiEcom(ListECom &L, ListRelasi &R, adrECom E);
bool cekIdEcom(ListECom L, string id);

//Child
void insertFirstToko(ListToko &L, adrToko P);
void deleteTokofromEcom(ListToko LT, ListECom LE, ListRelasi &L, string IDEcom, string IDtoko);
adrToko searchToko(ListToko L, string IDtoko);
bool cekIDtoko(ListToko L, string IDtoko);

//relasi
adrRelasi searchTokoDiEcom(ListRelasi L, adrECom eCommerce, adrToko toko);
void addRelasi(ListRelasi &L, adrRelasi P);
void deleteFirstRelasi(ListRelasi &L, adrRelasi &P);
void deleteAfterRelasi(ListRelasi &L, adrRelasi prec, adrRelasi &P);
adrRelasi findRelasiEcom(ListRelasi &L, adrECom Ecom);




#endif // MLL_H_INCLUDED
