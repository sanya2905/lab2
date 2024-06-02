#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "monom.h"

struct Polynom {
    Monom* head;
    Monom* tail;
    Polynom();
    bool is_empty();
    void append(std::string monom);
    void append(double coef, size_t pows);
    void construct_polynom(std::string polynom);
    void print();
    void sort_by_pow();

    double get_val(double x, double y, double z);
    Polynom add(Polynom pol);
    Polynom sub(Polynom pol);
    Polynom mul(Polynom pol);
    Polynom get_derivative(char arg);
    Polynom get_antiderivative(char arg);
};