#include <iostream>
#include <string>
using namespace std;

// ===== Base class Person =====
class Person {
protected:
    int id;
    string lastName;
    string firstName;

public:
    // Sets the person's fields
    void setFields(int i, const string &last, const string &first) {
        id = i;
        lastName = last;
        firstName = first;
    }

    // Outputs person's data
    void outputData() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
    }
};

// ===== Derived class Customer =====
class Customer : public Person {
private:
    double balanceDue;

public:
    // Sets the balance due
    void setBalDue(double bal) {
        balanceDue = bal;
    }

    // Outputs the balance due
    void outputBalDue() const {
        cout << "Balance Due: $" << balanceDue << endl;
    }
};

// ===== main() function =====
int main() {
    Customer cust;

    // The next two functions are defined in base class Person
    cust.setFields(215, "Santini", "Linda");
    cust.outputData();

    // The next two functions are defined in derived class Customer
    cust.setBalDue(147.95);
    cust.outputBalDue();

    return 0;
}
