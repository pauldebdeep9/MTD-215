// house_destructor.cpp
#include <iostream>
using namespace std;

class House {
    int squareFeet;
public:
    House() : squareFeet(1000) { cout << "House created.\n"; }
    ~House() { cout << "House destroyed.\n"; } // called automatically at end of scope
    int getSquareFeet() const { return squareFeet; }
};

int main() {
    House h;
    cout << "Square feet: " << h.getSquareFeet() << "\n";
} // <-- destructor runs here
