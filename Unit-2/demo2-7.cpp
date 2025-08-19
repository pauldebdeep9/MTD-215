// employee_constructors.cpp
#include <iostream>
using namespace std;

class Employee {
private:
    int idNum;
    double hourlyRate;
public:
    Employee() : idNum(9999), hourlyRate(6.15) {}                   // default
    Employee(int id, double rate) : idNum(id), hourlyRate(rate) {}   // param
    int getId() const { return idNum; }
    double getRate() const { return hourlyRate; }
};

int main() {
    Employee a;               // uses default
    Employee b(101, 25.0);    // uses parameterized
    cout << a.getId() << " @" << a.getRate() << "\n";
    cout << b.getId() << " @" << b.getRate() << "\n";
}
