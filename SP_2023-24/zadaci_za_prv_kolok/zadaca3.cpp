#include <iostream>
using namespace std;
int main() {
    int n,suma,maxSuma=0, broj;
    cin>>n;
    for (int i=1; i<n; i++){
        suma=0;
        for (int j=1; j<i; j++){
            if (i%j==0 && i!=j) suma+=j;
        }
        if (suma>maxSuma) {
            broj = i;
            maxSuma=suma;
            }
        }
    cout<<broj;

    return 0;
}
