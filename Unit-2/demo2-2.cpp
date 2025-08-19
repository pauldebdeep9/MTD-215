// carpet_private_helper.cpp
#include <iostream>
using namespace std;

class Carpet {
private:
    int length{};    // in feet
    int width{};     // in feet
    double price{};  // computed
    // private helper—cannot be called directly by users
    void setPrice() {
        const int SMALL = 12, MED = 24;
        const double PRICE1 = 29.99, PRICE2 = 59.99, PRICE3 = 89.99;
        int area = length * width;
        if (area <= SMALL) price = PRICE1;
        else if (area <= MED) price = PRICE2;
        else price = PRICE3;
    }
public:
    void setLength(int len) { length = len; setPrice(); }
    void setWidth(int wid)  { width  = wid; setPrice(); }
    int getLength() const { return length; }
    int getWidth()  const { return width; }
    double getPrice() const { return price; }
};

int main() {
    Carpet c;
    c.setLength(3);
    c.setWidth(5);
    cout << "Area: " << c.getLength()*c.getWidth() 
         << "  Price: " << c.getPrice() << "\n";
}
