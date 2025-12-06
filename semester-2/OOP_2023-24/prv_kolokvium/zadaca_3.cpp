#include<iostream>
#include<cstring>


using namespace std;


// vasiot kod za klasite ovde
class StockRecord {
   char id[12];
   char company[50];
   double priceOld;
   double priceCurr;
   int n;
public:
   StockRecord(const char *id = "", const char *company = "", double priceOld = 0.0, int n = 0)
           : priceOld(priceOld), n(n) {
       priceCurr = 0;
       strcpy(this->id, id);
       strcpy(this->company, company);


   }


   void setNewPrice(double c) { priceCurr = c; }


   double value() {
       return n * priceCurr;
   }


   double profit() const {
       return n * (priceCurr - priceOld);
   }


   friend ostream &operator<<(ostream &COUT, const StockRecord &ob) {
       COUT << ob.company << ' ' << ob.n << ' ' << ob.priceOld
            << ' ' << ob.priceCurr << ' ' << ob.profit() << '\n';
       return COUT;
   }
};


class Client {
   char fullName[60];
   int id;
   StockRecord *companies;
   int n;
public:
   Client(const char *fullName = "", int id = 0) : id(id) {
       strcpy(this->fullName, fullName);
       companies = NULL;
       n = 0;
   }


   ~Client() {
       delete[] companies;
   }


   Client(const Client &ob) {
       strcpy(fullName, ob.fullName);
       id = ob.id;
       n = ob.n;
       companies = new StockRecord[n];
       for (int i = 0; i < n; ++i) {
           companies[i] = ob.companies[i];
       }
   }


   Client &operator=(const Client &ob) {
       if (&ob != this) {
           strcpy(fullName, ob.fullName);
           id = ob.id;
           n = ob.n;
           companies = new StockRecord[n];
           for (int i = 0; i < n; ++i) {
               companies[i] = ob.companies[i];
           }
       }
       return *this;
   }


   double totalValue() const {
       double value = 0.0;
       for (int i = 0; i < n; ++i) {
           value += companies[i].value();
       }
       return value;
   }


   Client &operator+=(const StockRecord &ob) {
       StockRecord *tmp = new StockRecord[n + 1];
       for (int i = 0; i < n; ++i) {
           tmp[i] = companies[i];
       }
       tmp[n++] = ob;
       delete[] companies;
       companies = tmp;
       return *this;
   }


   friend ostream &operator<<(ostream &COUT, const Client &ob) {
       COUT << ob.id << ' ' << ob.totalValue() << '\n';
       for (int i = 0; i < ob.n; ++i) {
           COUT << ob.companies[i];
       }
       return COUT;
   }
};


// ne menuvaj vo main-ot


int main() {


   int test;
   cin >> test;


   if (test == 1) {
       double price;
       cout << "=====TEST NA KLASATA StockRecord=====" << endl;
       StockRecord sr("1", "Microsoft", 60.0, 100);
       cout << "Konstruktor OK" << endl;
       cin >> price;
       sr.setNewPrice(price);
       cout << "SET metoda OK" << endl;
   } else if (test == 2) {
       cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
       char id[12], company[50];
       double price, newPrice;
       int n, shares;
       cin >> n;
       for (int i = 0; i < n; ++i) {
           cin >> id;
           cin >> company;
           cin >> price;
           cin >> newPrice;
           cin >> shares;
           StockRecord sr(id, company, price, shares);
           sr.setNewPrice(newPrice);
           cout << sr.value() << endl;
           cout << sr;
       }
   } else if (test == 3) {
       cout << "=====TEST NA KLASATA Client=====" << endl;
       char companyID[12], companyName[50], clientName[50];
       int clientID, n, shares;
       double oldPrice, newPrice;
       bool flag = true;
       cin >> clientName;
       cin >> clientID;
       cin >> n;
       Client c(clientName, clientID);
       cout << "Konstruktor OK" << endl;
       for (int i = 0; i < n; ++i) {
           cin >> companyID;
           cin >> companyName;
           cin >> oldPrice;
           cin >> newPrice;
           cin >> shares;
           StockRecord sr(companyID, companyName, oldPrice, shares);
           sr.setNewPrice(newPrice);
           c += sr;
           if (flag) {
               cout << "Operator += OK" << endl;
               flag = false;
           }
       }
       cout << c;
       cout << "Operator << OK" << endl;
   }
   return 0;
}
