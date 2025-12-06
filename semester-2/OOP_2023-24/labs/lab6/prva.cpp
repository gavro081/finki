#include <iostream>
#include <string>

using namespace std;

// Include necessary libraries and namespaces
class ResultsManager{
public:
    static string simplifyFormat(const string& line1){
        string line = line1;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == 'X') line.replace(i,1,"50");
        }
        return line;
    }

    static int calculateResult(const string& line){
        int sum = 0;
        string line1 = line;
        int num = stoi(line1);
        sum += num;
        int ind;
        while((ind = line1.find(' ')) != -1){
            // 7 5 1
            ind = line1.find(' ');
            line1 = line1.substr(ind + 1);
            num = stoi(line1);
            sum += num;
        }
        return sum;
    }

};



// Don't modify
int main() {
    string lines[2];
    getline(cin, lines[0]);
    getline(cin, lines[1]);
    int score1 = ResultsManager::calculateResult(ResultsManager::simplifyFormat(lines[0]));
    int score2 = ResultsManager::calculateResult(ResultsManager::simplifyFormat(lines[1]));
    cout << "Player " << ((score1 > score2) ? "1 " : "2 ") << "wins with " << abs(score1 - score2) << " additional points.";
}