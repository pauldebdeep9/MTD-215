// student_encapsulation.cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int idNum;
    string lastName;
    double gpa;
public:
    // simple mutators/accessors (public API hides private data)
    void setId(int id) { idNum = id; }
    void setLastName(const string& ln) { lastName = ln; }
    void setGpa(double v) { gpa = v; }
    int getId() const { return idNum; }
    string getLastName() const { return lastName; }
    double getGpa() const { return gpa; }

    void displayStudentData(); // declaration only here
};

// scope-resolution shows this function belongs to Student
void Student::displayStudentData() {
    cout << "Student #" << idNum << " last name: " << lastName << "\n";
    cout << "GPA: " << gpa << "\n";
}

int main() {
    Student s;
    s.setId(1001);
    s.setLastName("Tan");
    s.setGpa(3.85);
    s.displayStudentData();
}
