#include <iostream>
#include <cstring>


using namespace std;


enum tip{smartfon, kompjuter};


class Device{
   char model[100];
   tip t;
   double casovi;
   static int fixcasovi;
   int god;
public:
   Device(){}
   Device(char* model, tip t, int god){
       strcpy(this->model, model);
       this->t = t;
       this->god = god;
   }


   static void setPocetniCasovi(int a) {fixcasovi = a;}


   double casoviProverka(){
       double c = fixcasovi;
       if (god > 2015) c += 2;
       if (t==1) c += 2;
       casovi = c;
       return c;
   }


   friend ostream& operator<<(ostream& COUT, Device& ob){
       COUT << ob.model << '\n';
       COUT << ((ob.t == 0) ? "Mobilen" : "Laptop") << " " << ob.casoviProverka() << '\n';
       return COUT;
   }


   int getGod(){return god;}
};


class InvalidProductionDate{
public:
   void print(){
       cout << "Невалидна година на производство\n";
   }
};


class MobileServis{
   char adresa[100];
   Device* devices = nullptr;
   int n = 0;
public:
   MobileServis(char* adresa) { strcpy(this->adresa, adresa);}


   MobileServis& operator+=(Device& d){
       if (d.getGod() > 2019 || d.getGod() < 2000) throw InvalidProductionDate();
       Device* tmp = new Device[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = devices[i];
       }
       tmp[n++] = d;
       devices = tmp;
       return *this;
   }


   void pecatiCasovi(){
       cout << "Ime: " << adresa << '\n';
       for (int i = 0; i < n; ++i) {
           cout << devices[i];
       }
   }


};
int Device::fixcasovi = 1;


int main()
{
   int testCase;
   cin >> testCase;
   char ime[100];
   int tipDevice;
   int godina;
   int n;
   Device devices[50];
   if (testCase == 1){
       cout << "===== Testiranje na klasite ======" << endl;
       cin >> ime;
       cin >> tipDevice;
       cin >> godina;
       Device ig(ime,(tip)tipDevice,godina);
       cin>>ime;
       MobileServis t(ime);
       cout<<ig;
   }
   if (testCase == 2){
       cout << "===== Testiranje na operatorot += ======" << endl;
       cin>>ime;
       cin >> n;
       MobileServis t(ime);
       for(int i=0;i<n;i++)
       {
           cin >> ime;
           cin >> tipDevice;
           cin >> godina;
           Device tmp(ime,(tip)tipDevice,godina);
           try {
               t += tmp;
           }
           catch (InvalidProductionDate){InvalidProductionDate().print();}
       }
       t.pecatiCasovi();
   }
   if (testCase == 3){
       cout << "===== Testiranje na isklucoci ======" << endl;
       cin>>ime;
       cin >> n;
       MobileServis t(ime);
       for(int i=0;i<n;i++)
       {
           cin >> ime;
           cin >> tipDevice;
           cin >> godina;
           Device tmp(ime,(tip)tipDevice,godina);
           try {
               t += tmp;
           }
           catch (InvalidProductionDate){InvalidProductionDate().print();}
       }
       t.pecatiCasovi();
   }
   if (testCase == 4){
       cout <<"===== Testiranje na konstruktori ======"<<endl;
       cin>>ime;
       cin >> n;
       MobileServis t(ime);
       for(int i=0;i<n;i++)
       {
           cin >> ime;
           cin >> tipDevice;
           cin >> godina;
           Device tmp(ime,(tip)tipDevice,godina);
           try {
               t += tmp;
           }
           catch (InvalidProductionDate) {InvalidProductionDate().print();}
       }
       MobileServis t2 = t;
       t2.pecatiCasovi();
   }
   if (testCase == 5){
       cout << "===== Testiranje na static clenovi ======" << endl;
       cin>>ime;
       cin >> n;
       MobileServis t(ime);
       for(int i=0;i<n;i++)
       {
           cin >> ime;
           cin >> tipDevice;
           cin >> godina;
           Device tmp(ime,(tip)tipDevice,godina);
           try {
               t += tmp;
           }
           catch (InvalidProductionDate) {InvalidProductionDate().print();}
       }
       t.pecatiCasovi();
       cout << "===== Promena na static clenovi ======" << endl;
       Device::setPocetniCasovi(2);
       t.pecatiCasovi();
   }


   if (testCase == 6){
       cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
       cin>>ime;
       cin >> n;
       MobileServis t(ime);
       for(int i=0;i<n;i++)
       {
           cin >> ime;
           cin >> tipDevice;
           cin >> godina;
           Device tmp(ime,(tip)tipDevice,godina);
           try {
               t += tmp;
           }
           catch (InvalidProductionDate) {InvalidProductionDate().print();}
       }
       Device::setPocetniCasovi(3);
       MobileServis t2 = t;
       t2.pecatiCasovi();
   }


   return 0;


}
