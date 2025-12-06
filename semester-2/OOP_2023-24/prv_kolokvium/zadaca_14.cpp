#include<iostream>
#include<cstring>


using namespace std;


enum Extension {
   pdf, txt, exe
};
const char *extensions[] = {"pdf", "txt", "exe"};


class File {
   char *fileName;
   Extension ext;
   char *fileOwner;
   int fileSize;
public:
   File() {}


   File(const char *fileName,const char *fileOwner, int fileSize, Extension ext)
           : ext(ext), fileSize(fileSize) {
       this->fileName = new char[strlen(fileName) + 1];
       strcpy(this->fileName, fileName);
       this->fileOwner = new char[strlen(fileOwner) + 1];
       strcpy(this->fileOwner, fileOwner);
   }


   File(const File &ob) {
       this->ext = ob.ext;
       this->fileSize = ob.fileSize;
       this->fileName = new char[strlen(ob.fileName) + 1];
       strcpy(this->fileName, ob.fileName);
       this->fileOwner = new char[strlen(ob.fileOwner) + 1];
       strcpy(this->fileOwner, ob.fileOwner);
   }


   ~File() {
       delete[] fileName;
       delete[] fileOwner;
   }


   File &operator=(const File &ob) {
       if (this != &ob) {
           this->ext = ob.ext;
           this->fileSize = ob.fileSize;
           this->fileName = new char[strlen(ob.fileName) + 1];
           strcpy(this->fileName, ob.fileName);
           this->fileOwner = new char[strlen(ob.fileOwner) + 1];
           strcpy(this->fileOwner, ob.fileOwner);
       }
       return *this;
   }


   void print() {
       cout << "File name: " << fileName << '.' << extensions[ext] << '\n';
       cout << "File owner: " << fileOwner << '\n';
       cout << "File size: " << fileSize << '\n';
   }


   bool equals(const File &that) {
       return (strcmp(fileOwner, that.fileOwner) == 0 && this->equalsType(that));
   }


   bool equalsType(const File &that) {
       return (ext == that.ext && strcmp(fileName, that.fileName) == 0);
   }
};


class Folder {
   char *folderName;
   int numFiles;
   File *files;
public:
   Folder(const char *name) {
       numFiles = 0;
       files = NULL;
       folderName = new char[strlen(name) + 1];
       strcpy(this->folderName, name);
   }


   ~Folder() {
       delete[] folderName;
       delete[] files;
   }


   void print() {
       cout << "Folder name: " << folderName << '\n';
       for (int i = 0; i < numFiles; ++i) {
           files[i].print();
       }
   }


   void remove(const File &file) {
       File *tmp = new File[numFiles - 1];
       int j = 0;
       bool p = false;
       for (int i = 0; i < numFiles; ++i) {
           if (files[i].equals(file) && !p) {
               p = true;
           } else tmp[j++] = files[i];
       }
       numFiles--;
       delete[] files;
       files = tmp;
   }


   void add(const File &file) {
       File *tmp = new File[numFiles + 1];
       for (int i = 0; i < numFiles; ++i) {
           tmp[i] = files[i];
       }
       tmp[numFiles++] = file;
       delete [] files;
       files = tmp;
   }
};


int main() {
   char fileName[20];
   char fileOwner[20];
   int ext;
   int fileSize;


   int testCase;
   cin >> testCase;
   if (testCase == 1) {
       cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
       cin >> fileName;
       cin >> fileOwner;
       cin >> fileSize;
       cin >> ext;


       File created = File(fileName, fileOwner, fileSize, (Extension) ext);
       File copied = File(created);
       File assigned = created;


       cout << "======= CREATED =======" << endl;
       created.print();
       cout << endl;
       cout << "======= COPIED =======" << endl;
       copied.print();
       cout << endl;
       cout << "======= ASSIGNED =======" << endl;
       assigned.print();
   }
   else if (testCase == 2) {
       cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
       cin >> fileName;
       cin >> fileOwner;
       cin >> fileSize;
       cin >> ext;


       File first(fileName, fileOwner, fileSize, (Extension) ext);
       first.print();


       cin >> fileName;
       cin >> fileOwner;
       cin >> fileSize;
       cin >> ext;


       File second(fileName, fileOwner, fileSize, (Extension) ext);
       second.print();


       cin >> fileName;
       cin >> fileOwner;
       cin >> fileSize;
       cin >> ext;


       File third(fileName, fileOwner, fileSize, (Extension) ext);
       third.print();


       bool equals = first.equals(second);
       cout << "FIRST EQUALS SECOND: ";
       if (equals)
           cout << "TRUE" << endl;
       else
           cout << "FALSE" << endl;


       equals = first.equals(third);
       cout << "FIRST EQUALS THIRD: ";
       if (equals)
           cout << "TRUE" << endl;
       else
           cout << "FALSE" << endl;


       bool equalsType = first.equalsType(second);
       cout << "FIRST EQUALS TYPE SECOND: ";
       if (equalsType)
           cout << "TRUE" << endl;
       else
           cout << "FALSE" << endl;


       equalsType = second.equals(third);
       cout << "SECOND EQUALS TYPE THIRD: ";
       if (equalsType)
           cout << "TRUE" << endl;
       else
           cout << "FALSE" << endl;


   }
   else if (testCase == 3) {
       cout << "======= FOLDER CONSTRUCTOR =======" << endl;
       cin >> fileName;
       Folder folder(fileName);
       folder.print();


   }
   else if (testCase == 4) {
       cout << "======= ADD FILE IN FOLDER =======" << endl;
       char name[20];
       cin >> name;
       Folder folder(name);


       int iter;
       cin >> iter;


       while (iter > 0) {
           cin >> fileName;
           cin >> fileOwner;
           cin >> fileSize;
           cin >> ext;


           File file(fileName, fileOwner, fileSize, (Extension) ext);
           folder.add(file);
           iter--;
       }
       folder.print();
   }
   else {
       cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
       char name[20];
       cin >> name;
       Folder folder(name);


       int iter;
       cin >> iter;


       while (iter > 0) {
           cin >> fileName;
           cin >> fileOwner;
           cin >> fileSize;
           cin >> ext;


           File file(fileName, fileOwner, fileSize, (Extension) ext);
           folder.add(file);
           iter--;
       }
       cin >> fileName;
       cin >> fileOwner;
       cin >> fileSize;
       cin >> ext;


       File file(fileName, fileOwner, fileSize, (Extension) ext);
       folder.remove(file);
       folder.print();
   }
   return 0;
}
