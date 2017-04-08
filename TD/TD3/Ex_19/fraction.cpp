#include "fraction.h"
#include <iostream>

// à ajouter en tant méthode privée de la classe Fraction
void MATH::fraction::simplification()
{
// si le numerateur est 0, le denominateur prend la valeur 1
    if (m_numerateur==0)
    {
        m_denominateur=1;
        return;
    }
    /* un denominateur ne devrait pas être 0;
    si c’est le cas, on sort de la méthode */
    if (m_denominateur==0) return;
    /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=m_numerateur, b=m_denominateur;
// on ne travaille qu’avec des valeurs positives...
    if (a<0) a=-a;
    if (b<0) b=-b;
    while(a!=b)
    {
        if (a>b) a=a-b;
        else b=b-a;
    }
// on divise le numerateur et le denominateur par le PGCD=a
    m_numerateur/=a;
    m_denominateur/=a;
// si le denominateur est négatif, on fait passer le signe - au denominateur
    if (m_denominateur<0)
    {
        m_denominateur=-m_denominateur;
        m_numerateur=-m_numerateur;
    }
}


MATH::fraction::fraction(int n =0, int d = 1): // : pour dire qu'on initialise le numerateur a n et le denominateur a d
    m_numerateur(n), m_denominateur (d)  // on décalre un constructeur qui prends 2 paramètres
{
    std:: cout << "Fraction initialisee";
    simplification();

}
MATH::fraction::fraction(int n)
{
    m_numerateur = n; // on aff
    m_denominateur = 1;
}
MATH::fraction::fraction()
{
    m_numerateur = 0;
    m_denominateur = 1;
}
void  MATH::fraction::setFraction (int n, int d) // la classe fraction appartient au namespace MATH
{
    m_numerateur = n; // l'attribut reçoit directement la valeur car on est dans une méthode de la classe elle même
    m_denominateur = d;
    if (d==0)
    {
        std:: cout << "Le denominateur doit etre sup a 0" <<"\n";
        d=1;
    }
}

MATH::fraction MATH::fraction ::somme(const fraction &f) const
{
    MATH::fraction result;
    result.setFraction (m_numerateur * f.getDenominateur ()+
                        m_denominateur * f.getNumerateur ()+
                        m_denominateur *f.getDenominateur ());
    return result;

}
MATH::fraction MATH::somme (const fraction &f1, const fraction &f2)
{
    MATH::fraction result;
    result.setFraction (f1.getNumerateur ()* f2.getDenominateur() +
                        f1.getDenominateur()* f2.getNumerateur() +
                        f1.getDenominateur ()* f2.getDenominateur());
    return result;

}
~MATH::fraction()
{
    std:: cout <<






}




// UML

            FRACTION
    --------------------------------
    - numerateur:int
    - denominateur:int
    --------------------------------
    +somme (fractionf):fonction
    +fraction()
    +fraction (int n)
    +fraction (int n=0, int d=1)
    +~fraction()
    -simplification():void
    +setfraction(int n, int d):void
    +getNumerateur():int
    +getDenominateur():int
