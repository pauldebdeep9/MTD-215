// polymorphism_shapes.cpp
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
using namespace std;

struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0; // pure virtual => polymorphic API
};

struct Rectangle : Shape {
    double w, h;
    Rectangle(double w, double h): w(w), h(h) {}
    double area() const override { return w * h; }
};

struct Circle : Shape {
    double r;
    explicit Circle(double r): r(r) {}
    double area() const override { return M_PI * r * r; }
};

int main() {
    vector<unique_ptr<Shape>> v;
    v.emplace_back(make_unique<Rectangle>(3,4));
    v.emplace_back(make_unique<Circle>(2.0));
    for (auto& s : v) cout << s->area() << "\n"; // same call, different behavior
}
