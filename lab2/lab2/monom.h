#pragma once
#include <iostream>
#include <string>

struct Monom {
    double coef;
    size_t pows;
    Monom* next;
    Monom(std::string monom);
    Monom(double coef, size_t pows);
    void print();
    double get_val(double x, double y, double z);
};