#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n,a,b;
    cin>>n;
    for (int i=0;i<n;i++){
        int aprevrten=0,tmp=0,br=0,stepen=1;
        cin>>a>>b;
        tmp=a;
        aprevrten=tmp%10;
        while (tmp>0){
            tmp/=10;
            br++;
        }
        //  123
        // /123
        stepen=pow(10,br-1);
        if (aprevrten!=0) aprevrten=(a/10)% stepen + (aprevrten*stepen);
        else {
            if (a%stepen==0) aprevrten=a/stepen*(stepen/10);
            else aprevrten = a / 10;
        }
        if (aprevrten>b) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
