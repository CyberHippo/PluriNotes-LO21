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

    QDate d(15,12,2017);
    Article* n1 = new Article("1","Article", "test article \ref{1 tyhjkj    \ref}");
    Note* n2 = new Article("2", "Audio", "test audio");
    Note* n4 = new Audio("4", "t", "Audio \ref{1}, \ref{15}, \ref{4}", "subj");

    Corbeille& c = Corbeille::getInstance();
    c.addNote(n1);
    c.addNote(n2);

    Task* n3 = new Task("15","Task test", QDate(12,03,2017), QDate(13,03,2017), "subj",QDate(15,06,2017) , 10);

    nm.addNote(n1);
    nm.addNote(n2);
    nm.addNote(n3);
    nm.addNote(n4);

    RelationsManager& rm = RelationsManager::getInstance();

    MainWindow& mw = MainWindow::getInstance();
    mw.showNotesManager();
    mw.showTaskManager();
    mw.showRelationsManagerActive();
    mw.showArchivesManager();
    mw.show();


    return app.exec();
}
