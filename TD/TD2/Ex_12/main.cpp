#include <iostream>

#include "fonction.h"

using namespace std;

int main()
{
    int a = 6, b = 79;
    inverse(&a, &b);
    cout << a << "\n" << b << endl;

    return 0;
}
