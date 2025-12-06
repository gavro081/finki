#include <iostream>
using namespace std;
int main() {
    char n;
    int i=0;
    int suma=0;
    while (cin>>n){
        if (n=='.') break;
        else{
                if (n>='0' && n<='9'){
                suma+=(n-'0');
                i++;
            		 }
                else if (n>='a' && n<='f') suma+=n-'a'+0xA;
                else if (n>='A' && n<='F') suma+=n-'A'+0xA;
            }
        }
    if (suma%16==0) {
        if (suma%10==6 && (suma/10)%10==1) cout <<"Poln pogodok";
        else cout << "Pogodok";
        }
    else cout<<suma;

    return 0;
}
