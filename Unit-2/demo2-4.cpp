// student_static_member.cpp
#include <iostream>
using namespace std;

class Student {
private:
    int idNum{};
    static double athleticFee; // shared storage (one per class)
public:
    void setId(int id) { idNum = id; }
    int getId() const { return idNum; }
    static double getAthleticFee() { return athleticFee; } // static accessor
};

// define & initialize static storage outside the class
double Student::athleticFee = 45.25;

int main() {
    Student a, b;
    a.setId(1234); b.setId(2345);
    cout << "Freshman: " << a.getId() << " Fee: " << Student::getAthleticFee() << "\n";
    cout << "Sophomore: " << b.getId() << " Fee: " << b.getAthleticFee() << "\n";
}
