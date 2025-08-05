// Demonstrating single variables and array variables

#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    int singleInt = 52;
    int arrayInt[SIZE] = {12, 36};

    cout << "SingInt is " << singleInt << endl;
    cout << "First array element is " << arrayInt[0] << endl;

    ++singleInt;
    ++arrayInt[0];

    cout << "After incrementing, SingInt is " << singleInt << endl;
    cout << "After incrementing, First array element is " << arrayInt[0] << endl;

    singleInt = singleInt * 2;
    arrayInt[0] = arrayInt[0] * 2;

    cout << "After doubling, SingInt is " << singleInt << endl;
    cout << "After doubling, First array element is " << arrayInt[0] << endl;

    return 0;
}
