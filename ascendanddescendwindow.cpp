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
    listRelations = new QListWidget();
    QListWidgetItem* item;
    QString temp;
    RelationsManager& rm = RelationsManager::getInstance();
    item = new QListWidgetItem("(Ascendants)",listRelations);
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            if((*it2).getSecond() == *n){item = new QListWidgetItem((*it2).getFirst().getId(),listRelations);}
        }
    }
    item = new QListWidgetItem("-------------",listRelations);
    item = new QListWidgetItem("(Descendants)",listRelations);
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
             if((*it2).getFirst() == *n){item = new QListWidgetItem((*it2).getSecond().getId(),listRelations);}
        }
    }
    QWidget* multiWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listRelations);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);
}

