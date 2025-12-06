#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer {
protected:
    char *name;
    char team[40];
    double ppg;
    double apg;
    double rpg;
public:
    NBAPlayer(const char *name = "", const char *team = "", double ppg = 0.0, double apg = 0.0, double rpg = 0.0)
            : rpg(rpg), ppg(ppg), apg(apg) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->team, team);
    }

    NBAPlayer(const NBAPlayer &ob) {
        this->name = new char[strlen(ob.name) + 1];
        strcpy(this->name, ob.name);
        strcpy(this->team, ob.team);
        ppg = ob.ppg;
        apg = ob.apg;
        rpg = ob.rpg;
    }

    NBAPlayer &operator=(const NBAPlayer &ob) {
        this->name = new char[strlen(ob.name) + 1];
        strcpy(this->name, ob.name);
        strcpy(this->team, ob.team);
        ppg = ob.ppg;
        apg = ob.apg;
        rpg = ob.rpg;
        return *this;
    }

    double rating() {
        return 0.45 * ppg + 0.3 * apg + 0.25 * rpg;
    }

    void print() {
        cout << name << " - " << team << '\n';
        cout << "Points: " << ppg << '\n';
        cout << "Assists: " << apg << '\n';
        cout << "Rebounds: " << rpg << '\n';
        cout << "Rating: " << this->rating() << '\n';
    }

};


class AllStarPlayer : public NBAPlayer {
    double as_ppg;
    double as_apg;
    double as_rpg;
public:
    AllStarPlayer(NBAPlayer &ob, double p, double a, double r)
            : NBAPlayer(ob), as_ppg(p), as_apg(a), as_rpg(r) {}

    AllStarPlayer(const char *name = "", const char *team = "", double ppg = 0.0, double apg = 0.0, double rpg = 0.0,
                  double p = 0.0, double a = 0.0, double r = 0.0)
            : NBAPlayer(name, team, ppg, apg, rpg), as_rpg(r), as_apg(a), as_ppg(p) {}

    AllStarPlayer(const AllStarPlayer &ob) : NBAPlayer(ob) {
        this->as_ppg = ob.as_ppg;
        this->as_rpg = ob.as_rpg;
        this->as_apg = ob.as_apg;
    }

    AllStarPlayer &operator=(const AllStarPlayer &ob) {
        strcpy(this->team, ob.team);
        this->name = new char[strlen(ob.name) + 1];
        strcpy(this->name, ob.name);
        this->apg = ob.apg;
        this->ppg = ob.ppg;
        this->rpg = ob.rpg;
        this->as_ppg = ob.as_ppg;
        this->as_rpg = ob.as_rpg;
        this->as_apg = ob.as_apg;
    }

    double allStarRating() {
        return 0.3 * as_ppg + 0.4 * as_apg + 0.3 * as_rpg;
    }

    double rating() {
        return (NBAPlayer::rating() + allStarRating()) / 2;
    }

    void print() {
        NBAPlayer::print();
        cout << "All Star Rating: " << allStarRating() << '\n';
        cout << "New Rating: " << rating() << '\n';
    }


};


int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer *players = new NBAPlayer[5];
    AllStarPlayer *asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            players[i].print();
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            asPlayers[i] = AllStarPlayer(players[i], allStarPoints, allStarAssists, allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints, allStarAssists, allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete[] players;
    delete[] asPlayers;
}
