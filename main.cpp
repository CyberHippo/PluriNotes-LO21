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

    Article n1("1","Article", "test article");

    Audio n2("2", "Audio", "test audio", "link");

    Task n3("3", "Task", "act", "subj", date(5,10,2017) ,2);

    Video n4("4", "Video", "test video", "link");

    Image n5("5", "Image", "test image", "link");

    nm.addNote(&n1);
    nm.addNote(&n2);
    nm.addNote(&n3);
    nm.addNote(&n4);
    nm.addNote(&n5);

    //NotesManager::showNote(notes[1]);



    nm.showAll();



}
