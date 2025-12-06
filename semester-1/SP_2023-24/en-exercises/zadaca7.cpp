#include <iostream>
using namespace std;
int main() {
    int n,imax;
    cin>>n;
    int maxS=0;
    for (int i=0;i<n;i++){
        int sum=0;
        for (int j=1;j<i;j++){
            if (i%j==0) sum+=j;
        }
        if (sum>maxS) {
            maxS = sum;
            imax=i;
        }
    }
    cout<<imax;
    return 0;
}
