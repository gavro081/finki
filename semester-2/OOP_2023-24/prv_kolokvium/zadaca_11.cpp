// vashiot kod ovde
#include <iostream>
#include <cstring>


using namespace std;


class Ucesnik{
   char *ime;
   bool pol;
   int vozrast;
public:
   Ucesnik(const char *ime = "", bool pol = false, int vozrast = 0) :
           pol(pol), vozrast(vozrast){
       this->ime = new char[strlen(ime) + 1];
       strcpy(this->ime, ime);
   }


   Ucesnik (const Ucesnik& ob){
       this->ime = new char[strlen(ob.ime) + 1];
       strcpy(this->ime, ob.ime);
       this->pol = ob.pol;
       this->vozrast = ob.vozrast;
   }


   Ucesnik& operator=(const Ucesnik& ob){
       this->ime = new char[strlen(ob.ime) + 1];
       strcpy(this->ime, ob.ime);
       this->pol = ob.pol;
       this->vozrast = ob.vozrast;
   }


   ~Ucesnik(){
       delete [] ime;
   }


   bool operator>(const Ucesnik& ob){
       return vozrast > ob.vozrast;
   }


   friend ostream& operator<<(ostream& COUT, const Ucesnik& ob){
       COUT << ob.ime << '\n';
       if (!ob.pol) COUT << "zhenski";
       else COUT << "mashki";
       COUT << '\n' << ob.vozrast << '\n';
       return COUT;
   }


   int getVozrast(){return vozrast;}
};


class Maraton{
   char lokacija[100];
   Ucesnik *ucesnici;
   int n;
public:


   Maraton(const char *lokacija = ""){
       strcpy(this->lokacija, lokacija);
       ucesnici = NULL;
       n = 0;
   }
   ~Maraton(){
       delete [] ucesnici;
   }
   void operator+=(const Ucesnik& ob){
       Ucesnik *tmp = new Ucesnik[n+1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = ucesnici[i];
       }
       tmp[n++] = ob;
       delete [] ucesnici;
       ucesnici = tmp;
   }


   double prosecnoVozrast(){
       int total = 0;
       for (int i = 0; i < n; ++i) {
           total += ucesnici[i].getVozrast();
       }
       return (double)total / n;
   }


   void pecatiPomladi(Ucesnik& u){
       int reper = u.getVozrast();
       for (int i = 0; i < n; ++i) {
           if (ucesnici[i].getVozrast() < reper) cout << ucesnici[i];
       }
   }
};


int main() {
   char ime[100];
   bool maski;
   int vozrast, n;
   cin >> n;
   char lokacija[100];
   cin >> lokacija;
   Maraton m(lokacija);
   Ucesnik **u = new Ucesnik*[n];
   for(int i = 0; i < n; ++i) {
       cin >> ime >> maski >> vozrast;
       u[i] = new Ucesnik(ime, maski, vozrast);
       m += *u[i];
   }
   m.pecatiPomladi(*u[n - 1]);
   cout << m.prosecnoVozrast() << endl;
   for(int i = 0; i < n; ++i) {
       delete u[i];
   }
   delete [] u;
   return 0;
}


