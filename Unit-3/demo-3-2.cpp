#include <iostream>
using namespace std;

// Forward declaration of class Transaction (needed because Customer uses it)
class Transaction;

// -------------------- CLASS Customer --------------------
class Customer {
    // Declare friend function: gives access to private data
    friend void applyTransaction(Customer, Transaction);

private:
    int custNum;        // Customer number
    double balanceDue;  // Current balance owed or available

public:
    // Constructor with default values (custNum=0, balance=0.0)
    Customer(int = 0, double = 0.0);
};

// Definition of Customer constructor
Customer::Customer(int num, double balance) {
    custNum = num;         // Set customer number
    balanceDue = balance;  // Set initial balance
}

// -------------------- CLASS Transaction --------------------
class Transaction {
    // Declare the same friend function, so it can access Transaction’s private data
    friend void applyTransaction(Customer, Transaction);

private:
    int transactionNum;  // Transaction identifier
    int custNum;         // Customer number linked to this transaction
    double amount;       // Amount of transaction (can be + or -)

public:
    // Constructor with default values
    Transaction(int = 0, int = 0, double = 0.0);
};

// Definition of Transaction constructor
Transaction::Transaction(int trans, int cust, double amt) {
    transactionNum = trans;  // Set transaction number
    custNum = cust;          // Link to a customer number
    amount = amt;            // Transaction amount (+ deposit / - withdrawal)
}

// -------------------- FRIEND FUNCTION --------------------
void applyTransaction(Customer cust, Transaction trans) {
    // Show original balance
    cout << "Customer #" << cust.custNum
         << " original balance of $" << cust.balanceDue << endl;

    // Update balance by adding transaction amount
    cust.balanceDue += trans.amount;

    // Show details of transaction and updated balance
    cout << "After transaction #" << trans.transactionNum
         << " for " << trans.amount
         << " the new balance is $" << cust.balanceDue << endl;
}

// -------------------- MAIN PROGRAM --------------------
int main() {
    // Create a transaction: ID=111, customer=888, amount=-150.00
    Transaction oneTrans(111, 888, -150.00);

    // Create a customer: ID=888, initial balance=$200.00
    Customer oneCust(888, 200.00);

    // Apply the transaction to the customer (through friend function)
    applyTransaction(oneCust, oneTrans);

    return 0;
}
