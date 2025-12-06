#include <iostream>
using namespace std;
int main() {
    int n,ost,cifra,a,broj;
    cin>>n;
    if (!n || n<10) cout<<"Brojot ne e validen";
    else {
    for (int i=n-1; i>0; i--){
        broj=i;
        ost=0;
        a=0;
        while(broj>0){
            cifra=broj%10;
            ost=ost*10+cifra;
            broj/=10;
            a++;
        }

        if (ost%a==0) {
            cout<<i;
            break;
        }
        else continue;
   	 }
    }
    return 0;
}
