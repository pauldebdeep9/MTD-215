#include <iostream>
#include <string>
using namespace std;

// ====================
// Base Class: Vehicle
// ====================
class Vehicle {
protected:
    int idNumber;
    string make;
    double milesPerGallon;

public:
    Vehicle(int, string, double);
    void display();
};

Vehicle::Vehicle(int id, string make, double mpg) {
    idNumber = id;
    this->make = make;
    milesPerGallon = mpg;
}

void Vehicle::display() {
    cout << "ID # " << idNumber
         << "  Make: " << make
         << "  gets " << milesPerGallon
         << " miles per gallon" << endl;
}

// ====================
// Base Class: Dwelling
// ====================
class Dwelling {
protected:
    int numberOfBedrooms;
    int squareFeet;

public:
    Dwelling(int, int);
    void display();
};

Dwelling::Dwelling(int bedrooms, int sqFeet) {
    numberOfBedrooms = bedrooms;
    squareFeet = sqFeet;
}

void Dwelling::display() {
    cout << numberOfBedrooms << " bedrooms and "
         << squareFeet << " square feet" << endl;
}

// ==========================
// Derived Class: RV
// Multiple inheritance
// ==========================
class RV : public Vehicle, public Dwelling {
public:
    RV(int, string, double, int, int);
    void display();
};

// Use initialization list to call both base constructors
RV::RV(int id, string make, double mpg,
       int bedrooms, int sqFeet)
    : Vehicle(id, make, mpg), Dwelling(bedrooms, sqFeet) {
}

void RV::display() {
    cout << "A recreational vehicle:" << endl;
    Vehicle::display();  // show vehicle details
    Dwelling::display(); // show dwelling details
}

// ====================
// main() to test
// ====================
int main() {
    RV myRV(301, "Winnebago", 12.8, 2, 220);
    myRV.display();
    return 0;
}
