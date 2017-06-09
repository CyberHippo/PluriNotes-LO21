#include "ascendanddescendwindow.h"
#include "relationsmanagerwindow.h"
#include "notesmanagerwindow.h"
#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"



AscendAndDescendWindow::AscendAndDescendWindow(Note* n, QString title, QWidget* parent) : QDockWidget(title, parent){
    ///Création d'un QlistWidget pour répertorier les notes ascendantes et descendantes
    listRelations = new QListWidget();
    QListWidgetItem* item;
    QString temp;
    RelationsManager& rm = RelationsManager::getInstance();
    ///Nouvel item pour mentionner le début des ascendants
    item = new QListWidgetItem("(Ascendants)",listRelations);
    ///Itérations des relations
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        ///Itérations des couples de chaque relation
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            ///Si la note passée en argument correspond au champ second, on ajoute l'id du champ first dans le QListWidget
            if((*it2).getSecond() == *n){item = new QListWidgetItem((*it2).getFirst().getId(),listRelations);}
        }
    }
    ///Item pour séparer les ascendants des descendants
    item = new QListWidgetItem("-------------",listRelations);
    ///Nouvel item pour mentionner le début des descendants
    item = new QListWidgetItem("(Descendants)",listRelations);
    ///Iterations des relations
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        ///Iterations des couples de chaque relation
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            ///Si la note passée en argument correspond au champ first, on ajoute l'id du champ second dans le QListWidget
            if((*it2).getFirst() == *n){item = new QListWidgetItem((*it2).getSecond().getId(),listRelations);}
        }
    }
    QWidget* multiWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listRelations);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);
}

