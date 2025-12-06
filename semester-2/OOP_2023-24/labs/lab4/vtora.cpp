#include <iostream>
#include <cstring>

using namespace std;


class Student{
    char *name;
    int age;
    char *major;
public:
//    Student(){}

    Student(const char *name1="", int age1=0, const char *major1=""){
        age = age1;
        name = new char [strlen(name1)];
        strcpy(name, name1);
        major = new char [strlen(major1)];
        strcpy(major, major1);
    }

    Student (Student& s1){
        age = s1.age;
        name = new char [strlen(s1.name)];
        strcpy(name, s1.name);
        major = new char [strlen(s1.major)];
        strcpy(major, s1.major);
    }

    char *getName() { return name; }
    char *getMajor() { return major; }

    int getAge() { return age; }
};

class Classroom{
    Student *students;
    int numStudents;
    int capacity;
public:

    Classroom(int numStudents1=0, int capacity1=0){
        numStudents = numStudents1;
        capacity = capacity1;
    }

    Classroom(const Classroom& ob){
        numStudents = ob.numStudents;
        capacity = ob.capacity;
        students = new Student[numStudents];
        for (int i = 0 ; i < numStudents; i++){
            students[i] = ob.students[i];
        }
    }

    Classroom& operator=(const Classroom& ob){
        numStudents = ob.numStudents;
        capacity = ob.capacity;
        students = new Student[numStudents];
        for (int i = 0 ; i < numStudents; i++){
            students[i] = ob.students[i];
        }
        return *this;
    }

    void printStudents(){
        for (int i = 0 ; i < numStudents; i++){
            cout << students[i].getName() << " (" << students[i].getAge() << ", " <<
                 students[i].getMajor() << ")\n";
        }
        cout << '\n';
    }
    void add(Student &s){
        Student *tmp = new Student [numStudents + 1];
        for (int i = 0; i < numStudents; i++){
            tmp[i] = students[i];
        }
        tmp[numStudents] = s;
        numStudents++;
//        delete [] students;
        students = tmp;
    }

    void remove(char *name){
        int ctr = 0;
        Student *tmp = new Student[numStudents - 1];
        int j = 0;
        for (int i = 0; i < numStudents; i++){
            if (strcmp(students[i].getName(), name) != 0){
                tmp[j++] = students[i];
            }
            else{
                ctr++;
            }
        }
        numStudents -= ctr;
//        delete [] students;
        students = tmp;
    }

    Student& getStudent(int index) {return students[index];}

    int getNumStudents() { return numStudents; }
    
    friend double findMedianAge(Classroom cr);
};

double findMedianAge(Classroom cr){
    for (int i = 0; i < cr.getNumStudents(); i++){
        for (int j = i; j < cr.getNumStudents(); j++){
            if (cr.getStudent(i).getAge() > cr.getStudent(j).getAge()){
                Student tmp = cr.students[i];
                cr.students[i] = cr.students[j];
                cr.students[j] = tmp;
            }
        }
    }
    if (cr.getNumStudents() % 2 != 0) return cr.getStudent(cr.getNumStudents()/2).getAge();
    else {
        int n1 = cr.getStudent(cr.getNumStudents()/2 - 1).getAge();
        int n2 = cr.getStudent(cr.getNumStudents()/2).getAge();
        return (double)(n1 + n2) / 2;
    }
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; /// Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}

