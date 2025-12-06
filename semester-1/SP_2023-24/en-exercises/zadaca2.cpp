#include <iostream>
using namespace std;
int main() {
    int a,b,maxcifra,br=0,proizvod;
    int sreden;
    cin>>a>>b;
    for (int i=a; i<=b; i++){
        proizvod=1.0;
        int tmp=i;
        tmp/=10;
        while (tmp>0){
            if (tmp<10) {
                maxcifra=tmp;
                break;
            }
            proizvod*=tmp%10;
            tmp/=10;
        }
        int mincifra=i%10;
        sreden=maxcifra*10+mincifra;
        if (proizvod%sreden==0 && proizvod/sreden!=0){
            br++;
            cout << i << " -> (" << proizvod << " == " << maxcifra * 10 + i % 10 << " * " << proizvod/sreden << ")\n";
        }
    }
    cout << br << "\n";

    return 0;
}
