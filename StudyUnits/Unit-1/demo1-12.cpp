#include <iostream>
#include <string>
using namespace std;

int main() {
    string oneName = "John";
    string anotherName = "John";
    if (oneName == anotherName)
        cout << oneName << " and " << anotherName << " are equal" << endl;
    else
        cout << oneName << " and " << anotherName << " are different" << endl;

    anotherName = "Nicholas";
    if (oneName == anotherName)
        cout << oneName << " and " << anotherName << " are equal" << endl;
    else
        cout << oneName << " and " << anotherName << " are different" << endl;

    oneName = anotherName;
    if (oneName == anotherName)
        cout << oneName << " and " << anotherName << " are equal" << endl;
    else
        cout << oneName << " and " << anotherName << " are different" << endl;

    return 0;
}
