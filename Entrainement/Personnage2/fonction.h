#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <string.h>


class Personnage
{


public:
    double recevoirDegats(int m_degatArme,double m_pdv);
    void attaquer (Personnage &cible);
    void boirePotionDeVie(double m_pdv);
    void changerArme(int m_degatArme,std::string m_nomArme);
    void boireBooster(int m_force);
    bool estVivant();
    void statutJeu (estVivant());
private:
    double m_pdv;
    int m_force;
    int m_mana;
    double m_bouclier;
    int m_degatArme;
    double m_degatTotal;
    std::string m_nomArme;


};
   int calculDegats(int m_force,int m_degatArme);
#endif // FONCTION_H_INCLUDED

