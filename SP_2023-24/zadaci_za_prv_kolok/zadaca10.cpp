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
        if (c1==c2) continue; // ako poslednit 2 cifri se isti brojot ne e cikcak
        else if (c1>c2) prov=1; // moram tuka da go stavam ova za da znam
        else prov=-1;          // dali broevite trgaat vo rastecki ili opagacki redosled
        tmp/=10;
        while (tmp>=10){
            c1=c2;   /*vtorata cifra da stane prva za da se izbegnat slucai
		 	kako 9652 | 9>6 5>2*/
            c2=(tmp/10)%10;
            tmp/=10;
            if (prov==1){
                if (c1<c2) prov=-1; // za da prodolzi so proveruvanja od slednoto vrtenje
                else prov=2;  // ako p e 2 znaci nema da go printa brojot
            }
            else if(prov==-1){
                if (c1>c2) prov=1;
                else prov=2;  // ako p e 2 znaci nema da go printa brojot
            }
        }
        if (prov==1 || prov==-1) cout<<broj<<"\n";
    }
    return 0;
    }


