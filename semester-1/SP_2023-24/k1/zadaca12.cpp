#include <iostream>
using namespace std;
int main() {
    int n,br0=0,br1=0,br2=0,br3=0,br4=0,cifra=0;
    while (cin>>n){
        int a=n;
        int br=0;
        int max=0;
        while (a>0){
            cifra=a%10;
            a/=10;
            if (cifra>max) max=cifra;

        }
        while (n>0){
            cifra=n%10;
            n/=10;
            if (cifra==max) break;
            br++;
        }
        if (br==0) br0++;
        else if (br==1) br1++;
        else if (br==2) br2++;
        else if (br==3) br3++;
        else if (br==4) br4++;
    }
    cout<<0<<": "<<br0<<"\n";
    cout<<1<<": "<<br1<<"\n";
    cout<<2<<": "<<br2<<"\n";
    cout<<3<<": "<<br3<<"\n";
    cout<<4<<": "<<br4<<"\n";
    return 0;
}
