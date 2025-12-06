// vashiot kod ovde
#include <iostream>
#include <cstring>


using namespace std;


class Vozac{
protected:
   char ime[100];
   int vozrast;
   int trki;
   bool daliVeteran;
public:
   Vozac(const char* ime, int vozrast, int trki, bool daliVeteran)
   : vozrast(vozrast), trki(trki), daliVeteran(daliVeteran){
       strcpy(this->ime, ime);
   }


   friend ostream& operator<<(ostream& COUT, const Vozac& ob){
       COUT << ob.ime << '\n' << ob.vozrast << '\n' << ob.trki << '\n';
       if (ob.daliVeteran) COUT << "VETERAN\n";
       return COUT;
   }


   virtual double getZarabotuvacka()=0;


   virtual bool operator==(Vozac& ob){
       return getZarabotuvacka() == ob.getZarabotuvacka();
   }


   virtual double danok()=0;
};


class Avtomobilist : public Vozac{
   double cena;
public:
   Avtomobilist(const char* ime, int vozrast, int trki, bool daliVeteran, double cena) :
   cena(cena), Vozac(ime,vozrast,trki,daliVeteran){}


   using Vozac::operator==;


   double getZarabotuvacka() override{
       return cena / 5;
   }


   double danok()override{
       return (trki > 10) ? 0.15 * getZarabotuvacka() : 0.1 * getZarabotuvacka();
   }
};


class Motociklist : public Vozac{
   int moknost;
public:
   Motociklist(const char* ime, int vozrast, int trki, bool daliVeteran, int moknost)
   : moknost(moknost), Vozac(ime,vozrast, trki, daliVeteran){}


   double getZarabotuvacka() override{
       return moknost * 20;
   }
   double danok()override{
       return (daliVeteran) ? 0.25 * getZarabotuvacka() : 0.2 * getZarabotuvacka();
   }
};


int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac* v){
   int ctr = 0;
   double reper = v->getZarabotuvacka();
   for (int i = 0; i < n; ++i) {
       vozaci[i]->getZarabotuvacka();
       if (vozaci[i]->getZarabotuvacka() == reper) ctr++;
   }
   return ctr;
}


int main() {
   int n, x;
   cin >> n >> x;
   Vozac **v = new Vozac*[n];
   char ime[100];
   int vozrast;
   int trki;
   bool vet;
   for(int i = 0; i < n; ++i) {
       cin >> ime >> vozrast >> trki >> vet;
       if(i < x) {
           float cena_avto;
           cin >> cena_avto;
           v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
       } else {
           int mokjnost;
           cin >> mokjnost;
           v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
       }
   }
   cout << "=== DANOK ===" << endl;
   for(int i = 0; i < n; ++i) {
       cout << *v[i];
       cout << v[i]->danok() << endl;
   }
   cin >> ime >> vozrast >> trki >> vet;
   int mokjnost;
   cin >> mokjnost;
   Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
   cout << "=== VOZAC X ===" << endl;
   cout << *vx;
   cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
   cout << soIstaZarabotuvachka(v, n, vx);
   for(int i = 0; i < n; ++i) {
       delete v[i];
   }
   delete [] v;
   delete vx;
   return 0;
}
