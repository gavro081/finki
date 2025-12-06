#include <iostream>
#include <cstring>


using namespace std;


enum tip {
   pop, rap, rok
};


const char *tipovi[] = {"pop", "rap", "rok"};


class Pesna {
   char *ime;
   int minuti;
   tip kojtip;
public:
   Pesna(const char *ime="", int minuti=0, tip kojtip=pop) : minuti(minuti), kojtip(kojtip) {
       this->ime = new char[strlen(ime) + 1];
       strcpy(this->ime, ime);
   }


   ~Pesna() {
       delete[] ime;
   }


   Pesna(const Pesna &ob) {
       this->ime = new char[strlen(ob.ime) + 1];
       strcpy(this->ime, ob.ime);
       this->minuti = ob.minuti;
       this->kojtip = ob.kojtip;
   }


   Pesna &operator=(const Pesna &ob) {
       if (this != &ob) {
       this->ime = new char[strlen(ob.ime) + 1];
       strcpy(this->ime, ob.ime);
       this->minuti = ob.minuti;
       this->kojtip = ob.kojtip;
 }
       return *this;
   }


   void pecati() {
       cout << '\"' << ime << '\"' << '-' << minuti << "min\n";
   }


   int getMinuti() { return minuti; }


   int getTip() { return kojtip; }
};


class CD {
   Pesna pesni[10];
   int n;
   int maxVreme;
public:
   CD() {};


   int getN() { return n; }


   CD(int maxVreme) {
       this->maxVreme = maxVreme;
       n = 0;
   }


   ~CD(){}


   int getCurrMin() {
       int sum = 0;
       for (int i = 0; i < n; ++i) {
           sum += pesni[i].getMinuti();
       }
       return sum;
   }


   void dodadiPesna(Pesna p) {
       if (p.getMinuti() + this->getCurrMin() > maxVreme) return;
       if (n >= 10) return;


       pesni[n++] = p;
   }


   void pecatiPesniPoTip(tip t) {
       for (int i = 0; i < n; ++i) {
           if (pesni[i].getTip() == t) pesni[i].pecati();
       }
   }


   Pesna &getPesna(int i) {
       return pesni[i];
   }


   int getBroj() { return n; }
};


int main() {
   // se testira zadacata modularno
   int testCase;
   cin >> testCase;


   int n, minuti, kojtip;
   char ime[50];


   if (testCase == 1) {
       cout << "===== Testiranje na klasata Pesna ======" << endl;
       cin >> ime;
       cin >> minuti;
       cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
       Pesna p(ime, minuti, (tip) kojtip);
       p.pecati();
   } else if (testCase == 2) {
       cout << "===== Testiranje na klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       for (int i = 0; i < n; i++)
           (omileno.getPesna(i)).pecati();
   } else if (testCase == 3) {
       cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       for (int i = 0; i < omileno.getBroj(); i++)
           (omileno.getPesna(i)).pecati();
   } else if (testCase == 4) {
       cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       cin >> kojtip;
       omileno.pecatiPesniPoTip((tip) kojtip);


   } else if (testCase == 5) {
       cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       cin >> kojtip;
       omileno.pecatiPesniPoTip((tip) kojtip);


   }


   return 0;
}
