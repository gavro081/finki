#include<iostream>
#include<string.h>
using namespace std;


class Karticka{
protected:
   char smetka[16];
   int pin;
   bool povekjePin;
public:
   Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
   }
   // дополниете ја класата
   virtual int tezinaProbivanje(){
       int ctr = 0;
       int tmp = pin;
       while (tmp > 0){
           tmp /= 10;
           ctr++;
       }
       return ctr;
   }


   friend ostream& operator<<(ostream& COUT, Karticka& ob){
       COUT << ob.smetka << ": " << ob.tezinaProbivanje() << "\n";
       int a = ob.tezinaProbivanje();
       return COUT;
   }




   bool getDopolnitelenPin(){return povekjePin;}


   char* getSmetka(){return smetka;}


};


class OutOfBoundException{
public:
   void print(){
       cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto\n";
   }
};
//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka : public Karticka {
   int *pinovi = nullptr;
   int n = 0;
   static int p;
public:
   SpecijalnaKarticka(char *smetka, int pin)
           : Karticka(smetka, pin) {
       povekjePin = true;
   }


   int tezinaProbivanje()override{
       return (Karticka::tezinaProbivanje() + n);
   }


   friend ostream& operator<<(ostream& COUT, SpecijalnaKarticka& ob){
       COUT << ob.smetka << ": " << ob.tezinaProbivanje() << "\n";
       return COUT;
   }


   SpecijalnaKarticka& operator+=(int pin){
       if (n > 5) throw OutOfBoundException();
       int *tmp = new int[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = pinovi[i];
       }
       tmp[n++] = pin;
       pinovi = tmp;
       return *this;
   }


};
int SpecijalnaKarticka::p = 4;




class Banka {
private:
   char naziv[30];
   Karticka *karticki[20];
   int broj;
   static int LIMIT;
public:
   Banka(char *naziv, Karticka** karticki,int broj ){
       strcpy(this->naziv,naziv);
       for (int i=0;i<broj;i++){
           //ako kartickata ima dopolnitelni pin kodovi
           if (karticki[i]->getDopolnitelenPin()){
               this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
           }
           else this->karticki[i]=new Karticka(*karticki[i]);
       }
       this->broj=broj;
   }
   ~Banka(){
       for (int i=0;i<broj;i++) delete karticki[i];
   }


   //да се дополни класата
   static void setLIMIT(int l){LIMIT = l;}


   void pecatiKarticki(){
       cout << "Vo bankata " << naziv << " moze da se probijat kartickite:\n";
       for (int i = 0; i < broj; ++i) {
           if (karticki[i]->tezinaProbivanje() <= LIMIT)
               cout << *karticki[i];
       }
   }


   void dodadiDopolnitelenPin(char *smetka, int novPin) {
       for (int i = 0; i < broj; ++i) {
           if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
               SpecijalnaKarticka *ptr = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
               if (ptr) {
                   *ptr += novPin;
               }
           }
       }
   }
};
int Banka::LIMIT = 7;






int main(){


   Karticka **niza;
   int n,m,pin;
   char smetka[16];
   bool daliDopolnitelniPin;
   cin>>n;
   niza=new Karticka*[n];
   for (int i=0;i<n;i++){
       cin>>smetka;
       cin>>pin;
       cin>>daliDopolnitelniPin;
       if (!daliDopolnitelniPin)
           niza[i]=new Karticka(smetka,pin);
       else
           niza[i]=new SpecijalnaKarticka(smetka,pin);
   }


   Banka komercijalna("Komercijalna",niza,n);
   for (int i=0;i<n;i++) delete niza[i];
   delete [] niza;
   cin>>m;
   for (int i=0;i<m;i++){
       cin>>smetka>>pin;


       try{
           komercijalna.dodadiDopolnitelenPin(smetka,pin);
       }
       catch (OutOfBoundException){
           OutOfBoundException().print();
       }


   }


   Banka::setLIMIT(5);


   komercijalna.pecatiKarticki();


}
