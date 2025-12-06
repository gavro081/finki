#include <iostream>
#include <cstring>
using namespace std;

// TODO: Implement 'Achievement' and 'UserProfile' classes
class Achievement{
    char name[50];
    char description[100];
    static int totalUserAchievements;
public:
    Achievement(){}

    Achievement(const char* name, const char* description){
        strcpy(this->name, name);
        strcpy(this->description, description);
    }

    Achievement (const Achievement& ob){
        strcpy(this->name, ob.name);
        strcpy(this->description, ob.description);
//        totalUserAchievements = ob.totalUserAchievements;
    }

    void print(){
        cout << name << '\n' << description << '\n';
    }

    static void incrementTotalUserAchievements(){
        totalUserAchievements++;
    }

    bool operator==(const Achievement& ob){
        return (strcmp(name, ob.name) == 0);
    }

    const char *getName() { return name; }

    const char *getDescription() { return description; }

    static int getTotalUserAchievements() { return totalUserAchievements; }
};

int Achievement::totalUserAchievements = 0;

class UserProfile{
    char name[50];
    Achievement achievements[50];
    int n;
public:
    UserProfile(){}

    UserProfile(const char* name){
        strcpy(this->name, name);
        n = 0;
    }

    void print(){
        cout << "User: " <<  name << '\n' << "Achievements:" << '\n';
        for (int i = 0; i < n; ++i) {
            achievements[i].print();
        }
    }

    void addAchievement(const Achievement& achievement){
        achievements[n++] = achievement;
    }

    int getN () {return n;}

    Achievement getAchievement(int index) {return achievements[index];}
};

// TODO: Implement showAchievementsProgress function
void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m){
    int ctr;
    float percentage = 0.0;
    float percentageTot = 0.0;
    for (int i = 0; i < m; ++i) {
        achievements[i].print();
        ctr = 0;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < profiles[j].getN(); ++k) {
//                totCtr++;
                if (profiles[j].getAchievement(k) == achievements[i]) {
                    ctr++;
                    break;
                }
            }
        }
        percentage = (double) ctr / n * 100;
        percentageTot += percentage;
        cout << "---Percentage of users who have this achievement: " << percentage << "%\n";
    }
    cout << "------Average completion rate of the game: " << percentageTot / (float) m << "%\n";


//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < profiles[i].getN(); ++j) {
//
//        }
//    }
}



// Don't modify
int main() {
    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {  // Testing Achievement methods.
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {  // Testing UserProfile methods.
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {  // Testing showAchievementsProgress function.
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}