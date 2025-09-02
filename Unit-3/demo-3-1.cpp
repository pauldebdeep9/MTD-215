#include <iostream>
using namespace std;

class Customer {
    // Friend function declaration: allows this non-member function
    // to access private members of the Customer class
    friend void displayAsAFriend(Customer);

private:
    int custNum;        // Private data member: customer number
    double balanceDue;  // Private data member: balance due for the customer

public:
    // Constructor with default arguments
    Customer(int = 0, double = 0.0);

    // Member function to display customer info
    void displayCustomer();
};

// Constructor definition
Customer::Customer(int num, double balance) {
    custNum = num;          // Initialize customer number
    balanceDue = balance;   // Initialize balance
}

// Member function definition
void Customer::displayCustomer() {
    cout << "In the member function" << endl;
    cout << "Customer #" << custNum 
         << " has a balance of $" << balanceDue << endl;
}

// Friend function definition
void displayAsAFriend(Customer cust) {
    // Even though this is NOT a member of the class,
    // it can access private variables because it is a friend
    cout << "In the friend function" << endl;
    cout << "Customer #" << cust.custNum 
         << " has a balance of $" << cust.balanceDue << endl;
}


int main() {
    Customer c1(101, 250.75);

    // Calling member function
    c1.displayCustomer();

    // Calling friend function
    displayAsAFriend(c1);

    return 0;
}
// This code demonstrates the use of friend functions in C++.

