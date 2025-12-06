
#include <iostream>
#include <cstring>
using namespace std;
void test(int k);

class TennisPlayer {
    char name[50];
    char surname[50];
    int rank;
    int matchesPLayed;
    int matchesWon;
public:
    TennisPlayer(){}
    TennisPlayer(char *name, char *surname, int rank, int matchesPLayed, int matchesWon) :
            rank(rank), matchesPLayed(matchesPLayed), matchesWon(matchesWon) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    float findPercentageWins() {
        return (float) matchesWon / matchesPLayed * 100.00;
    }

    const char *getName() const {
        return name;
    }

    int getMatchesWon () {return matchesWon;}
    int getMatchesPlayed () {return matchesPLayed;}

    void setName(char *name) { strcpy(this->name, name);}
    void setSurname(char *surname) { strcpy(this->surname, surname);}

    const char *getSurname() const {
        return surname;
    }

    int getRank() const {
        return rank;
    }

    void setRank(int rank) {
        TennisPlayer::rank = rank;
    }

    void setMatchesPlayed(int matchesPLayed) {
        TennisPlayer::matchesPLayed = matchesPLayed;
    }

    void setMatchesWon(int matchesWon) {
        TennisPlayer::matchesWon = matchesWon;
    }
};

void printHighestRankedPlayerBelow50PercentWins(TennisPlayer* players, int n){
    TennisPlayer najmal;
    bool p = false;
    for (int i = 0; i < n ; i++){
        if (players[i].findPercentageWins() < 50) {
            if (!p){
                najmal = players[i];
                p = true;
            }
            else {
                if (players[i].getRank() < najmal.getRank()) najmal = players[i];
            }
        }
    }

    if (!p) cout << "No such tennis player.";
    else {
        cout << najmal.getName() <<' ' <<najmal.getSurname();
    }
}




int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0 || testCase == 1) {
        test(testCase);
        return 0;
    }

    int n;
    cin >> n;
    TennisPlayer players[n];char name[50];
    char surname[50];
    int rank;
    int matchesPLayed;
    int matchesWon;
    for (int i = 0; i < n; i++){
//        cin.get();
        cin >> name;
        cin >> surname;
        cin >> rank;
        cin >> matchesPLayed;
        cin >> matchesWon;
        players[i].setName(name);
        players[i].setSurname(surname);
        players[i].setMatchesWon(matchesWon);
        players[i].setMatchesPlayed(matchesPLayed);
        players[i].setRank(rank);

//        cout << players[i].getMatchesWon() <<'\n';
    }


    // TODO: Pass correct input arguments
    printHighestRankedPlayerBelow50PercentWins(players, n);

    return 0;
}


void test(int k) {
    if (k == 0) {
        cout << "Testing default constructor and getters/setters" << endl;
        cout << "---" << endl;
        TennisPlayer player = TennisPlayer();
        player.setName(new char[5] {'J', 'o', 'h', 'n', '\0'});
        player.setSurname(new char[5] {'D', 'o', 'e', '\0'});
        player.setRank(55);
        player.setMatchesPlayed(100);
        player.setMatchesWon(50);
        cout << "Full name: " << player.getName() << " " << player.getSurname() << endl;
        cout << "Rank and won matches out of total: " << player.getRank() << " " << player.getMatchesWon() << "/"
             << player.getMatchesPlayed() << endl;
    }
    else if (k == 1) {
        cout << "Testing findPercentageWins function" << endl;
        cout << "---" << endl;
        TennisPlayer player = TennisPlayer();
        player.setName(new char[5] {'J', 'o', 'h', 'n', '\0'});
        player.setSurname(new char[5] {'D', 'o', 'e', '\0'});
        player.setRank(55);
        player.setMatchesPlayed(100);
        player.setMatchesWon(50);
        if (player.findPercentageWins() != 50) {
            cout << "Test case failed." << endl;
            cout << "Expected: " << 0.5 << "; Got: " << player.findPercentageWins() << endl;
            return;
        }
        player.setMatchesWon(90);
        if (player.findPercentageWins() != 90) {
            cout << "Test case failed." << endl;
            cout << "Expected: " << 0.9 << "; Got: " << player.findPercentageWins() << endl;
            return;
        }
        cout << "Passed." << endl;
    }
}
