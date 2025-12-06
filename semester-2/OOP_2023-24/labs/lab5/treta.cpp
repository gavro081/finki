#include <iostream>
#include <cstring>

using namespace std;

enum Genre{HORROR, COMEDY, DOCUMENTARY};
const char *genres[3] = {"HORROR", "COMEDY", "DOCUMENTARY"};

class Movie{
    int ID;
    char name[30];
    Genre genre;
    float price;
public:
    Movie(){}
    Movie(int id, const char *name, Genre genre, float price) : ID(id), price(price){
        strcpy(this->name, name);
        this->genre = genre;
    }

    friend ostream& operator<<(ostream& out, Movie& ob){
        out << ob.name << ' ' << ob.genre << ' ' << ob.price << '\n';
        return out;
    }

    bool operator==(const Movie& ob){
        return ID == ob.ID;
    }

    Movie& operator+=(float num){
        price += price*num/100;
        return *this;
    }

    Genre getGenre() const {
        return genre;
    }

    float getPrice() const {
        return price;
    }

    void setPrice(float price) {
        this->price = price;
    }
};

class Cinema{
    char name[40];
    Movie *movies;
    int n;
    static int loyal_discount;
public:
    Cinema(){
        n = 0;
        movies = NULL;
    }

    Cinema(const char *name){
        strcpy(this->name, name);
        movies = NULL;
        n = 0;
    }

    Cinema (Cinema& ob){
        strcpy(this->name, ob.name);
        n = ob.n;
        movies = new Movie[n];
        for (int i = 0; i < n; ++i) {
            movies[i] = ob.movies[i];
        }
    }

    Cinema& operator=(Cinema& ob){
        strcpy(this->name, ob.name);
        n = ob.n;
        movies = new Movie[n];
        for (int i = 0; i < n; ++i) {
            movies[i] = ob.movies[i];
        }
        return *this;
    }

    Cinema& operator+=(Movie& ob){
        for (int i = 0; i < n; ++i) {
            if (movies[i] == ob) return *this;
        }
        Movie* tmp = new Movie[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = movies[i];
        }
        tmp[n++] = ob;
        delete [] movies;
        movies = tmp;
        return *this;
    }

    bool operator<(Cinema& ob){
        return n < ob.n;
    }

    void increase(Genre genre, float num){
        for (int i = 0; i < n; ++i) {
            if (movies[i].getGenre() == genre) {
                movies[i].setPrice(movies[i].getPrice() + movies[i].getPrice() * num/100);
            }
        }
    }

    static int getLoyalDiscount();

    friend ostream& operator<<(ostream& out, Cinema& ob){
        out << ob.name << " movies: \n";
        for (int i = 0; i < ob.n; ++i) {
            out << ob.movies[i];
        }
        out << ob.getLoyalDiscount() << '\n';
        return out;
    }

    int getN() const {
        return n;
    }

    static void setLOYAL_DISCOUNT(int num){
        loyal_discount = num;
    }
};
int Cinema::loyal_discount = 10;

int Cinema::getLoyalDiscount() {
    return loyal_discount;
}

Cinema& smallestChoice(Cinema* cinemas, int n){
    int minI = 0;
    for (int i = 0; i < n; ++i) {
        if (cinemas[i].getN() < cinemas[minI].getN()){
            minI = i;
        }
    }

    return cinemas[minI];
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 0: {
            cout << "TESTING MOVIE CONSTRUCTOR" << endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << "TEST PASSED" << endl;
            break;
        }
        case 1: {
            cout<<"TESTING MOVIE OPERATOR <<"<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 2: {
            cout<<"TESTING MOVIE OPERATOR +="<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            movie1 += 15;
            movie2 += 25.5;
            movie3 += 37;

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 3: {
            cout<<"TESTING CINEMA CONSTRUCTOR and <<"<<endl;

            Cinema cinema("Cineplexx");
            cout << cinema;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 4: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(20);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 5: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(25);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 6: {
            cout<<"TESTING CINEMA COPY-CONSTRUCTOR and OPERATOR ="<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);
            Movie movie3(3, "Omen", Genre::HORROR, 300);
            Movie movie4(4, "Argylle", Genre::COMEDY, 350);

            Cinema cinema1("Cineplexx");

            cinema1 += movie;
            cinema1 += movie1;
            cinema1 += movie2;


            Cinema cinema2(cinema1);
            Cinema cinema4;
            {
                Cinema cinema3("Galaxy");
                cinema3 += movie3;
                cinema3 += movie4;
                cinema4 = cinema3;
            }

            cout << cinema2;
            cout << cinema4;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 7: {
            cout<<"TESTING CINEMA OPERATOR < "<<endl;
            Movie horror(0, "Imaginary", Genre::HORROR, 300);
            Movie comedy(1, "Hangover", Genre::COMEDY, 350);
            Movie documentary(2, "Stormy", Genre::DOCUMENTARY, 300);

            Movie horror1(0, "Omen", Genre::HORROR, 300);
            Movie comedy1(3, "Argylle", Genre::COMEDY, 350);
            Movie documentary1(2, "Christspiracy", Genre::DOCUMENTARY, 300);

            Cinema cinema1("Galaxy");
            cinema1 += horror;
            cinema1 += comedy;
            cinema1 += documentary;

            Cinema cinema2("Encore");
            cinema2 += horror1;
            cinema2 += comedy;
            cinema2 += comedy1;
            cinema2 += documentary1;

            if (cinema1 < cinema2) {
                cout << "TEST PASSED" << endl;
            }
            break;

        }
        case 8: {
            cout<<"TESTING METHOD increase"<<endl;

            char name[40];
            cin.ignore();
            cin.getline(name, 40);

            Cinema cinema(name);

            int n;
            cin >> n;

            int id;
            char title[30];
            int genre;
            float cost;
            float percent;

            for (int i = 0; i < n; i++) {
                cin >> id;
                cin.ignore();
                cin.getline(title, 30);
                cin >> genre;
                cin >> cost;

                Movie movie(id, title, (Genre) genre, cost);
                cinema += movie;
            }

            cin >> percent;
            cin >> genre;
            cout << cinema << endl;
            cinema.increase((Genre)genre, percent);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 9: {
            cout<<"TESTING METHOD smallestChoiceCinema"<<endl;

            int n;
            cin >> n;
            Cinema cinemas[n];
            char name[40];

            for (int i = 0; i < n; i++) {
                cin.ignore();
                cin.getline(name, 40);
                Cinema cinema(name);

                int m;
                cin >> m;

                int id;
                char title[30];
                int genre;
                float cost;

                for (int j = 0; j < m; j++) {
                    cin >> id;
                    cin.ignore();
                    cin.getline(title, 30);
                    cin >> genre;
                    cin >> cost;

                    Movie movie(id, title, (Genre) genre, cost);
                    cinema += movie;
                }

                cinemas[i] = cinema;
            }

            Cinema smallestChoiceCinema = smallestChoice(cinemas, n);
            cout << smallestChoiceCinema << endl;

            cout << "TEST PASSED" << endl;

            break;
        }
    }
    return 0;
}