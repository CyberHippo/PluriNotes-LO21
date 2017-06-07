#include "relation.h"
#include "relationediteur.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"

//Definition des slots de relation editeur
void RelationEditeur::addRelation(){

    QListWidgetItem* selectedItem1 = listNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getInstance().getNoteWithTitle(title1);

    QListWidgetItem* selectedItem2 = listNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getInstance().getNoteWithTitle(title2);

    Relation* r = new Relation;
    (*r).addRelation(*n1,*n2);

    RelationsManager& rm = RelationsManager::getInstance();
    rm.addRelation(r);//Ceci est un test
    QMessageBox::information(this, "Succès", "La relation a bien été ajoutée");

}


void RelationEditeur::addRelationNotOriented(){

    QListWidgetItem* selectedItem1 = listNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getInstance().getNoteWithTitle(title1);

    QListWidgetItem* selectedItem2 = listNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getInstance().getNoteWithTitle(title2);

    Relation* r = new Relation;
    Couple*c = new Couple(*n1,*n2);
    (*r).addRelationNonOrientee(*c);

    RelationsManager& rm = RelationsManager::getInstance();
    rm.addRelation(r);//Ceci est un test
    QMessageBox::information(this, "Succès", "La relation non orientée a bien été ajoutée");
}


void RelationEditeur::enablePushButons(){
    add->setEnabled(true);
    addNotOriented->setEnabled(true);
}



RelationEditeur::RelationEditeur(QWidget* parent){

    QGridLayout *layout = new QGridLayout;

    listNotesLeft = new QListWidget();
    QListWidgetItem* item1;
    NotesManager& nm = NotesManager::getInstance();

    QDate d(15,12,2017);
    Note* n1 = new Article("1","Article", "test article");
    Note* n2 = new Audio("2", "Audio", "test audio", "link");
    Note* n3 = new Task("3", "Task", "subj",d,2);
    nm.addNote(n1);
    nm.addNote(n2);
    nm.addNote(n3);

    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item1 = new QListWidgetItem((*it)->getTitle(),listNotesLeft);
    }

    listNotesRight = new QListWidget();
    QListWidgetItem* item2;
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item2 = new QListWidgetItem((*it)->getTitle(),listNotesRight);
    }
    layer = new QVBoxLayout();
    scroller = new QScrollArea();

    add = new QPushButton("Ajouter une relation");
    addNotOriented = new QPushButton("Ajouter une relation (NO)");
    Bquit = new QPushButton("Quitter");

    QObject::connect(add, SIGNAL(clicked()), this, SLOT(addRelation()));
    QObject::connect(add, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(addRelationNotOriented()));
    QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(close()));

    layout->addWidget(listNotesLeft, 0, 0);

    layout->addWidget(listNotesRight, 0, 2);

    layout->addWidget(add, 1, 1);

    layout->addWidget(addNotOriented, 2, 1);

    layout->addWidget(Bquit, 3, 1);

    setLayout(layout);

}

void RelationEditeur::updateRelationManager(){
    MainWindow::getInstance().updateRelationManager();
}

void RelationEditeur::setEmptyCentralWidget(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}
