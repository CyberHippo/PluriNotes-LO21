#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

class Priority {
int valeur;
static const int min;
static const int max; /* sert à avoir une portée globale mais limité à notre classe sur les variables min et max */

public:
Priority():valeur (1){}
Priority(int V){}

int getValue () const{
return valeur;
}
void setvalue (int v)
{
    if ( v< min || v > max ) throw "erreur";}
    int getMin() const {return min;}
    int getMax() const {return max;}
} {valeur = v;}

#endif // FONCTIONS_H_INCLUDED
