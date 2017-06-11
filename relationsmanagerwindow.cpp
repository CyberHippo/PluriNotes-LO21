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
    ///Appel d'une instance de RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    ///On itère les relations
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        ///On itère les couples
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            ///On créée une QString temporaire composée de l'id du champ first du couple puis d'une flèche et ensuite l'id du champ second du couple
            temp = (*it2).getFirst().getId() + " -> " + (*it2).getSecond().getId();
            ///On ajoute un item dont le titre est cette Qstring temporaire à la liste des relations
            item = new QListWidgetItem(temp,listRelations);
        }
    }

    QWidget* multiWidget = new QWidget();
    ///Ajout d'un bouton "supprimer la relation"
    QPushButton* delRelation = new QPushButton("Supprimer la relation");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listRelations);
    layout->addWidget(delRelation);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    ///Connexions au slots
    QObject::connect(delRelation,SIGNAL(clicked()),this,SLOT(DeleteRelation()));
}

void relationsmanagerwindow::DeleteRelation(){
    if(!listRelations->currentItem() == 0){
        ///On récupère l'item courant
        QListWidgetItem* selectedItem1 = listRelations->currentItem();
        ///On récupère son texte
        QString temp = selectedItem1->text();
        ///On split ce texte à chaque espace
        QStringList listtemp = temp.split(" ");
        ///On récupère les note n1 et n2 grâce à leurs id qui correspondent à la permière et la troisième partie de la Qstringlist résultant du splitage.
        Note* n1 = NotesManager::getInstance().getNoteWithId(listtemp[0]);
        Note* n2 = NotesManager::getInstance().getNoteWithId(listtemp[2]);
        ///Appel d'une instance de RelationsManager
        RelationsManager& rm = RelationsManager::getInstance();
        ///Suppression de la relation entre n1 et n2
        rm.deleteRelation(*n1, *n2);
    }
    ///Si aucune relation n'a été séléctionnée, on affiche un message.
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de relations à supprimer"); msgBox.exec();}
}

