#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int a,b,c,d1,d2,d3;
    while (cin>>a>>b>>c){
        d1= abs(a-c); // 3 8 83
        d2= abs(a-b); // 5
        d3= abs(b-c);
        if (d1<d2 && d1<d3) {
            if (a>c) cout<<c<<" "<<a<<endl;
            else if (a<c) cout<<a<<" "<<c<<endl;
            else if (a==c) cout<<a<<" "<<a<<endl;
        }
        else if (d2<d1 && d2<d3){
            if (a>b) cout<<b<<" "<<a<<endl;
            else if (a<b) cout<<a<<" "<<b<<endl;
            else if (a==b) cout<<b<<" "<<b<<endl;

        }
        else if (d3<d1 && d3<d2){
            if (b>c) cout<<c<<" "<<b<<endl;
            else if (b<c) cout<<b<<" "<<c<<endl;
            else if (b==c) cout<<c<<" "<<c<<endl;
        }
        else {
            if (a<b && a<c) {
                if (b < c) cout << a << " " << b << " " << c << endl;
                else if (b > c) cout << a << " " << c << " " << b << endl;
            }
            if (b<c && b<a) {
                if (a < c) cout << b << " " << a << " " << c << endl;
                else if (a > c) cout << b << " " << c << " " << b << endl;
            }
            if (c<a && c<b) {
                if (a < b) cout << c << " " << a << " " << b << endl;
                else if (a > b) cout << c << " " << b << " " << a << endl;
            }

        }
    }
    return 0;
}
