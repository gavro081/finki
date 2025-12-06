#include<iostream>
#include<cstring>
using namespace std;

class Chocolate{
    char name[100];
    int price;
public:
    Chocolate(const char* name="", int price=0){
        strcpy(this->name, name);
        this->price = price;
    }

    friend ostream &operator<<(ostream &os, const Chocolate &chocolate) {
        os << chocolate.name << ": $" << chocolate.price;
        return os;
    }

    const char *getName() {
        return name;
    }

    int getPrice() const {
        return price;
    }


};

class ChocolateFactory{
    Chocolate *products;
    int *weeklyProduction;
    int numProducts;
public:
    ChocolateFactory(Chocolate *products= NULL, int *weeklyProduction=NULL, int numProucts = 0)
    : numProducts(numProucts){
        this->products = new Chocolate[numProducts];
        this->weeklyProduction = new int[numProducts];
        for (int i=0; i<numProducts; i++){
            this->products[i] = products[i]; // proveri tuka
            this->weeklyProduction[i] = weeklyProduction[i];
        }
    }

    int weeklyIncome() const{
        int sum = 0;
        for (int i = 0 ; i < numProducts; i++){
            sum +=products[i].getPrice() * weeklyProduction[i];
        }
        return sum;
    }

    bool operator<(const ChocolateFactory& ob){
        return this->weeklyIncome() < ob.weeklyIncome();
    }
    bool operator>(const ChocolateFactory& ob){
        return this->weeklyIncome() > ob.weeklyIncome();
    }
    ChocolateFactory& operator+(const ChocolateFactory& ob){
        ChocolateFactory tmp;
        tmp.products = new Chocolate[numProducts + ob.numProducts];
        tmp.weeklyProduction = new int[numProducts + ob.numProducts];
        tmp.numProducts = numProducts + ob.numProducts;

        for (int i=0; i<tmp.numProducts; i++){
            if (i < numProducts){
                tmp.products[i] = products[i];
                tmp.weeklyProduction[i] = weeklyProduction[i];
            }
            else {
                tmp.products[i] = ob.products[i];
                tmp.weeklyProduction[i] = ob.weeklyProduction[i];
            }
        }

        this->numProducts += ob.numProducts;

        delete [] products;
        delete [] weeklyProduction;
        products = new Chocolate[numProducts + ob.numProducts];
        weeklyProduction = new int[numProducts + ob.numProducts];

        products = tmp.products;
        weeklyProduction = tmp.weeklyProduction;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const ChocolateFactory &factory) {
        for (int i=0 ; i < factory.numProducts; i++){
            os << factory.products[i].getName() << " x " << factory.weeklyProduction[i] <<'\n';
        }
        os << factory.weeklyIncome() << '\n';
        return os;
    }
};

int main() {
    int testCase;
    char name[100];
    int price;

    Chocolate products[100];
    int weeklyProduction[100];

    cin >> testCase;
    if (testCase == 0) {
        cout<<"Testing Chocolate print operator:"<<endl;
        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            cout<<Chocolate(name,price)<<endl;
        }
    }
    else if (testCase == 1) {
        cout<<"Testing ChocolateFactory print operator:"<<endl;

        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            products[i] = Chocolate(name, price);
            cin>>weeklyProduction[i];
        }

        ChocolateFactory cf(products,weeklyProduction,10);
        cout<<cf<<endl;
    }
    else if (testCase == 2) {
        cout<<"Testing ChocolateFactory comparison operators:"<<endl;

        for (int i = 0; i < 3; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,3);

        for (int i = 0; i < 4; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,4);

        cout<<cf1<<cf2;

        cout<<"< operator: "<< (cf1 < cf2 ? "PASS" : "FAIL") <<endl;
        cout<<"> operator: "<< (cf2 > cf1 ? "PASS" : "FAIL") <<endl;
    }
    else if (testCase == 3) {
        cout<<"Testing ChocolateFactory sum operator:"<<endl;

        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,5);
        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,5);

        cout<<cf1+cf2;
    }
}