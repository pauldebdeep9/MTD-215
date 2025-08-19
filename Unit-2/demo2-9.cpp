// composition_transaction.cpp
#include <iostream>
#include <string>
using namespace std;

class InventoryItem {
    int stockNum{};
    double price{};
public:
    InventoryItem() = default;
    InventoryItem(int s, double p) : stockNum(s), price(p) {}
    void setStockNum(int s) { stockNum = s; }
    void setPrice(double p) { price = p; }
    void display() const {
        cout << "Item #" << stockNum << " $" << price << "\n";
    }
};

class Salesperson {
    int idNum{};
    string name;
public:
    Salesperson() = default;
    Salesperson(int id, string n) : idNum(id), name(std::move(n)) {}
    void setIdNum(int id) { idNum = id; }
    void setName(const string& n) { name = n; }
    void display() const {
        cout << "Salesperson #" << idNum << " " << name << "\n";
    }
};

// Transaction *has* an InventoryItem and a Salesperson
class Transaction {
    int transNum{};
    InventoryItem itemSold;
    Salesperson seller;
public:
    // initialize members in the initialization list (clean & efficient)
    Transaction(int num, int item, double pr, int salesId, string salesName)
        : transNum(num), itemSold(item, pr), seller(salesId, std::move(salesName)) {}

    void display() const {
        cout << "Transaction #" << transNum << "\n";
        itemSold.display();
        seller.display();
    }
};

int main() {
    Transaction t(9001, 555, 19.95, 77, "Lim");
    t.display();
}
