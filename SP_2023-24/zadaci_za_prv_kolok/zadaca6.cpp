#include <iostream>
using namespace std;
int main() {
    float z,a,b,brojac, parovi;
    cin>>z;
    float p=0.0;
    parovi=0.0;
    brojac=0.0;
    while (cin>>a>>b){
        if (a==0 && b==0) break;
        else {
            brojac++;
            if (a + b == z) parovi++;
        }
    }
    cout<<"Vnesovte "<<parovi<<" parovi od broevi chij zbir e "<<z<<endl;
    cout<<"Procentot na parovi so zbir "<<z<<" e "<<(parovi/brojac)*100<<"%\n";


    return 0;
}
