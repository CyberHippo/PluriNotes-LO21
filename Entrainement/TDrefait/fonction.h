#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <iostream>

struct Date {
private:
    unsigned int m_jour;
    unsigned int m_mois;
    unsigned int m_annee ;
public:
    Date (unsigned int m_jour,unsigned int m_mois,unsigned int m_annee):m_jour(01),m_mois(01),m_annee(2001) {}
    void changement (Date* objet, unsigned int m_jour, unsigned int m_mois,unsigned int m_annee);
};

#endif // FONCTION_H_INCLUDED
