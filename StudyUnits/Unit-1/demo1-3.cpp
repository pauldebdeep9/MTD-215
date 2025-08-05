#include <iostream>
using namespace std;

int main() {
    const int NUM_PRICES = 10;
    double price[NUM_PRICES];
    int sub;

    // Input prices
    for (sub = 0; sub < NUM_PRICES; ++sub) {
        cout << "Enter a price ";
        cin >> price[sub];
    }

    // Output prices in reverse order
    cout << endl << "The prices entered in reverse order:" << endl;
    for (sub = NUM_PRICES - 1; sub >= 0; --sub) {
        cout << price[sub] << " ";
    }
    cout << endl;
    return 0;
}
