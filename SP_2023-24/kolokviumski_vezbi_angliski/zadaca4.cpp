#include <iostream>
using namespace std;
int main() {
    int n;
    float points,max_points;
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>points>>max_points;
        if (points<max_points/2) cout<<points/max_points*100<<" FAIL\n";
        else if (points>=max_points*0.9) cout<<points/max_points*100<<" "<<10<<endl;
        else if (points>=max_points*0.8) cout<<points/max_points*100<<" "<<9<<endl;
        else if (points>=max_points*0.7) cout<<points/max_points*100<<" "<<8<<endl;
        else if (points>=max_points*0.6) cout<<points/max_points*100<<" "<<7<<endl;
        else if (points>=max_points*0.5) cout<<points/max_points*100<<" "<<6<<endl;
    }
    return 0;
}
