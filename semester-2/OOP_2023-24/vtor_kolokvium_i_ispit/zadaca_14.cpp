#include <iostream>
#include <cstring>


using namespace std;


class SMS{
protected:
   char number[20];
   float base_price;
   static float TAX;
public:
   virtual float SMS_CENA(){return base_price;}
   friend ostream& operator<<(ostream& out, SMS& ob){
       out << "Tel: "<< ob.number <<
           " - cena: "<< ob.SMS_CENA() << "den.\n";
       return out;
   }
};
float SMS::TAX = 18.0;


class RegularSMS : public SMS{
   char content[1000];
   bool isRoaming;
   static float rProcent;
public:
   RegularSMS (char *number = 0, float base_price=0.0, char* content=0, bool isRoaming=false){
       strcpy(this->number, number);
       strcpy(this->content, content);
       this->base_price = base_price;
       this->isRoaming = isRoaming;
   }
   float SMS_CENA() override {
       float price = base_price * (float)(strlen(content)/160 + 1) ;
       if (isRoaming) price += rProcent/100 * price;
       else price += SMS::TAX/100 * price;
       return price;
   }
   static void set_rProcent (float num) { rProcent = num;}
};
float RegularSMS::rProcent = 300.0;


class SpecialSMS : public SMS{
   bool isCharity;
   static float sProcent;
public:
   SpecialSMS (char *number = 0, float base_price=0.0, bool isCharity=false){
       strcpy(this->number, number);
       this->base_price = base_price;
       this->isCharity = isCharity;
   }
   float SMS_CENA() override {
       float price = SMS::SMS_CENA();
       if (isCharity) return price;
       else return price += sProcent/100 * price;
   }
   static void set_sProcent (float num) { sProcent = num;}
};
float SpecialSMS::sProcent = 150.0;


void vkupno_SMS(SMS** poraka, int n){
   float rSum = 0.0, sSum = 0.0;
   int rCtr = 0, sCtr = 0;
   for (int i = 0; i < n; ++i) {
       SpecialSMS* sPtr = dynamic_cast<SpecialSMS*>(poraka[i]);
       RegularSMS* rPtr = dynamic_cast<RegularSMS*>(poraka[i]);
       if (rPtr) {
           rSum += rPtr->SMS_CENA();
           rCtr++;
       }
       else if (sPtr) {
           sSum += sPtr->SMS_CENA();
           sCtr++;
       }
   }
   cout << "Vkupno ima " << rCtr << " regularni SMS poraki i nivnata cena e: " << rSum << '\n';
   cout << "Vkupno ima " << sCtr << " specijalni SMS poraki i nivnata cena e: " << sSum << '\n';
}


int main(){


   char tel[20], msg[1000];
   float cena;
   float price;
   int p;
   bool roam, hum;
   SMS  **sms;
   int n;
   int tip;


   int testCase;
   cin >> testCase;


   if (testCase == 1){
       cout << "====== Testing RegularSMS class ======" << endl;
       cin >> n;
       sms = new SMS *[n];


       for (int i = 0; i < n; i++){
           cin >> tel;
           cin >> cena;
           cin.get();
           cin.getline(msg, 1000);
           cin >> roam;
           cout << "CONSTRUCTOR" << endl;
           sms[i] = new RegularSMS(tel, cena, msg, roam);
           cout << "OPERATOR <<" << endl;
           cout << *sms[i];
       }
       for (int i = 0; i<n; i++) delete sms[i];
       delete[] sms;
   }
   if (testCase == 2){
       cout << "====== Testing SpecialSMS class ======" << endl;
       cin >> n;
       sms = new SMS *[n];


       for (int i = 0; i < n; i++){
           cin >> tel;
           cin >> cena;
           cin >> hum;
           cout << "CONSTRUCTOR" << endl;
           sms[i] = new SpecialSMS(tel, cena, hum);
           cout << "OPERATOR <<" << endl;
           cout << *sms[i];
       }
       for (int i = 0; i<n; i++) delete sms[i];
       delete[] sms;
   }
   if (testCase == 3){
       cout << "====== Testing method vkupno_SMS() ======" << endl;
       cin >> n;
       sms = new SMS *[n];


       for (int i = 0; i<n; i++){


           cin >> tip;
           cin >> tel;
           cin >> cena;
           if (tip == 1) {


               cin.get();
               cin.getline(msg, 1000);
               cin >> roam;


               sms[i] = new RegularSMS(tel, cena, msg, roam);


           }
           else {
               cin >> hum;


               sms[i] = new SpecialSMS(tel, cena, hum);
           }
       }


       vkupno_SMS(sms, n);
       for (int i = 0; i<n; i++) delete sms[i];
       delete[] sms;
   }
   if (testCase == 4){
       cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
       SMS *sms1, *sms2;
       cin >> tel;
       cin >> cena;
       cin.get();
       cin.getline(msg, 1000);
       cin >> roam;
       sms1 = new RegularSMS(tel, cena, msg, roam);
       cout << *sms1;


       cin >> tel;
       cin >> cena;
       cin.get();
       cin.getline(msg, 1000);
       cin >> roam;
       cin >> p;
       RegularSMS::set_rProcent(p);
       sms2 = new RegularSMS(tel, cena, msg, roam);
       cout << *sms2;


       delete sms1, sms2;
   }
   if (testCase == 5){
       cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
       SMS *sms1, *sms2;
       cin >> tel;
       cin >> cena;
       cin >> hum;
       sms1 = new SpecialSMS(tel, cena, hum);
       cout << *sms1;


       cin >> tel;
       cin >> cena;
       cin >> hum;
       cin >> p;
       SpecialSMS::set_sProcent(p);
       sms2 = new SpecialSMS(tel, cena, hum);
       cout << *sms2;


       delete sms1, sms2;
   }


   return 0;
}
