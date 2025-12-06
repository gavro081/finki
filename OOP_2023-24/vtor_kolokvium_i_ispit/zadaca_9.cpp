#include <iostream>
#include <cstring>


using namespace std;


class Trud{
   char vid;
   int god;
public:
   Trud(char vid='X', int god=0) : vid(vid), god(god){}


   char getVid(){return vid;}
   int getGod(){return god;}


   friend istream& operator>>(istream& CIN, Trud& ob){
       CIN >> ob.vid >> ob.god;
       return CIN;
   }
};


class Student{
   char ime[30];
   int indeks;
   int god_upis;
   int *oceni;
   int n;
public:
   Student(char *ime, int indeks, int god_upis, int *oceni, int n)
           : indeks(indeks), god_upis(god_upis), n(n){
       strcpy(this->ime, ime);
       this->oceni = new int[n];
       for (int i = 0; i < n; ++i) {
           this->oceni[i] = oceni[i];
       }
   }


   int getGod(){return god_upis;}


   virtual double rang(){
       int sum = 0;
       for (int i = 0; i < n; ++i) {
           sum += oceni[i];
       }
       return (double)sum / n;
   }


   friend ostream& operator<<(ostream& COUT, Student& ob){
       COUT << ob.indeks << " " << ob.ime << " " << ob.god_upis << " " << ob.rang() << '\n';
       return COUT;
   }


   int getIndeks(){return indeks;}
};


class Exception{
public:
   void print(){cout << "Ne moze da se vnese dadeniot trud\n";}
};




class PhDStudent : public Student{
   Trud* trudovi;
   int m;
   static int trudC;
   static int trudJ;
public:
   PhDStudent(char *ime, int indeks, int god_upis, int *oceni, int n, Trud *trudovi, int m)
           : Student(ime, indeks, god_upis, oceni, n) {
       int ctr = 0;
       for (int i = 0; i < m; ++i) {
           if (trudovi[i].getGod() < god_upis) Exception().print();
           else ctr++;
       }
       this->m = ctr;
       this->trudovi = new Trud[ctr];


       int j = 0;


       for (int i = 0; i < m; ++i) {
           if (trudovi[i].getGod() >= god_upis) this->trudovi[j++] = trudovi[i];
       }




   }


   static void setTrudC(int a){trudC = a;}
   static void setTrudJ(int a){trudJ = a;}


   double rang()override{
       double r = Student::rang();
       for (int i = 0; i < m; ++i) {
           r += (trudovi[i].getVid() == 'c' || trudovi[i].getVid() == 'C') ? trudC : trudJ;
       }
       return r;
   }


   PhDStudent& operator+= (Trud& t){
       if (t.getGod() < this->getGod()) throw Exception();
       Trud* tmp = new Trud[m + 1];
       for (int i = 0; i < m; ++i) {
           tmp[i] = trudovi[i];
       }
       tmp[m++] = t;
       trudovi = tmp;
       return *this;
   }
};
int PhDStudent::trudC = 1;
int PhDStudent::trudJ = 3;


int main(){
   int testCase;
   cin >> testCase;


   int god, indeks, n, god_tr, m, n_tr;
   int izbor; //0 za Student, 1 za PhDStudent
   char ime[30];
   int oceni[50];
   char tip;
   Trud trud[50];


   if (testCase == 1){
       cout << "===== Testiranje na klasite ======" << endl;
       cin >> ime;
       cin >> indeks;
       cin >> god;
       cin >> n;
       for (int j = 0; j < n; j++)
           cin >> oceni[j];
       Student s(ime, indeks, god, oceni, n);
       cout << s;


       cin >> ime;
       cin >> indeks;
       cin >> god;
       cin >> n;
       for (int j = 0; j < n; j++)
           cin >> oceni[j];
       cin >> n_tr;
       for (int j = 0; j < n_tr; j++){
           cin >> tip;
           cin >> god_tr;
           Trud t(tip, god_tr);
           trud[j] = t;
       }
       PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
       cout << phd;
   }
   if (testCase == 2){
       cout << "===== Testiranje na operatorot += ======" << endl;
       Student **niza;
       cin >> m;
       niza = new Student *[m];
       for (int i = 0; i<m; i++){
           cin >> izbor;
           cin >> ime;
           cin >> indeks;
           cin >> god;
           cin >> n;
           for (int j = 0; j < n; j++)
               cin >> oceni[j];


           if (izbor == 0){
               niza[i] = new Student(ime, indeks, god, oceni, n);
           }
           else{
               cin >> n_tr;
               for (int j = 0; j < n_tr; j++){
                   cin >> tip;
                   cin >> god_tr;
                   Trud t(tip, god_tr);
                   trud[j] = t;
               }
               niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
           }
       }
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];


       // dodavanje nov trud za PhD student spored indeks
       Trud t;
       cin >> indeks;
       cin >> t;


       // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
       bool p = false;
       for (int i = 0; i < m; ++i) {
           PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
           if (phd){
               try {
                   if (phd->getIndeks() == indeks) {
                       *phd += t;
                       p = true;
                   }
               }
               catch (Exception) {Exception().print();}
           }
       }
       if (!p) cout << "Ne postoi PhD student so indeks " << indeks << '\n';
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];
   }
   if (testCase == 3){
       cout << "===== Testiranje na operatorot += ======" << endl;
       Student **niza;
       cin >> m;
       niza = new Student *[m];
       for (int i = 0; i<m; i++){
           cin >> izbor;
           cin >> ime;
           cin >> indeks;
           cin >> god;
           cin >> n;
           for (int j = 0; j < n; j++)
               cin >> oceni[j];


           if (izbor == 0){
               niza[i] = new Student(ime, indeks, god, oceni, n);
           }
           else{
               cin >> n_tr;
               for (int j = 0; j < n_tr; j++){
                   cin >> tip;
                   cin >> god_tr;
                   Trud t(tip, god_tr);
                   trud[j] = t;
               }
               niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
           }
       }
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];


       // dodavanje nov trud za PhD student spored indeks
       Trud t;
       cin >> indeks;
       cin >> t;


       // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
       bool p = false;
       for (int i = 0; i < m; ++i) {
           PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
           if (phd){
               try {
                   if (phd->getIndeks() == indeks) {
                       *phd += t;
                       p = true;
                   }
               }
               catch (Exception) {Exception().print();}
           }
       }
       if (!p) cout << "Ne postoi student so indeks " << indeks << '\n';


       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];
   }
   if (testCase == 4){
       cout << "===== Testiranje na isklucoci ======" << endl;
       cin >> ime;
       cin >> indeks;
       cin >> god;
       cin >> n;
       for (int j = 0; j < n; j++)
           cin >> oceni[j];
       cin >> n_tr;
       for (int j = 0; j < n_tr; j++){
           cin >> tip;
           cin >> god_tr;
           Trud t(tip, god_tr);
           trud[j] = t;
       }
       PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
       cout << phd;
   }
   if (testCase == 5){
       cout << "===== Testiranje na isklucoci ======" << endl;
       Student **niza;
       cin >> m;
       niza = new Student *[m];
       for (int i = 0; i<m; i++){
           cin >> izbor;
           cin >> ime;
           cin >> indeks;
           cin >> god;
           cin >> n;
           for (int j = 0; j < n; j++)
               cin >> oceni[j];


           if (izbor == 0){
               niza[i] = new Student(ime, indeks, god, oceni, n);
           }
           else{
               cin >> n_tr;
               for (int j = 0; j < n_tr; j++){
                   cin >> tip;
                   cin >> god_tr;
                   Trud t(tip, god_tr);
                   trud[j] = t;
               }
               niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
           }
       }
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];


       // dodavanje nov trud za PhD student spored indeks
       Trud t;
       cin >> indeks;
       cin >> t;


       // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
       for (int i = 0; i < m; ++i) {
           PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
           if (phd){
               try {
                   if (phd->getIndeks() == indeks) {
                       *phd += t;
                   }
               }
               catch (Exception) {Exception().print();}
           }
       }
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];
   }
   if (testCase == 6){
       cout << "===== Testiranje na static clenovi ======" << endl;
       Student **niza;
       cin >> m;
       niza = new Student *[m];
       for (int i = 0; i<m; i++){
           cin >> izbor;
           cin >> ime;
           cin >> indeks;
           cin >> god;
           cin >> n;
           for (int j = 0; j < n; j++)
               cin >> oceni[j];


           if (izbor == 0){
               niza[i] = new Student(ime, indeks, god, oceni, n);
           }
           else{
               cin >> n_tr;
               for (int j = 0; j < n_tr; j++){
                   cin >> tip;
                   cin >> god_tr;
                   Trud t(tip, god_tr);
                   trud[j] = t;
               }
               niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
           }
       }
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];


       int conf, journal;
       cin >> conf;
       cin >> journal;


       //postavete gi soodvetnite vrednosti za statickite promenlivi
       PhDStudent::setTrudC(conf);
       PhDStudent::setTrudJ(journal);
       // pecatenje na site studenti
       cout << "\nLista na site studenti:\n";
       for (int i = 0; i < m; i++)
           cout << *niza[i];
   }


   return 0;
}
