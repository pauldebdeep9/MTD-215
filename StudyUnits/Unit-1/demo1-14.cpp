#include <iostream>
using namespace std;

int main() {
    const int DAYS = 7;
    int sales[DAYS] = { 500, 300, 450, 200, 525, 800, 1000 };
    int* p = &sales[0]; // int* p = sales would produce identical results

    int x;
    for (x = 0; x < DAYS; x++)
        cout << "$" << sales[x] << " ";
    cout << endl;
    for (x = 0; x < DAYS; x++)
        cout << "$" << p[x] << " ";
    cout << endl;

    for (x = 0; x < DAYS; x++)
        cout << "$" << *(sales + x) << " ";
    cout << endl;
    for (x = 0; x < DAYS; x++)
        cout << "$" << *(p + x) << " ";
    cout << endl;
    for (x = 0; x < DAYS; x++, p++)
        cout << "$" << *p << " ";
    cout << endl;

    return 0;
}
