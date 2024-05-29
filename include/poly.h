
#include "list.h"
#include <iostream>
#include <string>

using namespace std;

class monom {
	int deg;
	double coef;
public:
	monom() :deg(0),coef(0){}
	monom(int a, int b, int c, double co) {
		coef = co;
		if (a < 10 && b < 10 && c < 10) {
			deg = a * 100 + b * 10 + c;
		}
		else
			throw "deg is large";

	}
	monom(int de, double co) {
		coef = co;
		if (de < 1000)
			deg = de;
		else throw "deg is large";
	}
	int geta() {
		return deg / 100;
	}
	int getb() {
		return (deg / 10) % 10;
	}
	int getc() {
		return deg % 10;
	}
	int getdeg() {
		return deg;
	}
	double getcoef() {
		return coef;
	}
	bool operator==(const monom& a) const {
		return ((a.deg == deg) && (a.coef==coef));
	}
	bool operator!=(const monom& a)const {
		return !((a.deg == deg) && (a.coef == coef));
	}
	bool operator >=(monom& a) {
		return a.deg >= deg;
	}
	bool operator<(monom& a) {
		return a.deg < deg;
	}
 monom parsemonom(const string& a);
 void print() {
	 cout << getcoef() << "x" << geta() << "y" << getb() << "z" << getc() << endl;
 }
};

class poly
{
	list<monom> pol;
public:
	poly() {};
	poly(const poly& a) {

		list<monom>::iterator it = a.pol.begin();
		while (it != a.pol.end()) {
			pol.insert(pol.end(), *it);
			it++;
		}
	}
	poly(const list<monom> a) {
		pol = a;
	}
	poly(const string& a) {
		*this = parsepoly(a);
	}
	bool operator==(const poly& a) const {
		return pol == a.pol;
	}
	bool operator!=(const poly& a)const {
		return !(pol == a.pol);	
	}
	poly operator+(const poly& a);
	poly operator-(poly& a);
	poly operator*(const poly& a);
	poly operator*(double b);
	double at_point(double x, double y, double z);
	void print();
	poly parsepoly(const string& a);
	void insert_monom( monom& a);

	};

