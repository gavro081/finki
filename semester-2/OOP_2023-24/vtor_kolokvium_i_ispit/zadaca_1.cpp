#include <iostream>
#include <cstring>


using namespace std;


class Book{
protected:
   char isbn[20];
   char title[50];
   char author[30];
   float price;
public:
   virtual ~Book(){}


   virtual float bookPrice(){return price;};


   virtual bool operator>(const Book& ob){
       return price > ob.price;
   }


   friend ostream& operator<<(ostream& COUT, Book& ob){
       COUT << ob.isbn << ": " << ob.title << ", " << ob.author << " " << ob.bookPrice() << '\n';
       return COUT;
   }
};


class OnlineBook : public Book{
   char *url;
   int size;
public:


   OnlineBook(char* isbn, char* title, char* author, float price, char* url, int size ){
       this->size = size;
       this->price = (size > 20) ? (1.2*price) : price;
       strcpy(this->isbn, isbn);
       strcpy(this->title, title);
       strcpy(this->author, author);
       this->url = new char[strlen(url) + 1];
       strcpy(this->url, url);
   }


   OnlineBook(const OnlineBook& ob){
       size = ob.size;
       this->price = ob.price;
       strcpy(this->isbn, ob.isbn);
       strcpy(this->title, ob.title);
       strcpy(this->author, ob.author);
       this->url = new char[strlen(ob.url) + 1];
       strcpy(this->url, ob.url);
   }


   OnlineBook& operator=(const OnlineBook& ob){
       size = ob.size;
       this->price = ob.price;
       strcpy(this->isbn, ob.isbn);
       strcpy(this->title, ob.title);
       strcpy(this->author, ob.author);
       this->url = new char[strlen(ob.url) + 1];
       strcpy(this->url, ob.url);
       return *this;
   }


   float bookPrice() {
       return price;
   }


   using Book::operator>;


   friend ostream& operator<<(ostream& COUT, OnlineBook& ob){
       COUT << ob.isbn << ": " << ob.title << ", " << ob.author << " " << ob.bookPrice() << '\n';
       return COUT;
   }


   void setISBN(char* isbn){
       strcpy(this->isbn, isbn);
   }
};


class PrintBook : public Book{
   float weight;
   bool inStock;
public:
   PrintBook(char* isbn,  char* title,  char* author, float price, float weight , bool inStock ){
       this->weight = weight;
       this->inStock = inStock;
       this->price = (weight > 0.7) ? (price * 1.15) : price;
       strcpy(this->isbn, isbn);
       strcpy(this->title, title);
       strcpy(this->author, author);
   }


   float bookPrice() override {
       return price;
   }


   using Book::operator>;


   friend ostream& operator<<(ostream& COUT, PrintBook& ob){
       COUT << ob.isbn << ": " << ob.title << ", " << ob.author << " " << ob.bookPrice() << '\n';
       return COUT;
   }
};


void mostExpensiveBook (Book** books, int n){
   int ctrO = 0, ctrP = 0;
   for (int i = 0; i < n; ++i) {
       OnlineBook *O = dynamic_cast<OnlineBook *>(books[i]);
       PrintBook *P = dynamic_cast<PrintBook *>(books[i]);
       if (O) ctrO++;
       if (P) ctrP++;
   }
   cout << "FINKI-Education\n";
   cout << "Total number of online books: " << ctrO << '\n';
   cout << "Total number of print books: " << ctrP << '\n';


   int maxI = 0;
   float maxPrice = 0.0;
   for (int i = 0; i < n; ++i) {
       if (books[i]->bookPrice() > maxPrice) {
           maxI = i;
           maxPrice = books[i]->bookPrice();
       }
   }
   cout << "The most expensive book is: \n" << *books[maxI] << '\n';
}


int main(){


   char isbn[20], title[50], author[30], url[100];
   int size, tip;
   float price, weight;
   bool inStock;
   Book  **books;
   int n;


   int testCase;
   cin >> testCase;


   if (testCase == 1){
       cout << "====== Testing OnlineBook class ======" << endl;
       cin >> n;
       books = new Book *[n];


       for (int i = 0; i < n; i++){
           cin >> isbn;
           cin.get();
           cin.getline(title, 50);
           cin.getline(author, 30);
           cin >> price;
           cin >> url;
           cin >> size;
           cout << "CONSTRUCTOR" << endl;
           books[i] = new OnlineBook(isbn, title, author, price, url, size);
           cout << "OPERATOR <<" << endl;
           cout << *books[i];
       }
       cout << "OPERATOR >" << endl;
       cout << "Rezultat od sporedbata e: " << endl;
       if (*books[0] > *books[1])
           cout << *books[0];
       else
           cout << *books[1];
   }
   if (testCase == 2){
       cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
       cin >> isbn;
       cin.get();
       cin.getline(title, 50);
       cin.getline(author, 30);
       cin >> price;
       cin >> url;
       cin >> size;
       cout << "CONSTRUCTOR" << endl;
       OnlineBook ob1(isbn, title, author, price, url, size);
       cout << ob1 << endl;
       cout << "COPY CONSTRUCTOR" << endl;
       OnlineBook ob2(ob1);
       cin >> isbn;
       ob2.setISBN(isbn);
       cout << ob1 << endl;
       cout << ob2 << endl;
       cout << "OPERATOR =" << endl;
       ob1 = ob2;
       cin >> isbn;
       ob2.setISBN(isbn);
       cout << ob1 << endl;
       cout << ob2 << endl;
   }
   if (testCase == 3){
       cout << "====== Testing PrintBook class ======" << endl;
       cin >> n;
       books = new Book *[n];


       for (int i = 0; i < n; i++){
           cin >> isbn;
           cin.get();
           cin.getline(title, 50);
           cin.getline(author, 30);
           cin >> price;
           cin >> weight;
           cin >> inStock;
           cout << "CONSTRUCTOR" << endl;
           books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
           cout << "OPERATOR <<" << endl;
           cout << *books[i];
       }
       cout << "OPERATOR >" << endl;
       cout << "Rezultat od sporedbata e: " << endl;
       if (*books[0] > *books[1])
           cout << *books[0];
       else
           cout << *books[1];
   }
   if (testCase == 4){
       cout << "====== Testing method mostExpensiveBook() ======" << endl;
       cin >> n;
       books = new Book *[n];


       for (int i = 0; i<n; i++){


           cin >> tip >> isbn;
           cin.get();
           cin.getline(title, 50);
           cin.getline(author, 30);
           cin >> price;
           if (tip == 1) {


               cin >> url;
               cin >> size;


               books[i] = new OnlineBook(isbn, title, author, price, url, size);


           }
           else {
               cin >> weight;
               cin >> inStock;


               books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
           }
       }


       mostExpensiveBook(books, n);
   }


   for (int i = 0; i < n; i++) delete books[i];
   delete[] books;
   return 0;
}
