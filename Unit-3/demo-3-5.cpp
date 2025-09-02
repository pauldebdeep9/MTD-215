#include <iostream>
using namespace std;

// ---------------------------------------------------
// Class Sale: represents a single sales transaction
// ---------------------------------------------------
class Sale {
private:
    int receiptNum;       // Unique receipt number for the sale
    double saleAmount;    // Sale amount in dollars

public:
    // Constructor: initializes receipt number and sale amount
    Sale(int = 0, double = 0.0);

    // Overloaded + operator: allows adding two Sale objects
    Sale operator+(Sale);

    // Display sale info
    void showSale();
};

// ---------------- Constructor -----------------
Sale::Sale(int num, double sale) {
    receiptNum = num;
    saleAmount = sale;
}

// ---------------- Operator + ------------------
// Add the sale amounts of two Sale objects
Sale Sale::operator+(Sale transaction) {
    // Create a temporary Sale object to hold the result
    // receiptNum is not meaningful here, so we set a dummy value
    Sale temp(999, 0.0);

    // Add the two sale amounts
    temp.saleAmount = saleAmount + transaction.saleAmount;

    // Return the new Sale object
    return temp;
}

// ---------------- Display ---------------------
void Sale::showSale() {
    cout << "Sale #" << receiptNum
         << " for $" << saleAmount << endl;
}

// ---------------- Main Program ----------------
int main() {
    // Create Sale objects with receipt numbers and amounts
    Sale aShirt(1567, 39.95);   // Shirt purchase
    Sale aTie(1568, 33.55);     // Tie purchase
    Sale pants(1569, 49.99);    // Pants purchase

    // A Sale object to hold the total
    Sale total(0, 0.0);

    // Add sales using overloaded + operator
    // Equivalent to total = ((aShirt + aTie) + pants)
    total = aShirt + aTie + pants;

    // Show individual sales
    aShirt.showSale();
    aTie.showSale();
    pants.showSale();

    // Show total
    cout << "Total:" << endl;
    total.showSale();

    return 0;
}
