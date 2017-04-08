#include <iostream>
#include "fraction.h"

using namespace std;

int main()
{
    MATH::fraction objet(3,4);
    //objet.setFraction(3,4);
    MATH:: fraction f1;
    MATH:: fraction f2;
    MATH:: fraction f;

    return 0;
}


// But de l'exercice. On a crée une classe fraction, avec un objet "objet". Pour éviter de l'initialiser en lui affectant les valeurs (objet.m_denominateur=...),
//on a cree un constructeur qui va automatiquement initialiser notre objet avec un constructeur.
