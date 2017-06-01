#include <iostream>
#include <fstream>
#include "fonction.h"
#include "relation.h"

using namespace std;

int main()
{

    /// Test des notes
    /*
    NotesManager& nm = NotesManager::getInstance(); // Ref vers l'instance unique de NotesManager

    Article n1("1","Article", "test article");

    Audio n2("2", "Audio", "test audio", "link");

    Task n3("3", "Task", "subj", date(5,10,2017) ,2);

    n3.addAction("Action 1");
    n3.addAction("Action 2");
    n3.addAction("Action 3");

    Video n4("4", "Video", "test video", "link");

    Image n5("5", "Image", "test image", "link");

    nm.addNote(&n1);
    nm.addNote(&n2);
    nm.addNote(&n3);
    nm.addNote(&n4);
    nm.addNote(&n5);
    nm.editNote("2");
    //nm.editNote("2");
    //nm.editNote("2");
    //nm.editNote("2");
    nm.showOldNotes("2");
    cout << "\n\n\n\n";
    nm.showAll();


    cout << "______________________\n";
    cout << "______________________\n";
    cout << "______________________\n";
    cout << "______________________\n\n\n";
    cout << "Restauration de la note:\n";
    nm.restaurerNote("2", "Audio");
    nm.showAll();
    cout << "\n\n\n\n";
    nm.showOldNotes("2");
    //NotesManager::showNote(notes[1]);

    cout << "\n\n\n\n";
    */

    /// Test des relations
    /*
    Article n1("102392","Article", "test article");

    Audio n2("43422", "Audio", "test audio", "link");

    Video n4("54543", "Video", "test video", "link");

    Relation r;

    r.addRelation(n1,n2);

    Couple c2(n1,n4);

    c2.setLabel("Label test");

    cout << c2.getLabel() << "\n\n";

    r.addRelation(c2);

    r.addRelationNonOrientee(n2,n4);

    r.getCouples();

    cout << "\n\n---- Ascend N4 ----\n\n";

    r.showAscendants(n4);

    cout << "\n\n---- Descend N1 ----\n\n";

    r.showDescendants(n1);
    */

    /// Test du searchiterator
    /*
    cout << "\n\n--------------------\n\n";

    NotesManager& nm = NotesManager::getInstance();

    nm.addNote(&n1);
    nm.addNote(&n2);
    nm.addNote(&n4);

    NotesManager::SearchIterator s = NotesManager::SearchIterator("ça sert à R");

    Article* res = s.NotesManager::SearchIterator::SearchTextArticle("test");

    res->print();
    */

    /// Test du searchiterator

    NotesManager& nm = NotesManager::getInstance();

    Article n1("12","Article1", "\ref{18} test article1 \ref{15}");
    Article n2("15","Article2", "test article2 ");
    Article n3("18","Article2", "test article3 ");

    nm.addNote(&n1);
    nm.addNote(&n3);
    nm.addNote(&n2);

    nm.showAll();

    nm.deleteNote("15");

    nm.showAll();


    /*
    RelationsManager rm;

    Relation* res;

    res = rm.RelationsManager::checkReference(n1);

    res->getCouples();*/

    }