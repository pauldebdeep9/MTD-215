// Salesperson.cpp
#include "Salesperson.hpp"
using namespace std;

Salesperson::Salesperson(int id, string n) : idNum(id), name(std::move(n)) {}
void Salesperson::display() const {
    cout << "Salesperson #" << idNum << " " << name << "\n";
}
