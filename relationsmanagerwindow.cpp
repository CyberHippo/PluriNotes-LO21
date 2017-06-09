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
            item = new QListWidgetItem(temp,listRelations);
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
    QObject::connect(delRelation,SIGNAL(clicked()),this,SLOT(DeleteRelation()));
}

void relationsmanagerwindow::DeleteRelation(){
    if(!listRelations->currentItem() == 0){

        QListWidgetItem* selectedItem1 = listRelations->currentItem();
        QString temp = selectedItem1->text();
        QStringList listtemp = temp.split(" ");
        //qDebug() << listtemp[0];
        //qDebug() << listtemp[2];
        Note* n1 = NotesManager::getInstance().getNoteWithId(listtemp[0]);
        Note* n2 = NotesManager::getInstance().getNoteWithId(listtemp[2]);

        qDebug() << n1->getTitle();
        qDebug() << n2->getTitle();

        RelationsManager& rm = RelationsManager::getInstance();
        rm.deleteRelation(*n1, *n2);


    }
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de relations à supprimer"); msgBox.exec();}
}

