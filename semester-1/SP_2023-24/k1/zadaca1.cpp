#include <iostream>
using namespace std;
int main() {
   int m,n,cifra;
   cin>>m>>n;
    bool k=1;
   for (int i=m; i<=n; i++) {
       int temp = i;
       bool p = 0;
       while (temp > 0) {
           cifra = temp % 10;
           if (cifra % 2 != 0) p = 1;
           temp /= 10;
       }
       if (p == 0) {
           cout << i;
           k=2;
          return 0;
            }
     }
   if (k==1) cout<<"NE";

    return 0;
}
