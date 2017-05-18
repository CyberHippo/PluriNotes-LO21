#include <iostream>
#include <fstream>
#include "fonction.h"

using namespace std;

int main()
{

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
    nm.editNote("2");
    nm.editNote("2");
    nm.editNote("2");
    nm.editNote("2");
    nm.showOldNotes("2");
    cout << "\n\n\n\n";
    nm.showAll();


    cout << "______________________\n";
    cout << "______________________\n";
    cout << "______________________\n";
    cout << "______________________\n";
    cout << "Restauration de la note:\n";
    nm.restaurerNote("2", "Audio");
    nm.showAll();
    cout << "\n\n\n\n";
    nm.showOldNotes("2");
    //NotesManager::showNote(notes[1]);

    cout << "\n\n\n\n";





}
