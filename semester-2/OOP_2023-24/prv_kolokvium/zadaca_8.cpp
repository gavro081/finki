#include <iostream>
#include <cstring>


using namespace std;


struct Laptop{
   char manufacturer[100];
   double dimension;
   bool hasTouch;
   int price;
};


struct ITStore{
   char name[100];
   char location[100];
   Laptop laptops[100];
   int n;


   void print(){
       cout << name << ' ' << location << '\n';
       for (int i = 0; i < n; ++i) {
           cout << laptops[i].manufacturer << ' ' << laptops[i].dimension
                << ' ' << laptops[i].price << '\n';
       }
   }
};


void najeftina_ponuda(ITStore *stores, int n){
   //    int lowestPrice = INT_MAX;
   int lowestPrice = 1e6;
   Laptop lowestComp;
   ITStore lowestStore;
   for (int i = 0; i < n; ++i) {
       for (int j = 0; j < stores[i].n; ++j) {
           if (stores[i].laptops[j].price < lowestPrice && stores[i].laptops[j].hasTouch){
               lowestComp = stores[i].laptops[j];
               lowestPrice = lowestComp.price;
               lowestStore = stores[i];
           }
       }
   }
   cout << "Najeftina ponuda ima prodavnicata:\n" << lowestStore.name << ' ' << lowestStore.location << '\n';
   cout << "Najniskata cena iznesuva: " <<  lowestPrice;
}


int main() {
   ITStore s[100];
   int n;
   cin >> n; //broj na IT prodavnici


   //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
   for (int i = 0; i < n; ++i) {
       cin >> s[i].name;
       cin >> s[i].location;
       cin >> s[i].n;
       for (int j = 0; j < s[i].n; ++j) {
           cin >> s[i].laptops[j].manufacturer;
           cin >> s[i].laptops[j].dimension;
           cin >> s[i].laptops[j].hasTouch;
           cin >> s[i].laptops[j].price;
       }


   }


   //pecatenje na site prodavnici
   for (int i = 0; i < n; ++i) {
       s[i].print();
   }


   //povik na glavnata metoda
   najeftina_ponuda(s, n);


   return 0;
}
