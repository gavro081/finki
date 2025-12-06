//
// Created by Filip on 29.12.24.
//
#include <iostream>
#include <cmath>

using namespace std;

void print_time(double total_sec, double distance);
void pace_to_time();
void helper_time_to_pace(int hours, int minutes, int seconds, double distance);
void time_to_pace();

int main() {
    int input;
    cout << "For calculating a race result for a certain pace, press 1."
            "\nFor required pace for a certain time target, press 2.\n";
    cin>>input;
    if (input==1) pace_to_time();
    else if (input==2) time_to_pace();
    else cout<<"Invalid input!\n";
}

void print_time(double total_sec, double distance) {
    total_sec *= distance;
    total_sec = round(total_sec);
    int sec, min, hours;
    sec = min = hours = 0;
    if (total_sec >= 3600) {
        hours = floor(total_sec / 3600);
        total_sec -= hours * 3600;
    }
    if (total_sec >= 60) {
        min = floor(total_sec / 60);
        total_sec -= min * 60;
    }
    if (total_sec > 0) {
        sec = int (total_sec);
    }
    if (hours > 0) {
        cout << hours << ":";
        if (min==0) cout<<"00:";
    }
    if (min > 0) cout << min << ":";
    if (sec == 0) cout << "00\n";
    else if (sec < 10) cout << "0" << sec << '\n';
    else cout << sec << '\n';
}

void pace_to_time(){
    int min, sec;
    cout << "Enter your pace!\n";
    cout << "minutes:";
    cin >> min;
    cout << "seconds:";
    cin >> sec;
    int total_sec = 60 * min + sec;
    cout << "Your 5K time is: ";
    print_time(double (total_sec), 5);
    cout << "Your 10K time is: ";
    print_time(double (total_sec), 10);
    cout << "Your Half-Marathon time is: ";
    print_time(double (total_sec), 21.1);
    cout << "Your Marathon time is: ";
    print_time(double (total_sec), 42.2);
}

void helper_time_to_pace(int hours, int minutes, int seconds, double distance){
    auto total_sec = double (3600*hours + 60*minutes + seconds);
    int min,sec;
    min = sec = 0;
    total_sec /= distance;
    if (total_sec>=60.00){
        min = int(total_sec/60);
        total_sec-=double (60*min);
    }
    if (total_sec>0.00){
        sec = int(total_sec);
    }
    cout<<"Your target pace is ";
    if (min>0){
        if (min<10) cout<<0<<min<<":";
        else cout<<min<<":";
    }
    if (sec<10) cout<<0<<sec<<'\n';
    else cout<<sec<<'\n';

}

void time_to_pace(){
    int input, hours,seconds,minutes;
    hours = minutes = seconds = 0;
    double distance;
    cout<<"Choose type of race\n"
          "1 - 5K\n"
          "2 - 10K\n"
          "3 - Half-Marathon\n"
          "4 - Marathon\n";
    cin>>input;
    switch (input) {
        case 1: distance=5; break;
        case 2: distance=10; break;
        case 3: distance=21.1; break;
        case 4: distance=42.2; break;
        default:cout<<"Invalid input!\n";return;
    }
    cout<<"Enter target time:\n";
    if (input!=1){
        cout << "hours:";
        cin >> hours;
    }
    cout<<"minutes:";
    cin>>minutes;
    cout<<"seconds:";
    cin>>seconds;
    helper_time_to_pace(hours,minutes,seconds,distance);
}
