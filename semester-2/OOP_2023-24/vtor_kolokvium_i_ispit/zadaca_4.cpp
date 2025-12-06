#include <cstring>
#include <iostream>
using namespace std;


// Your Code goes here


enum Size {small, big, family};
const char *sizes[] = {"small", "big", "family"};


class Pizza{
protected:
   char name[20];
   char ingredients[100];
   double basePrice;
public:
   virtual double price(){return basePrice;}


   bool operator<(Pizza& ob){
       return this->price() < ob.price();
   }


   friend ostream& operator<<(ostream& COUT, Pizza& ob){
       COUT << ob.name << ": " << ob.ingredients;
       return COUT;
   }


};


class FlatPizza : public Pizza{
   Size size = small;
public:
   FlatPizza(char *name, char* ingredients, double basePrice){
       strcpy(this->name, name);
       strcpy(this->ingredients, ingredients);
       this->basePrice = basePrice;
   }
   FlatPizza(char *name, char* ingredients, double basePrice, Size size){
       strcpy(this->name, name);
       strcpy(this->ingredients, ingredients);
       this->basePrice = basePrice;
       this->size = size;
   }


   double price()override{
       if (size == 0) return basePrice * 1.1;
       if (size == 1) return basePrice * 1.2;
       if (size == 2) return basePrice * 1.3;
       return basePrice;
   }


   using Pizza::operator<;


   friend ostream& operator<<(ostream& COUT, FlatPizza& ob){
       COUT << ob.name << ": " << ob.ingredients << ", " << sizes[ob.size] << " - " << ob.price() << '\n';
       return COUT;
   }


};


class FoldedPizza : public Pizza{
   bool whiteFlour = true;
public:
   FoldedPizza(char *name, char* ingredients, double basePrice, bool whiteFlour){
       strcpy(this->name, name);
       strcpy(this->ingredients, ingredients);
       this->basePrice = basePrice;
       this->whiteFlour = whiteFlour;
   }
   FoldedPizza(char *name, char* ingredients, double basePrice){
       strcpy(this->name, name);
       strcpy(this->ingredients, ingredients);
       this->basePrice = basePrice;
   }


   double price()override{
       return (whiteFlour) ? basePrice * 1.1 : basePrice * 1.3;
   }


   using Pizza::operator<;


   friend ostream& operator<<(ostream& COUT, FoldedPizza& ob){
       COUT << ob.name << ": " << ob.ingredients << ", ";
       COUT << ((ob.whiteFlour) ? "wf" : "nwf");
       COUT << " - " << ob.price() << '\n';
       return COUT;
   }


   void setWhiteFlour(bool wf) {whiteFlour = wf;}
};


void expensivePizza(Pizza** pizzas, int n){
   int maxI = 0;
   double maxPrice = 0.0;
   for (int i = 0; i < n; ++i) {
       if (pizzas[i]->price() > maxPrice) {
           maxPrice = pizzas[i]->price();
           maxI = i;
       }
   }
   FlatPizza *fp1 = dynamic_cast<FlatPizza *>(pizzas[maxI]);
   FoldedPizza *fp2 = dynamic_cast<FoldedPizza *>(pizzas[maxI]);
   if (fp1) cout << *fp1;
   else cout << *fp2;
}


// Testing


int main() {
   int test_case;
   char name[20];
   char ingredients[100];
   float inPrice;
   Size size;
   bool whiteFlour;


   cin >> test_case;
   if (test_case == 1) {
       // Test Case FlatPizza - Constructor, operator <<, price
       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       FlatPizza fp(name, ingredients, inPrice);
       cout << fp;
   } else if (test_case == 2) {
       // Test Case FlatPizza - Constructor, operator <<, price
       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       int s;
       cin>>s;
       FlatPizza fp(name, ingredients, inPrice, (Size)s);
       cout << fp;


   } else if (test_case == 3) {
       // Test Case FoldedPizza - Constructor, operator <<, price
       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       FoldedPizza fp(name, ingredients, inPrice);
       cout << fp;
   } else if (test_case == 4) {
       // Test Case FoldedPizza - Constructor, operator <<, price
       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       FoldedPizza fp(name, ingredients, inPrice);
       fp.setWhiteFlour(false);
       cout << fp;


   } else if (test_case == 5) {
       // Test Cast - operator <, price
       int s;


       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       cin>>s;
       FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
       cout << *fp1;


       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       cin>>s;
       FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
       cout << *fp2;


       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
       cout << *fp3;


       cin.get();
       cin.getline(name,20);
       cin.getline(ingredients,100);
       cin >> inPrice;
       FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
       fp4->setWhiteFlour(false);
       cout << *fp4;


       cout<<"Lower price: "<<endl;
       if(*fp1<*fp2)
           cout<<fp1->price()<<endl;
       else cout<<fp2->price()<<endl;


       if(*fp1<*fp3)
           cout<<fp1->price()<<endl;
       else cout<<fp3->price()<<endl;


       if(*fp4<*fp2)
           cout<<fp4->price()<<endl;
       else cout<<fp2->price()<<endl;


       if(*fp3<*fp4)
           cout<<fp3->price()<<endl;
       else cout<<fp4->price()<<endl;


   } else if (test_case == 6) {
       // Test Cast - expensivePizza
       int num_p;
       int pizza_type;


       cin >> num_p;
       Pizza **pi = new Pizza *[num_p];
       for (int j = 0; j < num_p; ++j) {


           cin >> pizza_type;
           if (pizza_type == 1) {
               cin.get();
               cin.getline(name,20);


               cin.getline(ingredients,100);
               cin >> inPrice;
               int s;
               cin>>s;
               FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
               cout << (*fp);
               pi[j] = fp;
           }
           if (pizza_type == 2) {


               cin.get();
               cin.getline(name,20);
               cin.getline(ingredients,100);
               cin >> inPrice;
               FoldedPizza *fp =
                       new FoldedPizza (name, ingredients, inPrice);
               if(j%2)
                   (*fp).setWhiteFlour(false);
               cout << (*fp);
               pi[j] = fp;


           }
       }


       cout << endl;
       cout << "The most expensive pizza:\n";
       expensivePizza(pi,num_p);




   }
   return 0;
}
