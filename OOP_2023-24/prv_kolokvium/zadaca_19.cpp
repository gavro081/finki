#include <iostream>
#include <cstring>
using namespace std;




// vashiot kod ovde
class IceCream{
   char *name;
   char ingredients[100];
   float price;
   int discount;
public:
   IceCream(){}


   IceCream(char *name, char *ingredients, float price) : price(price){
       this->name = new char[strlen(name) + 1];
       strcpy(this->name, name);
       strcpy(this->ingredients, ingredients);
       this->discount = 0;
   }


   IceCream (const IceCream& ob){
       delete [] name;
       this->price = ob.price;
       this->name = new char[strlen(ob.name) + 1];
       strcpy(this->name, ob.name);
       strcpy(this->ingredients, ob.ingredients);
       this->discount = ob.discount;
   }


   IceCream& operator=(const IceCream& ob){
       if (this != &ob){
           delete [] name;
           this->price = ob.price;
           this->name = new char[strlen(ob.name) + 1];
           strcpy(this->name, ob.name);
           strcpy(this->ingredients, ob.ingredients);
           this->discount = ob.discount;
       }
       return *this;
   }


   friend ostream& operator<<(ostream& COUT, IceCream& ob){
       COUT << ob.name << ": " << ob.ingredients << ' ' << ob.price;
       if (ob.discount > 0) COUT << " (" << (double)ob.price * (100 - ob.discount) / 100 << ')';
//        COUT << '\n';
       return COUT;
   }


   ~IceCream(){
       delete [] name;
   }


   IceCream& operator++(){
       discount += 5;
       return *this;
   }


   IceCream& operator+(char *arr){
       char *newName = new char[strlen(name) + strlen(arr) + 3];
       strcat(newName,name);
       strcat(newName," + ");
       strcat(newName, arr);


       delete [] name;
       name = new char[strlen(newName) + 1];
       name = newName;


       price += 10;


       return *this;
   }


   void setDiscount(int discount){
       if (discount >= 0 && discount <= 100) this->discount = discount;
   }


   void setName(char *name){
       delete [] this->name;
       this->name = new char[strlen(name)];
       strcpy(this->name,name);
   }
};


class IceCreamShop{
   char name[50];
   IceCream* icecreams;
   int n;
public:
   IceCreamShop(){}


   IceCreamShop(char *name){
       strcpy(this->name,name);
       icecreams = NULL;
       n = 0;
   }


   ~IceCreamShop(){
       delete [] icecreams;
   }


   IceCreamShop(const IceCreamShop& ob){
       strcpy(this->name,ob.name);
       delete [] icecreams;
       icecreams = new IceCream[ob.n];
       for (int i = 0; i < ob.n; ++i) {
           icecreams[i] = ob.icecreams[i];
       }
       n = ob.n;
   }


   IceCreamShop& operator=(const IceCreamShop& ob){
       if (this != &ob){
           strcpy(this->name,ob.name);
           delete [] icecreams;
           icecreams = new IceCream[ob.n];
           for (int i = 0; i < ob.n; ++i) {
               icecreams[i] = ob.icecreams[i];
           }
           n = ob.n;
       }
       return *this;
   }


   void operator+= (IceCream& ob){
       IceCream *tmp = new IceCream[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = icecreams[i];
       }
       delete [] icecreams;
       tmp[n++] = ob;
       icecreams = tmp;
   }


   friend ostream& operator<<(ostream& COUT, IceCreamShop& ob){
       COUT << ob.name << '\n';
       for (int i = 0; i < ob.n; ++i) {
           cout << ob.icecreams[i] << '\n';
       }
       return COUT;
   }
};


int main() {
   char name[100];
   char ingr[100];
   float price;
   int discount;


   int testCase;


   cin >> testCase;
   cin.get();
   if(testCase == 1) {
       cout << "====== TESTING IceCream CLASS ======" << endl;
       cin.getline(name,100);
       cin.getline(ingr,100);
       cin >> price;
       cin >> discount;
       cout << "CONSTRUCTOR" << endl;
       IceCream ic1(name, ingr, price);
       ic1.setDiscount(discount);
       cin.get();
       cin.getline(name,100);
       cin.getline(ingr,100);
       cin >> price;
       cin >> discount;
       IceCream ic2(name, ingr, price);
       ic2.setDiscount(discount);
       cout << "OPERATOR <<" << endl;
       cout << ic1 << endl;
       cout << ic2 << endl;
       cout << "OPERATOR ++" << endl;
       ++ic1;
       cout << ic1 << endl;
       cout << "OPERATOR +" << endl;
       IceCream ic3 = ic2 + "chocolate";
       cout << ic3 << endl;
   } else if(testCase == 2) {
       cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
       cin.getline(name,100);
       cin.getline(ingr,100);
       cin >> price;
       cout << "CONSTRUCTOR" << endl;
       IceCream ic1(name, ingr, price);
       cout << ic1 << endl;
       cout << "COPY CONSTRUCTOR" << endl;
       IceCream ic2(ic1);
       cin.get();
       cin.getline(name,100);
       ic2.setName(name);
       cout << ic1 << endl;
       cout << ic2 << endl;
       cout << "OPERATOR =" << endl;
       ic1 = ic2;
       cin.getline(name,100);
       ic2.setName(name);
       cout << ic1 << endl;
       cout << ic2 << endl;


       cin >> discount;
       ic1.setDiscount(discount);




   } else if(testCase == 3) {
       cout << "====== TESTING IceCreamShop ======" << endl;
       char icsName[50];
       cin.getline(icsName,100);
       cout << "CONSTRUCTOR" << endl;
       IceCreamShop ics(icsName);
       int n;
       cin >> n;
       cout << "OPERATOR +=" << endl;
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,100);
           cin.getline(ingr,100);
           cin >> price;
           IceCream ic(name, ingr, price);
           ics += ic;
       }
       cout << ics;
   } else if(testCase == 4) {
       cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
       char icsName[50];
       cin.getline(icsName,100);
       IceCreamShop ics(icsName);
       int n;
       cin >> n;
       for(int i = 0; i < n; ++i) {
           cin.get();
           cin.getline(name,100);
           cin.getline(ingr,100);
           cin >> price;
           IceCream ic(name, ingr, price);
           ics += ic;
       }
       IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
       IceCreamShop icp = ics;
       ics+=x;
       cout << ics << endl;
       cout << icp << endl;
   }
   return 0;
}
