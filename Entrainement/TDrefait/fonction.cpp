#include "fonction.h"

void Date::changement (Date* objet, unsigned int NvJour, unsigned int NvMois,unsigned int NvlleAnnee)
{
    objet ->m_jour = NvJour;
    objet ->m_mois = NvMois;
    objet ->m_annee = NvlleAnnee;
}
