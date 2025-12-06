#include<iostream>
#include<string.h>
using namespace std;


//место за вашиот код
class Delo{
   char ime[50];
   int god;
   char zemja[50];
public:
   Delo(){}
   Delo(char *ime, int god, char* zemja) : god(god){
       strcpy(this->ime,ime);
       strcpy(this->zemja,zemja);
   }


   int getGod(){return god;}
   char* getZemja(){return zemja;}
   char* getIme(){return ime;}


   bool operator==(Delo& d){
       return strcmp(this->ime, d.ime) == 0;
   }
};


class Pretstava{
protected:
   Delo delo;
   int karti;
   char data[15];
public:
   Pretstava(Delo delo, int karti, char* data): karti(karti){
       this->delo = delo;
       strcpy(this->data,data);
   }
   int getKarti(){return karti;}
   virtual int cena(){
       int c = 0;
       if (delo.getGod() >= 1900) c += 50;
       else if (delo.getGod() >= 1800) c += 75;
       else c += 100;


       if (strcmp(delo.getZemja(),"Italija") == 0) c += 100;
       else if (strcmp(delo.getZemja(),"Rusija") == 0) c += 150;
       else c += 80;


       return c;
   }


   Delo getDelo(){return delo;}
};


class Opera : public Pretstava{
public:
   Opera(Delo delo, int karti, char* data) : Pretstava(delo,karti,data){}


   using Pretstava::cena;
};


class Balet : public Pretstava{
   static int cenaplus;
public:
   Balet(Delo delo, int karti, char* data) : Pretstava(delo,karti,data){}


   static void setCenaBalet(int c){cenaplus = c;}


   int cena()override{
       return Pretstava::cena() + cenaplus;
   }


};
int Balet::cenaplus = 150;
int prihod(Pretstava** pretstavi, int n){
   int suma = 0;
   for (int i = 0; i < n; ++i) {
       suma += pretstavi[i]->cena() * pretstavi[i]->getKarti();
   }
   return suma;
}


int brojPretstaviNaDelo(Pretstava** pretstavi, int n, Delo& d) {
   int ctr = 0;
   for (int i = 0; i < n; ++i) {
       if (pretstavi[i]->getDelo() == d) ctr++;
   }
   return ctr;
}


//citanje na delo
Delo readDelo(){
   char ime[50];
   int godina;
   char zemja[50];
   cin>>ime>>godina>>zemja;
   return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
   int tip; //0 za Balet , 1 za Opera
   cin>>tip;
   Delo d=readDelo();
   int brojProdadeni;
   char data[15];
   cin>>brojProdadeni>>data;
   if (tip==0)  return new Balet(d,brojProdadeni,data);
   else return new Opera(d,brojProdadeni,data);
}


int main(){
   int test_case;
   cin>>test_case;


   switch(test_case){
       case 1:
           //Testiranje na klasite Opera i Balet
       {
           cout<<"======TEST CASE 1======="<<endl;
           Pretstava* p1=readPretstava();
           cout<<p1->getDelo().getIme()<<endl;
           Pretstava* p2=readPretstava();
           cout<<p2->getDelo().getIme()<<endl;
       }break;


       case 2:
           //Testiranje na  klasite Opera i Balet so cena
       {
           cout<<"======TEST CASE 2======="<<endl;
           Pretstava* p1=readPretstava();
           cout<<p1->cena()<<endl;
           Pretstava* p2=readPretstava();
           cout<<p2->cena()<<endl;
       }break;


       case 3:
           //Testiranje na operator ==
       {
           cout<<"======TEST CASE 3======="<<endl;
           Delo f1=readDelo();
           Delo f2=readDelo();
           Delo f3=readDelo();


           if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
           if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;


       }break;


       case 4:
           //testiranje na funkcijata prihod
       {
           cout<<"======TEST CASE 4======="<<endl;
           int n;
           cin>>n;
           Pretstava **pole=new Pretstava*[n];
           for (int i=0;i<n;i++){
               pole[i]=readPretstava();


           }
           cout<<prihod(pole,n);
       }break;


       case 5:
           //testiranje na prihod so izmena na cena za 3d proekcii
       {
           cout<<"======TEST CASE 5======="<<endl;
           int cenaBalet;
           cin>>cenaBalet;
           Balet::setCenaBalet(cenaBalet);
           int n;
           cin>>n;
           Pretstava **pole=new Pretstava*[n];
           for (int i=0;i<n;i++){
               pole[i]=readPretstava();
           }
           cout<<prihod(pole,n);
       }break;


       case 6:
           //testiranje na brojPretstaviNaDelo
       {
           cout<<"======TEST CASE 6======="<<endl;
           int n;
           cin>>n;
           Pretstava **pole=new Pretstava*[n];
           for (int i=0;i<n;i++){
               pole[i]=readPretstava();
           }
           Delo f=readDelo();
           cout<<brojPretstaviNaDelo(pole,n,f);
       }break;
   };
   return 0;
}
