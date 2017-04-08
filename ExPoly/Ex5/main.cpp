#include <iostream>

using namespace std;

int main()
{
    double x = 3.14;
    cout << x <<endl;
    double* pt = &x;
    *pt = 4;
    cout << x << *pt << endl;
    double &ref = x;
    ref = 6;
    cout << x << ref << endl;
    cout << &ref <<endl;
    return 0;
}
