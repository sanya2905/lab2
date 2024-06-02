#include "monom.h"

using namespace std;

bool is_var(string& str, int i) {
    return str[i] == 'x' || str[i] == 'y' || str[i] == 'z';
}

Monom::Monom(double coef, size_t pows) {
    next = nullptr;
    this->coef = coef;
    this->pows = pows;
}
Monom::Monom(string monom) {
    next = nullptr;
    int i = 0;
    pows = 0;
    // x5y6z7
    if (is_var(monom, 0)) {
        coef = 1;
        i++;
    }
    // +x7y2
    else if (monom[0] == '+' && is_var(monom, 1)) {
        coef = 1;
        i++;
    }
    else if (monom[0] == '-' && is_var(monom, 1)) {
        coef = -1;
        i++;
    }
    else {
        //-85.13526
        string cstr_coef = "";
        while (!is_var(monom, i)) {
            cstr_coef += monom[i];
            i++;
        }
        coef = stod(cstr_coef);
    }
    if (monom[i] == 'x') {
        if (!is_var(monom, i + 1)) {
            i++;
            pows += (monom[i] - 48) * 100;
        }
        else {
            pows += 100;
        }
        i++;
    }
    if (monom[i] == 'y') {
        if (!is_var(monom, i + 1)) {
            i++;
            pows += (monom[i] - 48) * 10;
        }
        else {
            pows += 10;
        }
        i++;
    }
    if (monom[i] == 'z') {
        if (monom.size() - 1 == i) {
            pows += 1;
        }
        else {
            i++;
            pows += (monom[i] - 48) * 1;
        }
    }
}

void Monom::print() {
    int x = pows / 100, y = (pows / 10) % 10, z = pows % 10;
    if (coef > 0)
        cout << "+" << coef;
    if (coef < 0)
        cout << coef;
    if (x != 0)
        cout << "x" << x;
    if (y != 0)
        cout << "y" << y;
    if (z != 0)
        cout << "z" << z;
}

double Monom::get_val(double x, double y, double z) {
    double res;
    int x_ = pows / 100, y_ = (pows / 10) % 10, z_ = pows % 10;
    res = coef * pow(x, x_) * pow(y, y_) * pow(z, z_);
    return res;
}