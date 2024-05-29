#include "poly.h"
#include "list.h"
#include <iostream>



void poly::insert_monom(monom& m) {
    if (abs(m.getcoef()) < 1e-10) return;

    auto it = pol.begin();
    for (; it != pol.end(); it++) {
        if ((*it).getdeg() == m.getdeg()) {
            double newCoef = (*it).getcoef() + m.getcoef();
            if (std::abs(newCoef) < 1e-10) {
                pol.erase(it);
            }
            else {
                *it = monom(m.geta(), m.getb(), m.getc(), newCoef);
            }
            return;
        }
        else if (*it < m) {
            break;
        }
    }
    pol.insert(it, m);
}
poly poly::operator+(const poly& a) {
    poly result;
    for (auto it = pol.begin(); it != pol.end(); it++) {
        result.insert_monom(*it);
    }
    for (auto it = a.pol.begin(); it != a.pol.end(); it++) {
        result.insert_monom(*it);
    }
    result.pol.reverse();
    return result;
}

 
poly poly:: operator*(double b) {
    poly result;
    list<monom> newPol;
    list<monom>::iterator it = pol.begin();
    if (abs(b) > 1e-10) {
        while (it != pol.end()) {
            newPol.insert(newPol.end(), monom((*it).getdeg(), (*it).getcoef() * b));
            it++;
        }
    }
    result.pol = newPol;
    return result;
}

poly poly::operator-(poly& a)
{
    poly result = *this + a * (-1);
    return  result;
}

poly poly::operator*(const poly& a) {
    poly result;
    for (auto it1 = pol.begin(); it1 != pol.end(); it1++) {
        for (auto it2 = a.pol.begin(); it2 != a.pol.end(); it2++) {
            int new_xdeg = (*it1).geta() + (*it2).geta();
            int new_ydeg = (*it1).getb() + (*it2).getb();
            int new_zdeg = (*it1).getc() + (*it2).getc();
            double new_coef = (*it1).getcoef() * (*it2).getcoef();
            result.insert_monom(monom(new_xdeg, new_ydeg, new_zdeg, new_coef));
        }
    }
    result.pol.insertion_sort();
    return result;
}



monom monom::parsemonom(const string& a)
{
    double coef = 1.0;
    int xdeg = 0;
    int ydeg = 0;
    int zdeg = 0;
    int pos = 0;
    if (a[pos] == '+' || a[pos] == '-') {
        if (a[pos] == '-') {
            coef = -1;
        }
        pos++;
    }
    int start = pos;
    while (pos < a.size() && (isdigit(a[pos]) || a[pos] == '.')) {
        pos++;
    }
    if (pos > start) {
            coef *= stod(a.substr(start, pos - start));
    }
    while (pos < a.size()) {
        char var = a[pos];
        int deg = 0;
        if (pos < a.size() && isdigit(a[++pos])) {
            deg = a[pos++] - '0';
        }
        else {
            deg = 1;
        }
        switch (var) {
        case 'x': xdeg = deg; break;
        case'y': ydeg = deg; break;
        case 'z': zdeg = deg; break;
        }
    }
    return monom(xdeg,ydeg,zdeg,coef);
}
poly poly::parsepoly(const string& a) {
    poly result;
    string mon;
    monom r;
    bool ismonomstarted = false;
    for (char ch : a) {
        if (ch == '+' || ch == '-') {
            if (ismonomstarted) {
                result.pol.insert(result.pol.end(), r.parsemonom(mon));
                mon.clear();
            }
            mon += ch;
            ismonomstarted = true;
        }
        else {
            mon += ch;
            ismonomstarted = true;
        }
    }
    if (!mon.empty()) {
        result.pol.insert(result.pol.end(), r.parsemonom(mon));
        
    }
    result.pol.insertion_sort();
    return result;
}
double poly::at_point(double x, double y, double z) {
    list<monom>::iterator it = pol.begin();
    double result = 0;
    while (it != pol.end()) {
        result += (*it).getcoef() *( pow(x, (*it).geta()) )* (pow(y, (*it).getb())) *( pow(z, (*it).getc()));
        it++;
    }
    return result;
}

void poly::print() {
    list<monom>::iterator it = pol.begin();
   if (pol.isempty()) {
        cout << 0<<endl;
        return;
    }
    else {
        bool first = true;

        while (it != pol.end()) {
            double coef = (*it).getcoef();
            int x = (*it).geta(), y = (*it).getb(), z = (*it).getc();

            if (!first && coef > 0) cout << "+";
            if (coef < 0) cout << "-";
            if (abs(coef) != 1 || (x == 0 && y == 0 && z == 0)) cout << abs(coef);

            if (x != 0) {
                if (x != 1)
                    cout << "x" << x;
                else
                    cout << "x";
            }
            if (y != 0) {
                if (y != 1)
                    cout << "y" << y;
                else
                    cout << "y";
            }
            if (z != 0) {
                if (z != 1)
                    cout << "z" << z;
                else
                    cout << "z";
            }

            first = false;
            it++;
        }

        cout << endl;
    }
}

