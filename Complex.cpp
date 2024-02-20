#include <iostream>
#include "Complex.h"

   Complex Complex::operator+(const Complex& k1)
   {

     return Complex(x + k1.x, y + k1.y);
   }

   Complex Complex::operator-(const Complex& k2)
   {     return Complex(x - k2.x, y - k2.y);

   }

   Complex Complex::operator*(int num)
   {

     return Complex(x * num , y * num);
   }

