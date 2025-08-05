#include <iostream>
using namespace std;

int main() {
    int rents[4][3] = {
        { 400, 450, 510 },
        { 500, 560, 630 },
        { 625, 676, 740 },
        { 1000, 1250, 1600 }
    };
    int floor, bedrooms;
    cout << "What floor do you want ? ";
    cin >> floor;
    cout << "How many bedrooms you want ? ";
    cin >> bedrooms;
    cout << "The cost is $" << rents[floor][bedrooms] << endl;
    return 0;
}
