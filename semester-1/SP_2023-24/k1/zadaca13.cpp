#include <iostream>
using namespace std;
int main() {
    int n,suma,cifra,max,tmp;
    max=0;
    while (cin>>n){
        cout<<n<<": ";
        suma=max;
        max=0;
        tmp=n;
        while (tmp>0){
            cifra=tmp%10;
            if (cifra>max) max=cifra;
            tmp/=10;
            suma+=cifra;
        }
        cout<<suma<<"\n";
    }

    return 0;
}


