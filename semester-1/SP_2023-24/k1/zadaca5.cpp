#include <iostream>
using namespace std;
int main() {
    int a,b,cifra;
    cin>>a>>b;
    if (a<=0 || b<=0) {
        cout<<"Invalid input";
        return 0;
    }
    if (b>a) {
        int temp=b;
        b=a;
        a=temp;
    }
    int temp=0;
    a/=10;
        while (a>0) {
            cifra = a % 10;
            temp = 10 * temp + cifra;
            a /= 100;
        }
        cifra=0;
        int novtemp=0;
        while (temp>0){
            cifra = temp % 10;
            novtemp = 10 * novtemp + cifra;
            temp /= 10;
        }
            if (novtemp == b) cout << "PAREN";
            else cout << "NE";
    return 0;
}
