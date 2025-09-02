#include <iostream>
#include <string>
using namespace std;

// -------------------------------------------------
// Class: Classroom
// Demonstrates dynamic memory allocation for an
// array of student names, destructor cleanup, and
// operator= overload for deep copying.
// -------------------------------------------------
class Classroom {
private:
    string* student;   // Dynamic array to store student names
    int numStudents;   // Number of students in the class
    int gradeLevel;    // Grade level of this classroom

public:
    Classroom();                  // Constructor: allocates memory and reads input
    ~Classroom();                 // Destructor: frees memory
    void display();               // Display class info
    Classroom& operator=(Classroom&);  // Assignment operator overload
};

// -------------------------------------------------
// Constructor: prompts user for class info and
// dynamically allocates memory for student names
// -------------------------------------------------
Classroom::Classroom() {
    int x;
    cout << "What grade level is this class? ";
    cin >> gradeLevel;

    cout << "How many students in this class? ";
    cin >> numStudents;

    // Dynamically allocate memory for students
    student = new string[numStudents];

    // Input each student's name
    for (x = 0; x < numStudents; x++) {
        cout << "Please enter the student's name: ";
        cin >> student[x];
    }
}

// -------------------------------------------------
// Destructor: releases the dynamically allocated
// memory to avoid memory leaks
// -------------------------------------------------
Classroom::~Classroom() {
    delete[] student;
}

// -------------------------------------------------
// display(): prints out grade level and all student names
// -------------------------------------------------
void Classroom::display() {
    int x;
    cout << "Grade " << gradeLevel << " class list:" << endl;
    for (x = 0; x < numStudents; x++) {
        cout << student[x] << endl;
    }
}

// -------------------------------------------------
// Assignment Operator Overload
// Ensures deep copy (copies actual names, not just pointer)
// -------------------------------------------------
Classroom& Classroom::operator=(Classroom& aClassroom) {
    int x;

    // Copy grade level and number of students
    gradeLevel = aClassroom.gradeLevel;
    numStudents = aClassroom.numStudents;

    // Free old memory
    delete[] student;

    // Allocate new memory of correct size
    student = new string[numStudents];

    // Copy student names one by one
    for (x = 0; x < numStudents; x++) {
        student[x] = aClassroom.student[x];
    }

    // Return reference to current object
    return *this;
}

// -------------------------------------------------
// Main Program
// Demonstrates constructor, display, assignment
// operator, and destructor when object goes out of scope
// -------------------------------------------------
int main() {
    Classroom oneClass; {    // Create first classroom
        Classroom anotherClass;   // Create another classroom

        cout << "The original classroom before assignment:" << endl;
        oneClass.display();

        cout << endl << "The second classroom:" << endl;
        anotherClass.display();

        // Assign contents of anotherClass to oneClass
        oneClass = anotherClass;

        cout << "The original classroom after assignment:" << endl;
        oneClass.display();
    } // <- anotherClass goes out of scope here, destructor called

    cout << endl;
    cout << "After the second class has gone out of scope:" << endl;
    oneClass.display();  // oneClass still has a deep copy

    return 0;
}
