#include <iostream>
using namespace std;

// --------------------------------------------------
// Class: Inventory
// Demonstrates overloading of:
// 1. The function call operator `operator()`
// 2. The stream insertion operator `operator<<`
// --------------------------------------------------
class Inventory {
    // Friend function to overload << for output
    // This allows direct printing of Inventory objects using cout
    friend ostream& operator<<(ostream&, const Inventory&);

private:
    int stockNum;   // Stock item number
    int numSold;    // Number of items sold
    double price;   // Price of the item (after discount)

public:
    // Overloaded function call operator:
    // Lets us "call" an Inventory object like a function
    Inventory& operator()(int, int, double, double);
};

// --------------------------------------------------
// Overloaded << operator for easy output
// Usage: cout << object;
// --------------------------------------------------
ostream& operator<<(ostream& out, const Inventory& item) {
    out << "Item #" << item.stockNum
        << "  Quantity: " << item.numSold
        << "  Price: " << item.price;
    return out; // allows chaining (cout << a << b)
}

// --------------------------------------------------
// Overloaded function call operator
// Usage: object(args...);
// Sets values of stockNum, numSold, and price
// Applies discount directly on price
// --------------------------------------------------
Inventory& Inventory::operator()(int num, int sold, double pr, double discount) {
    stockNum = num;               // set stock number
    numSold = sold;               // set quantity sold
    price = pr - pr * discount;   // apply discount to price
    return *this;                 // return the current object
}

// --------------------------------------------------
// Main Program
// --------------------------------------------------
int main() {
    Inventory oneItem;  // Create an Inventory object

    // Call overloaded function-call operator
    // Sets: stockNum=1234, numSold=100, price=39.9 - 10% discount
    oneItem(1234, 100, 39.9, 0.10);

    // Print object using overloaded << operator
    cout << oneItem << endl;

    return 0;
}
