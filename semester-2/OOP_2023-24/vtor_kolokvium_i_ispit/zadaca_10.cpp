#include <iostream>
#include <cstring>
#include <cstdlib>


using namespace std;


//место за вашиот код
class Oglas{
   char naslov[50];
   char kategorija[30];
   char opis[100];
   float cena;
public:
   Oglas(const char *naslov="", const char *kategorija="", const char *opis="", float cena=-1)
           : cena(cena){
       strcpy(this->naslov, naslov);
       strcpy(this->kategorija, kategorija);
       strcpy(this->opis, opis);
   }


   bool operator>(Oglas& ob){
       return cena > ob.cena;
   }


   friend ostream& operator<<(ostream& COUT, Oglas& ob){
       COUT << ob.naslov << '\n' << ob.opis << '\n' << ob.cena << " evra\n";
       return COUT;
   }


   float getCena(){return cena;}
   char* getKategorija(){return kategorija;}
};


class NegativnaVrednost{
public:
   void print(){
       cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!\n";
   }
};
class Oglasnik{
   char ime[20];
   Oglas* oglasi = nullptr;
   int n = 0;
public:
   Oglasnik(char *ime) {strcpy(this->ime, ime);}


   Oglasnik& operator+=(Oglas& o){
       if (o.getCena() < 0) throw NegativnaVrednost();
       Oglas* tmp = new Oglas[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = oglasi[i];
       }
       tmp[n++] = o;
       oglasi = tmp;
       return *this;
   }


   friend ostream& operator<<(ostream& COUT, Oglasnik& ob){
       COUT << ob.ime << '\n';
       for (int i = 0; i < ob.n; ++i) {
           COUT << ob.oglasi[i] << '\n';
       }
       return COUT;
   }


   void oglasiOdKategorija(const char *k){
       for (int i = 0; i < n; ++i) {
           if (strcmp(oglasi[i].getKategorija(),k) == 0) cout << oglasi[i] << '\n';
       }
   }
   void najniskaCena(){
       Oglas najevtin = oglasi[0];
       for (int i = 1; i < n; ++i) {
           if (oglasi[i].getCena() < najevtin.getCena()) najevtin = oglasi[i];
       }
       cout << najevtin;
   }
};




int main(){


   char naslov[50];
   char kategorija[30];
   char opis[100];
   float cena;
   char naziv[50];
   char k[30];
   int n;


   int tip;
   cin>>tip;


   if (tip==1){
       cout<<"-----Test Oglas & operator <<-----" <<endl;
       cin.get();
       cin.getline(naslov,49);
       cin.getline(kategorija,29);
       cin.getline(opis,99);
       cin>>cena;
       Oglas o(naslov, kategorija, opis, cena);
       cout<<o;
   }
   else if (tip==2){
       cout<<"-----Test Oglas & operator > -----" <<endl;
       cin.get();
       cin.getline(naslov,49);
       cin.getline(kategorija,29);
       cin.getline(opis,99);
       cin>>cena;
       Oglas o1(naslov, kategorija, opis, cena);
       cin.get();
       cin.getline(naslov,49);
       cin.getline(kategorija,29);
       cin.getline(opis,99);
       cin>>cena;
       Oglas o2(naslov, kategorija, opis, cena);
       if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
       else cout<<"Prviot oglas ne e poskap."<<endl;
   }
   else if (tip==3){
       cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
       cin.get();
       cin.getline(naziv,49);
       cin>>n;
       Oglasnik ogl(naziv);
       for (int i = 0; i < n; i++){
           cin.get();
           cin.getline(naslov,49);
           cin.getline(kategorija,29);
           cin.getline(opis,99);
           cin>>cena;
           Oglas o(naslov, kategorija, opis, cena);
           ogl+=o;
       }
       cout<<ogl;
   }
   else if (tip==4){
       cout<<"-----Test oglasOdKategorija -----" <<endl ;
       cin.get();
       cin.getline(naziv,49);
       cin>>n;
       Oglasnik ogl(naziv);
       for (int i = 0; i < n; i++){
           cin.get();
           cin.getline(naslov,49);
           cin.getline(kategorija,29);
           cin.getline(opis,99);
           cin>>cena;
           Oglas o(naslov, kategorija, opis, cena);
           ogl+=o;
       }
       cin.get();
       cin.getline(k,29);
       cout<<"Oglasi od kategorijata: " <<k<<endl;
       ogl.oglasiOdKategorija(k);


   }
   else if (tip==5){
       cout<<"-----Test Exception -----" <<endl ;
       cin.get();
       cin.getline(naziv,49);
       cin>>n;
       Oglasnik ogl(naziv);
       for (int i = 0; i < n; i++){
           cin.get();
           cin.getline(naslov,49);
           cin.getline(kategorija,29);
           cin.getline(opis,99);
           cin>>cena;
           Oglas o(naslov, kategorija, opis, cena);
           try{
               ogl+=o;
           }
           catch (NegativnaVrednost) {NegativnaVrednost().print();}


       }
       cout<<ogl;


   }
   else if (tip==6){
       cout<<"-----Test najniskaCena -----" <<endl ;
       cin.get();
       cin.getline(naziv,49);
       cin>>n;
       Oglasnik ogl(naziv);
       for (int i = 0; i < n; i++){
           cin.get();
           cin.getline(naslov,49);
           cin.getline(kategorija,29);
           cin.getline(opis,99);
           cin>>cena;
           Oglas o(naslov, kategorija, opis, cena);
           ogl+=o;
       }
       cout<<"Oglas so najniska cena:"<<endl;
       ogl.najniskaCena();


   }
   else if (tip==7){
       cout<<"-----Test All -----" <<endl ;
       cin.get();
       cin.getline(naziv,49);
       cin>>n;
       Oglasnik ogl(naziv);
       for (int i = 0; i < n; i++){
           cin.get();
           cin.getline(naslov,49);
           cin.getline(kategorija,29);
           cin.getline(opis,99);
           cin>>cena;
           Oglas o(naslov, kategorija, opis, cena);
           try{
               ogl+=o;
           }
           catch (NegativnaVrednost) {NegativnaVrednost().print();}
       }
       cout<<ogl;


       cin.get();
       cin.get();
       cin.getline(k,29);
       cout<<"Oglasi od kategorijata: " <<k<<endl;
       ogl.oglasiOdKategorija(k);


       cout<<"Oglas so najniska cena:"<<endl;
       ogl.najniskaCena();


   }


   return 0;
}
