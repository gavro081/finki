#include<iostream>
#include<cstring>


using namespace std;


//ова е место за вашиот код


char klasi[] = {'F', 'D','E', 'C', 'B','A'};


class Zichara{
   char *mesto;
   int cena;
public:
   Zichara(const char *mesto, int cena) : cena(cena){
       this->mesto = new char[strlen(mesto) + 1];
       strcpy(this->mesto, mesto);
   }


   ~Zichara(){
       delete[] mesto;
   }


   int getCena(){
       return cena;
   }
};


class PlaninarskiDom{
   char ime[15];
   int ceni[2]; // index 0 - letna sezona; 1 - zimska
   char klasa;
   bool daliZichara;
   Zichara *zichara;
public:
   PlaninarskiDom (const char *ime = nullptr, int *ceni = nullptr,
                   char klasa='0', bool daliZichara = false, Zichara *zichara = nullptr) :
           klasa(klasa), daliZichara(daliZichara) {
       if (ime)strcpy(this->ime, ime);
       if (ceni){
           this->ceni[0] = ceni[0];
           this->ceni[1] = ceni[1];
       }
       this->zichara = zichara;
   }


   ~PlaninarskiDom(){}


   void setZichara(Zichara &z) {
       daliZichara = true;
       zichara = &z;
   }


   PlaninarskiDom& operator--(){
       for (int i = 1; i < 6; ++i) {
           if (klasi[i] == klasa) {
               klasa = klasi[i-1];
               return *this;
           }
       }
       return *this;
   }


   bool operator<=(char znak){
       int ind1,ind2;
       for (int i = 0; i < 6; ++i) {
           if (klasa == klasi[i]) ind1 = i;
           if (znak == klasi[i]) ind2 = i;
       }
       return (ind1 <= ind2);
   }


   friend ostream& operator<<(ostream& COUT, PlaninarskiDom& ob){
       COUT << ob.ime << " klasa:" << ob.klasa;
       if (ob.daliZichara) COUT << " so Zichara";
       COUT << '\n';
       return COUT;
   }


   void presmetajDnevenPrestoj(int den, int mesec, int &cena){
       if (den < 0 || den > 31 || mesec < 0 || mesec > 12) throw 1;
       // od 1.4 do 1.9 letna sezona t.e. ceni[0]
       cena = (mesec >= 4 && mesec < 9) ? ceni[0] : ceni[1];
       if (daliZichara) cena += zichara->getCena();
   }


};


int main(){


   PlaninarskiDom p; //креирање на нов објект од класата планинарски дом


   //во следниот дел се вчитуваат информации за планинарскиот дом
   char imePlaninarskiDom[15],mestoZichara[30],klasa;
   int ceni[12];
   int dnevnakartaZichara;
   bool daliZichara;
   cin>>imePlaninarskiDom;
   for (int i=0;i<2;i++) cin>>ceni[i];
   cin>>klasa;
   cin>>daliZichara;


   //во следниот дел се внесуваат информации и за жичарата ако постои
   if (daliZichara) {
       cin>>mestoZichara>>dnevnakartaZichara;
       PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
       Zichara r(mestoZichara,dnevnakartaZichara);
       pom.setZichara(r);
       p=pom;
   }
   else{
       PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
       p=*pok;
   }


   //се намалува класата на планинарскиот дом за 2
   --p;
   --p;


   int cena;
   int den,mesec;
   cin>>den>>mesec;
   try{
       p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
       cout<<"Informacii za PlaninarskiDomot:"<<endl;
       cout<<p;
       if (p<='D')
           cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";


       cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
   }
   catch (int){
       cout<<"Mesecot ili denot e greshno vnesen!";
   }
}

