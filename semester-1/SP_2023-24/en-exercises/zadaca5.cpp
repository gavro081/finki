#include <iostream>
using namespace std;
int main() {
    int date_today,n,today_year,today_month,today_day;
    int bday,y,m,d;
    cin>>date_today>>n;
    today_year=date_today%10000;
    today_day=date_today/1000000;
    today_month=(date_today/10000)%100;
    for (int i=0; i<n; i++){
        cin>>bday;
        y=bday%10000;
        d=bday/1000000;
        m=(bday/10000)%100;
        if (today_year-y>18) cout<<"YES\n";
        else if (today_year-y<18) cout<<"NO\n";
        else {
            if (today_month>m) cout<<"YES\n";
            else if (today_month<m) cout<<"NO\n";
            else {
                if (today_day>=d) cout<<"YES\n";
                else cout<<"NO\n";
            }
        }
    }
    return 0;
}
