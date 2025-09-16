#include <iostream>
#include <string>
using namespace std;

// ====================
// Base Class: Person
// ====================
class Person {
private:
    int idNum;
    string lastName;
    string firstName;

public:
    void setFields(int, string, string);
    void outputData();
    int getId();
};

// ---------------------
// Person definitions
// ---------------------
void Person::setFields(int num, string last, string first) {
    idNum = num;
    lastName = last;
    firstName = first;
}

void Person::outputData() {
    cout << "ID # " << idNum
         << "   Name: " << firstName << " " << lastName << endl;
}

int Person::getId() {
    return idNum;
}

// =========================
// Derived Class: Employee
// =========================
class Employee : public Person {
private:
    int dept;
    double hourlyRate;

public:
    void setFields(int, string, string, int, double);
    void outputData();
};

// -------------------------
// Employee definitions
// -------------------------
void Employee::setFields(int num, string last, string first,
                         int dep, double sal) {
    Person::setFields(num, last, first);  // call base version
    dept = dep;
    hourlyRate = sal;
}

void Employee::outputData() {
    Person::outputData();  // call base version
    cout << "Department # " << dept
         << "   Pay rate $ " << hourlyRate << endl;
}

// ===================
// main() to test
// ===================
int main() {
    Employee e;
    e.setFields(502, "Brown", "Alice", 12, 55.75);
    e.outputData();
    return 0;
}
