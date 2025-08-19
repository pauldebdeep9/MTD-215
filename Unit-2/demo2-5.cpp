// this_pointer_demo.cpp
#include <iostream>
using namespace std;

class Account {
    double balance{};
public:
    Account& deposit(double amt) {
        this->balance += amt;    // explicit this-> for clarity
        return *this;            // enable call chaining
    }
    Account& withdraw(double amt) {
        this->balance -= amt;
        return *this;
    }
    double getBalance() const { return balance; }
};

int main() {
    Account acc;
    acc.deposit(100).withdraw(30).deposit(10);
    cout << "Balance: " << acc.getBalance() << "\n";
}
