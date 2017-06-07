#include "relationsmanagerwindow.h"
#include "notesmanagerwindow.h"
#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"


relationsmanagerwindow::relationsmanagerwindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listRelations = new QListWidget();
    QListWidgetItem* item;
    QString temp;
    RelationsManager& rm = RelationsManager::getInstance();
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            temp = (*it2).getFirst().getId() + " -> " + (*it2).getSecond().getId();
            item= new QListWidgetItem(temp,listRelations);
        }
    }

    QWidget* multiWidget = new QWidget();
    QPushButton* delRelation = new QPushButton("Supprimer la relation");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listRelations);
    layout->addWidget(delRelation);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    //QObject::connect(delRelation,SIGNAL(clicked()),this,SLOT(DeleteRelation()));
}
/*
void NotesManagerWindow::afficherNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    else {throw NotesException("Couldn't show the note..");}
}
*/
