#ifndef CORBEILLEEDITEUR_H
#define CORBEILLEEDITEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

#include "fonction.h"
#include "corbeille.h"

class CorbeilleEditeur : public QWidget{
    Q_OBJECT
private:
    QListWidget* list;
    QVBoxLayout* layer;
    QScrollArea* scroller;
    QPushButton* supp;
    QPushButton* empty;
    QPushButton* restor;

public:
    CorbeilleEditeur(QWidget* parent=0);
    QListWidget* getList(){return list;}
    QPushButton* getSuppButton(){ return supp; }
    QPushButton* getEmptyButton() { return empty; }
    QPushButton* getRestorButton() { return restor; }

public slots :
    void deleteNote(); //slot qui supprime la note selectionnee
    void emptyDustBin(); //slot qui vide la corbeille
    Note* restorNote(); //slot qui restaure la note dans le note manager
    void enablePushButons(); //slot qui active les buttons de la fenêtre
};

#endif // CORBEILLEEDITEUR_H
