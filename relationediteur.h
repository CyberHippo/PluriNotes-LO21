#ifndef RELATIONEDITEUR_H
#define RELATIONEDITEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

#include "fonction.h"
#include "relation.h"

///Qwidget permettant de créer des relations, il s'affiche au milieu de l'application
class RelationEditeur : public QWidget{
    Q_OBJECT
private:
    QListWidget* listNotesLeft;
    QListWidget* listNotesRight;
    QVBoxLayout* layer;
    QScrollArea* scroller;
    QPushButton* add;
    QPushButton* addNotOriented;
    QPushButton* Bquit;
///Deux QListWidgets pour lister toutes les notes présentes dans notesManager, un bouton pour ajouter une relation, un autre bouton pour ajouter une relation non orientée ainsi qu'un bouton pour quitter l'éditeur.
public:
    RelationEditeur(QWidget* parent=0);
    QListWidget* getListLeft(){return listNotesLeft;}
    QListWidget* getListRight(){return listNotesRight;}
    QPushButton* getAddButton(){ return add; }
    QPushButton* getAddNotOrientedButton() { return addNotOriented; }
///Slots permettant de relier les boutons aux actions
public slots :
    void addRelation();
    void addRelationNotOriented();
    void updateRelationManager();
    void enablePushButons();
    void setEmptyCentralWidget();
};


#endif // RELATIONEDITEUR_H
