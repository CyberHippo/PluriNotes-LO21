#include <string.h>
#include "fonction.h"

using namespace std ;



 double Personnage :: recevoirDegats(int m_degatArme,double m_pdv)
 {
     while (m_pdv > 0 )
     {
         if (m_bouclier !=0)
     {
         m_bouclier = m_bouclier - m_degatTotal;

     }
     else
    {
     m_pdv = m_pdv - m_degatArme;
    }
    }
    return (Personnage.m_pdv);
 }

 void Personnage :: attaquer (Personnage &cible)
 {
     cible.m_pdv = recevoirDegats();
 }
 void Personnage :: boirePotionDeVie(int pdvPotion)
 {
     Personnage.m_pdv += pdvPotion;
 }
 void Personnage :: changerArme(int m_degatNvlArme,string m_nomNvlArme)
 {
    m_nomArme= m_nomNvlArme;
    m_degatArme = m_degatNvlArme;
 }
 void Personnage :: boireBooster(int forcePotion)
 {
     Personnage.m_force += forcePotion;
 }

 bool Personnage :: estVivant()
 {
     if (m_pdv > 0)
     {
        printf("Personnage encore en vie!")
         return true;
     }
     else
     {
         printf("Le personnage est mort... Fin du game");
         return false;
     }
 }
 void Personnage :: statutJeu (estVivant())
 {
     if (estVivant() = 0)
     {
         printf("Le jeu est terminé");
         break;
     }
     else
 }
int Personnage :: calculDegats(m_force,m_degatArme)
 {
     Personnage.m_degatTotal = Personnage.m_degatArme + (Personnage.m_force/10);
     return (Personnage.m_degatTotal);
 }


