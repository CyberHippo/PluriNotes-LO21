#include "fonction.h"
#include<stdio.h>
#include <iostream>

using namespace std ;

const double pi = 3.14159;
void exerciceA()
{
int r;

cout<<"donnez le rayon entier d’un cercle:"<< endl;
cin>>r ;
double p=2*pi*r;
double s=pi*r*r;
cout <<"le cercle de rayon est" <<r<<endl;
cout<<"a un perimetre de"<<p<<" et une surface de"<<s<<endl;
}
