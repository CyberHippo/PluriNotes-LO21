#include <iostream>
#include "raz.h"
using namespace std;

void raz(essai* e){
    e-> n=0 ;
    (*e).x = 0;
}

void raz(essai& e){
    e.n = 0 ;
    e.x = 0;
}

void essai :: raz(){
    n=0;
    this -> x = 0;
}
// 3 façons différentes de faire la raz
