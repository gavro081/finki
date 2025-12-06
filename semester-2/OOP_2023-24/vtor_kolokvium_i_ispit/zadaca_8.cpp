#include <iostream>
#include <cstring>


using namespace std;


class Koncert{
   char naziv[20];
   char lokacija[100];
   static double popust;
   double bilet;
public:
   Koncert(char *naziv, char *lokacija, double bilet) : bilet(bilet){
       strcpy(this->naziv, naziv);
       strcpy(this->lokacija, lokacija);
   }


   static void setSezonskiPopust(double p){popust = p;}
   static double getSezonskiPopust(){return popust;}


   virtual double cena(){
       return (bilet - bilet * popust );
   }


   char* getNaziv(){return naziv;}
};
double Koncert::popust = 0.2;


class ElektronskiKoncert : public Koncert{
   char *imeDJ;
   double vreme;
   bool daliDnevna;
public:
   ElektronskiKoncert(char *naziv, char *lokacija, double bilet, char* imeDJ, double vreme, bool daliDnevna)
           : Koncert(naziv,lokacija,bilet), vreme(vreme), daliDnevna(daliDnevna){
       this->imeDJ = new char[strlen(imeDJ) + 1];
       strcpy(this->imeDJ, imeDJ);
   }


   double cena()override{
       double c = Koncert::cena();
       if (vreme >= 7) c += 360;
       else if (vreme > 5) c += 150;
       if (daliDnevna) c -= 50;
       else c += 100;
       return c;
   }
};


void najskapKoncert(Koncert **koncerti, int n){
   Koncert *najskap = koncerti[0];
   int ctr = 0;
   for (int i = 0; i < n; ++i) {
       if (koncerti[i]->cena() > najskap->cena()) najskap = koncerti[i];


       ElektronskiKoncert* ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
       if (ek) ctr++;
   }
   cout << "Najskap koncert: " << najskap->getNaziv() << " " << najskap->cena() << '\n';
   cout << "Elektronski koncerti: " << ctr << " od vkupno " << n << "\n";
}


bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
   for (int i = 0; i < n; ++i) {
       if (!elektronski && strcmp(koncerti[i]->getNaziv(),naziv) == 0) {
           cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << '\n';
           return true;
       }
       if (elektronski){
           ElektronskiKoncert* ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
           if (ek && strcmp(ek->getNaziv(), naziv) == 0) {
               cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << '\n';
               return true;
           }
       }
   }
   return false;
}


int main(){


   int tip,n,novaCena;
   char naziv[100], lokacija[100], imeDJ[40];
   bool dnevna;
   float cenaBilet, novPopust;
   float casovi;


   cin>>tip;
   if (tip==1){//Koncert
       cin>>naziv>>lokacija>>cenaBilet;
       Koncert k1(naziv,lokacija,cenaBilet);
       cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
   }
   else if (tip==2){//cena - Koncert
       cin>>naziv>>lokacija>>cenaBilet;
       Koncert k1(naziv,lokacija,cenaBilet);
       cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
   }
   else if (tip==3){//ElektronskiKoncert
       cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
       ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
       cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
   }
   else if (tip==4){//cena - ElektronskiKoncert
       cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
       ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
       cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
   }
   else if (tip==5) {//najskapKoncert


   }
   else if (tip==6) {//prebarajKoncert
       Koncert ** koncerti = new Koncert *[5];
       int n;
       koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
       koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
       koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
       koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
       koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
       char naziv[100];
       najskapKoncert(koncerti,5);
   }
   else if (tip==7){//prebaraj
       Koncert ** koncerti = new Koncert *[5];
       int n;
       koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
       koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
       koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
       koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
       koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
       char naziv[100];
       bool elektronski;
       cin>>elektronski;
       if(prebarajKoncert(koncerti,5, "Area",elektronski))
           cout<<"Pronajden"<<endl;
       else cout<<"Ne e pronajden"<<endl;


       if(prebarajKoncert(koncerti,5, "Area",!elektronski))
           cout<<"Pronajden"<<endl;
       else cout<<"Ne e pronajden"<<endl;


   }
   else if (tip==8){//smeni cena
       Koncert ** koncerti = new Koncert *[5];
       int n;
       koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
       koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
       koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
       koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
       koncerti[2] -> setSezonskiPopust(0.9);
       najskapKoncert(koncerti,4);
   }


   return 0;
}
