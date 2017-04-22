#include <iostream>
#include "Task.h"

using namespace std;

int main()
{
    Date *a;
    a = new Date (31,12,2017);
    a->afficherDate();
    delete(a);
    return 0;
}
