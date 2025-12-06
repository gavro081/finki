#include <iostream>
#include <cstring>
#include <cmath>


using namespace std;


class ExistingGame {
public:
   static void message() {
       cout << "The game is already in the collection\n";
   }
};


int broj_na_meseci(int mes1, int god1, int mes2, int god2) {
   if (god2 == god1) return mes2 - mes1;
   else if (god2 - god1 == 1) return (12 - mes1) + mes2;
   else return (12 - mes1) + mes2 + ((god2 - god1) * 12);
}


class Game {
protected:
   char ime[100];
   float cena;
   bool rasprodazba;
public:
   Game(const char *ime = "", float cena = -1, bool rasprodazba = false) {
       strcpy(this->ime, ime);
       this->cena = cena;
       this->rasprodazba = rasprodazba;
   }


   virtual bool operator==(Game &ob) {
       return (strcmp(ime, ob.ime) == 0);
   }


   friend istream &operator>>(istream &CIN, Game &ob) {
       CIN.get();
       CIN.getline(ob.ime, 100);
       CIN >> ob.cena;
       CIN >> ob.rasprodazba;
       // tuka
       return CIN;
   }


   friend ostream &operator<<(ostream &out, Game &ob) {
       out << "Game: " << ob.ime << ", regular price: $" << ob.cena;
       if (ob.getRasprodazba()) out << ", bought on sale";
       out << '\n';
       return out;
   }


   char *getIme() { return ime; }


   virtual float getCena() {
       if (rasprodazba) return cena*0.3;
       return cena;
   }


   bool getRasprodazba() { return rasprodazba; }


   void setCena(float num) { this->cena = num; }
};


class SubscriptionGame : public Game {
private:
   float nadomest;
   unsigned int mesec;
   unsigned int god;
public:
   SubscriptionGame(const char *ime = "", float cena = -1, bool rasprodazba = false,
                    float nadomest = 0.0, unsigned int mesec = 0, unsigned int god = 0)
           : Game(ime, cena, rasprodazba) {
       this->nadomest = nadomest;
       this->mesec = mesec;
       this->god = god;
   }
   SubscriptionGame (const SubscriptionGame& ob){
       strcpy(this->ime, ob.ime);
       this->cena = ob.cena;
       this->rasprodazba = ob.rasprodazba;
       this->nadomest = ob.nadomest;
       this->mesec = ob.mesec;
       this->god = ob.god;
   }


   friend istream &operator>>(istream &CIN, SubscriptionGame &ob) {
       CIN.get();
       CIN.getline(ob.ime, 100);
       CIN >> ob.cena;
       CIN >> ob.rasprodazba;
       CIN >> ob.nadomest;
       CIN >> ob.mesec;
       CIN >> ob.god;
       return CIN;
   }


   friend ostream &operator<<(ostream &out, SubscriptionGame &ob) {
       out << "Game: " << ob.ime << ", regular price: $" << ob.cena;
       if (ob.getRasprodazba()) out << ", bought on sale";
       out << ", monthly fee: $" << ob.nadomest << ", purchased: " <<
           ob.mesec << '-' << ob.god << '\n';
       return out;
   }


   using Game::operator==;


   float getCena() override{
       float cena = Game::getCena();
       cena += broj_na_meseci(mesec,god, 5,2018) * nadomest;
       return cena;
   }


   float getNadomest() { return nadomest; }


   unsigned int getMesec() { return mesec; }


   unsigned int getGod() { return god; }


};


class User {
   char ime[100];
   Game **games;
   int n;
public:
   User(const char *ime = "", Game **games = 0, int n = 0) {
       strcpy(this->ime, ime);
       this->games = new Game*[n];
       this->games = games;
       this->n = n;
   }


   User &operator+=(Game &ob) {
       for (int i = 0; i < n; ++i) {
           if (strcmp(games[i]->getIme(), ob.getIme()) == 0) throw ExistingGame();
       }


       Game **temp = new Game*[n + 1];
       for (int i = 0; i < n; ++i) {
           temp[i] = games[i];
       }
       SubscriptionGame *ptr = dynamic_cast<SubscriptionGame*>(&ob);
       if (ptr){
           temp[n++] = new SubscriptionGame(*ptr);
       }
       else {
           temp[n++] = new Game(ob);
       }
       //temp[n++] = ob;
       games = temp;
       return *this;
   }


   char *get_name() { return ime; }


   int get_games_numer() { return n; }




   friend ostream &operator<<(ostream &out, User &ob) {
       out << "\nUser: " << ob.ime << '\n';
       for (int i = 0; i < ob.n; ++i) {
           SubscriptionGame *ptr = dynamic_cast<SubscriptionGame *>(ob.games[i]);
           if (ptr) {
               out << "- " << *ptr;
           } else out << "- " << *ob.games[i];
       }
       out << '\n';
       return out;
   }


   int total_spent (){
       float suma = 0.0;
       for (int i = 0; i < n ; ++i) {
           suma += games[i]->getCena();
       }
       return round(suma);
   }
};




int main() {
   int test_case_num;


   cin >> test_case_num;


   // for Game
   char game_name[100];
   float game_price;
   bool game_on_sale;


   // for SubscritionGame
   float sub_game_monthly_fee;
   int sub_game_month, sub_game_year;


   // for User
   char username[100];
   int num_user_games;


   if (test_case_num == 1) {
       cout << "Testing class Game and operator<< for Game" << std::endl;
       cin.get();
       cin.getline(game_name, 100);
       //cin.get();
       cin >> game_price >> game_on_sale;


       Game g(game_name, game_price, game_on_sale);


       cout << g;
   } else if (test_case_num == 2) {
       cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << std::endl;
       cin.get();
       cin.getline(game_name, 100);


       cin >> game_price >> game_on_sale;


       cin >> sub_game_monthly_fee;
       cin >> sub_game_month >> sub_game_year;


       SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
       cout << sg;
   } else if (test_case_num == 3) {
       cout << "Testing operator>> for Game" << std::endl;
       Game g;


       cin >> g;


       cout << g;
   } else if (test_case_num == 4) {
       cout << "Testing operator>> for SubscriptionGame" << std::endl;
       SubscriptionGame sg;


       cin >> sg;


       cout << sg;
   } else if (test_case_num == 5) {
       cout << "Testing class User and operator+= for User" << std::endl;
       cin.get();
       cin.getline(username, 100);
       User u(username);


       int num_user_games;
       int game_type;
       cin >> num_user_games;


       try {


           for (int i = 0; i < num_user_games; ++i) {


               cin >> game_type;


               Game *g;
               // 1 - Game, 2 - SubscriptionGame
               if (game_type == 1) {
                   cin.get();
                   cin.getline(game_name, 100);


                   cin >> game_price >> game_on_sale;
                   g = new Game(game_name, game_price, game_on_sale);
               } else if (game_type == 2) {
                   cin.get();
                   cin.getline(game_name, 100);


                   cin >> game_price >> game_on_sale;


                   cin >> sub_game_monthly_fee;
                   cin >> sub_game_month >> sub_game_year;
                   g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                            sub_game_year);
               }


               //cout<<(*g);




               u += (*g);
           }
       } catch (ExistingGame &ex) {
           ex.message();
       }


       cout << u;


//    cout<<"\nUser: "<<u.get_username()<<"\n";


//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));


//        sg = dynamic_cast<SubscriptionGame *> (g);


//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }


   } else if (test_case_num == 6) {
       cout << "Testing exception ExistingGame for User" << std::endl;
       cin.get();
       cin.getline(username, 100);
       User u(username);


       int num_user_games;
       int game_type;
       cin >> num_user_games;


       for (int i = 0; i < num_user_games; ++i) {


           cin >> game_type;


           Game *g;
           // 1 - Game, 2 - SubscriptionGame
           if (game_type == 1) {
               cin.get();
               cin.getline(game_name, 100);


               cin >> game_price >> game_on_sale;
               g = new Game(game_name, game_price, game_on_sale);
           } else if (game_type == 2) {
               cin.get();
               cin.getline(game_name, 100);


               cin >> game_price >> game_on_sale;


               cin >> sub_game_monthly_fee;
               cin >> sub_game_month >> sub_game_year;
               g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                        sub_game_year);
           }


           //cout<<(*g);


           try {
               u += (*g);
           }
           catch (ExistingGame &ex) {
               ex.message();
           }
       }


       cout << u;


//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));


//          sg = dynamic_cast<SubscriptionGame *> (g);


//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
   } else if (test_case_num == 7) {
       cout << "Testing total_spent method() for User" << std::endl;
       cin.get();
       cin.getline(username, 100);
       User u(username);


       int num_user_games;
       int game_type;
       cin >> num_user_games;


       for (int i = 0; i < num_user_games; ++i) {


           cin >> game_type;


           Game *g;
           // 1 - Game, 2 - SubscriptionGame
           if (game_type == 1) {
               cin.get();
               cin.getline(game_name, 100);


               cin >> game_price >> game_on_sale;
               g = new Game(game_name, game_price, game_on_sale);
           } else if (game_type == 2) {
               cin.get();
               cin.getline(game_name, 100);


               cin >> game_price >> game_on_sale;


               cin >> sub_game_monthly_fee;
               cin >> sub_game_month >> sub_game_year;
               g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month,
                                        sub_game_year);
           }


           //cout<<(*g);




           u += (*g);
       }


       cout << u;


       cout << "Total money spent: $" << u.total_spent() << endl;
   }
}
