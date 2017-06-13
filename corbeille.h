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

/// Classe permettant le stockage lorsqu'une note est supprimée. La note devient en attente d'une éventuelle restauration
class Corbeille{
private :
    /// vector d'objet pointeur sur Note
    vector<Note*> dustBin;
    /// Constructeur
    Corbeille();
    /// Constructeur de recopie
    Corbeille(const Corbeille& c);
     ///Surcharge de l'opérateur =
    Corbeille& operator=(const Corbeille& c);
    ///Destructeur
    ~Corbeille();

    ///static Corbeille *instance: Implantation du singleton
    struct Handler2{
        Corbeille* instance;
        Handler2() : instance(0){}
        ~Handler2(){if(instance) delete instance; instance = 0;}
    };
    static Handler2 handler2;

public :
    static Corbeille& getInstance();
    static void libererInstance();
    ///Permet de savoir le nombre d'éléments dans la corbeille
    int getDustBinSize() const {return dustBin.size();}
    /// Restaurer une note
    void RestoreNote(Note* n);
    /// Trouver une note par son titre
    Note* getNoteWithTitle(QString title);
    ///Trouver une note par son ID
    Note* getNoteWithId(QString id);
    /// Trouver une note par sa position dans la corbeille
    Note* getNoteWithPosition(unsigned int position);
    ///Suppression d'une note de la corbeille
    void deleteNote(Note* n);
    ///Ajout d'une note dans la corbeille
    void addNote(Note*n);
    ///Retourne la position d'une note dans le vecteur dustbin
    unsigned int getNotePosition(Note*n);
    ///Vide le vecteur dustbin
    void emptyDustBin();
};



#endif // CORBEILLE_H
