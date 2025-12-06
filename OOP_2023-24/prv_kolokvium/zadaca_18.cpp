//STARTER
#include <iostream>
#include <cstring>


using namespace std;


struct SkiLift{
   char ime[15];
   int n;
   bool daliPusten;
};


struct SkiCenter{
   char ime[20];
   char drzava[20];
   SkiLift liftovi[20];
   int n;
};


void najgolemKapacitet(SkiCenter *sc, int n){
   int ctr, maxCtr;
   SkiCenter maxSc;
   ctr = maxCtr = 0;
   for (int i = 0; i < n; ++i) {
       ctr = 0;
       for (int j = 0; j < sc[i].n; ++j) {
           if (sc[i].liftovi[j].daliPusten)
           ctr += sc[i].liftovi[j].n;
       }
       if (ctr > maxCtr) {
           maxSc = sc[i];
           maxCtr = ctr;
       }
       if (ctr == maxCtr) {
          if (maxSc.n < sc[i].n) maxSc = sc[i];
       }
   }
   cout << maxSc.ime << '\n';
   cout << maxSc.drzava << '\n';
   cout << maxCtr << '\n';
}


int main()
{
   int n;
   cin >> n;
   SkiCenter sc[20];
   for (int i = 0; i < n; i++){
       cin >> sc[i].ime;
       cin >> sc[i].drzava;
       cin >> sc[i].n;


       for (int j = 0; j < sc[i].n; ++j) {
           cin >> sc[i].liftovi[j].ime;
           cin >> sc[i].liftovi[j].n;
           cin >> sc[i].liftovi[j].daliPusten;
       }


   }


   najgolemKapacitet(sc, n);


   return 0;
}


