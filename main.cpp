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
#include "corbeille.h"
#include "corbeilleediteur.h"
#include "mainwindow.h"
#include "notesmanagerwindow.h"
#include "relationediteur.h"
#include "relationsmanagerwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NotesManager& nm = NotesManager::getInstance();

    /*
    QDate d(15,12,2017);
    Article* n1 = new Article("1","Article", "test article ref{2}");
    Image* n2 = new Image("2", "Audio ref{1}", "test audio ref{4}","image filename");
    Audio* n4 = new Audio("4", "t ref{2}", "Audio ref{1}, , \ref{41}", "subj ref{1}");

    /*Corbeille& c = Corbeille::getInstance();
    c.addNote(n1);
    c.addNote(n2);*/

    /*Task* n3 = new Task("15","Task test", QDate(12,03,2017), QDate(13,03,2017), "subj",QDate(15,06,2017) , 10);

    nm.addNote(n1);
    nm.addNote(n2);
    nm.addNote(n3);
    nm.addNote(n4);*/
/*
    RelationsManager& rm = RelationsManager::getInstance();

    rm.setFilename("TEMP2.xml");
/*
    rm.load();
    */
    /*

    rm.checkReferenceInText(n1,n1->getText());

    qDebug() << "----";

    rm.checkReferenceInText(n2,n2->getTitle());

    qDebug() << "----";

    rm.checkReferenceInText(n2,n2->getDescription());

    qDebug() << "----";

    rm.checkReferenceInText(n4,n4->getTitle());

    qDebug() << "----";

    rm.checkReferenceInText(n4,n4->getDescription());

    Relation rtest;

    rtest.addRelation(*n4,*n2);

    qDebug() << rm.isAlreadyPresent(rtest);


    Relation rtest2;

    rtest2.addRelation(*n4,*n4);

    qDebug() << rm.isAlreadyPresent(rtest2);
    */



    //rm.saveAll();


    MainWindow& mw = MainWindow::getInstance();
    mw.showNotesManager();
    mw.showTaskManager();
    mw.showRelationsManagerActive();
    mw.showArchivesManager();
    mw.show();


    return app.exec();
}
