#include <iostream>
#include <cstring>


using namespace std;


enum Tip {LINUX, UNIX, WINDOWS};


class OperativenSistem{
   char *ime;
   float verzija;
   Tip tip;
   float golemina;
public:
   OperativenSistem(){}
   OperativenSistem(const char *ime, float verzija, Tip tip, float golemina)
           : verzija(verzija), tip(tip), golemina(golemina){
       this->ime = new char[strlen(ime) + 1];
       strcpy(this->ime, ime);
   }


   ~OperativenSistem(){
       delete [] ime;
   }


   OperativenSistem& operator=(const OperativenSistem& ob){
       delete [] ime;
       this->ime = new char[strlen(ob.ime)];
       strcpy(this->ime, ob.ime);
       this->verzija = ob.verzija;
       this->tip = ob.tip;
       this->golemina = ob.golemina;
       return *this;
   }


   void pecati(){
       cout << "Ime: " << ime << " Verzija: " << verzija <<
            " Tip: " << tip << " Golemina:" << golemina << "GB\n";
   }


   bool ednakviSe(const OperativenSistem &os){
       return (strcmp(ime,os.ime) == 0 && verzija == os.verzija
               && tip == os.tip && golemina == os.golemina);
   }


   int sporediVerzija(const OperativenSistem &os){
       if (verzija == os.verzija) return 0;
       if (verzija < os.verzija) return -1;
       else return 1;
   }


   bool istaFamilija(const OperativenSistem &sporedba){
       return (strcmp(ime,sporedba.ime) == 0 && tip == sporedba.tip);
   }
};


class Repozitorium{
   char ime[20];
   OperativenSistem *sistemi;
   int n;
public:
   Repozitorium(const char* ime){
       strcpy(this->ime, ime);
       sistemi = NULL;
       n = 0;
   }


   ~Repozitorium() {
       delete [] sistemi;
   }


   void pecatiOperativniSistemi(){
       cout << "Repozitorium: " << ime << '\n';
       for (int i = 0; i < n; ++i) {
           sistemi[i].pecati();
       }
   }


   void izbrishi(const OperativenSistem &operativenSistem){
       bool p = false;
       for (int i = 0; i < n; ++i) {
           if (sistemi[i].ednakviSe(operativenSistem)) p = true;
       }
       if (!p) return;


       OperativenSistem *tmp = new OperativenSistem[n - 1];
       int index = 0;
       for (int i = 0; i < n; ++i) {
           if (!sistemi[i].ednakviSe(operativenSistem)) {
               tmp[index++] = sistemi[i];
           }
       }
       delete [] sistemi;
       n--;
       sistemi = tmp;
   }


   void dodadi(const OperativenSistem &nov){
       for (int i = 0; i < n; ++i) {
           if (sistemi[i].istaFamilija(nov) && sistemi[i].sporediVerzija(nov) == -1){
               sistemi[i] = nov;
               return;
           }
       }


       OperativenSistem *tmp = new OperativenSistem[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = sistemi[i];
       }
       tmp[n++] = nov;
       delete [] sistemi;
       sistemi = tmp;
   }
};




int main() {
   char repoName[20];
   cin>>repoName;
   Repozitorium repozitorium=Repozitorium(repoName);
   int brojOperativniSistemi = 0;
   cin>>brojOperativniSistemi;
   char ime[20];
   float verzija;
   int tip;
   float golemina;
   for (int i = 0; i<brojOperativniSistemi; i++){
       cin>>ime;
       cin>>verzija;
       cin>>tip;
       cin>>golemina;
       OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
       repozitorium.dodadi(os);
   }


   repozitorium.pecatiOperativniSistemi();
   cin>>ime;
   cin>>verzija;
   cin>>tip;
   cin>>golemina;
   OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
   cout<<"=====Brishenje na operativen sistem====="<<endl;
   repozitorium.izbrishi(os);
   repozitorium.pecatiOperativniSistemi();
   return 0;
}
