
# include <iostream>
using namespace std;

int main() {
    const int SIZE= 5;
    int singleInt= 52;
    int arrayInt[SIZE]= {12, 36};

    cout << "SingInt is" << singleInt << endl;
    cout << "The first element of the array is " << arrayInt[0] << endl;

    ++singleInt;
    ++arrayInt[0];

    cout << "After increase the SingleInte is " << singleInt << endl;
    cout << "After increase the first element of array " << arrayInt[0] << endl;

    singleInt = singleInt * 2;
    arrayInt[0] = arrayInt[0] * 2;

    cout << "After multiplication the SingleInte is " << singleInt<< endl;
    cout << "After multiplication the first element of array " << arrayInt[0] << endl;

    return 0;
}