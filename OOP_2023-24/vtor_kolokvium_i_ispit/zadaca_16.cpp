// вашиот код треба да биде тука
#include <iostream>
#include <cstring>


using namespace std;


class Transport{
protected:
   char destinacija[50];
   int cena, rastojanie;
public:
   Transport(char* destinacija, int cena, int rastojanie)
   : cena(cena), rastojanie(rastojanie){
       strcpy(this->destinacija, destinacija);
   }


   virtual float cenaTransport(){return cena;}
   virtual void pecati(){
       cout << destinacija << " " << rastojanie << " " << cenaTransport() << '\n';
   }
};


class AvtomobilTransport : public Transport{
   bool sofer;
public:
   AvtomobilTransport(char* destinacija, int cena, int rastojanie, bool sofer)
   : Transport(destinacija, cena, rastojanie), sofer(sofer){}


   float cenaTransport()override{
       return ((sofer) ? 1.2 * cena : cena);
   }
};


class KombeTransport : public Transport{
   int luge;
public:
   KombeTransport(char* destinacija, int cena, int rastojanie, int luge)
   : Transport(destinacija, cena, rastojanie), luge(luge){}


   float cenaTransport()override{
       float c = cena - luge * 200;
       if (c < 0) return 0; else return c;
   }


};


void pecatiPoloshiPonudi(Transport** ponudi, int n, Transport& T){
   for (int i = 0; i < n; ++i) {
       for (int j = i; j < n; ++j) {
           if (ponudi[i]->cenaTransport() > ponudi[j]->cenaTransport()){
               swap(ponudi[i],ponudi[j]);
           }
       }
   }
   for (int i = 0; i < n; ++i) {
       if (ponudi[i]->cenaTransport() > T.cenaTransport())
           ponudi[i]->pecati();
   }
}


int main(){


   char destinacija[20];
   int tip,cena,rastojanie,lugje;
   bool shofer;
   int n;
   cin>>n;
   Transport  **ponudi;
   ponudi=new Transport *[n];


   for (int i=0;i<n;i++){


       cin>>tip>>destinacija>>cena>>rastojanie;
       if (tip==1) {
           cin>>shofer;
           ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);


       }
       else {
           cin>>lugje;
           ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
       }




   }


   AvtomobilTransport nov("Ohrid",2000,600,false);
   pecatiPoloshiPonudi(ponudi,n,nov);


   for (int i=0;i<n;i++) delete ponudi[i];
   delete [] ponudi;
   return 0;
}
