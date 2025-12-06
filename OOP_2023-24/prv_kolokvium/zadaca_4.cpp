#include<iostream>
#include<cstring>


using namespace std;


class Patnik{
private:
   char name[100];
   int klasa;
   bool bike;
public:
   Patnik(){}


   Patnik (const char *name, int klasa, bool bike) : klasa(klasa), bike(bike){
       strcpy(this->name, name);
   }


   friend ostream& operator<<(ostream& COUT, Patnik& ob) {
       COUT << ob.name << '\n';
       COUT << ob.klasa << '\n';
       COUT << ob.bike << '\n';
       return COUT;
   }


   bool getBike()const{return bike;}
   int getKlasa(){return klasa;}
};


class Voz{
private:
   char destination[100];
   Patnik* travelers;
   int n;
   int allowedBikes;
public:
   Voz(char *destination, int allowedBikes) : allowedBikes(allowedBikes){
       strcpy(this->destination, destination);
       n = 0;
       travelers = NULL;
   }


   Voz(){
	delete [] travelers;
   }


   Voz& operator+=(const Patnik& ob){
       if (ob.getBike() && allowedBikes <= 0) return *this;
       Patnik *tmp = new Patnik[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = travelers[i];
       }
       tmp[n++] = ob;
       travelers = tmp;
       return *this;
   }


   friend ostream& operator<<(ostream& COUT, Voz& ob){
       COUT << ob.destination << '\n';
       for (int i = 0; i < ob.n; ++i) {
           COUT << ob.travelers[i] << '\n';
       }
       return COUT;
   }


   void patniciNemaMesto(){
      int ctrFc, ctrSc;
      int leftFc, leftSc;
      ctrFc = ctrSc = 0;
       for (int i = 0; i < n; ++i) {
           if (travelers[i].getKlasa() == 1 && travelers[i].getBike()) ctrFc++;
           else if (travelers[i].getBike()) ctrSc++;
       }
       if (allowedBikes < ctrFc) {
           leftFc = ctrFc - allowedBikes;
           leftSc = ctrSc;
       }
       else {
           leftFc = 0;
           allowedBikes -= ctrFc;
           if (allowedBikes < ctrSc) {
               leftSc = ctrSc - allowedBikes;
           }
           else leftSc = 0;
       }
       cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << leftFc << '\n';
       cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << leftSc << '\n';
   }
};


f
int main()
{
   Patnik p;
   char ime[100], destinacija[100];
   int n;
   bool velosiped;
   int klasa;
   int maxv;
   cin >> destinacija >> maxv;
   cin >> n;
   Voz v(destinacija, maxv);
   //cout<<v<<endl;
   for (int i = 0; i < n; i++){
       cin >> ime >> klasa >> velosiped;
       Patnik p(ime, klasa, velosiped);
       //cout<<p<<endl;
       v += p;
   }
   cout << v;
   v.patniciNemaMesto();


   return 0;
}
