#include <iostream>
#include <cmath>
#include <vector>
class Complex {
 public:
   int x;
   int y;

   Complex(int x, int y): x(x), y(y) {}

   Complex operator+(const Complex& k1);

   Complex operator-(const Complex& k2);

   Complex operator*(int num);

   double absolute_value()
   {
     double z = sqrt(x * x + y * y);
     return z;
   }
   friend std::ostream& operator<<(std::ostream& out, const Complex& k)
   {
      out << " " << k.x << " " << k.y ;
      return out;
   }
};
  template <class T>
  void  bubble_sort(std::vector<T>& arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j) 
        {
            if (arr[j].absolute_value() > arr[j + 1].absolute_value())
            {
                 std::swap(arr[j], arr[j + 1]);
            }
        }
    }
   for (int i = 0; i < size ; ++i)
   {
      std::cout<<arr[i]<<" ";
   }

};

