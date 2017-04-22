#include <iostream>
#include <fstream>
#include "fonction.h"

using namespace std;

int main()
{
    string idArticle1 = "123\n";
    string titreArticle1 = "\nMonaco se qualifie pour les demis-finale de la Champions League!\n";
    string textArticle1 = "\nL'AS Monaco a battu le Borussia Dortmund ce mercredi en quarts de finale retour de la Ligue des champions (3-1, 6-3 sur l'ensemble des deux matches) grace a des buts Mbappe, Falcao et Germain, et disputera les demi-finales, une premiere pour un club francais depuis 2010.\n";


    NotesManager& nm = NotesManager::getInstance(); // Ref vers l'instance unique de NotesManager

    nm.getNewArticle(idArticle1); // La méthode getNewArticle crée un article avec l'id
    nm.getArticle(idArticle1).setTitle(titreArticle1); //on ajoute un titre à l'article
    nm.getArticle(idArticle1).setText(textArticle1); //on ajoute un text à l'article
    nm.getArticle(idArticle1).print(); //on affiche l'article avec la méthode print
}
