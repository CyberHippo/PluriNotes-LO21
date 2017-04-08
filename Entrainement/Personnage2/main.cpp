#include <iostream>

using namespace std;

int main()
{
    Personnage david, goliath;

    goliath.attaquer(david);
    david.boireBooster(30);
    david.estVivant();
    david.changerArme(30, "Epee Kitutamere");
    goliath.boirePotionDeVie(25);
    david.attaquer(goliath);
    david.attaquer(goliath);
    goliath.estVivant();
    return 0;
}
