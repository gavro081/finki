#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

class Sentence{
    vector<string>words;
    vector<string>stopwords;
public:
    Sentence(vector<string>stopwords){
        this->stopwords = stopwords;
    }

    Sentence operator+=(string word){
        unsigned int n = stopwords.size();
        for (int i = 0; i < n; ++i) {
            if (stopwords.at(i) == word) return *this;
        }
        words.push_back(word);
        return *this;
    }

    Sentence operator-=(string word){
        for (int i = 0; i < words.size(); ++i) {
            if (words.at(i) == word) words.erase(words.begin() + i);
        }
        return *this;
    }

    friend ostream & operator<<(ostream& out, Sentence& ob){
        for (int i = 0; i < ob.words.size(); ++i) {
            out << ob.words.at(i) << " ";
        }
        return out;
    }
};

int main() {
    // Read stopwords from standard input
    vector<string> stopwords;
    string stopword;
    while (cin >> stopword) {
        if (stopword == "done") {
            break;
        }
        stopwords.push_back(stopword);
    }

    // Create a Sentence object with the stopwords
    Sentence sentence(stopwords);

    // Read words to add to the sentence from standard input
    string word;
    while (cin >> word) {
        if (word == "exit") {
            break;
        }
        sentence += word;
    }

    // Display the sentence
    cout << sentence << endl;

    // Demonstrate removing a word
    cin >> word;
    sentence -= word;

    // Display the updated sentence
    cout << sentence << endl;

    return 0;
}
