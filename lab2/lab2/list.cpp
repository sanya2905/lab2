#include "list.h"

using namespace std;

Polynom::Polynom() {
    head = nullptr;
    tail = nullptr;
}

bool Polynom::is_empty() {
    return head == nullptr;
}

void Polynom::append(string monom_) {
    Monom* monom = new Monom(monom_);
    if (is_empty()) {
        head = monom;
        tail = monom;
    }
    else {
        tail->next = monom;
        tail = tail->next;
    }
}

void Polynom::append(double coef, size_t pows) {
    Monom* monom = new Monom(coef, pows);
    if (is_empty()) {
        head = monom;
        tail = monom;
    }
    else {
        tail->next = monom;
        tail = tail->next;
    }
}

void Polynom::construct_polynom(string polynom) {
    vector<int> ind_of_monoms = { 0 };
    for (int i = 1; i < polynom.size(); i++) {
        if (polynom[i] == '+' || polynom[i] == '-') {
            ind_of_monoms.push_back(i);
        }
    }
    ind_of_monoms.push_back(polynom.size());
    for (int i = 0; i < ind_of_monoms.size() - 1; i++) {
        append(polynom.substr(ind_of_monoms[i], ind_of_monoms[i + 1]));
    }
    sort_by_pow();
}

void Polynom::sort_by_pow() {
    if (is_empty()) return;
    size_t t;
    double t_coef;
    for (Monom* temp = head; temp->next != nullptr; temp = temp->next) {
        for (Monom* cur = head; cur->next != nullptr; cur = cur->next) {
            if (cur->pows < cur->next->pows) {
                t = cur->pows;
                cur->pows = cur->next->pows;
                cur->next->pows = t;
                t_coef = cur->coef;
                cur->coef = cur->next->coef;
                cur->next->coef = t_coef;
            }
        }
    }
}

void Polynom::print() {
    if (is_empty())
        cout << "Polynom is empty." << endl;
    else {
        for (Monom* p = head; p != nullptr; p = p->next) {
            p->print();
        }
        cout << endl;
    }
}


double Polynom::get_val(double x, double y, double z) {
    double res = 0;
    for (Monom* p = head; p != nullptr; p = p->next) {
        res += p->get_val(x, y, z);
    }
    return res;
}


Polynom Polynom::add(Polynom pol) {
    Polynom res;
    Monom* q;
    for (Monom* p = head; p != nullptr; p = p->next) {
        bool is_same = false;
        for (q = pol.head; q != nullptr; q = q->next) {
            if (p->pows == q->pows) {
                is_same = true;
                break;
            }
        }
        if (is_same && p->coef + q->coef != 0) {
            res.append(p->coef + q->coef, p->pows);
        }
        if (!is_same) {
            res.append(p->coef, p->pows);
        }
    }
    for (Monom* q = pol.head; q != nullptr; q = q->next) {
        bool is_same = false;
        for (Monom* p = head; p != nullptr; p = p->next) {
            if (p->pows == q->pows) {
                is_same = true;
                break;
            }
        }
        if (!is_same) {
            res.append(q->coef, q->pows);
        }
    }
    res.sort_by_pow();
    return res;
}

Polynom Polynom::sub(Polynom pol) {
    Polynom res;
    Monom* q;
    for (Monom* p = head; p != nullptr; p = p->next) {
        bool is_same = false;
        for (q = pol.head; q != nullptr; q = q->next) {
            if (p->pows == q->pows) {
                is_same = true;
                break;
            }
        }
        if (is_same && p->coef - q->coef != 0) {
            res.append(p->coef - q->coef, p->pows);
        }
        if (!is_same) {
            res.append(p->coef, p->pows);
        }
    }
    for (Monom* q = pol.head; q != nullptr; q = q->next) {
        bool is_same = false;
        for (Monom* p = head; p != nullptr; p = p->next) {
            if (p->pows == q->pows) {
                is_same = true;
                break;
            }
        }
        if (!is_same) {
            res.append(-q->coef, q->pows);
        }
    }
    res.sort_by_pow();
    return res;
}

int is_in(vector<size_t> vec, int item) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == item)
            return i;
    }
    return -1;
}

Polynom Polynom::mul(Polynom pol) {
    vector<size_t> new_pows;
    vector<double> new_coefs;
    for (Monom* p = head; p != nullptr; p = p->next) {
        for (Monom* q = pol.head; q != nullptr; q = q->next) {
            int x1 = p->pows / 100, y1 = (p->pows / 10) % 10, z1 = (p->pows) % 10,
                x2 = q->pows / 100, y2 = (q->pows / 10) % 10, z2 = (q->pows) % 10;
            if (x1 + x2 >= 10 || y1 + y2 >= 10 || z1 + z2 >= 10) {
                throw 15;
            }
            int new_x = x1 + x2, new_y = y1 + y2, new_z = z1 + z2;
            int new_pow = new_x * 100 + new_y * 10 + new_z;
            double new_coef = p->coef * q->coef;
            int index = is_in(new_pows, new_pow);
            if (index == -1) {
                new_pows.push_back(new_pow);
                new_coefs.push_back(new_coef);
            }
            else {
                new_coefs[index] += new_coef;
            }
        }
    }
    Polynom res;
    for (int i = 0; i < new_coefs.size(); i++) {
        res.append(new_coefs[i], new_pows[i]);
    }
    res.sort_by_pow();
    return res;
}

Polynom Polynom::get_derivative(char arg) {
    if (arg != 'x' && arg != 'y' && arg != 'z') {
        throw 10;
    }
    Polynom res;
    for (Monom* p = head; p != nullptr; p = p->next) {
        int x = p->pows / 100, y = (p->pows / 10) % 10, z = p->pows % 10;
        double new_coef, new_x = x, new_y = y, new_z = z;
        if (arg == 'x') {
            new_coef = p->coef * x;
            new_x = x - 1;
        }
        else if (arg == 'y') {
            new_coef = p->coef * y;
            new_y = y - 1;
        }
        else if (arg == 'z') {
            new_coef = p->coef * z;
            new_z = z - 1;
        }
        if (new_x == -1 || new_y == -1 || new_z == -1)
            continue;
        size_t new_pows = new_x * 100 + new_y * 10 + new_z;
        res.append(new_coef, new_pows);
    }
    res.sort_by_pow();
    return res;
}

Polynom Polynom::get_antiderivative(char arg) {
    if (arg != 'x' && arg != 'y' && arg != 'z') {
        throw 10;
    }
    Polynom res;
    for (Monom* p = head; p != nullptr; p = p->next) {
        int x = p->pows / 100, y = (p->pows / 10) % 10, z = p->pows % 10;
        double new_coef;
        int new_x = x, new_y = y, new_z = z;
        if (arg == 'x') {
            new_x++;
            new_coef = p->coef / new_x;
        }
        else if (arg == 'y') {
            new_y++;
            new_coef = p->coef / new_y;
        }
        else if (arg == 'z') {
            new_z++;
            new_coef = p->coef / new_z;
        }
        if (new_x == 1 || new_y == 1 || new_z == 1) {
            new_coef = p->coef;
        }
        if (new_x >= 10 || new_y >= 10 || new_z >= 10) {
            throw 15;
        }
        size_t new_pows = new_x * 100 + new_y * 10 + new_z * 1;;
        res.append(new_coef, new_pows);
    }
    return res;
}