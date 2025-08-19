// Salesperson.hpp
#ifndef SALESPERSON_HPP    // if not defined, define once
#define SALESPERSON_HPP

#include <string>
#include <iostream>

class Salesperson {
private:
    int idNum;
    std::string name;
public:
    Salesperson(int id, std::string n);
    void display() const;
};

#endif // SALESPERSON_HPP
