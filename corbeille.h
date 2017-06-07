#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "fonction.h"

///Stockage lorsqu'une note est supprimée. La note devient en attente d'une éventuelle restauration
class Corbeille{

private :
    QList<Note*> dustBin;    /// Qlist d'objet pointeur sur Note, associé à la corbeille.
    Corbeille(); /// Constructeur
    Corbeille(const Corbeille& c); /// Constructeur de recopie
    Corbeille& operator=(const Corbeille& c);    ///Surcharge de l'opérateur =
    ~Corbeille();

    ///static Corbeille *instance;
    struct Handler2{
        Corbeille* instance;
        Handler2() : instance(0){}
        ~Handler2(){if(instance) delete instance; instance = 0;}
    };
    static Handler2 handler2;

public :
    static Corbeille& getInstance();
    static void libererInstance();
    int getDustBinSize() const {return dustBin.size();} ///Afin de savoir le nombre d'éléments dans la corbeille
    void RestoreNote(Note* n);   /// Restaurer une note
    Note* getNoteWithTitle(QString title); /// Trouver une note par son titre
    Note* getNoteWithId(QString id);/// Trouver une note par son id
    Note* getNoteWithPosition(unsigned int position); /// Trouver une note par sa position dans la corbeille
    void deleteNote(Note* n);
    void addNote(Note*n);
    unsigned int getNotePosition(Note*n);
    void emptyDustBin(){dustBin.clear();}
    void callEditeur();
};



#endif // CORBEILLE_H

