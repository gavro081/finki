#include <iostream>
#include <cstring>

using namespace std;

class BasketballPlayer {
    char ime[20];
    char prezime[20];
    int broj;
    int prv;
    int vtor;
    int tret;
public:
    BasketballPlayer(){};
    BasketballPlayer(char *ime, char *prezime, int broj, int prv, int vtor, int tret) 
    : broj(broj), prv(prv), vtor(vtor), tret(tret) {
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
    }

    void print() {
        cout << "Player: " << ime << ' ' << prezime <<
        " with number: " << broj << " has "<< float(prv+vtor + tret) /3.0<<" points on average\n";
    }
    
};

int main() {
    
    char ime[50], prezime[50];
    int a,b,c,d;
    cin >> ime;
    cin >> prezime;
    cin >> a >> b >> c >> d;
    BasketballPlayer A(ime,prezime,a,b,c,d);
    A.print();
    return 0;
}
