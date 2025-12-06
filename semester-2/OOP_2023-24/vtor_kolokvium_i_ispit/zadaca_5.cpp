#include <iostream>
#include <cstring>


#define MAX 50
using namespace std;


class UserExistsException {
public:
   void print() {
       cout << "The user already exists in the list!\n";
   }
};


const char *kupuvaci[] = {"standard", "loyal", "vip"};
enum typeC {
   standardni,
   lojalni,
   vip
};


class Customer {
   char ime[50];
   char adresa[50];
   typeC vid;
   static int osn_popust;
   static int dop_popust;
   int kupeni;
public:
   Customer() {}


   Customer(char *ime, char *adresa, typeC vid, int kupeni) {
       strcpy(this->ime, ime);
       strcpy(this->adresa, adresa);
       this->vid = vid;
       this->kupeni = kupeni;
   }


   static void setDiscount1(int num) { osn_popust = num; }


   int najdiPopust() {
       if (vid == 0) return 0;
       if (vid == 1) return osn_popust;
       if (vid == 2) return osn_popust + dop_popust;
       return -1;
   }


   friend ostream &operator<<(ostream &out, Customer &ob) {
       out << ob.ime << '\n' << ob.adresa << '\n' << ob.kupeni <<
           '\n' << kupuvaci[ob.vid] << ' ' << ob.najdiPopust() << "\n";
       return out;
   }


   int getKupeni(){return kupeni;}
   typeC getVid(){return vid;}
   void setVid(int a) {vid = typeC(a);}
   char* getAdresa () { return adresa;}
};


int Customer::osn_popust = 10;
int Customer::dop_popust = 20;


class FINKI_bookstore {
   Customer *customers;
   int n;
public:
   FINKI_bookstore() {
       customers = nullptr;
       n = 0;
   }


   void setCustomers(Customer* customers, int n){
       this->customers = new Customer[n];
       for (int i = 0; i < n; ++i) {
           this->customers[i] = customers[i];
       }
       this->n = n;
   }


   FINKI_bookstore &operator+=(Customer &ob) {
       Customer *temp = new Customer[n + 1];
       for (int i = 0; i < n; ++i) {
           if (strcmp(customers[i].getAdresa(),ob.getAdresa())==0) throw UserExistsException();
           temp[i] = customers[i];
       }
       temp[n++] = ob;
       delete [] customers;
       customers = temp;
       return *this;
   }


   void update(){
       for (int i = 0; i < n; ++i) {
           if (customers[i].getKupeni() > 5 && customers[i].getVid() == 0)
               customers[i].setVid(1);
           else if (customers[i].getKupeni() > 10 && customers[i].getVid() == 1)
               customers[i].setVid(2);
       }
   }


   friend ostream& operator<<(ostream &out,FINKI_bookstore& ob){
       for (int i = 0; i < ob.n; ++i) {
           out << ob.customers[i];
       }
       out << '\n';
       return out;
   }


};


int main() {
   int testCase;
   cin >> testCase;


   char name[MAX];
   char email[MAX];
   int tC;
   int discount;
   int numProducts;




   if (testCase == 1){
       cout << "===== Test Case - Customer Class ======" << endl;
       cin.get();
       cin.getline(name,MAX);
       cin.getline(email,MAX);
       cin >> tC;
       cin >> numProducts;
       cout << "===== CONSTRUCTOR ======" << endl;
       Customer c(name, email, (typeC) tC, numProducts);
       cout << c;


   }


   if (testCase == 2){
       cout << "===== Test Case - Static Members ======" << endl;
       cin.get();
       cin.getline(name,MAX);
       cin.getline(email,MAX);
       cin >> tC;
       cin >> numProducts;
       cout << "===== CONSTRUCTOR ======" << endl;
       Customer c(name, email, (typeC) tC, numProducts);
       cout << c;


       c.setDiscount1(5);


       cout << c;
   }


   if (testCase == 3){
       cout << "===== Test Case - FINKI-bookstore ======" << endl;
       FINKI_bookstore fc;
       int n;
       cin >> n;
       Customer customers[MAX];
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,MAX);
           cin.getline(email,MAX);
           cin >> tC;
           cin >> numProducts;
           Customer c(name, email, (typeC) tC, numProducts);
           customers[i] = c;
       }


       fc.setCustomers(customers, n);


       cout << fc <<endl;
   }


   if (testCase == 4){
       cout << "===== Test Case - operator+= ======" << endl;
       FINKI_bookstore fc;
       int n;
       cin >> n;
       Customer customers[MAX];
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,MAX);
           cin.getline(email,MAX);
           cin >> tC;
           cin >> numProducts;
           Customer c(name, email, (typeC) tC, numProducts);
           customers[i] = c;
       }


       fc.setCustomers(customers, n);
       cout << "OPERATOR +=" << endl;
       cin.get();
       cin.getline(name,MAX);
       cin.getline(email,MAX);
       cin >> tC;
       cin >> numProducts;
       Customer c(name, email, (typeC) tC, numProducts);
       try {
           fc += c;
       }
       catch (UserExistsException) {
           UserExistsException().print();
       }
       cout << fc;
   }


   if (testCase == 5){
       cout << "===== Test Case - operator+= (exception) ======" << endl;
       FINKI_bookstore fc;
       int n;
       cin >> n;
       Customer customers[MAX];
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,MAX);
           cin.getline(email,MAX);
           cin >> tC;
           cin >> numProducts;
           Customer c(name, email, (typeC) tC, numProducts);
           customers[i] = c;
       }


       fc.setCustomers(customers, n);
       cout << "OPERATOR +=" << endl;
       cin.get();
       cin.getline(name,MAX);
       cin.getline(email,MAX);
       cin >> tC;
       cin >> numProducts;
       Customer c(name, email, (typeC) tC, numProducts);
       try {
           fc += c;
       }
       catch (UserExistsException) {
           UserExistsException().print();
       }


       cout << fc;
   }


   if (testCase == 6){
       cout << "===== Test Case - update method  ======" << endl << endl;
       FINKI_bookstore fc;
       int n;
       cin >> n;
       Customer customers[MAX];
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,MAX);
           cin.getline(email,MAX);
           cin >> tC;
           cin >> numProducts;
           Customer c(name, email, (typeC) tC, numProducts);
           customers[i] = c;
       }


       fc.setCustomers(customers, n);


       cout << "Update:" << endl;
       fc.update();
       cout << fc;
   }
   return 0;
}
