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

public:
    RelationEditeur(QWidget* parent=0);
    QListWidget* getListLeft(){return listNotesLeft;}
    QListWidget* getListRight(){return listNotesRight;}
    QPushButton* getAddButton(){ return add; }
    QPushButton* getAddNotOrientedButton() { return addNotOriented; }

public slots :
    void addRelation(); //slot qui supprime la note selectionnee
    void addRelationNotOriented(); //slot qui vide la corbeille
    void enablePushButons(); //slot qui active les buttons de la fenêtre
    //void quitEditor();// ferme le widget
};


#endif // RELATIONEDITEUR_H