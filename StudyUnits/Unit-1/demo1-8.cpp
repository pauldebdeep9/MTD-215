#include <iostream>
using namespace std;

struct Part {
    int partNum;
    double partPrice;
};

int main() {
    const int NUMPARTS = 4;
    Part part[NUMPARTS] = { {210, 1.29}, {312, 2.45},
                            {367, 5.99}, {456, 1.42} };

    int isFound = 0;
    int neededPart;
    int x;
    cout << "Enter the part number you want: ";
    cin >> neededPart;
    for (x = 0; x < NUMPARTS; ++x) {
        if (neededPart == part[x].partNum) {
            cout << "The price is " << part[x].partPrice << endl;
            isFound = 1;
        }
    }
    if (isFound == 0)
        cout << "Sorry -- no such part number." << endl;
    return 0;
}
