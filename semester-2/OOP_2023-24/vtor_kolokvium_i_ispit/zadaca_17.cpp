#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde
class FudbalskaEkipa{
protected:
   char name[100];
   char coach[100];
   int goals[10];
public:
   virtual int uspeh(){
       int sum = 0;
       for (int i = 0; i < 10; ++i) {
           sum += goals[i];
       }
       return sum;
   };
   bool operator>(FudbalskaEkipa& ob) {return uspeh() > ob.uspeh();}

   friend ostream& operator<<(ostream& COUT, FudbalskaEkipa& ob){
       COUT << ob.name << '\n' << ob.coach << '\n' << ob.uspeh() << '\n';
       return COUT;
   }

   FudbalskaEkipa& operator+=(int g){
       for (int i = 0; i < 9; ++i) {
           goals[i] = goals[i + 1];
       }
       goals[9] = g;
       return *this;
   }
};


class Klub : public FudbalskaEkipa{
   int titles;
public:
   Klub(char* coach, int goals[10], char* name, int titles)
   : titles(titles){
       strcpy(this->coach, coach);
       strcpy(this->name, name);
       for (int i = 0; i < 10; ++i) {
           this->goals[i] = goals[i];
       }
   }


   int uspeh()override{ return FudbalskaEkipa::uspeh() * 3 + titles * 1000; }
};


class Reprezentacija : public FudbalskaEkipa{
   int matches;
public:
   Reprezentacija(char* coach, int goals[10], char* name, int matches)
       : matches(matches){
       strcpy(this->coach, coach);
       strcpy(this->name, name);
       for (int i = 0; i < 10; ++i) {
           this->goals[i] = goals[i];
       }
   }
   int uspeh()override{ return FudbalskaEkipa::uspeh() * 3 + matches * 50; }
   friend ostream& operator<<(ostream& COUT, Reprezentacija& ob){
       COUT << ob.name << '\n' << ob.coach << '\n' << ob.uspeh() << '\n';
       return COUT;
   }
};


void najdobarTrener(FudbalskaEkipa** ekipi, int n){
   int maxi = 0;
   int maxuspeh = 0;
   for (int i = 0; i < n; ++i) {
       if (ekipi[i]->uspeh() > maxuspeh){
           maxi = i;
           maxuspeh = ekipi[i]->uspeh();
       }
   }
   cout << *ekipi[maxi];
}


int main() {
   int n;
   cin >> n;
   FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
   char coach[100];
   int goals[10];
   char x[100];
   int tg;
   for (int i = 0; i < n; ++i) {
       int type;
       cin >> type;
       cin.getline(coach, 100);
       cin.getline(coach, 100);
       for (int j = 0; j < 10; ++j) {
           cin >> goals[j];
       }
       cin.getline(x, 100);
       cin.getline(x, 100);
       cin >> tg;
       if (type == 0) {
           ekipi[i] = new Klub(coach, goals, x, tg);
       } else if (type == 1) {
           ekipi[i] = new Reprezentacija(coach, goals, x, tg);
       }
   }
   cout << "===== SITE EKIPI =====" << endl;
   for (int i = 0; i < n; ++i) {
       cout << *ekipi[i];
   }
   cout << "===== DODADI GOLOVI =====" << endl;
   for (int i = 0; i < n; ++i) {
       int p;
       cin >> p;
       cout << "dodavam golovi: " << p << endl;
       *ekipi[i] += p;
   }
   cout << "===== SITE EKIPI =====" << endl;
   for (int i = 0; i < n; ++i) {
       cout << *ekipi[i];
   }
   cout << "===== NAJDOBAR TRENER =====" << endl;
   najdobarTrener(ekipi, n);
   for (int i = 0; i < n; ++i) {
       delete ekipi[i];
   }
   delete[] ekipi;
   return 0;
}
