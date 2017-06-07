#ifndef CORBEILLEEDITEUR_H
#define CORBEILLEEDITEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDockWidget>

#include "fonction.h"
#include "corbeille.h"


/// Editeur de la corbeille (Organisation de la fenêtre d'affichage)
class CorbeilleEditeur : public QWidget{
    Q_OBJECT
private:
    QListWidget* list; /// Liste
    QVBoxLayout* layer; /// Organisation verticale des Widgets
    QScrollArea* scroller; ///Scroller pour parcourir la liste
    QPushButton* supp; /// Ensemble de 3 PushButton pour sélectionner l'action: Suppression, Restauration, Vider
    QPushButton* empty;
    QPushButton* restor;

public:
    CorbeilleEditeur(QWidget* parent=0); /// Constructeur avec argument par défaut QWidget *parent =0
    QListWidget* getList(){return list;} ///Accesseur
    QPushButton* getSuppButton(){ return supp; }
    QPushButton* getEmptyButton() { return empty; }
    QPushButton* getRestorButton() { return restor; }

public slots :
    void deleteNote(); //slot qui supprime la note selectionnee
    void emptyDustBin(); //slot qui vide la corbeille
    Note* restorNote(); //slot qui restaure la note dans le note manager
    void enablePushButons(); //slot qui active les buttons de la fenêtre
    void updateNotesManager(); //slot qui met a jour la fenetre notesmanager qd on restaure les notes
};

#endif // CORBEILLEEDITEUR_H

