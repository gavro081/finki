
#include <iostream>
using namespace std;
int main() {
    int a,b,br=0;
    cin>>a>>b;
    if (a<100 && b>100) a=100;
    else if (a<100 && b<100) return 0;
    for (int i=a; i<=b; i++){
            int digitsum=i%10;
            int tmp=i;
            int sum=0;
            tmp/=10;
            while (tmp>0){
                if (tmp<10) {
                    digitsum += tmp;
                }
                else{
                    sum=sum*10+tmp%10;
                }
                tmp/=10;
            }
            if (sum%digitsum==0 && sum/digitsum!=0) {
                cout << i << " -> (" << sum << " == (" << i % 10 << " + " << digitsum - i % 10 << ") * " << sum/digitsum
                     << ")\n";
                br++;
            }
    }
    cout<<br;
    return 0;
}
