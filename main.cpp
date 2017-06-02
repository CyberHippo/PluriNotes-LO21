#include <QDebug>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <fstream>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>



#include "fonction.h"
#include "notemanager.h"
#include "relation.h"
#include "notefactory.h"
#include "noteediteur.h"
#include "fenetres.h"
#include "corbeille.h"
#include "corbeilleediteur.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


///-------MAIN MINH--------///



/*    Principale fenetre;
    fenetre.show();
//            QFile file(":/default.txt");
//            file.open(QIODevice::ReadOnly);

//            TreeModel model(file.readAll());

//            file.close();

//            QTreeView view;
//            view.setModel(&model);
//            view.setWindowTitle(QObject::tr("Simple Tree Model"));
//            view.show();

*/

    ///----------MAIN ERIC---------///




    ///Test des factory
    QString t = "test";
    QString type = "task";
    QString t2 = "test2";
    QString type2 = "task";
    NotesManager& nm = NotesManager::getInstance();
    nm.getNewNote(t, type);
    //nm.getNewNote(t2, type2);
    //nm.showAll();
    QDate d(15,12,2017);

    Note* n1 = new Article("1","Article", "test article");

    Note* n2 = new Audio("2", "Audio", "test audio", "link");

    Note* n3 = new Task("3", "Task", "subj",d,2);

    Corbeille& c = Corbeille::getInstance();
    c.addNote(n1);
    c.addNote(n2);
    c.addNote(n3);

    CorbeilleEditeur ce;
    ce.show();

    //nm.addNote(&n1);
    //nm.addNote(&n2);
    //nm.addNote(&n3);
    //nm.addNote(&n4);
    //nm.addNote(&n5);

    nm.setFilename("TEMP.xml");
    nm.load();
    qDebug() << "\n";
    nm.showAll();

    qDebug() << "______________________\n";

    qDebug() << "Debut save\n";
    try
    {
        nm.saveAll(); //
    }
    catch ( NotesException& e )
    {
        qDebug() << e.getInfo();
    }

    qDebug() << "fin save\n";

    return app.exec();

    ///Test du delete
    /*NotesManager& nm = NotesManager::getInstance(); // Ref vers l'instance unique de NotesManager

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
    nm.showAll();
    nm.deleteNote("5");
    nm.deleteNote("1");
    nm.deleteNote("3");
    nm.showAll();*/

    /// Test des relations
    /*
    //Article n1("102392","Article", "test article");

    //Audio n2("43422", "Audio", "test audio", "link");

    //Video n4("54543", "Video", "test video", "link");

    Relation r;

    r.addRelation(n1,n2);

    Couple c2(n1,n4);

    c2.setLabel("Label test");

    qDebug() << c2.getLabel() << "\n\n";

    r.addRelation(c2);

    r.addRelationNonOrientee(n2,n4);

    r.getCouples();

    //cout << "\n\n---- Ascend N4 ----\n\n";

    r.showAscendants(n4);

    //cout << "\n\n---- Descend N1 ----\n\n";

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
    /*
    NotesManager& nm = NotesManager::getInstance();

    Article n1("12","Article1", "\ref{18} test article1 \ref{15}");
    Article n2("15","Article2", "test article2 ");
    Article n3("18","Article2", "test article3 ");

    nm.addNote(&n1);
    nm.addNote(&n3);
    nm.addNote(&n2);

    RelationsManager rm;

    Relation* res;

    res = rm.RelationsManager::checkReference(n1);

    res->getCouples();*/
    //return app.exec();
}
