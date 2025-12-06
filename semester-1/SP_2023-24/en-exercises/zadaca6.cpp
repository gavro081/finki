#include <iostream>
using namespace std;
int main() {
    int a;
    cin>>a;
    if (a<10) cout<<"The number is invalid";
    else {
        for (int i=a-1;i>0;i--){
            int tmp=i,obraten=0,br=0;
            while (tmp>0){
                obraten=10*obraten+tmp%10;
                tmp/=10;
                br++;
            }
            if (obraten%br==0) {
                cout<<i;
                break;
            }
        }
    }
    return 0;
}
