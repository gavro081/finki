#include <iostream>
using namespace std;
int main() {
    char a;
    int br1,suma=0,br=0;
    while (cin.get(a)){
        if (a=='!') break;
        else {
            if (a >= '0' && a <= '9') {
                if (br==1) {
                    suma+=9*br1;
                }
                br1 = a - '0';
                suma+=br1;
                br++;
            }
            else {
                br=0;
                br1=0;
            }
        }

    }
    cout<<suma;

    return 0;
}
