// customer_scope_resolution.cpp
#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string name;
    double balance{};
public:
    void setName(string n);
    void setBalance(double b);
    string getName();
    double getBalance();
};

void Customer::setName(string n) { name = std::move(n); }
void Customer::setBalance(double b) { balance = b; }
string Customer::getName() { return name; }
double Customer::getBalance() { return balance; }

int main() {
    Customer c;
    c.setName("Aisha");
    c.setBalance(120.50);
    cout << c.getName() << " has $" << c.getBalance() << "\n";
}
