#include <iostream>
using namespace std;

int main() {
    const int NUMPARTS = 4;
    int partNum[NUMPARTS] = {210, 312, 367, 456};
    double partPrice[NUMPARTS] = {1.29, 2.45, 5.99, 1.42};
    int neededPart;
    int x;

    cout << "Enter the part number you want: ";
    cin >> neededPart;

    for (x = 0; x < NUMPARTS; ++x) {
        if (neededPart == partNum[x])
            cout << "The price is " << partPrice[x] << endl;
    }
    return 0;
}
