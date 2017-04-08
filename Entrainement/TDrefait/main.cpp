#include <iostream>
#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    Date *pt= NULL;
    pt = new Date;
    printf("Rentrer un jour, mois, annee");
    scanf("%d, %d, %d",pt.m_jour,pt.m_mois,pt.m_annee);
    pt.affichage();
    return 0;
}
