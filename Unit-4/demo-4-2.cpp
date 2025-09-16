#include <iostream>
#include <string>
using namespace std;

// =======================
// Base Class Declaration
// =======================
class InsurancePolicy {
private:
    int policyNumber;            // private: accessible only inside this class
protected:
    string policyHolder;         // protected: accessible inside this class and derived classes
public:
    double annualRate;            // public: accessible anywhere

    // Function prototypes
    void setPolicy(int, string, double);
    void showPolicy();
};

// =============================
// Member function definitions
// =============================
void InsurancePolicy::setPolicy(int num, string name, double rate) {
    // Assign values to data members
    policyNumber = num;
    policyHolder = name;
    annualRate = rate;
}

void InsurancePolicy::showPolicy() {
    // Output values of data members
    cout << "Policy # " << policyNumber
         << "   Name: " << policyHolder
         << "   Annual premium: $" << annualRate << endl;
}

// ========================================
// Derived Class with protected inheritance
// ========================================
class AutomobileInsurancePolicy : protected InsurancePolicy {
    // Because we used `protected` inheritance, all public members
    // of InsurancePolicy become protected inside this derived class.
    // So we must make them public again to access from main().
public:
    using InsurancePolicy::setPolicy;  // make setPolicy() public again
    using InsurancePolicy::showPolicy; // make showPolicy() public again
};

// ===================
// main() function
// ===================
int main() {
    AutomobileInsurancePolicy autoPolicy;

    // These methods are inherited from InsurancePolicy
    autoPolicy.setPolicy(101, "Alice Johnson", 1299.75);
    autoPolicy.showPolicy();

    return 0;
}
