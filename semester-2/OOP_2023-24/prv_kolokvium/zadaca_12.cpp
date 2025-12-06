// ima greska ili vo baranje ili vo main; vo tekstot bara funkcija dodadi() a vo main bara preoptovaren += operator
// moevo e so dodadi() i smeneti 2 reda vo main; ctrl f ‘TUKA’


#include <iostream>
#include <cstring>


using namespace std;


class Pica {
   char ime[50];
   int cena;
   char *sostojki;
   int namaluvanje;
public:
   Pica() {}


   Pica(const char *ime, int cena, const char *sostojki, int namaluvanje)
           : cena(cena), namaluvanje(namaluvanje) {
       strcpy(this->ime, ime);
       this->sostojki = new char[strlen(sostojki) + 1];
       strcpy(this->sostojki, sostojki);
   }


   Pica(const Pica &ob) {
       strcpy(this->ime, ob.ime);
       this->sostojki = new char[strlen(ob.sostojki) + 1];
       strcpy(this->sostojki, ob.sostojki);
       this->cena = ob.cena;
       this->namaluvanje = ob.namaluvanje;
   }


   Pica &operator=(const Pica &ob) {
       if (this != &ob) {
           strcpy(this->ime, ob.ime);
           this->sostojki = new char[strlen(ob.sostojki) + 1];
           strcpy(this->sostojki, ob.sostojki);
           this->cena = ob.cena;
           this->namaluvanje = ob.namaluvanje;
       }
       return *this;
   }


   ~Pica() {
       delete[] sostojki;
   }


   char *getIme() { return ime; }


   int getNamaluvanje() { return namaluvanje; }


   int getCena() { return cena; }


   void pecati() {
       cout << ime << " - " << sostojki << ", " << cena;
   }


   bool istiSe(Pica p) {
       return (strcmp(sostojki, p.sostojki) == 0);
   }


};


class Picerija {
   char ime[15];
   Pica *pici;
   int n;
public:
   Picerija() {}


   Picerija(char *ime) {
       strcpy(this->ime, ime);
       n = 0;
       pici = NULL;
   }


   ~Picerija() {
       delete[] pici;
   }


   Picerija(const Picerija &ob) {
       strcpy(this->ime, ob.ime);
       this->n = ob.n;
       pici = new Pica[n];
       for (int i = 0; i < n; ++i) {
           pici[i] = ob.pici[i];
       }
   }


   Picerija &operator=(const Picerija &ob) {
       if (this != &ob) {
           strcpy(this->ime, ob.ime);
           this->n = ob.n;
           pici = new Pica[n];
           for (int i = 0; i < n; ++i) {
               pici[i] = ob.pici[i];
           }
       }
       return *this;
   }


   Picerija(char *ime, Pica *pici, int n) : n(n) {
       strcpy(this->ime, ime);
       this->pici = new Pica[n];
       for (int i = 0; i < n; ++i) {
           this->pici[i] = pici[i];
       }
   }


   char *getIme() { return ime; }


   void setIme(char *ime) { strcpy(this->ime, ime); }


   void dodadi(Pica P) {
       for (int i = 0; i < n; ++i) {
           if (P.istiSe(pici[i])) return;
       }
       Pica *tmp = new Pica[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = pici[i];
       }
       delete[] pici;
       tmp[n++] = P;
       pici = new Pica[n + 1];
       pici = tmp;
   }


   void piciNaPromocija() {
//        cout << "Pici na promocija: \n";
       for (int i = 0; i < n; ++i) {
           if (pici[i].getNamaluvanje() > 0) {
               pici[i].pecati();
               cout << ' ' << pici[i].getCena() * (double) (100 - pici[i].getNamaluvanje()) / 100 << '\n';
           }
       }
   }
};


int main() {


   int n;
   char ime[15];
   cin >> ime;
   cin >> n;


   Picerija p1(ime);
   for (int i = 0; i < n; i++) {
       char imp[100];
       cin.get();
       cin.getline(imp, 100);
       int cena;
       cin >> cena;
       char sostojki[100];
       cin.get();
       cin.getline(sostojki, 100);
       int popust;
       cin >> popust;
       Pica p(imp, cena, sostojki, popust);
//        p1+=p; TUKA IMA GRESKA VO MAIN
       p1.dodadi(p);


   }


   Picerija p2 = p1;
   cin >> ime;
   p2.setIme(ime);
   char imp[100];
   cin.get();
   cin.getline(imp, 100);
   int cena;
   cin >> cena;
   char sostojki[100];
   cin.get();
   cin.getline(sostojki, 100);
   int popust;
   cin >> popust;
   Pica p(imp, cena, sostojki, popust);
//    p2+=p; TUKA IMA GRESKA VO MAIN
   p2.dodadi(p);


   cout << p1.getIme() << endl;
   cout << "Pici na promocija:" << endl;
   p1.piciNaPromocija();


   cout << p2.getIme() << endl;
   cout << "Pici na promocija:" << endl;
   p2.piciNaPromocija();


   return 0;
}

