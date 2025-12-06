#include <iostream>
#include <cstring>


using namespace std;


class Gitara {
   char seriski[20];
   double nabavna;
   int godinaProizvodstvo;
   char tip[40];
public:
   Gitara(const char *tip = nullptr,const char *seriski = nullptr, int god = 0, double nabavna = -1.0) :
           nabavna(nabavna), godinaProizvodstvo(god) {
       if (seriski) {
           strcpy(this->seriski, seriski);
       }
       if (tip) {
           strcpy(this->tip, tip);
       }
   }


   ~Gitara() {}


   bool daliIsti(const Gitara &ob) {
       return (strcmp(seriski, ob.seriski) == 0);
   }


   void pecati() {
       cout << seriski << ' ' << tip << ' ' << nabavna << '\n';
   }


   double getNabavna() { return nabavna; }


   int getGodina() { return godinaProizvodstvo; }


   char *getTip() { return tip; }


   char *getSeriski() { return seriski; }
};


class Magacin {
   char ime[30];
   char lokacija[60];
   Gitara *gitari;
   int n;
   int godOtvaranje;
public:
   Magacin(const char *ime = "",const char *lokacija = "", int god = 0) : godOtvaranje(god) {
       strcpy(this->ime, ime);
       strcpy(this->lokacija, lokacija);
       gitari = NULL;
       n = 0;
   }


   ~Magacin() {
       delete[] gitari;
   }


   Magacin(const Magacin &ob) {
       strcpy(this->ime, ob.ime);
       strcpy(this->lokacija, ob.lokacija);
       this->n = ob.n;
       this->godOtvaranje = ob.godOtvaranje;
       this->gitari = new Gitara[n];
       for (int i = 0; i < n; ++i) {
           this->gitari[i] = ob.gitari[i];
       }
   }


   Magacin &operator=(const Magacin &ob) {
       delete[] gitari;
       strcpy(this->ime, ob.ime);
       strcpy(this->lokacija, ob.lokacija);
       this->n = ob.n;
       this->godOtvaranje = ob.godOtvaranje;
       this->gitari = new Gitara[n];
       for (int i = 0; i < n; ++i) {
           this->gitari[i] = ob.gitari[i];
       }
       return *this;
   }




   double vrednost() {
       double vrednost = 0.0;
       for (int i = 0; i < n; ++i) {
           vrednost += gitari[i].getNabavna();
       }
       return vrednost;
   }


   void dodadi(Gitara d) {
       Gitara *tmp = new Gitara[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = gitari[i];
       }
       tmp[n++] = d;
       delete[] gitari;
       gitari = tmp;
   }


   void prodadi(Gitara p) {
       int ctr = 0;
       for (int i = 0; i < n; ++i) {
           if (gitari[i].daliIsti(p)) ctr++;
       }
       Gitara *tmp = new Gitara[n - ctr];
       int j = 0;
       for (int i = 0; i < n; ++i) {
           if (!gitari[i].daliIsti(p)) {
               tmp[j++] = gitari[i];
           }
       }
       delete [] gitari;
       n -= ctr;
       gitari = tmp;
   }


   void pecati(bool daliNovi) {
       cout << ime << ' ' << lokacija << '\n';
       if (daliNovi) {
           for (int i = 0; i < n; ++i) {
               if (gitari[i].getGodina() > godOtvaranje) {
                   gitari[i].pecati();
               }
           }
       } else {
           for (int i = 0; i < n; ++i) {
               gitari[i].pecati();
           }
       }
   }
};


int main() {
//     se testira zadacata modularno
   int testCase;
   cin >> testCase;
   int n, godina;
   float cena;
   char seriski[50], tip[50];


   if (testCase == 1) {
       cout << "===== Testiranje na klasata Gitara ======" << endl;
       cin >> tip;
       cin >> seriski;
       cin >> godina;
       cin >> cena;
       Gitara g(tip, seriski, godina, cena);
       cout << g.getTip() << endl;
       cout << g.getSeriski() << endl;
       cout << g.getGodina() << endl;
       cout << g.getNabavna() << endl;
   } else if (testCase == 2) {
       cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
       Magacin kb("Magacin1", "Lokacija1");
       kb.pecati(false);
   } else if (testCase == 3) {
       cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
       Magacin kb("Magacin1", "Lokacija1", 2005);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> tip;
           cin >> seriski;
           cin >> godina;
           cin >> cena;
           Gitara g(tip, seriski, godina, cena);
           cout << "gitara dodadi" << endl;
           kb.dodadi(g);
       }
       kb.pecati(true);
   } else if (testCase == 4) {
       cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
       Magacin kb("Magacin1", "Lokacija1", 2012);
       cin >> n;
       Gitara brisi;
       for (int i = 0; i < n; i++) {
           cin >> tip;
           cin >> seriski;
           cin >> godina;
           cin >> cena;


           Gitara g(tip, seriski, godina, cena);
           if (i == 2)
               brisi = g;
           cout << "gitara dodadi" << endl;
           kb.dodadi(g);
       }
       kb.pecati(false);
       kb.prodadi(brisi);
       kb.pecati(false);
   } else if (testCase == 5) {
       cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
       Magacin kb("Magacin1", "Lokacija1", 2011);
       cin >> n;
       Gitara brisi;
       for (int i = 0; i < n; i++) {
           cin >> tip;
           cin >> seriski;
           cin >> godina;
           cin >> cena;


           Gitara g(tip, seriski, godina, cena);
           if (i == 2)
               brisi = g;
           cout << "gitara dodadi" << endl;
           kb.dodadi(g);
       }
       kb.pecati(true);
       kb.prodadi(brisi);
       cout << "Po brisenje:" << endl;
       Magacin kb3;
       kb3 = kb;
       kb3.pecati(true);
   } else if (testCase == 6) {
       cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
       Magacin kb("Magacin1", "Lokacija1", 2011);
       cin >> n;
       Gitara brisi;
       for (int i = 0; i < n; i++) {
           cin >> tip;
           cin >> seriski;
           cin >> godina;
           cin >> cena;


           Gitara g(tip, seriski, godina, cena);
           if (i == 2)
               brisi = g;
           kb.dodadi(g);
       }
       cout << kb.vrednost() << endl;
       kb.prodadi(brisi);
       cout << "Po brisenje:" << endl;
       cout << kb.vrednost();
       Magacin kb3;
       kb3 = kb;
   }
   return 0;
}