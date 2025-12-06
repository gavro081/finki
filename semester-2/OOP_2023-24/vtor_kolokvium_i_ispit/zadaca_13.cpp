#include <iostream>
#include <cstdlib>
#include <cstring>


using namespace std;


// TODO...
class Image{
protected:
   char *name;
   char *user;
   int w,h;
public:
   Image(const char* name = "untitled", const char* user = "unknown", int w = 800, int h = 800)
           : w(w),h(h){
       this->name = new char[strlen(name) + 1];
       strcpy(this->name, name);
       this->user = new char[strlen(user) + 1];
       strcpy(this->user, user);
   }


   virtual int fileSize(){
       return w * h * 3;
   }


   friend ostream& operator<<(ostream& COUT, Image& ob){
       COUT << ob.name << " " << ob.user << " " << ob.fileSize() << '\n';
       return COUT;
   }


   bool operator>(Image& ob) {return fileSize() > ob.fileSize();}
};


class TransparentImage : public Image{
   bool transparent;
public:
   TransparentImage(const char* name = "untitled", const char* user = "unknown", int w = 800, int h = 800, bool transparent = true)
   : Image(name,user,w,h), transparent(transparent){}


       int fileSize()override{
       if (transparent) return w * h * 4;
       return w * h + ((w * h) / 8);
   }


   friend ostream& operator<<(ostream& COUT, TransparentImage& ob){
       COUT << ob.name << " " << ob.user << " " << ob.fileSize() << '\n';
       return COUT;
   }
};


class Folder{
protected:
   char name[255];
   char user[50];
   Image* images[100];
   int n;
public:
   Folder(char* name = "", char* user = "unknown"){
       strcpy(this->name, name);
       strcpy(this->user, user);
       n = 0;
   }


   Image* getMaxFile(){
       Image *maxi = images[0];
       for (int i = 0; i < n; ++i) {
           if (images[i]->fileSize() > maxi->fileSize()) maxi = images[i];
       }
       return maxi;
   }


   int folderSize(){
       int sum = 0;
       for (int i = 0; i < n; ++i) {
           sum += images[i]->fileSize();
       }
       return sum;
   }


   Folder& operator+=(Image& i){
       images[n++] = &i;
       return *this;
   }


   friend ostream& operator<<(ostream& COUT, Folder ob){
       COUT << ob.name << " " << ob.user << " \n--\n";
       for (int i = 0; i < ob.n; ++i) {
           COUT << *ob.images[i];
       }
       COUT << "--\nFolder size: " << ob.folderSize();
       return COUT;
   }


   Image* operator[](int index){return images[index];}
};


Folder& max_folder_size(Folder* folders, int n){
   Folder najgolem = folders[0];
   int maxi = 0;
   for (int i = 1; i < n; ++i) {
       if (folders[i].folderSize() > najgolem.folderSize()) {
           najgolem = folders[i];
           maxi = i;
       }
   }
   return folders[maxi];
}




int main() {


   int tc; // Test Case


   char name[255];
   char user_name[51];
   int w, h;
   bool tl;


   cin >> tc;


   if (tc==1){
       // Testing constructor(s) & operator << for class File


       cin >> name;
       cin >> user_name;
       cin >> w;
       cin >> h;




       Image f1;


       cout<< f1;


       Image f2(name);
       cout<< f2;


       Image f3(name, user_name);
       cout<< f3;


       Image f4(name, user_name, w, h);
       cout<< f4;
   }
   else if (tc==2){
       // Testing constructor(s) & operator << for class TextFile
       cin >> name;
       cin >> user_name;
       cin >> w >> h;
       cin >> tl;


       TransparentImage tf1;
       cout<< tf1;


       TransparentImage tf4(name, user_name, w, h, tl);
       cout<< tf4;
   }
   else if (tc==3){
       // Testing constructor(s) & operator << for class Folder
       cin >> name;
       cin >> user_name;


       Folder f3(name, user_name);
       cout<< f3;
   }
   else if (tc==4){
       // Adding files to folder
       cin >> name;
       cin >> user_name;


       Folder dir(name, user_name);


       Image * f;
       TransparentImage *tf;


       int sub, fileType;


       while (1){
           cin >> sub; // Should we add subfiles to this folder
           if (!sub) break;


           cin >>fileType;
           if (fileType == 1){ // Reading File
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               f = new Image(name,user_name, w, h);
               dir += *f;
           }
           else if (fileType == 2){
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               cin >> tl;
               tf = new TransparentImage(name,user_name, w, h, tl);
               dir += *tf;
           }
       }
       cout<<dir;
   }
   else if(tc==5){
       // Testing getMaxFile for folder


       cin >> name;
       cin >> user_name;


       Folder dir(name, user_name);


       Image* f;
       TransparentImage* tf;


       int sub, fileType;


       while (1){
           cin >> sub; // Should we add subfiles to this folder
           if (!sub) break;


           cin >>fileType;
           if (fileType == 1){ // Reading File
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               f = new Image(name,user_name, w, h);
               dir += *f;
           }
           else if (fileType == 2){
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               cin >> tl;
               tf = new TransparentImage(name,user_name, w, h, tl);
               dir += *tf;
           }
       }
       cout<< *(dir.getMaxFile());
   }
   else if(tc==6){
       // Testing operator [] for folder


       cin >> name;
       cin >> user_name;


       Folder dir(name, user_name);


       Image* f;
       TransparentImage* tf;


       int sub, fileType;


       while (1){
           cin >> sub; // Should we add subfiles to this folder
           if (!sub) break;


           cin >>fileType;
           if (fileType == 1){ // Reading File
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               f = new Image(name,user_name, w, h);
               dir += *f;
           }
           else if (fileType == 2){
               cin >> name;
               cin >> user_name;
               cin >> w >> h;
               cin >> tl;
               tf = new TransparentImage(name,user_name, w, h, tl);
               dir += *tf;
           }
       }


       cin >> sub; // Reading index of specific file
       cout<< *dir[sub];
   }
   else if(tc==7){
       // Testing function max_folder_size
       int folders_num;


       Folder dir_list[10];


       Folder dir;
       cin >> folders_num;


       for (int i=0; i<folders_num; ++i){
           cin >> name;
           cin >> user_name;
           dir = Folder(name, user_name);




           Image* f;
           TransparentImage *tf;


           int sub, fileType;


           while (1){
               cin >> sub; // Should we add subfiles to this folder
               if (!sub) break;


               cin >>fileType;
               if (fileType == 1){ // Reading File
                   cin >> name;
                   cin >> user_name;
                   cin >> w >> h;
                   f = new Image(name,user_name, w, h);
                   dir += *f;
               }
               else if (fileType == 2){
                   cin >> name;
                   cin >> user_name;
                   cin >> w >> h;
                   cin >> tl;
                   tf = new TransparentImage(name,user_name, w, h, tl);
                   dir += *tf;
               }
           }
           dir_list[i] = dir;
       }


       cout<<max_folder_size(dir_list, folders_num);
   }
   return 0;
};
