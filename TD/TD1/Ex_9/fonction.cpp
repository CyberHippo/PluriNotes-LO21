#include <iostream>
#include "fonction.h"
inline int fct(int x)
{
    std::cout<<"1:"<<x<<"\n"; return 0;
}
inline int fct(float y)
{
    std::cout<<"2:"<<y<<"\n"; return 0;
}
inline int fct(int x, float y)
{
    std::cout<<"3:"<<x<<y<<"\n"; return 0;
}
inline float fct(float x, int y)
{
    std::cout<<"4:"<<x<<y<<"\n"; return 3.14;
}
void exercice_surcharge()
{
int i=3,j=15;
float x=3.14159,y=1.414;

 fct(i); //appel 1
 fct(x); //appel 2
 fct(i,y); //appel 3
 fct(x,j); //appel 4

}
