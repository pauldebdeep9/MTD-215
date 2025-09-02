#include <iostream>
using namespace std;

// ------------------------------------------------------------
// Employee: minimal class to demonstrate operator overloading.
// ------------------------------------------------------------
class Employee {
private:
    // Private state
    int    idNum;    // e.g., 1234
    double salary;   // e.g., 400.00

    // Non-member operator that needs access to private 'salary'.
    // Declaring it 'friend' lets that function read private fields.
    friend double operator+(double raise, const Employee& emp);

public:
    // Constructor with defaults so we can write: Employee e; or Employee(1234, 400.0)
    Employee(int id = 0, double sal = 0.0) : idNum(id), salary(sal) {}

    // -------- Member operator overloads --------

    // Employee + Employee  -> numeric sum of salaries
    // Marked 'const' because it does not modify either operand.
    double operator+(const Employee& rhs) const {
        return this->salary + rhs.salary;
    }

    // Employee - Employee  -> numeric difference of salaries
    double operator-(const Employee& rhs) const {
        return this->salary - rhs.salary;
    }

    // Employee + double  -> returns a NEW Employee with a raised salary.
    // We *do not* mutate 'this'; we return a copy with the updated salary.
    Employee operator+(double raise) const {
        Employee tmp = *this;        // start with a copy of the left operand
        tmp.salary = this->salary + raise;
        return tmp;                  // enables: Employee e2 = e1 + 50.0;
    }

    // (Optional) helper for printing in this demo
    void print(const string& label = "") const {
        if (!label.empty()) cout << label << ": ";
        cout << "Employee #" << idNum << " with salary $" << salary << '\n';
    }
};

// -------- Non-member (free) operator --------
// double + Employee -> numeric result
// Because it's NOT a member, the left operand can be a built-in ('double').
// We declared it 'friend' so it can read emp.salary directly.
double operator+(double raise, const Employee& emp) {
    // Just a toy example that returns a number; in real code, you might
    // want symmetry with Employee + double (return an Employee).
    return raise + emp.salary;
}

// ---------------------------- Demo (main) ----------------------------
int main() {
    // Create an employee with ID and starting salary
    Employee aClerk(1234, 400.00);
    aClerk.print("Initial aClerk");

    // -------- Employee = Employee + double --------
    // Uses member Employee::operator+(double) returning a NEW Employee
    aClerk = aClerk + 50.00;      // give a $50 raise (returns copy, then assign)
    aClerk.print("After $50 raise (aClerk = aClerk + 50)");

    // You can also construct another Employee directly from the result
    Employee anotherClerk = aClerk + 50.00;  // another $50 on top
    anotherClerk.print("anotherClerk");

    // -------- double = double + Employee --------
    // Uses the friend non-member operator+(double, Employee)
    Employee oneEmp(2222, 14.55);
    double newSalary = 2.33 + oneEmp;        // 2.33 + 14.55 -> 16.88
    cout << "2.33 + oneEmp.salary = $" << newSalary << '\n';

    // -------- Employee ± Employee (numeric results) --------
    double sumSalaries  = aClerk + anotherClerk;  // calls Employee::operator+(Employee)
    double diffSalaries = anotherClerk - aClerk;  // calls Employee::operator-(Employee)
    cout << "Sum of aClerk and anotherClerk salaries = $" << sumSalaries << '\n';
    cout << "Difference (anotherClerk - aClerk)      = $" << diffSalaries << '\n';

    return 0;
}
