#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int m,n;
    cin>>m>>n;
    for (int i=m;i<=n;i++){
        int tmp=i;
        int cifra;
        bool p=true;
        while (tmp>0){
            cifra=tmp%10;
            if (cifra%2!=0) {
                p=false;
                break;
            }
            tmp/=10;
        }
        if (p) {
            cout<<i;
            return 0;
        }
    }
    cout<<"NSN";
    return 0;
}
