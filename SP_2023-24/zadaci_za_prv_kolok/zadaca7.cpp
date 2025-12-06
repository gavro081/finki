
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    if (n<2) return 1;
    for (int i=0; i<n; i++){
        cout<<"%";
        if (i==0 || i==n-1) {
            for (int j = 0; j < n-2; j++) {
                cout << "@";
            }
        }
        else {
            for (int j = 0; j < n-2; j++) {
                cout << ".";
            }
        }
        cout<<"%\n";
    }
    return 0;
}
