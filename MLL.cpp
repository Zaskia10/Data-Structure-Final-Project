#include "MLL.h"

void createListEcom(ListECom &L){
    first(L) = NULL;
}

void createListToko(ListToko &L){
    first(L) = NULL;
    last(L) = NULL;
}

void createListRelasi(ListRelasi &R){
    first(R) = NULL;
}

adrECom createElmEcom(infoEcom data){
    adrECom E = new ElmECommerce;
    info(E) = data;
    nextEcom(E) = NULL;
    return E;
}

adrRelasi createElmRelasi(adrECom Ec, adrToko To){
    adrRelasi R = new ElmRelasi;
    Ecom(R) = Ec;
    Toko(R) = To;
    nextRelasi(R) = NULL;
    return R;
}

adrToko createElmToko(infoToko data){
    adrToko T = new ElmTokoOnline;
    info(T) = data;
    nextToko(T) = NULL;
    prevToko(T) = NULL;
    return T;
}

void insertLastEcom(ListECom &L, adrECom P){
/*memasukkan elemen parent (ECommerce) ke dalam list parent dari belakang*/
    if (first(L) == NULL){
        first(L) = P;
    } else {
        adrECom prec;
        prec = first(L);
        while (nextEcom(prec) != NULL){
            prec = nextEcom(prec);
        }
        nextEcom(prec) = P;
    }
}

void deleteFirstEcom(ListECom &L, adrECom &P){
/*Menghapus elemen pertama dari list Ecom*/
    if (first(L) == NULL){
        P = NULL;
        cout << "List Kosong" << endl;
    } else {
        P = first(L);
        first(L) = nextEcom(P);
        nextEcom(P) = NULL;
    }
}

void addRelasi(ListRelasi &L, adrRelasi P) {
    //menghubungkan list Ecom dan Toko online
    if (first(L) == NULL) {
        first(L) = P;
        nextRelasi(P) = NULL;
    } else {
        nextRelasi(P) = first(L);
        first(L) = P;
    }
}

void printListEcom(ListECom L){
/*mencetak elemen parent (E-Commerce)*/
    if (first(L)==NULL){
        cout << "Tidak ada data E-Commerce" << endl;
    } else {
        adrECom P = first(L);
        cout << "Data Id E-Commerce dan Nama E-Commerce" << endl;
        while (P != NULL){
            cout << info(P).id << "  " << info(P).nama << endl;
            P = nextEcom(P);
        }
    }
}

void printListEcomdanToko(ListECom L, ListRelasi R) {
    // Penelusuran Ecom
    adrECom E = first(L);
    while (E != NULL) {
        cout << "E-Commerce: " << info(E).nama << endl; // Print nama E-Commerce
        adrRelasi rel = first(R);
        int tokoCount = 0;
        // Penelusuran relasi untuk mencari toko-toko yang berhubungan dengan Ecom ini
        while (rel != NULL) {
            if (Ecom(rel) == E) {
                tokoCount++;
                cout << tokoCount << ". Toko: " << info(Toko(rel)).nama << endl;
            }
            rel = nextRelasi(rel);
        }
        if (tokoCount == 0) {
            cout << "Tidak ada toko yang berelasi dengan E-Commerce ini." << endl;
        }
        cout << endl; // Tambahkan newline untuk memisahkan output E-Commerce
        E = nextEcom(E); // Pindah ke E-Commerce berikutnya
    }
}

int jumlahToko(ListRelasi L, string namaEcom){
/*mengembalikan jumlah toko yang di parent tertentu*/
    adrRelasi R = first(L);
    int count = 0;
    while (R!=NULL){
        if (info(Ecom(R)).nama == namaEcom){
            count++;
        }
        R = nextRelasi(R);
    }
    return count;
}

adrECom findEcommerce(ListECom L, string id){
/*mengembalikan pointer yang menunjuk ke elemen yang berisi "id"*/
    adrECom P = first(L);
    while (P != NULL && info(P).id != id){
        P = nextEcom(P);
    }
    return P;
}

void deleteRelasiEcom(ListECom &L, ListRelasi &R, adrECom E) {
    adrRelasi A = first(R);
    adrRelasi prec = NULL;

    // Menghapus semua relasi terkait
    while (A != NULL) {
        if (Ecom(A) == E) {
            adrRelasi Q = A;
            if (A == first(R)) {
                first(R) = nextRelasi(A);
            } else {
                nextRelasi(prec) = nextRelasi(A);
            }
            A = nextRelasi(A);
            nextRelasi(Q) = NULL;
        } else {
            prec = A;
            A = nextRelasi(A);
        }
    }

    // Menghapus ECom dari list ECom
    adrECom X = first(L);
    adrECom precE = NULL;

    if (X == E) {
        deleteFirstEcom(L, E);
    } else {
        while (X != NULL && X != E) {
            precE = X;
            X = nextEcom(X);
        }
        if (X != NULL) { // pastikan elemen ditemukan
            if (precE != NULL) {
                nextEcom(precE) = nextEcom(X);
            }
            nextEcom(X) = NULL;
        }
    }
}

bool cekIdEcom(ListECom L, string id) {
    adrECom P = first(L);
    while (P != NULL) {
        if (info(P).id == id) {
            return true;
        }
        P = nextEcom(P);
    }
    return false;
}

//CHILD
void insertFirstToko(ListToko &L, adrToko P){
    //memasukkan data baru ke list Toko dari depan
    if(first(L) == NULL) {
        first(L) = P;
    } else {
        nextToko(P) = first(L);
        prevToko(first(L)) = P;
        first(L) = P;
    }
}

adrToko searchToko(ListToko L, string IDtoko){
    //mengembalikan adrToko dari id toko yang di cari
    adrToko P = first(L);
    while (P != NULL && info(P).id != IDtoko) {
        P = nextToko(P);
    }
    return P;
}

bool cekIDtoko(ListToko L, string IDtoko) {
    //mengembalikan true jika unik dan false jika tidak unik
    adrToko P = first(L);
    bool unik = true;
    while (P != NULL && unik) {
        if(info(P).id == IDtoko) {
            unik = false;
        }
        P = nextToko(P);
    }
    return unik;
}

void deleteTokofromEcom(ListToko LT, ListECom LE, ListRelasi &LR, string IDEcom, string IDtoko) {
    adrECom eCommerce = findEcommerce(LE, IDEcom);
    adrToko toko = searchToko(LT, IDtoko);
    if (eCommerce == NULL || toko == NULL) {
        cout << "Toko dengan id" << IDtoko << " dan eCommerce dengan id " << IDEcom << " tidak ada pada list" << endl;
    } else {
        adrRelasi P = first(LR);
        if (Ecom(P) == eCommerce && Toko(P) == toko) {
            deleteFirstRelasi(LR, P);
        } else {
            while ( nextRelasi(P) != NULL && (Ecom(nextRelasi(P)) != eCommerce || Toko(nextRelasi(P)) != toko)) {
                P = nextRelasi(P);
            }

            if (nextRelasi(P) == NULL) {
                cout << "Toko tidak terhubung dengan eCommerce" << endl;
            } else {
                adrRelasi Q;
                deleteAfterRelasi(LR, P, Q);
            }

        }
    }
}

void deleteFirstRelasi(ListRelasi &L, adrRelasi &P) {
    first(L) = nextRelasi(P);
    nextRelasi(P) = NULL;
}

void deleteAfterRelasi(ListRelasi &L, adrRelasi prec, adrRelasi &P) {
    P = nextRelasi(prec);
    nextRelasi(prec) = nextRelasi(P);
    nextRelasi(P) = NULL;
}

adrRelasi searchTokoDiEcom(ListRelasi L, adrECom eCommerce, adrToko toko) {
    //Mencari data toko pada ecom tertentu
    adrRelasi P = first(L);
    while(P != NULL && (Ecom(P) != eCommerce || Toko(P) != toko)) {
        P = nextRelasi(P);
    }
    return P;
}
