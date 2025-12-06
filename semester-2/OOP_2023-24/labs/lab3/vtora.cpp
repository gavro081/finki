//DO NOT CHANGE main()
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Employee{
    char name[100];
    char surname[100];
    int salary;
public:
    Employee(){}

    ~Employee(){}

    Employee(const char* name, const char* surname, int salary) : salary(salary){
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    Employee(const Employee& ob){
        strcpy(name, ob.name);
        strcpy(surname, ob.surname);
        salary = ob.salary;
    }

    void printEmployee(){
        cout << "Employee name: " << name << '\n';
        cout << "Employee surname: " << surname << '\n';
        cout << "Employee salary: " << salary << '\n';
    }

    int getSalary() {return salary;}
    const char* getName() {return name;}
    const char* getSurname() {return surname;}

    void setName (const char* name) { strcpy(this->name, name);}
    void setSurame (const char* surname) { strcpy(this->surname, surname);}
    void setSalary(int salary) {this->salary = salary;}

};

class TechCompany{
    char name[100];
    Employee employees[50];
    int numOfEmployees;
public:
    TechCompany(){}

    TechCompany(const char* name){
        strcpy(this->name, name);
        numOfEmployees = 0;
    }
    TechCompany(const TechCompany& ob){
        strcpy(name, name);
        numOfEmployees = ob.numOfEmployees;
        for (int i = 0; i < numOfEmployees; ++i) {
            employees[i] = ob.employees[i];
        }
    }

    void addEmployee(const Employee& ob){
        employees[numOfEmployees++] = ob;
    }

    char* getName (){return name;}
    Employee getEmployee(int index) {return employees[index];}
    int getNumOfEmployees() {return numOfEmployees;}

    void setName(const char* name) {
        strcpy(this->name, name);
    }

    ~TechCompany(){}

    void printCompany(){
        cout << "Tech Company name: " << name << '\n';
        cout << "Number of employees: " << numOfEmployees << '\n';
    }

    double getAverageOfEmployeesSalary(){
        int salaryTot = 0;
        for (int i = 0; i < numOfEmployees; ++i) {
            salaryTot += employees[i].getSalary();
        }
        return (double) salaryTot / numOfEmployees;
    }

};

TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies){
    TechCompany maxCompany = companies[0];
    for (int i = 0; i < numCompanies; ++i) {
        if (companies[i].getAverageOfEmployeesSalary() > maxCompany.getAverageOfEmployeesSalary()){
            maxCompany = companies[i];
        }
    }
    return maxCompany;
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies) {
    float varCurr;
    float stdCurr;
    float avgCurr;
    float sumCurr;
    TechCompany maxCompany;
    float stdMax = 0.0;
    int partialSum;
    for (int i = 0; i < numCompanies; ++i) {
        sumCurr = 0;
        avgCurr = companies[i].getAverageOfEmployeesSalary();
        for (int j = 0; j < companies[i].getNumOfEmployees(); ++j) {
            partialSum = companies[i].getEmployee(j).getSalary() - avgCurr;
            partialSum *= partialSum;
            sumCurr += partialSum;
        }
        varCurr = sumCurr / (companies[i].getNumOfEmployees() - 1);
        stdCurr = sqrt(varCurr);

        if (stdCurr > stdMax) {
            stdMax = stdCurr;
            maxCompany = companies[i];
        }
    }

    return maxCompany;
}
bool isSameCompany(TechCompany& company1, TechCompany& company2){
    return strcmp(company1.getName(),company2.getName()) == 0;
}

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumOfEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
