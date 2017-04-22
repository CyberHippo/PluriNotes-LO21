#include "Task.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <cstdlib>

using namespace std;

//------ClasseDate----//
Date::Date(int j, int m, int a)
{
 static int finMois[]={0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // nombre de jours max pour chaque mois. On met 0 au premier, comme ça tab[1] correspond au premier mois (janvier)
  if (m>12)
  {
      TaskException("Erreur sur le mois renseigne");   // si le nombre de mois est sup a 12, on retourne une erreur
      exit(EXIT_FAILURE);
  }
 else if (j>finMois[m])
 {
     TaskException("Erreur sur le nombre de jours renseigne");
     exit(EXIT_FAILURE);
 }
 else if (a< 2017)
 {
     TaskException("Erreur sur l'annee renseignee");  // on veut que la tâche soit executée après 2017 de préférence
     exit(EXIT_FAILURE);
 }
 else
 {//si tout est bon, on attribue les valeurs aux variables membres
    setJ(j);
     setM(m);
     setA(a);
 }
};

void Date::afficherDate()  //on crée un tableau de char avec les noms des mois. On affiche la date intégrale
{
    static char *nom[]= {"","Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};
    cout<<J<<" "<<nom[M]<<" "<<A<<endl;
}
