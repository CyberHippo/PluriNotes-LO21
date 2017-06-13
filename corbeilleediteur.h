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
     /// Liste
    QListWidget* list;
    /// Organisation verticale des Widgets
    QVBoxLayout* layer;
    ///Scroller pour parcourir la liste
    QScrollArea* scroller;
    /// PushButton pour l'action de suppression
    QPushButton* supp;
    /// PushButton pour l'action de vider
    QPushButton* empty;
    /// PushButton pour l'action de restaurer
    QPushButton* restor;

public:
    /// Constructeur avec argument par défaut QWidget *parent =0
    CorbeilleEditeur(QWidget* parent=0);
    ///Accesseur pour la liste
    QListWidget* getList(){return list;}
    ///Accesseur retournant un pointeur sur le QPushButton suppression
    QPushButton* getSuppButton(){ return supp; }
    ///Accesseur retournant un pointeur sur le QPushButton Vider
    QPushButton* getEmptyButton() { return empty; }
    ///Accesseur retournant un pointeur sur le QPushButton restauration
    QPushButton* getRestorButton() { return restor; }

public slots :
    ///slot qui supprime la note selectionnee
    void deleteNote();
    ///slot qui vide la corbeille
    void emptyDustBin();
    ///slot qui restaure la note dans le note manager
    Note* restorNote();
     ///slot qui active les buttons de la fenêtre
    void enablePushButons();
    ///slot qui met a jour la fenetre notesmanager qd on restaure les notes
    void updateNotesManager();
};

#endif // CORBEILLEEDITEUR_H
