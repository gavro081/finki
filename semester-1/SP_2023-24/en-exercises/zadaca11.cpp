#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int a,b,c;
    cin>>a>>b>>c;
    if (a+b+c!=180) cout<<"NO";
    else {
        cout<<"YES\n";
        if(a>90 || b>90 || c>90) cout<<"OBTUSE\n";
        else if (a==90 || b==90 || c==90) cout<<"RIGHT\n";
        else cout<<"ACUTE\n";
    }
    return 0;
}
