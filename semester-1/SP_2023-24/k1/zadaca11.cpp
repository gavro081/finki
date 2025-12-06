#include <iostream>
using namespace std;

int main() {
    int broj;
    int c1,c2;
    while (cin>>broj){
        int prov=0;
        int tmp=broj;
        if (broj<10) continue;
        c1=broj%10;
        c2=(broj/10)%10;
        if (c1==c2) continue;
        else if (c1>=5 && c2<5) prov=1;
        else if (c1<5 && c2>=5) prov=-1;
        tmp/=10;
        while (tmp>=10){
            c1=c2;
            c2=(tmp/10)%10;
            tmp/=10;
            if (prov==1){
                if (c1<5 && c2>=5) prov=-1;
                else prov=2;
            }
            else if(prov==-1){
                if (c1>=5 && c2<5) prov=1;
                else prov=2;
            }
        }
        if (prov==1 || prov==-1) cout<<broj<<"\n";
    }
    return 0;
}


