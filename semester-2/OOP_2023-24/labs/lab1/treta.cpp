#include <iostream>

using namespace std;

struct FootballPlayer{
    char name[50];
    int num;
    int goals;
};

struct FootballTeam{
    char name[50];
    FootballPlayer players[11];
};

void bestTeam(FootballTeam teams[], int n){
    FootballTeam best = teams[0];
    int maxGoals;
//    int maxGoals = 1e7;
    for (int i = 0; i < n; ++i) {
        int teamGoals = 0;
        for (int j = 0; j < 11; ++j) {
            teamGoals += teams[i].players[j].goals;
        }
            if (i==0) maxGoals = teamGoals;
            else if (teamGoals > maxGoals) {
                maxGoals = teamGoals;
                best = teams[i];
            }
    }
    cout << "Najdobar tim e: " << best.name;
}

int main(){
    int n;
    cin >> n;
    FootballTeam teams[n];
    for (int i = 0; i < n; ++i) {
        cin >> teams[i].name;
        for (int j = 0; j < 11; ++j) {
            cin >> teams[i].players[j].name;
            cin >> teams[i].players[j].num;
            cin >> teams[i].players[j].goals;
        }
    }
    bestTeam(teams, n);
}