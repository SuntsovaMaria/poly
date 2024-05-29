
#include <iostream>
#include "poly.h"

using namespace std;

int main()
{
    poly p1("2x2yz4+3xy2-50");
    poly p2 ("x2y+4xy2+z+1");
    std::cout << "Polynomial p1: ";
    p1.print();
    std::cout << "Polynomial p2: ";
    p2.print();
    poly p3 = p1 + p2;
    std::cout << "p1 + p2: ";
    p3.print();
    poly p4 = p1 - p2;
    std::cout << "p1 - p2: ";
    p4.print();
    poly p5 = p1 * 2.5;
    std::cout << "p1 * 2.5: ";
    p5.print();
    double value = p1.at_point(1, 2, 0);
    std::cout << "p1(1, 2, 0) = " << value << std::endl;
    return 0;
	
}