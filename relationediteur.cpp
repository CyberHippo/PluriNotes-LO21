#include "relation.h"
#include "relationediteur.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"

///Definition des slots de relation editeur

///Slot permettant d'ajouter une relation.
void RelationEditeur::addRelation(){
    ///On récupère la note n1 dans le QlistWidget listNotesLeft
    QListWidgetItem* selectedItem1 = listNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getInstance().getNoteWithTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getInstance().getNoteWithTitle(title2);
    ///Création d'une relation de n1 vers n2
    Relation* r = new Relation;
    (*r).addRelation(*n1,*n2);
    ///Insertion de la relation dans RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    rm.addRelation(r);
    ///MessageBox attestant du succès de l'ajout de la relation
    QMessageBox::information(this, "Succès", "La relation a bien été ajoutée");

}

///Slot permettant d'ajouter une relation non orientée.
void RelationEditeur::addRelationNotOriented(){
    ///On récupère la note n1 dans le QlistWidget listNotesLeft
    QListWidgetItem* selectedItem1 = listNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getInstance().getNoteWithTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getInstance().getNoteWithTitle(title2);
    ///Création d'une relation de n1 vers n2
    Relation* r1 = new Relation;
    (*r1).addRelation(*n1,*n2);
    ///Création d'une relation de n2 vers n1
    Relation* r2 = new Relation;
    (*r2).addRelation(*n2,*n1);
    ///Insertion des deux relations dans RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    rm.addRelation(r1);
    rm.addRelation(r2);
    ///MessageBox attestant du succès de l'ajout de la relation non orientée
    QMessageBox::information(this, "Succès", "La relation non orientée a bien été ajoutée");
}


///Slot permettant de rendre les boutons cliquables
void RelationEditeur::enablePushButons(){
    add->setEnabled(true);
    addNotOriented->setEnabled(true);
}


RelationEditeur::RelationEditeur(QWidget* parent){

    QGridLayout *layout = new QGridLayout;
    ///Premier QlistWidget : listNotesLeft
    listNotesLeft = new QListWidget();
    QListWidgetItem* item1;
    NotesManager& nm = NotesManager::getInstance();
    ///Remplissage de listNotesLeft
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item1 = new QListWidgetItem((*it)->getTitle(),listNotesLeft);
    }
    ///Second QlistWidget : listNotesRight
    listNotesRight = new QListWidget();
    QListWidgetItem* item2;
    ///Remplissage de listNotesRight
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item2 = new QListWidgetItem((*it)->getTitle(),listNotesRight);
    }
    layer = new QVBoxLayout();
    scroller = new QScrollArea();

    add = new QPushButton("Ajouter une relation");
    addNotOriented = new QPushButton("Ajouter une relation (NO)");
    Bquit = new QPushButton("Quitter");
    ///Connexion des boutons aux slots
    QObject::connect(add, SIGNAL(clicked()), this, SLOT(addRelation()));
    QObject::connect(add, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(addRelationNotOriented()));
    QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(setEmptyCentralWidget()));
    QObject::connect(Bquit, SIGNAL(clicked()), this, SLOT(close()));
    ///Ajout des boutons
    layout->addWidget(listNotesLeft, 0, 0);

    layout->addWidget(listNotesRight, 0, 2);

    layout->addWidget(add, 1, 1);

    layout->addWidget(addNotOriented, 2, 1);

    layout->addWidget(Bquit, 3, 1);

    setLayout(layout);

}

///Slot permettant de mettre à jour le widget relationsManager
void RelationEditeur::updateRelationManager(){
    MainWindow::getInstance().updateRelationManager();
}

///Slot permettant de mettre le Widget dans la partie centrale de l'application
void RelationEditeur::setEmptyCentralWidget(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}
