#include<iostream>
#include<cstring>
using namespace std;


class StudentKurs{
protected:
   char ime[30];
   int ocenka;
   bool daliUsno;
   static unsigned int MAX;
   static int MINOCENKA;
public:
   StudentKurs(char* ime,int finalenIspit){
       strcpy(this->ime,ime);
       this->ocenka=finalenIspit;
       this->daliUsno=false;
   }
   //дополни ја класата
   static void setMAX(int a){MAX = a;}


   virtual int getocenka(){return ocenka;}


   friend ostream& operator<<(ostream& COUT, StudentKurs& ob){
       COUT << ob.ime << " --- " << ob.getocenka() << '\n';
       return COUT;
   }


   bool getDaliUsno(){return daliUsno;}
   static int getMINOCENKA(){return MINOCENKA;}
   char *getIme(){return ime;}
};
unsigned int StudentKurs::MAX = 10;
int StudentKurs::MINOCENKA = 6;


//вметни го кодот за StudentKursUsno
class BadInputException{
public:
   void print(){
       cout << "Greshna opisna ocenka\n";
   }
};


char* smenistring(char* c){
   int ctr = 0;
   for (int i = 0; i < strlen(c) + 1; ++i) {
       if (isalpha(c[i])) ctr++;
   }
   char* newstring = new char[ctr + 1];
   int j = 0;
   for (int i = 0; i < strlen(c) + 1; ++i) {
       if (isalpha(c[i])) newstring[j++] = c[i];
   }
   newstring[ctr] = '\0';
   return newstring;
}


class StudentKursUsno : public StudentKurs{
   char *opisna;
public:
   StudentKursUsno(char* ime,int finalenIspit)
   : StudentKurs(ime,finalenIspit){
       opisna = "";
       daliUsno = true;
   }
//    ~StudentKursUsno(){delete [] opisna;}


   int getocenka()override{
       int o = ocenka;
       if (strcmp(opisna,"odlicen") == 0){ o += 2; }
       else if (strcmp(opisna,"dobro") == 0){ o += 1; }
       else if (strcmp(opisna,"losho") == 0){ o -= 1; }
       if (o > MAX) o = MAX;
       return o;
   }


   friend ostream& operator<<(ostream& COUT, StudentKursUsno& ob){
       COUT << ob.ime << " --- " << ob.getocenka();
       return COUT;
   }


   StudentKursUsno& operator+=(char* o){
       for (int i = 0; i < strlen(o); ++i) {
           if (!isalpha(o[i])) throw BadInputException();
       }
       this->opisna = new char[strlen(o) + 1];
       strcpy(this->opisna, o);
       return *this;
   }


   void setOpisnaOcenka(char *o){
       try {
           *this += o;
       }
       catch (BadInputException) {
           BadInputException().print();
//            *this += smenistring(o);
               this->setOpisnaOcenka(smenistring(o));
       }
   }
};




class KursFakultet{
private:
   char naziv[30];
   StudentKurs *studenti[20];
   int broj;


public:
   KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
       strcpy(this->naziv,naziv);
       for (int i=0;i<broj;i++){
           //ako studentot ima usno isprashuvanje
           if (studenti[i]->getDaliUsno()){
               this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
           }
           else this->studenti[i]=new StudentKurs(*studenti[i]);
       }
       this->broj=broj;
   }
   ~KursFakultet(){
       for (int i=0;i<broj;i++) delete studenti[i];
   }


   //дополни ја класата
   void pecatiStudenti(){
       cout << "Kursot " << naziv << " go polozile:\n";
       for (int i = 0; i < broj; ++i) {
           if (studenti[i]->getocenka() >= StudentKurs::getMINOCENKA())
               cout << *studenti[i];
       }
   }


   void postaviOpisnaOcenka(char *ime, char *opisnaOcenka){
       for (int i = 0; i < broj; ++i) {
           if (strcmp(studenti[i]->getIme(),ime) == 0 && studenti[i]->getDaliUsno()){
               StudentKursUsno* ptr = dynamic_cast<StudentKursUsno*>(studenti[i]);
               if (ptr)
                   ptr->setOpisnaOcenka(opisnaOcenka);
           }
       }
   }
};


int main(){


   StudentKurs **niza;
   int n,m,ocenka;
   char ime[30],opisna[10];
   bool daliUsno;
   cin>>n;
   niza=new StudentKurs*[n];
   for (int i=0;i<n;i++){
       cin>>ime;
       cin>>ocenka;
       cin>>daliUsno;
       if (!daliUsno)
           niza[i]=new StudentKurs(ime,ocenka);
       else
           niza[i]=new StudentKursUsno(ime,ocenka);
   }


   KursFakultet programiranje("OOP",niza,n);
   for (int i=0;i<n;i++) delete niza[i];
   delete [] niza;
   cin>>m;


   for (int i=0;i<m;i++){
       cin>>ime>>opisna;
       programiranje.postaviOpisnaOcenka(ime,opisna);
   }


   StudentKurs::setMAX(9);


   programiranje.pecatiStudenti();


}
