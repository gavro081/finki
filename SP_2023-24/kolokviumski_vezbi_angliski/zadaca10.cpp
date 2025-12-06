#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int z,a,b;
    float br=0.0, totalbr=0.0;
    cin>>z;
    while (cin>>a>>b){
        if (a==0 && b==0) break;
        else {
            if (a+b==z) br++;
        }
        totalbr++;
    }
    cout<<"You entered "<<br<<" pairs of numbers that have a sum equal to "<<z<<endl;
    cout<<"The percentage of pairs with sum "<<z<<" is "<<(br/totalbr)*100<<"%\n";
    return 0;
}
