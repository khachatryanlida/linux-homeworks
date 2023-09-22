#include <iostream>
#include "Complex.h"
#include <vector>
int main()
{
    Complex x(10 , 4);
    Complex y(5 , 2);
    Complex z(7 , 8);

std::cout << x + y << std::endl;
std::cout << x - y << std::endl;
std::cout << x * 3 << std::endl;
std::cout << x.absolute_value() << std::endl;

    std::vector<Complex> Arr;
    Arr.push_back(x);
    Arr.push_back(y);
    Arr.push_back(z);
    bubble_sort<Complex>(Arr, 2);

    return 0;
}


