#include <iostream>
#include <string>
using namespace std;

// ===================
// Base Class: Person
// ===================
class Person {
private:
    int idNum;             // only accessible inside Person
    string lastName;
    string firstName;
public:
    // Function prototypes
    void setFields(int, string, string);
    void outputData();
    int getId();
};

// --------------------
// Person Definitions
// --------------------
void Person::setFields(int num, string last, string first) {
    idNum = num;
    lastName = last;
    firstName = first;
}

void Person::outputData() {
    cout << "ID # " << idNum << "   Name: "
         << firstName << " " << lastName << endl;
}

int Person::getId() {
    return idNum;
}

// ==========================
// Derived Class: Employee
// ==========================
class Employee : public Person {
private:
    int dept;               // new field in derived class
    double hourlyRate;      // new field in derived class
public:
    void setFields(int, string, string, int, double);
    void outputData();
};

// ---------------------------
// Employee Definitions
// ---------------------------
void Employee::setFields(int num, string last, string first,
                         int dep, double sal) {
    // Call base class version to set id + names
    Person::setFields(num, last, first);
    // Set own new fields
    dept = dep;
    hourlyRate = sal;
}

void Employee::outputData() {
    // Call base class version to print id + name
    Person::outputData();
    // Print own fields
    cout << "Department # " << dept
         << "   Pay rate $ " << hourlyRate << endl;
}

// ==========================
// main() for demonstration
// ==========================
int main() {
    Employee emp;
    emp.setFields(501, "Smith", "John", 7, 42.50);
    emp.outputData();
    return 0;
}
