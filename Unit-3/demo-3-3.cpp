#include <iostream>
using namespace std;

// ---------------------- CLASS Employee ----------------------
class Employee {
private:
    int idNum;       // Employee ID number (for identification)
    double salary;   // Employee salary

public:
    // Constructor to initialize employee with ID and salary
    Employee(int, double);

    // Overloaded + operator: returns sum of two employees' salaries
    double operator+(Employee);

    // Overloaded - operator: returns difference between two employees' salaries
    double operator-(Employee);
};

// ---------------------- CONSTRUCTOR ----------------------
Employee::Employee(int id, double sal) {
    idNum = id;      // Assign employee ID
    salary = sal;    // Assign employee salary
}

// ---------------------- OPERATOR + ----------------------
double Employee::operator+(Employee emp) {
    // Add salaries of this employee and the passed employee
    double total = salary + emp.salary;
    return total;    // Return the total
}

// ---------------------- OPERATOR - ----------------------
double Employee::operator-(Employee emp) {
    // Subtract passed employee’s salary from this employee’s salary
    double difference = salary - emp.salary;
    return difference;   // Return the difference
}

// ---------------------- MAIN PROGRAM ----------------------
int main() {
    // Create two employee objects with IDs and salaries
    Employee clerk(1234, 400.00);   // Clerk earns $400
    Employee driver(3456, 650.00);  // Driver earns $650

    // Use overloaded + operator to sum their salaries
    double sum = clerk + driver;
    cout << "Adding clerk to driver -- Sum is $" << sum << endl;

    // Use overloaded - operator to subtract clerk's salary from driver’s
    double diff = driver - clerk;
    cout << "Subtracting clerk from driver -- Difference is $" << diff << endl;

    return 0;
}
