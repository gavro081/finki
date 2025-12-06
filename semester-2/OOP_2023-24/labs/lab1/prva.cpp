#include <iostream>

using namespace std;

struct Transaction{
    int id;
    int sum;
    int fee;
    bool type;

    void print(){
        cout << id << ' ' << sum + fee << '\n';
    }
};

int main(){
    int n, suma = 0;
    bool p = false;
    cin >> n;
    Transaction transactions[n];
    for (int i = 0; i < n; ++i) {
        cin >> transactions[i].id;
        cin >> transactions[i].sum;
        cin >> transactions[i].fee;
        cin >> transactions[i].type;
    }

    for (int i = 0; i < n; ++i) {
        if (transactions[i].type) {
            transactions[i].print();
            suma += transactions[i].sum;
            p = true;
        }
    }
    if (!p) cout << "No credit card transaction\n";
}